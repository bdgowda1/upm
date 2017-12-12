#pragma once

#include "iUpmObject.hpp"

namespace upm
{
    /**
     * iActuatorType abstract class.
     *
     * Provides a common interface for sensor classes.  This interface is
     * meant to be used by derived sensor categories.
     *
     * For example, iServoActuator
     *
     */
    class iActuatorType : public virtual iUpmObject
    {
        public:
            /**
             * Return a JsonDefinition string which defines this sensor
             *
             * @return JsonDefinition-encoded string.
             */
            virtual std::string JsonDefinition() const;

            /**
             * Allow derived classes to provide their own destructor
             */
            virtual ~iActuatorType();
    };
}
