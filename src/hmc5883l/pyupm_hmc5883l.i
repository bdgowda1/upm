// Include doxygen-generated documentation
%include "pyupm_doxy2swig.i"
%module pyupm_hmc5883l
%include "../upm.i"
%include "../carrays_int16_t.i"

%typemap(out) int16_t* {
  $result = SWIG_NewPointerObj(SWIG_as_voidptr(result), SWIGTYPE_p_int16Array, 0 |  0 );
}

%include "hmc5883l.hpp"
%{
    #include "hmc5883l.hpp"
%}
