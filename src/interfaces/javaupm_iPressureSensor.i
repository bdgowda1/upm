#if SWIG_VERSION >= 0x030009
    %include <swiginterface.i>
    %interface_impl(upm::iPressureSensor);
#endif

%include "javaupm_interfaces.i"

%include "iPressureSensor.hpp"
%{
	#include "iPressureSensor.hpp"
%}