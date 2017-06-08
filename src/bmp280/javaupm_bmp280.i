%module javaupm_bmp280

%import "../interfaces/javaupm_iTemperatureSensor.i"
%import "../interfaces/javaupm_iHumiditySensor.i"
%import "../interfaces/javaupm_iPressureSensor.i"


%include "../upm.i"
%include "typemaps.i"
%include "arrays_java.i";
%include "../java_buffer.i"

%typemap(javaimports) SWIGTYPE %{
    import upm_interfaces.*;
%}

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_bmp280)
