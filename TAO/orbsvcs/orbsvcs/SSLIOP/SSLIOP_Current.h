// -*- C++ -*-

// ===================================================================
/**
 *  @file   SSLIOP_Current.h
 *
 *  $Id$
 *
 *  @author Ossama Othman <ossama@uci.edu>
 */
// ===================================================================

#ifndef TAO_SSLIOP_CURRENT_H
#define TAO_SSLIOP_CURRENT_H

#include "ace/pre.h"

#include "SSLIOP_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "SSLIOP_Current_Impl.h"

#include "orbsvcs/SSLIOPC.h"
#include "tao/ORB_Core.h"

// This is to remove "inherits via dominance" warnings from MSVC.
// MSVC is being a little too paranoid.
#if defined(_MSC_VER)
#if (_MSC_VER >= 1200)
#pragma warning(push)
#endif /* _MSC_VER >= 1200 */
#pragma warning(disable:4250)
#endif /* _MSC_VER */


class TAO_SSLIOP_Current;
class TAO_SSLIOP_Current_var;
typedef TAO_SSLIOP_Current *TAO_SSLIOP_Current_ptr;


/**
 * @class TAO_SSLIOP_Current
 *
 * @brief Implementation of the TAO SSLIOP::Current extension.
 *
 * This object can be used to obtain SSL session related information
 * about the current execution context.  For example, SSL peer
 * certificate chains for the current request can be obtained from
 * this object.
 */
class TAO_SSLIOP_Export TAO_SSLIOP_Current
  : public SSLIOP::Current,
    public TAO_Local_RefCounted_Object
{
public:

  /// Constructor.
  TAO_SSLIOP_Current (TAO_ORB_Core *orb_core);

  /// Return the peer certificate associated with the current
  /// request.
  virtual SSLIOP::ASN_1_Cert * get_peer_certificate (
      ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     SSLIOP::Current::NoContext));

  /// Return the certificate chain associated with the current
  /// execution context.  If no SSL session is being used for the
  /// request or upcall, then the NoContext exception is raised.
  ///
  /// On the client side, the chain does include the peer (server)
  /// certficate.  However, the certificate chain on the server side
  /// does NOT contain the peer (client) certificate.
  virtual SSLIOP::SSL_Cert * get_peer_certificate_chain (
      ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException,
                     SSLIOP::Current::NoContext));

  /// Returns true if the current execution context is not within a
  /// SSL session.  This method is mostly useful as an inexpensive
  /// means of determining whether or not SSL session state is
  /// available.
  virtual CORBA::Boolean no_context (
      ACE_ENV_SINGLE_ARG_DECL_WITH_DEFAULTS)
    ACE_THROW_SPEC ((CORBA::SystemException));

  /// Set the TSS slot ID assigned to this object.
  void tss_slot (size_t slot);

  /// Setup the Current.
  void setup (TAO_SSLIOP_Current_Impl *&prev_impl,
              TAO_SSLIOP_Current_Impl *new_impl,
              CORBA::Boolean &setup_done);

  /// Teardown the Current for this request.
  void teardown (TAO_SSLIOP_Current_Impl *prev_impl,
                 CORBA::Boolean &setup_done);

  /**
   * @name Downcast and Reference Counting Methods
   *
   * These are basically the same methods generated by the IDL
   * compiler for all IDL interfaces.
   */
  //@{
#if !defined(__GNUC__) || !defined (ACE_HAS_GNUG_PRE_2_8)
  typedef TAO_SSLIOP_Current_ptr _ptr_type;
  typedef TAO_SSLIOP_Current_var _var_type;
#endif /* ! __GNUC__ || g++ >= 2.8 */

  static int _tao_class_id;

  // The static operations.
  static TAO_SSLIOP_Current_ptr _duplicate (TAO_SSLIOP_Current_ptr obj);

  static TAO_SSLIOP_Current_ptr _narrow (
      CORBA::Object_ptr obj
      ACE_ENV_ARG_DECL_WITH_DEFAULTS);


  static TAO_SSLIOP_Current_ptr _unchecked_narrow (
      CORBA::Object_ptr obj
      ACE_ENV_ARG_DECL_WITH_DEFAULTS);


  static TAO_SSLIOP_Current_ptr _nil (void)
    {
      return (TAO_SSLIOP_Current_ptr)0;
    }

  virtual void *_tao_QueryInterface (ptrdiff_t type);

  virtual const char* _interface_repository_id (void) const;
  //@}

protected:

  /// Destructor
  /// Protected to force allocation on the heap.
  ~TAO_SSLIOP_Current (void);

  /// Set the TSS SSLIOP::Current implementation.
  int implementation (TAO_SSLIOP_Current_Impl *impl);

  /// Return the TSS SSLIOP::Current implementation.
  TAO_SSLIOP_Current_Impl *implementation (void);

private:

  /// Prevent copying through the copy constructor and the assignment
  /// operator.
  //@{
  ACE_UNIMPLEMENTED_FUNC (
    TAO_SSLIOP_Current (const TAO_SSLIOP_Current &))
  ACE_UNIMPLEMENTED_FUNC (void operator= (const TAO_SSLIOP_Current &))
  //@}

private:

  /// TSS slot assigned to this object.
  size_t tss_slot_;

  /// Pointer to the ORB Core corresponding to the ORB with which this
  /// object is registered.
  TAO_ORB_Core *orb_core_;

};

class TAO_SSLIOP_Current_var : public TAO_Base_var
{
public:
  TAO_SSLIOP_Current_var (void); // default constructor
  TAO_SSLIOP_Current_var (TAO_SSLIOP_Current_ptr p) : ptr_ (p) {}
  TAO_SSLIOP_Current_var (const TAO_SSLIOP_Current_var &); // copy constructor
  ~TAO_SSLIOP_Current_var (void); // destructor

  TAO_SSLIOP_Current_var &operator= (TAO_SSLIOP_Current_ptr);
  TAO_SSLIOP_Current_var &operator= (const TAO_SSLIOP_Current_var &);
  TAO_SSLIOP_Current_ptr operator-> (void) const;

  operator const TAO_SSLIOP_Current_ptr &() const;
  operator TAO_SSLIOP_Current_ptr &();
  // in, inout, out, _retn
  TAO_SSLIOP_Current_ptr in (void) const;
  TAO_SSLIOP_Current_ptr &inout (void);
  TAO_SSLIOP_Current_ptr &out (void);
  TAO_SSLIOP_Current_ptr _retn (void);
  TAO_SSLIOP_Current_ptr ptr (void) const;

  // Hooks used by template sequence and object manager classes
  // for non-defined forward declared interfaces.
  static TAO_SSLIOP_Current_ptr tao_duplicate (TAO_SSLIOP_Current_ptr);
  static void tao_release (TAO_SSLIOP_Current_ptr);
  static TAO_SSLIOP_Current_ptr tao_nil (void);
  static TAO_SSLIOP_Current_ptr tao_narrow (
      CORBA::Object *
      ACE_ENV_ARG_DECL_NOT_USED
    );
  static CORBA::Object * tao_upcast (void *);

private:
  TAO_SSLIOP_Current_ptr ptr_;
  // Unimplemented - prevents widening assignment.
  TAO_SSLIOP_Current_var (const TAO_Base_var &rhs);
  TAO_SSLIOP_Current_var &operator= (const TAO_Base_var &rhs);
};


#if defined (__ACE_INLINE__)
# include "SSLIOP_Current.inl"
#endif /* __ACE_INLINE__ */

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma warning(pop)
#endif /* _MSC_VER */

#include "ace/post.h"

#endif  /* TAO_SSLIOP_CURRENT_H */
