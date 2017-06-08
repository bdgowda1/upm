#if SWIG_VERSION >= 0x030009
    %include <swiginterface.i>
    %interface_impl(upm::iLightSensor);
#endif

%include "javaupm_interfaces.i"

%include "iLightSensor.hpp"
%{
	#include "iLightSensor.hpp"
%}