// $Id$

// ============================================================================
//
// = LIBRARY
//    tests
//
// = FILENAME
//    Thread_Pool_Reactor_Test.cpp
//
// = DESCRIPTION
//      This program is a torture test of thread poll reactors.  It
//      starts by spawning several server threads waiting to handle
//      events.  Several other client threads are spawned right after
//      to initiate connections to server threads.  Each connection
//      adds a new Svc_Handler into the TP_Reactor and sends out
//      several "requests" to the server thread.  After the connection
//      is closed, the Svc_Handler is removed from the TP_Reactor.
//      Each message is treated as a separate request by the server so
//      two consecutive requests might be serviced by two different
//      threads.
//
//      Usage: Thread_Pool_Reactor_Test [-r <hostname:port#>]
//                [-s <server thr#>] [-c <client thr#>] [-d <delay>]
//                [-i <client conn attempt#>] [-n <client request# per conn>]
//
//      Default value:
//          <hostname:port#>:       ACE_DEFAULT_RENDEZVOUS
//          <server thr#>:          ACE_MAX_THREADS
//          <client thr#>:          ACE_MAX_ITERATIONS
//          <client conn attempt#>: ACE_MAX_ITERATIONS
//          <client req# per conn>: ACE_MAX_THREADS
//          <delay>:                50 usec
//
// = AUTHOR
//      Irfan Pyarali <irfan@cs.wustl.edu> and
//      Nanbor Wang <nanbor@cs.wustl.edu>
//
// ============================================================================

#include "tests/test_config.h"
#include "ace/Get_Opt.h"
#include "ace/SOCK_Connector.h"
#include "ace/SOCK_Acceptor.h"
#include "ace/Acceptor.h"
#include "ace/Thread_Manager.h"
#include "ace/TP_Reactor.h"

ACE_RCSID(tests, Atomic_Op_Test, "$Id$")

#if defined (ACE_HAS_THREADS)

#include "tests/Thread_Pool_Reactor_Test.h"
typedef ACE_Strategy_Acceptor <Request_Handler, ACE_SOCK_ACCEPTOR> ACCEPTOR;

// Accepting end point.  This is actually "localhost:10010", but some
// platform couldn't resolve the name so we use the IP address
// directly here.
static const ASYS_TCHAR *rendezvous = ASYS_TEXT ("127.0.0.1:10010");

// Total number of server threads.
static size_t svr_thrno = ACE_MAX_THREADS;

#if defined (CHORUS) // Add platforms that can't handle too many
                     // connection simultaneously here.
#define ACE_LOAD_FACTOR /2
#else
#define ACE_LOAD_FACTOR
#endif

// Total number of client threads.
static size_t cli_thrno = ACE_MAX_THREADS ACE_LOAD_FACTOR;

// Total connection attemps of a client thread.
static size_t cli_conn_no = ACE_MAX_ITERATIONS ACE_LOAD_FACTOR;

// Total requests a client thread sends.
static size_t cli_req_no = ACE_MAX_THREADS ACE_LOAD_FACTOR;

// Delay before a thread sending the next request (in msec.)
static int req_delay = 50;

static void
parse_arg (int argc, ASYS_TCHAR *argv[])
{
  ACE_Get_Opt getopt (argc, argv, ASYS_TEXT ("r:s:c:d:i:n:"));

  int c;

  while ((c = getopt ()) != -1)
    {
      switch (c)
        {
        case 'r':                   // hostname:port
          rendezvous = getopt.optarg;
          break;
        case 's':
          svr_thrno = ACE_OS::atoi (getopt.optarg);
          break;
        case 'c':
          cli_thrno = ACE_OS::atoi (getopt.optarg);
          break;
        case 'd':
          req_delay = ACE_OS::atoi (getopt.optarg);
          break;
        case 'i':
          cli_conn_no = ACE_OS::atoi (getopt.optarg);
          break;
        case 'n':
          cli_req_no = ACE_OS::atoi (getopt.optarg);
          break;
        default:
          ACE_ERROR ((LM_ERROR,
                      ASYS_TEXT ("Usage: Thread_Pool_Reactor_Test [-r <hostname:port#>]")
                      ASYS_TEXT ("\t[-s <server thr#>] [-c <client thr#>] [-d <delay>]")
                      ASYS_TEXT ("\t[-i <client conn attempt#>]")
                      ASYS_TEXT ("[-n <client request# per conn>]\n")));
          break;
        }
    }
}

