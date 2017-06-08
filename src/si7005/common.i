/* TODO: better way to do this? */
%feature("notabstract") upm::SI7005;

%include "iMraa.i"
%include "iHumiditySensor.i"
%include "iTemperatureSensor.i"

%{
    #include "si7005.hpp"
%}
%include "si7005.hpp"
