%include "upm_interfaces.i"
%import "iPressureSensor.i"
%import "iTemperatureSensor.i"

%include "stdint.i"

%{
#include "bmpx8x.hpp"
%}
%include "bmpx8x_defs.h"
%include "bmpx8x.hpp"
