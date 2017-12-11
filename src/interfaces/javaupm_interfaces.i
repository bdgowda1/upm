%module javaupm_interfaces

#if SWIG_VERSION >= 0x030009
%include "swiginterface.i"
%interface_impl(upm::iUpmObject);
%interface_impl(upm::iSensorType);
%interface_impl(upm::iMraa);
%interface_impl(upm::iADC);
%interface_impl(upm::iCO2Sensor);
%interface_impl(upm::iHumiditySensor);
%interface_impl(upm::iLightController);
%interface_impl(upm::iLightSensor);
%interface_impl(upm::iMoistureSensor);
%interface_impl(upm::iPressureSensor);
%interface_impl(upm::iTemperatureSensor);
#endif

%include "common.i"

%pragma(java) jniclasscode=%{
    static {
        try {
            System.loadLibrary("javaupm_interfaces");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("Native code library failed to load. \n" + e);
            System.exit(1);
        }
    }
%}
