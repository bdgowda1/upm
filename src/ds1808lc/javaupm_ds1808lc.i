%module javaupm_ds1808lc

%typemap(javaimports) SWIGTYPE %{
import upm_interfaces.*;
%}

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_ds1808lc)
