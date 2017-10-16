%include "iUpmObject.i"

/* Explicitly ignore the base implementation */
#ifndef SWIGJAVASCRIPT
%ignore "upm::iUpmObject::JsonDefinition";
#endif

#if (SWIGJAVA)
#if SWIG_VERSION >= 0x030009
%include "swiginterface.i"
%interface_impl(upm::iSensorType);
#endif
#endif
%{
#include "iSensorType.hpp"
%}
%import "iSensorType.hpp"
