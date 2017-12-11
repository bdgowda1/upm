%include "std_vector.i"
%include "std_map.i"
%include "stl.i"
%include "std_string.i"

/* Using the JAVA class types outside the interfaces package requires
getCPtr to be public, modify that here */
%typemap(javabody) SWIGTYPE %{
private long swigCPtr;
protected boolean swigCMemOwn;
public $javaclassname(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
}
public static long getCPtr($javaclassname obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
}
%}

/* Add typemaps for the vector and maps used in the interfaces */
typedef std::vector<std::string> vec_str;
%template(vec_str) std::vector<std::string>;

typedef std::map<std::string, float> map_str_float;
%template(map_str_float) std::map<std::string, float>;

typedef std::map<std::string, std::string> map_str_str;
%template(map_str_str) std::map<std::string, std::string>;

/* JAVA has multiple define collisions once these get flattened out,
so ignore the base implementation */
#if SWIGJAVA
%ignore "upm::iUpmObject::JsonDefinition";
#endif

%{
#include "iUpmObject.hpp"
#include "iSensorType.hpp"
#include "iMraa.hpp"
#include "iADC.hpp"
#include "iTemperatureSensor.hpp"
#include "iPressureSensor.hpp"
#include "iMoistureSensor.hpp"
#include "iLightSensor.hpp"
#include "iLightController.hpp"
#include "iHumiditySensor.hpp"
#include "iCO2Sensor.hpp"
%}


%include "iUpmObject.hpp"
%include "iSensorType.hpp"
%include "iMraa.hpp"
%include "iADC.hpp"
%include "iTemperatureSensor.hpp"
%include "iPressureSensor.hpp"
%include "iMoistureSensor.hpp"
%include "iLightSensor.hpp"
%include "iLightController.hpp"
%include "iHumiditySensor.hpp"
%include "iCO2Sensor.hpp"

/* Add typemaps for the vectors of mraa types used in the interfaces */
typedef std::vector<mraa::Aio*> vec_aio;
%template(vec_aio) std::vector<mraa::Aio*>;

typedef std::vector<mraa::Gpio*> vec_gpio;
%template(vec_gpio) std::vector<mraa::Gpio*>;

typedef std::vector<mraa::I2c*> vec_i2c;
%template(vec_i2c) std::vector<mraa::I2c*>;

typedef std::vector<mraa::Iio*> vec_iio;
%template(vec_iio) std::vector<mraa::Iio*>;

typedef std::vector<mraa::Pwm*> vec_pwm;
%template(vec_pwm) std::vector<mraa::Pwm*>;

typedef std::vector<mraa::Spi*> vec_spi;
%template(vec_spi) std::vector<mraa::Spi*>;

typedef std::vector<mraa::Uart*> vec_uart;
%template(vec_uart) std::vector<mraa::Uart*>;

typedef std::vector<mraa::UartOW*> vec_uartow;
%template(vec_uartow) std::vector<mraa::UartOW*>;

