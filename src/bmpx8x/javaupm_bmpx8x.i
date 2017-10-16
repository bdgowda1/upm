%module javaupm_bmpx8x

%typemap(javaimports) SWIGTYPE %{
import upm_interfaces.*;
%}

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_bmpx8x)
