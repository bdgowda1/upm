#ifdef ANDROID
    %module javaupm_si1132
#else
    %module(directors="1") javaupm_si1132
#endif

%include "common.i"

JAVA_JNI_LOADLIBRARY(javaupm_si1132)
