%include "upm_interfaces.i"
%import "iHumiditySensor.i"
%import "iTemperatureSensor.i"
%import "iPressureSensor.i"

%{
    #include "bmp280.hpp"
%}
%include "bmp280_regs.h"
%include "bmp280.hpp"

%{
    #include "bme280.hpp"
%}
%include "bme280.hpp"
