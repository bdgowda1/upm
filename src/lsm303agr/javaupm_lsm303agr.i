%module javaupm_lsm303agr
%include "../upm.i"
%include "typemaps.i"
%include "../upm_javastdvector.i"

%ignore getMagnetometer(float *, float *, float *);
%ignore getAccelerometer(float *, float *, float *);

%typemap(javaimports) SWIGTYPE %{
import java.util.AbstractList;
import java.lang.Float;
%}

%typemap(javaout) SWIGTYPE {
    return new $&javaclassname($jnicall, true);
}
%typemap(javaout) std::vector<float> {
    return (AbstractList<Float>)(new $&javaclassname($jnicall, true));
}
%typemap(jstype) std::vector<float> "AbstractList<Float>"

%template(floatVector) std::vector<float>;

%{
    #include "lsm303agr.hpp"
    #include "lsm303agr_defs.h"
%}
%include "lsm303agr_defs.h"
%include "lsm303agr.hpp"


%ignore installISR(LSM303AGR_INTERRUPT_PINS_T , int ,  mraa::Edge , void *, void *);

%define INTERRUPT LSM303AGR_INTERRUPT_PINS_T
%enddef
JAVA_ADD_INSTALLISR_INTERRUPT(upm::LSM303AGR)

JAVA_JNI_LOADLIBRARY(javaupm_lsm303agr)
