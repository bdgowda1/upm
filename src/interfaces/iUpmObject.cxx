#include "iUpmObject.hpp"

using namespace upm;

iUpmObject::~iUpmObject() {}

std::string iUpmObject::JsonDefinition () const
{
    std::stringstream ss;
    ss << "{" << std::endl
        << "  \"name\" : \"" << Name() << "\"," << std::endl
        << "  \"description\" : \"" << Description() << "\""
        << std::endl << "}";
    return ss.str();
}

void iUpmObject::AddSerializer (iUpmObject * instance, t_getJson method)
{ _children[method] = instance; }
