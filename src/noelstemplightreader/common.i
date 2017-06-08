/* TODO: better way to do this? */
%feature("notabstract") upm::NoelsTempLightReader;

%include "iLightSensor.i"
%include "iTemperatureSensor.i"

%{
    /* SWIG preprocessor copies this directly to the output wrapper*/
    #include "noelstemplightreader.hpp"
%}

/* %include is a SWIG directive.  SWIG will wrap types exposed in this
 * header to the target language. */
%include "noelstemplightreader.hpp"
