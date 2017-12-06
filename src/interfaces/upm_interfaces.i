/* Any java package including upm_interfaces.i will import the
upm_interfaces java package in the JNI source */
%pragma(java) jniclassimports=%{
import upm_interfaces.*;
%}

%import "_upm_interfaces.i"

/* JAVASCRIPT does not have classes/inheritance, so include all the definitions.
This will cause warnings for the stl typemaps - ignore them */
#if SWIGJAVASCRIPT
#pragma SWIG nowarn=302
//%include "common.i"
#endif

/* Add the global UPM methods to all wrappers */
%{
#include "../upm_library_globals.hpp"
%}
%include "../upm_library_globals.hpp"
