#include "iSensorType.hpp"

using namespace upm;

void iSensorType::AddSource (std::string source, std::string unit)
{
    /* Add the source:unit to the map */
    _sources_2_units[source] = unit;

    /* Each call regens the sources and units vectors */
    _sources.clear();
    _units.clear();

    for(std::map<std::string, std::string>::const_iterator it = SourceMap().begin();
            it != SourceMap().end(); ++it)
    {
        _sources.push_back(it->first);
        _units.push_back(it->second);
    }

    /* Uniquify the sources vector */
    std::sort(_sources.begin(), _sources.end());
    _sources.erase(std::unique(_sources.begin(), _sources.end()), _sources.end());
    /* Uniquify the units vector */
    std::sort(_units.begin(), _units.end());
    _units.erase(std::unique(_units.begin(), _units.end()), _units.end());
}

std::map <std::string, std::string> const & iSensorType::SourceMap () const
{ return _sources_2_units;}

std::vector <std::string> const & iSensorType::Sources () const
{ return _sources; }

std::vector <std::string> const & iSensorType::Units () const
{ return _units; }

std::string const iSensorType::Unit (std::string source) const
{
    std::map<std::string, std::string>::const_iterator it =
        SourceMap().find(source);
    if (it != SourceMap().end())
        return it->second;
    else
        return "";
}

bool const iSensorType::HasSource (std::string source) const
{
    return std::find(Sources().begin(), Sources().end(), source) != Sources().end();
}

bool const iSensorType::HasUnit (std::string unit) const
{
    return std::find(Units().begin(), Units().end(), unit) != Units().end();
}

std::string iSensorType::JsonDefinition () const
{
    std::stringstream ss;

    ss << "{" << std::endl
        << "  \"name\" : \"" << Name() << "\"," << std::endl
        << "  \"description\" : \"" << Description() << "\"";

    if (!SourceMap().empty())
    {
        ss << "," << std::endl << "  \"sources\" :" << std::endl << "  {" << std::endl;
        for(std::map<std::string, std::string>::const_iterator it = SourceMap().begin();
                it != SourceMap().end();)
        {
            ss << "    \"" << it->first << "\" : {\"units\" : \"" << it->second << "\"}";
            if (++it != SourceMap().end())
                ss << "," << std::endl;
        }
        ss << std::endl << "  }";
    }
    ss << std::endl << "}";
    return ss.str();
}

iSensorType::~iSensorType () {}

std::string iSensorType::JsonValues ()
{
    std::stringstream ss;
    ss << "{" << std::endl;
    if (!_children.empty())
    {
        /* Iterate over each serializer method */
        for (std::map<t_getJson, iUpmObject*>::const_iterator it = _children.begin();
                it != _children.end();)
        {
            // Call static method to serialize data from the derived classes
            ss << it->first(it->second);
            if (++it != _children.end()) ss << ",";
            ss << std::endl;
        }
    }
    ss << "}";
    return ss.str();
}
