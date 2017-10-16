%module javaupm_t6713

%typemap(javaimports) SWIGTYPE %{
import upm_interfaces.*;
%}

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_t6713)