Request_Handler::Request_Handler (ACE_Thread_Manager *thr_mgr)
  : ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH> (thr_mgr),
    nr_msgs_rcvd_(0)
{
  // Make sure we use TP_Reactor with this class (that's the whole
  // point, right?)
  this->reactor (ACE_Reactor::instance ());
}

int
Request_Handler::handle_input (ACE_HANDLE fd)
{
  ASYS_TCHAR buffer[BUFSIZ];
  ASYS_TCHAR len = 0;
  ssize_t result = this->peer ().recv (&len,
                                       sizeof (ASYS_TCHAR));

  if (result > 0
      && this->peer ().recv_n (buffer, len) == len)
    {
      ++this->nr_msgs_rcvd_;

      ACE_DEBUG ((LM_DEBUG,
                  ASYS_TEXT ("(%t) svr input; fd: 0x%x; input: %s\n"),
                  fd,
                  buffer));
      if (ACE_OS::strcmp (buffer,
                          ASYS_TEXT ("shutdown")) == 0)
          ACE_Reactor::end_event_loop ();
      return 0;
    }
  else
    ACE_DEBUG ((LM_DEBUG,
                ASYS_TEXT ("(%t) Request_Handler: end handle input (0x%x)\n"),
                fd));
  return -1;
}

int
Request_Handler::handle_close (ACE_HANDLE fd, ACE_Reactor_Mask)
{
  ACE_DEBUG ((LM_DEBUG,
              ASYS_TEXT ("(%t) svr close; fd: 0x%x, rcvd %d msgs\n"),
              fd,
              this->nr_msgs_rcvd_));
  if (this->nr_msgs_rcvd_ != cli_req_no)
    ACE_ERROR((LM_ERROR,
               ASYS_TEXT ("(%t) Expected %d messages; got %d\n"),
               cli_req_no,
               this->nr_msgs_rcvd_));
  this->destroy ();
  return 0;
}

static void *
svr_worker (void *)
{
  // Server thread function.

  while (!ACE_Reactor::event_loop_done ())
    {
      ACE_DEBUG ((LM_DEBUG,
                  ASYS_TEXT ("(%t) handling events ....\n")));

      if (ACE_Reactor::instance ()->handle_events () == -1)
        ACE_ERROR ((LM_ERROR,
                    ASYS_TEXT ("(%t) %p\n"),
                    ASYS_TEXT ("Error handling events")));
    }

  ACE_DEBUG ((LM_DEBUG,
              ASYS_TEXT ("(%t) I am done handling events. Bye, bye\n")));
  return 0;
}

static void *
cli_worker (void *arg)
{
  // Client thread function.
  ACE_INET_Addr addr (rendezvous);
  ACE_SOCK_Stream stream;
  ACE_SOCK_Connector connect;
  ACE_Time_Value delay (0, req_delay);
  size_t len = * ACE_reinterpret_cast (ASYS_TCHAR *, arg);

  for (size_t i = 0 ; i < cli_conn_no; i++)
    {
      if (connect.connect (stream, addr) < 0)
        {
          ACE_ERROR ((LM_ERROR,
                      ASYS_TEXT ("(%t) %p\n"),
                      ASYS_TEXT ("connect")));
          continue;
        }

      for (size_t j = 0; j < cli_req_no; j++)
        {
          ACE_DEBUG ((LM_DEBUG,
                      ASYS_TEXT ("(%t) conn_worker handle 0x%x, req %d\n"),
                      stream.get_handle (),
                      j+1));
          if (stream.send_n (arg,
                             len + sizeof (ASYS_TCHAR)) == -1)
            {
              ACE_ERROR ((LM_ERROR,
                          ASYS_TEXT ("(%t) %p\n"),
                          ASYS_TEXT ("send_n")));
              continue;
            }
          ACE_OS::sleep (delay);
        }

      stream.close ();
    }

  return 0;
}

