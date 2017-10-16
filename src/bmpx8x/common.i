/* TODO: better way to do this? */
%feature("notabstract") upm::BMPX8X;

%include "stdint.i"

%include "iTemperatureSensor.i"
%include "iPressureSensor.i"

%{
    #include "bmpx8x.hpp"
%}
%include "bmpx8x_defs.h"
%include "bmpx8x.hpp"
