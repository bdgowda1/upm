/* TODO: better way to do this? */
%feature("notabstract") upm::ms5611;

%include "iTemperatureSensor.i"
%include "iPressureSensor.i"

%{
    #include "ms5611.hpp"
%}
%include "ms5611.hpp"
