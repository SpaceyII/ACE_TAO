// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

#include "orb_typesC.h"
#include "tao/Null_RefCount_Policy.h"
#include "tao/TypeCode_Constants.h"
#include "tao/Alias_TypeCode.h"
#include "tao/String_TypeCode.h"
#include "tao/CDR.h"
#include "tao/Any.h"

// TAO_IDL - Generated from
// be/be_visitor_typecode/alias_typecode.cpp:31

static TAO::TypeCode::Alias<char const *,
                            TAO::Null_RefCount_Policy>
  _tao_tc_CORBA_ORBid (
    "IDL:omg.org/CORBA/ORBid:1.0",
    "ORBid",
    &CORBA::_tc_string);
  
namespace CORBA
{
  ::CORBA::TypeCode_ptr const _tc_ORBid =
    &_tao_tc_CORBA_ORBid;
}



// TAO_IDL - Generated from
// be/be_visitor_typecode/alias_typecode.cpp:31

static TAO::TypeCode::Alias<char const *,
                            TAO::Null_RefCount_Policy>
  _tao_tc_CORBA_Flags (
    "IDL:omg.org/CORBA/Flags:1.0",
    "Flags",
    &CORBA::_tc_ulong);
  
namespace CORBA
{
  ::CORBA::TypeCode_ptr const _tc_Flags =
    &_tao_tc_CORBA_Flags;
}



// TAO_IDL - Generated from
// be/be_visitor_typecode/alias_typecode.cpp:31

static TAO::TypeCode::Alias<char const *,
                            TAO::Null_RefCount_Policy>
  _tao_tc_CORBA_Identifier (
    "IDL:omg.org/CORBA/Identifier:1.0",
    "Identifier",
    &CORBA::_tc_string);
  
namespace CORBA
{
  ::CORBA::TypeCode_ptr const _tc_Identifier =
    &_tao_tc_CORBA_Identifier;
}



// TAO_IDL - Generated from
// be/be_visitor_typecode/alias_typecode.cpp:31

static TAO::TypeCode::Alias<char const *,
                            TAO::Null_RefCount_Policy>
  _tao_tc_CORBA_RepositoryId (
    "IDL:omg.org/CORBA/RepositoryId:1.0",
    "RepositoryId",
    &CORBA::_tc_string);
  
namespace CORBA
{
  ::CORBA::TypeCode_ptr const _tc_RepositoryId =
    &_tao_tc_CORBA_RepositoryId;
}



#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

#endif /* !ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */ 
