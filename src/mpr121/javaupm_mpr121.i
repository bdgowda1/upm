%module javaupm_mpr121
%include "../upm.i"
%include "arrays_java.i";
%include "../java_buffer.i"

%{
    #include "mpr121.hpp"
%}

%include "mpr121.hpp"

JAVA_JNI_LOADLIBRARY(javaupm_mpr121)