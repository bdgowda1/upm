#include "iActuatorType.hpp"

using namespace upm;

std::string iActuatorType::JsonDefinition () const
{
    std::stringstream ss;

    ss << "{" << std::endl
        << "  \"name\" : \"" << Name() << "\"," << std::endl
        << "  \"description\" : \"" << Description() << "\"";

    ss << std::endl << "}";
    return ss.str();
}

iActuatorType::~iActuatorType () {}
