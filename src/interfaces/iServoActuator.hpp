#pragma once

#include "iActuatorType.hpp"

namespace upm
{
    /**
     * iServoActuator abstract class.
     *
     * Provides a common interface for all sensors which detect light.
     */
    class iServoActuator : public virtual iActuatorType
    {
        public:
            virtual ~iServoActuator();

            /**
             * Sets the angle of the servo engine.
             *
             * @param angle Number between 0 and 180
             * @return 0 if successful, non-zero otherwise
             */
            virtual bool Angle(int angle) = 0;
    };
}
