#if SWIG_VERSION >= 0x030009
    %include <swiginterface.i>
    %interface_impl(upm::iTemperatureSensor);
#endif

%include "javaupm_interfaces.i"

%include "iTemperatureSensor.hpp"
%{
    #include "iTemperatureSensor.hpp"
%}
