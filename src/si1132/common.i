/* TODO: better way to do this? */
%feature("notabstract") upm::SI1132;

%include "iLightSensor.i"

%{
    #include "si1132.hpp"
%}
%include "si1132.hpp"
