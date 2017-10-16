%include "iSensorType.i"

#if (SWIGJAVA)
#if SWIG_VERSION >= 0x030009
%include "swiginterface.i"
%interface_impl(upm::iLightSensor);
#endif
#endif

%{
#include "iLightSensor.hpp"
%}
%import (module="upm.pyupm_interfaces") "iLightSensor.hpp"
