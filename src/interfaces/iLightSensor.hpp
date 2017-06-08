#pragma once

#include <map>
#include <vector>

#include "iSensorType.hpp"

namespace upm
{
    /**
     * iLightSensor abstract class.
     *
     * Provides a common interface for all sensors which detect light.
     */
    class iLightSensor : public virtual iSensorType
    {
        public:
            /**
             * Read and return all values for this sensor as a map of sources
             * to values.
             *
             * @return Map of sources to values.
             */
            virtual std::map<std::string, float> Light() {return Light(Sources());}

            /**
             * Read and return a single value from the source provided
             *
             * @param source Target source to read
             *
             * @throws std::invalid_argument If source is NOT valid for this sensor
             *
             * @return Map of sources to values.
             */
            virtual float Light(std::string source)
            {
                std::map<std::string, float> vals = Light(std::vector<std::string>(1, source));

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

            /**
             * Read and return all values for this sensor for the provided
             * vector of sources.
             *
             * @param sources Vector of sources to read
             *
             * @return Map of sources to values.
             */
            virtual std::map<std::string, float> Light(std::vector<std::string> sources) = 0;

            /**
             * Add a pointer to this type and a proxy function pointer for
             * serializing all values from this sensor type.
             */
            iLightSensor()
            {
                AddSerializer(this, &_JsonLight);
            }

            /**
             * Read and return all values for this sensor as JSON
             *
             * @return JSON string of light values
             */
            virtual std::string JsonLight() const
            {
                return "{" + _JsonLight((iLightSensor*)this) + "}";
            }

        private:
            /**
             * Provide a means to read and serialize values from this sensor
             * as a static method.  This method, along with a pointer to the
             * class can be called from a base class
             *
             * @param inst Instance of iLightSensor to call _JsonLight on
             *
             * @return JSON string of light values (minus wrapping '{' and '}'
             */
            static std::string _JsonLight(iUpmObject * inst)
            {
                std::stringstream ss;

                /* Downcast to reference (throws if cast fails) */
                iLightSensor& ref = dynamic_cast<iLightSensor&>(*inst);

                std::map<std::string, float> data = ref.Light();

                for (std::map<std::string, float>::const_iterator it = data.begin();
                        it != data.end();)
                {
                    ss << "\"" << it->first << "\" : {\"value\" : " << it->second
                        << ", \"units\" : \"" << ref.Unit(it->first) << "\"}";
                    if (++it != data.end()) ss << "," << std::endl;
                }

                return ss.str();
            }
    };
}
