/* TODO: better way to do this? */
%feature("notabstract") upm::DS1808LC;

%include "iLightController.i"

%{
    #include "ds1808lc.hpp"
%}
%include "ds1808lc.hpp"
