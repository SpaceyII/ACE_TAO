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

#include "TAOC.h"
#include "tao/Null_RefCount_Policy.h"
#include "tao/TypeCode_Constants.h"
#include "tao/Alias_TypeCode.h"
#include "tao/Objref_TypeCode.h"
#include "tao/Struct_TypeCode.h"
#include "tao/CDR.h"
#include "tao/Any.h"
#include "tao/Any_Impl_T.h"
#include "tao/Any_Dual_Impl_T.h"

// TAO_IDL - Generated from
// be/be_visitor_typecode/alias_typecode.cpp:31

static TAO::TypeCode::Alias<char const *,
                            TAO::Null_RefCount_Policy>
  _tao_tc_TAO_BufferingConstraintMode (
    "IDL:tao/TAO/BufferingConstraintMode:1.0",
    "BufferingConstraintMode",
    &CORBA::_tc_ushort);
  
namespace TAO
{
  ::CORBA::TypeCode_ptr const _tc_BufferingConstraintMode =
    &_tao_tc_TAO_BufferingConstraintMode;
}



// TAO_IDL - Generated from
// be/be_visitor_typecode/struct_typecode.cpp:34

static TAO::TypeCode::Struct_Field<char const *> _tao_fields_TAO_BufferingConstraint[] =
  {
    { "mode", &TAO::_tc_BufferingConstraintMode },
    { "timeout", &TimeBase::_tc_TimeT },
    { "message_count", &CORBA::_tc_ulong },
    { "message_bytes", &CORBA::_tc_ulong }
    
  };
static TAO::TypeCode::Struct<char const *,
                             TAO::TypeCode::Struct_Field<char const *> const *,
                             CORBA::tk_struct,
                             TAO::Null_RefCount_Policy>
  _tao_tc_TAO_BufferingConstraint (
    "IDL:tao/TAO/BufferingConstraint:1.0",
    "BufferingConstraint",
    _tao_fields_TAO_BufferingConstraint,
    4);
  
namespace TAO
{
  ::CORBA::TypeCode_ptr const _tc_BufferingConstraint =
    &_tao_tc_TAO_BufferingConstraint;
}



// TAO_IDL - Generated from
// be/be_visitor_typecode/objref_typecode.cpp:73

static TAO::TypeCode::Objref<char const *,
                             CORBA::tk_local_interface,
                             TAO::Null_RefCount_Policy>
  _tao_tc_TAO_BufferingConstraintPolicy (
    "IDL:tao/TAO/BufferingConstraintPolicy:1.0",
    "BufferingConstraintPolicy");
  
namespace TAO
{
  ::CORBA::TypeCode_ptr const _tc_BufferingConstraintPolicy =
    &_tao_tc_TAO_BufferingConstraintPolicy;
}



// TAO_IDL - Generated from 
// be/be_visitor_structure/any_op_cs.cpp:54

// Copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    const TAO::BufferingConstraint &_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<TAO::BufferingConstraint>::insert_copy (
      _tao_any,
      TAO::BufferingConstraint::_tao_any_destructor,
      TAO::_tc_BufferingConstraint,
      _tao_elem
    );
}

// Non-copying insertion.
void operator<<= (
    CORBA::Any &_tao_any,
    TAO::BufferingConstraint *_tao_elem
  )
{
  TAO::Any_Dual_Impl_T<TAO::BufferingConstraint>::insert (
      _tao_any,
      TAO::BufferingConstraint::_tao_any_destructor,
      TAO::_tc_BufferingConstraint,
      _tao_elem
    );
}

// Extraction to non-const pointer (deprecated).
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    TAO::BufferingConstraint *&_tao_elem
  )
{
  return _tao_any >>= const_cast<
      const TAO::BufferingConstraint *&> (
      _tao_elem
    );
}

// Extraction to const pointer.
CORBA::Boolean operator>>= (
    const CORBA::Any &_tao_any,
    const TAO::BufferingConstraint *&_tao_elem
  )
{
  return
    TAO::Any_Dual_Impl_T<TAO::BufferingConstraint>::extract (
        _tao_any,
        TAO::BufferingConstraint::_tao_any_destructor,
        TAO::_tc_BufferingConstraint,
        _tao_elem
      );
}

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_cs.cpp:50

template<>
CORBA::Boolean
TAO::Any_Impl_T<TAO::BufferingConstraintPolicy>::to_object (
    CORBA::Object_ptr &_tao_elem
  ) const
{
  _tao_elem = CORBA::Object::_duplicate (this->value_);
  return 1;
}

template<>
CORBA::Boolean
TAO::Any_Impl_T<TAO::BufferingConstraintPolicy>::marshal_value (TAO_OutputCDR &)
{
  return false;
}

template<>
CORBA::Boolean
TAO::Any_Impl_T<TAO::BufferingConstraintPolicy>::demarshal_value (TAO_InputCDR &)
{
  return false;
}

// Copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    TAO::BufferingConstraintPolicy_ptr _tao_elem
  )
{
  TAO::BufferingConstraintPolicy_ptr _tao_objptr =
    TAO::BufferingConstraintPolicy::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

// Non-copying insertion.
void
operator<<= (
    CORBA::Any &_tao_any,
    TAO::BufferingConstraintPolicy_ptr *_tao_elem
  )
{
  TAO::Any_Impl_T<TAO::BufferingConstraintPolicy>::insert (
      _tao_any,
      TAO::BufferingConstraintPolicy::_tao_any_destructor,
      TAO::_tc_BufferingConstraintPolicy,
      *_tao_elem
    );
}

CORBA::Boolean
operator>>= (
    const CORBA::Any &_tao_any,
    TAO::BufferingConstraintPolicy_ptr &_tao_elem
  )
{
  return
    TAO::Any_Impl_T<TAO::BufferingConstraintPolicy>::extract (
        _tao_any,
        TAO::BufferingConstraintPolicy::_tao_any_destructor,
        TAO::_tc_BufferingConstraintPolicy,
        _tao_elem
      );
}

#if defined (ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION)

  template class
    TAO::Any_Dual_Impl_T<
        TAO::BufferingConstraint
      >;

  template class
    TAO::Any_Impl_T<
        TAO::BufferingConstraintPolicy
      >;

#elif defined (ACE_HAS_TEMPLATE_INSTANTIATION_PRAGMA)

# pragma instantiate \
    TAO::Any_Dual_Impl_T< \
        TAO::BufferingConstraint \
      >

# pragma instantiate \
    TAO::Any_Impl_T< \
        TAO::BufferingConstraintPolicy \
      >

#endif /* !ACE_HAS_EXPLICIT_TEMPLATE_INSTANTIATION */ 
