/* TODO: better way to do this? */
%feature("notabstract") upm::MAX44009;

%include "iLightSensor.i"

%{
    #include "max44009.hpp"
%}
%include "max44009.hpp"
