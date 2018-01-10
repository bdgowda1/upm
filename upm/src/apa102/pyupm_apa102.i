// Include doxygen-generated documentation
%include "pyupm_doxy2swig.i"

%module pyupm_apa102

%include "../upm.i"

// setLeds
%typemap(in) (uint8_t *colors) {
  if (PyByteArray_Check($input)) {
    $1 = (uint8_t*) PyByteArray_AsString($input);
  } else {
    PyErr_SetString(PyExc_ValueError, "bytearray expected");
    return NULL;
  }
}

%include "apa102.hpp"

%{

    #include "apa102.hpp"
%}
