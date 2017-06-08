/* TODO: better way to do this? */
%feature("notabstract") upm::IMS;

%include "iLightSensor.i"
%include "iMoistureSensor.i"
%include "iTemperatureSensor.i"

%{
    #include "ims.hpp"
%}

%include "ims_defs.h"
%include "ims.hpp"
