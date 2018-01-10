// Include doxygen-generated documentation
%include "pyupm_doxy2swig.i"
%module pyupm_h3lis331dl
%include "../upm.i"
%include "cpointer.i"

/* Send "int *" and "float *" to python as intp and floatp */
%pointer_functions(int, intp);
%pointer_functions(float, floatp);

#ifdef DOXYGEN
%include "h3lis331dl_doc.i"
#endif

%include "h3lis331dl.hpp"
%{
    #include "h3lis331dl.hpp"
%}
