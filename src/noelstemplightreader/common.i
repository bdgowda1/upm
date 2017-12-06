%include "upm_interfaces.i"
%import "iMraa.i"
%import "iLightSensor.i"
%import "iTemperatureSensor.i"

%{
/* SWIG preprocessor copies this directly to the output wrapper*/
#include "noelstemplightreader.hpp"
%}

/* %include is a SWIG directive.  SWIG will wrap types exposed in this
 * header to the target language. */
%include "noelstemplightreader.hpp"
