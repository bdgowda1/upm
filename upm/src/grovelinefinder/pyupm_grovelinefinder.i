// Include doxygen-generated documentation
%include "pyupm_doxy2swig.i"
%module pyupm_grovelinefinder
%include "../upm.i"

%include "grovelinefinder.hpp"
%{
    #include "grovelinefinder.hpp"
%}
