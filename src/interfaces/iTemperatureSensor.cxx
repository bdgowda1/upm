#include "iTemperatureSensor.hpp"

using namespace upm;

std::map <std::string, float> iTemperatureSensor::TemperatureAll ()
{return TemperatureForSources(Sources());}

float iTemperatureSensor::TemperatureForSource (std::string source)
{
    std::map<std::string, float> vals = TemperatureForSources(std::vector<std::string>(1, source));

    if (vals.empty())
    {
        std::stringstream ss;
        ss << __FUNCTION__ << " sensor does not provide source: '"
            << source << ".  Valid sources are: {";
        std::copy(Sources().begin(), Sources().end() - 1,
                std::ostream_iterator<std::string>(ss, ", "));
        ss << Sources().back() << "}";
        throw std::invalid_argument(ss.str());
    }

    return vals[source];
}

iTemperatureSensor::iTemperatureSensor ()
{
    AddSerializer(this, &_JsonTemperature);
}

std::string iTemperatureSensor::JsonTemperature () const
{
    return "{" + _JsonTemperature((iTemperatureSensor*)this) + "}";
}

std::string iTemperatureSensor::_JsonTemperature (iUpmObject * inst)
{
    std::stringstream ss;

    /* Downcast to reference (throws if cast fails) */
    iTemperatureSensor& ref = dynamic_cast<iTemperatureSensor&>(*inst);

    std::map<std::string, float> data = ref.TemperatureAll();

    for (std::map<std::string, float>::const_iterator it = data.begin();
            it != data.end();)
    {
        ss << "\"" << it->first << "\" : {\"value\" : " << it->second
            << ", \"units\" : \"" << ref.Unit(it->first) << "\"}";
        if (++it != data.end()) ss << "," << std::endl;
    }

    return ss.str();
}
