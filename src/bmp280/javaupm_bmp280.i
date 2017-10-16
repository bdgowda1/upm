%module javaupm_bmp280

%include "typemaps.i"
%include "arrays_java.i";
%include "../java_buffer.i"

%typemap(javaimports) SWIGTYPE %{
    import upm_interfaces.*;
%}

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_bmp280)
