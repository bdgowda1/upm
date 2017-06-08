/* TODO: better way to do this? */
%feature("notabstract") upm::BMP280;
%feature("notabstract") upm::BME280;

%include "cpointer.i"

%include "bmp280_regs.h"
%include "bmp280.hpp"
%{
    #include "bmp280.hpp"
%}

%include "bme280.hpp"
%{
    #include "bme280.hpp"
%}