static void *
worker (void *)
{
  ACE_OS::sleep (3);
  const ASYS_TCHAR *msg = ASYS_TEXT ("Message from Connection worker");
  ASYS_TCHAR buf [BUFSIZ];
  buf[0] = (ACE_OS::strlen (msg) + 1) * sizeof (ASYS_TCHAR);
  ACE_OS::strcpy (&buf[1], msg);

  ACE_INET_Addr addr (rendezvous);

  ACE_DEBUG((LM_DEBUG,
             ASYS_TEXT ("(%t) Spawning %d client threads...\n"),
             cli_thrno));
  int grp = ACE_Thread_Manager::instance ()->spawn_n (cli_thrno,
                                                      &cli_worker,
                                                      buf);
  ACE_ASSERT (grp != -1);

  ACE_Thread_Manager::instance ()->wait_grp (grp);

  ACE_DEBUG ((LM_DEBUG,
              ASYS_TEXT ("(%t) Client threads done; shutting down...\n")));
  ACE_SOCK_Stream stream;
  ACE_SOCK_Connector connect;

  if (connect.connect (stream, addr) == -1)
    ACE_ERROR ((LM_ERROR,
                ASYS_TEXT ("(%t) %p Error while connecting\n"),
                ASYS_TEXT ("connect")));

  const char *sbuf = "\011shutdown";

  ACE_DEBUG ((LM_DEBUG,
              ASYS_TEXT ("shutdown stream handle = %x\n"),
              stream.get_handle ()));

  if (stream.send_n (sbuf, ACE_OS::strlen (sbuf) + 1) == -1)
    ACE_ERROR ((LM_ERROR,
                ASYS_TEXT ("(%t) %p\n"),
                ASYS_TEXT ("send_n")));

  stream.close ();

  return 0;
}

int
main (int argc, ASYS_TCHAR *argv[])
{
  ACE_START_TEST (ASYS_TEXT ("Thread_Pool_Reactor_Test"));
  parse_arg (argc, argv);

  // Changed the default
  ACE_TP_Reactor sr;
  ACE_Reactor new_reactor (&sr);
  ACE_Reactor::instance (&new_reactor);

  ACCEPTOR acceptor;
  ACE_INET_Addr accept_addr (rendezvous);

  if (acceptor.open (accept_addr) == -1)
    ACE_ERROR_RETURN ((LM_ERROR,
                       ASYS_TEXT ("%p\n"),
                       ASYS_TEXT ("open")),
                      1);

  ACE_DEBUG((LM_DEBUG,
             ASYS_TEXT ("(%t) Spawning %d server threads...\n"),
             svr_thrno));
  ACE_Thread_Manager::instance ()->spawn_n (svr_thrno,
                                            svr_worker);
  ACE_Thread_Manager::instance ()->spawn (worker);

  ACE_Thread_Manager::instance ()->wait ();

  ACE_END_TEST;
  return 0;
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)
template class ACE_Accept_Strategy<Request_Handler, ACE_SOCK_ACCEPTOR>;
template class ACE_Concurrency_Strategy<Request_Handler>;
template class ACE_Creation_Strategy<Request_Handler>;
template class ACE_Scheduling_Strategy<Request_Handler>;
template class ACE_Acceptor<Request_Handler, ACE_SOCK_ACCEPTOR>;
template class ACE_Strategy_Acceptor<Request_Handler, ACE_SOCK_ACCEPTOR>;
template class ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>;
#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)
#pragma instantiate  ACE_Accept_Strategy<Request_Handler, ACE_SOCK_ACCEPTOR>
#pragma instantiate  ACE_Concurrency_Strategy<Request_Handler>
#pragma instantiate  ACE_Creation_Strategy<Request_Handler>
#pragma instantiate  ACE_Scheduling_Strategy<Request_Handler>
#pragma instantiate  ACE_Acceptor<Request_Handler, ACE_SOCK_ACCEPTOR>
#pragma instantiate  ACE_Strategy_Acceptor<Request_Handler, ACE_SOCK_ACCEPTOR>
#pragma instantiate  ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_MT_SYNCH>
#endif /* ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */

#else
int
main (int, ASYS_TCHAR *[])
{
  ACE_START_TEST (ASYS_TEXT ("Thread_Pool_Reactor_Test"));

  ACE_ERROR ((LM_INFO,
              ASYS_TEXT ("threads not supported on this platform\n")));

  ACE_END_TEST;
  return 0;
}
#endif /* ACE_HAS_THREADS */
