%module javaupm_max44009

%typemap(javaimports) SWIGTYPE %{
import upm_interfaces.*;
%}

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_max44009)
