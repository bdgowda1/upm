/* TODO: better way to do this? */
%feature("notabstract") upm::HLG150H;

%include "iLightController.i"

%{
    #include "hlg150h.hpp"
%}
%include "hlg150h.hpp"
