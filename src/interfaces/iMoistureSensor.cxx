#include "iMoistureSensor.hpp"

using namespace upm;

std::map <std::string, float> iMoistureSensor::GetMoistureAll ()
{return GetMoistureForSources(Sources());}

std::map <std::string, float> iMoistureSensor::GetMoistureForSource (std::string source)
{ return GetMoistureForSources(std::vector<std::string>(1, source)); }

iMoistureSensor::iMoistureSensor ()
{
    AddSerializer(this, &_JsonMoisture);
}

std::string iMoistureSensor::JsonMoisture () const
{
    return "{" + _JsonMoisture((iMoistureSensor*)this) + "}";
}

std::string iMoistureSensor::_JsonMoisture (iUpmObject * inst)
{
    std::stringstream ss;

    /* Downcast to reference (throws if cast fails) */
    iMoistureSensor& ref = dynamic_cast<iMoistureSensor&>(*inst);

    std::map<std::string, float> data = ref.GetMoistureAll();

    for (std::map<std::string, float>::const_iterator it = data.begin();
            it != data.end();)
    {
        ss << "\"" << it->first << "\" : {\"value\" : " << it->second
            << ", \"units\" : \"" << ref.Unit(it->first) << "\"}";
        if (++it != data.end()) ss << "," << std::endl;
    }

    return ss.str();
}
