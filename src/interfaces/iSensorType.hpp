#pragma once

#include <map>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>


#include "iUpmObject.hpp"

namespace upm
{
    /**
     * Forward declaration of iSensorType class for ostream usage
     */
    class iSensorType;

    /**
     * iSensorType abstract class.
     *
     * Provides a common interface for sensor classes.  This interface is
     * meant to be used by derived sensor categories.
     *
     * For example, iTemperatureSensor or iLightSensor
     *
     */
    class iSensorType : public virtual iUpmObject
    {
        private:
            /**
             * Sensor source vector
             */
            std::vector<std::string> _sources;

            /**
             * Sensor unit vector
             */
            std::vector<std::string> _units;

            /**
             * Mapping of sources to units
             */
            std::map<std::string, std::string> _sources_2_units;

        protected:
            /**
             * Mapping of sources to units, also re-creates the sources
             * and units vector on each add.
             */
            void AddSource(std::string source, std::string unit)
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

        public:
            /**
             * Return a map reference of sources to units.  This map can
             * be used to get the units for a sensor value given a source.
             *
             * @return Map of sources to units.
             */
            virtual const std::map<std::string, std::string>& SourceMap() const { return _sources_2_units;}

            /**
             * Return a vector of all known sources for this sensor.
             *
             * @return Vector of sources
             */
            virtual const std::vector<std::string>& Sources() const { return _sources; }

            /**
             * Return a vector of all known units for this sensor.
             *
             * @return Vector of units
             */
            virtual const std::vector<std::string>& Units() const { return _units; }

            /**
             * Return a unit string given a single source.
             *
             * @return Corresponding unit for source or empty string if not found.
             */
            virtual const std::string Unit(std::string source) const
            {
                std::map<std::string, std::string>::const_iterator it =
                    SourceMap().find(source);
                if (it != SourceMap().end())
                    return it->second;
                else
                    return "";
            }

            /**
             * Determine if this sensor has a given source.
             *
             * @return True if source string is available, fails otherwise.
             */
            virtual const bool HasSource(std::string source) const
            {
                return std::find(Sources().begin(), Sources().end(), source) != Sources().end();
            }

            /**
             * Determine if this sensor has a given unit.
             *
             * @return True if unit string is available, fails otherwise.
             */
            virtual const bool HasUnit(std::string unit) const
            {
                return std::find(Units().begin(), Units().end(), unit) != Units().end();
            }

            /**
             * Return a JsonDefinition string which defines this sensor
             *
             * @return JsonDefinition-encoded string.
             */
            virtual std::string JsonDefinition() const
            {
                std::stringstream ss;
                ss << "{" << std::endl << this << std::endl << "}";
                return ss.str();
            }

            /**
             * Allow derived classes to provide their own destructor
             */
            virtual ~iSensorType() {}

            /**
             * @brief Json string of sensor data.
             *
             * The JsonValues call serializes ALL values returned by this sensor
             * as a Json string.
             *
             * Example:
             *
             *      "Temperature" : {"value" : 25.0, "units" : "C"}
             *      "Acceleration" : {"value" : 1.1, "units" : "m/s^2"}
             *
             *  @return Json-encoded string.
             */
            virtual std::string JsonValues()
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

            /**
             * Overload for stream operator - output a meaningful JsonDefinition string from
             * an iSensorType Instance
             */
            friend std::ostream& operator<<(std::ostream& os, const iSensorType& o)
            {
                os << dynamic_cast<const iUpmObject&>(o) << "," << std::endl;
                if (!o.SourceMap().empty())
                {
                    os << "  \"sources\" :" << std::endl << "  {" << std::endl;
                    for(std::map<std::string, std::string>::const_iterator it = o.SourceMap().begin();
                            it != o.SourceMap().end();)
                    {
                        os << "    \"" << it->first << "\" : {\"units\" : \"" << it->second << "\"}";
                        if (++it != o.SourceMap().end())
                            os << "," << std::endl;
                    }
                    os << std::endl << "  }";
                }
                return os;
            }

            /**
             * Overload for stream operator - output a meaningful JsonDefinition string from
             * an iSensorType Instance
             */
            friend std::ostream& operator<<(std::ostream& os, const iSensorType* o)
            { return os << *o; }
    };
}
