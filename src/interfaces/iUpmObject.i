#if (SWIGJAVA)
#if SWIG_VERSION >= 0x030009
%include "swiginterface.i"
%interface_impl(upm::iUpmObject);
%pragma(java) moduleimports=%{
import upm_interfaces.*;
%}
#endif
#endif

%{
#include "iUpmObject.hpp"
%}
%import "iUpmObject.hpp"
