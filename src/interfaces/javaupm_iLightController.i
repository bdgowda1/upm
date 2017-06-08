#if SWIG_VERSION >= 0x030009
    %include <swiginterface.i>
    %interface_impl(upm::ILightController);
#endif

%include "javaupm_interfaces.i"

%include "iLightController.hpp"
%{
	#include "iLightController.hpp"
%}