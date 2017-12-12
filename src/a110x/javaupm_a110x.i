%module javaupm_a110x
%include "stdint.i"
%include "typemaps.i"

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_a110x)
JAVA_ADD_INSTALLISR(upm::A110X)
