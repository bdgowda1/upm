%include "upm_interfaces.i"
%import "iPressureSensor.i"
%import "iTemperatureSensor.i"

%{
    #include "ms5611.hpp"
%}
%include "ms5611.hpp"
