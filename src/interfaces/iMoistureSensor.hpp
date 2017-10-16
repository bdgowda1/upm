#pragma once

#include <map>
#include <vector>

#include "iSensorType.hpp"

namespace upm
{
    class iMoistureSensor : public virtual iSensorType
    {
        public:
            virtual std::map<std::string, float> GetMoistureAll() {return GetMoistureForSources(Sources());}
            virtual std::map<std::string, float> GetMoistureForSource(std::string source){ return GetMoistureForSources(std::vector<std::string>(1, source)); }
            virtual std::map<std::string, float> GetMoistureForSources(std::vector<std::string> sources) = 0;

            iMoistureSensor()
            {
                AddSerializer(this, &_JsonMoisture);
            }

            /**
             * Read and return all values for this sensor as JSON
             *
             * @return JSON string of moisture values
             */
            virtual std::string JsonMoisture() const
            {
                return "{" + _JsonMoisture((iMoistureSensor*)this) + "}";
            }

        private:
            static std::string _JsonMoisture(iUpmObject * inst)
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
    };
}
