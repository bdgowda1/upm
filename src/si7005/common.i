%include "upm_interfaces.i"
%import "iMraa.i"
%import "iHumiditySensor.i"
%import "iTemperatureSensor.i"

%{
#include "si7005.hpp"
%}
%include "si7005.hpp"
