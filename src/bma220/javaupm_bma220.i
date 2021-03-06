%module javaupm_bma220
%include "../upm.i"
%include "cpointer.i"
%include "typemaps.i"
%include "arrays_java.i";
%include "../java_buffer.i"

%apply int {mraa::Edge};
%apply float *INOUT { float *x, float *y, float *z };

%typemap(jni) float* "jfloatArray"
%typemap(jstype) float* "float[]"
%typemap(jtype) float* "float[]"

%typemap(javaout) float* {
    return $jnicall;
}

%typemap(out) float *getAccelerometer {
    $result = JCALL1(NewFloatArray, jenv, 3);
    JCALL4(SetFloatArrayRegion, jenv, $result, 0, 3, $1);
    delete [] $1;
}

%ignore getAccelerometer(float *, float *, float *);

%{
    #include "bma220.hpp"
%}

%include "bma220.hpp"

%define GETTER get_gpioIntr();
%enddef
JAVA_ADD_INSTALLISR_GPIO(upm::BMA220)

%ignore installISR(int, mraa::Edge, void *, void *);

JAVA_JNI_LOADLIBRARY(javaupm_bma220)
