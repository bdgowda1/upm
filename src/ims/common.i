%include "upm_interfaces.i"
%import "iMraa.i"
%import "iLightSensor.i"
%import "iMoistureSensor.i"
%import "iTemperatureSensor.i"

%{
    #include "ims.hpp"
%}

%include "ims_defs.h"
%include "ims.hpp"
