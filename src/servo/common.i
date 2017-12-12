%include "upm_interfaces.i"
%import "iMraa.i"
%import "iServoActuator.i"

%{
#include "servo.hpp"
%}
%include "servo.hpp"

%{
#include "es08a.hpp"
%}
%include "es08a.hpp"

%{
#include "es9257.hpp"
%}
%include "es9257.hpp"
