%module javaupm_ms5611

%typemap(javaimports) SWIGTYPE %{
import upm_interfaces.*;
%}

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_ms5611)
