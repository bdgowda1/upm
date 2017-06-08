upm_mixed_module_init (NAME interfaces
    DESCRIPTION "CXX Interface Library"
    CPP_HDR iADC.hpp
            iCO2Sensor.hpp
            iHumiditySensor.hpp
            iLightController.hpp
            iLightSensor.hpp
            iMoistureSensor.hpp
            iMraa.hpp
            iPressureSensor.hpp
            iSensorType.hpp
            iTemperatureSensor.hpp
            iUpmObject.hpp
    CPP_SRC iMraa.cxx
    REQUIRES mraa utilities-c)

# Add a PUBLIC include directory to the CMAKE src dir
target_include_directories (${libname}
    PUBLIC ${CMAKE_SOURCE_DIR}/src
           ${CMAKE_BINARY_DIR}/src)
