%include "iActuatorType.i"

#if (SWIGJAVA)
#if SWIG_VERSION >= 0x030009
%include "swiginterface.i"
%interface_impl(upm::iServoActuator);
#endif
#endif

%{
#include "iServoActuator.hpp"
%}
%import (module="upm.pyupm_interfaces") "iServoActuator.hpp"
