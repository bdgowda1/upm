/* TODO: better way to do this? */
%feature("notabstract") upm::LP8860;

%include "iLightController.i"

%{
    #include "lp8860.hpp"
%}
%include "lp8860.hpp"
