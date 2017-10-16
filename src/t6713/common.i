/* TODO: better way to do this? */
%feature("notabstract") upm::t6713;

%include "iCO2Sensor.i"

%include "stdint.i"

%include "../carrays_uint16_t.i"

%{
    #include "t6713.hpp"
%}
%include "t6713.hpp"
