#include <dlfcn.h>
#include <typeinfo>
#include <cxxabi.h>
#include <string.h>
#include <iostream>
#include <regex>
#include <fstream>


#include "json.hpp"
#include "iUpmObject.hpp"
#include "upm_library_globals.hpp"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define THROW_RUNTIME(msg) throw std::runtime_error(std::string(__FILENAME__) + ":" + std::to_string(__LINE__) + " [" + std::string(__FUNCTION__) + "] " + msg)

using namespace upm;
using json = nlohmann::json;

/* Locate method to test if a file exists */
static bool exists(const std::string& filename)
{
    std::ifstream f(filename.c_str());
    return f.good();
}

iUpmObject::iUpmObject() : _json(new json) {}

iUpmObject::~iUpmObject() {}

std::string iUpmObject::Description() const
{
    json x = LibraryJson()["Sensor Class"][Name()]["Description"];

    std::cout << "XXX " << x << std::endl;
    if (x.empty())
        THROW_RUNTIME("No Description found for sensor class '" + Name() + "' in the JSON library descriptor file: " + LibraryJsonFilename());

    return x;
}

std::string iUpmObject::JsonDefinition () const
{
    std::stringstream ss;
    ss << "{" << std::endl
       << "  \"name\" : \"" << Name() << "\"," << std::endl
       << "  \"description\" : \"" << Description() << "\""
       << std::endl << "}";
    return ss.str();
}

std::string iUpmObject::Name() const
{
    /* Make sure the derived class name (from std::type_info) matches a JSON sensor class name */
    std::string classname_derived = DerivedClassName();

    /* Look at all objects under 'Sensor Class' */
    json x = LibraryJson()["Sensor Class"][classname_derived];

    if (x.empty())
        THROW_RUNTIME("Sensor class Name '" + classname_derived + "' was not found in the JSON library descriptor file: " + LibraryJsonFilename());

    return classname_derived;
}

json &iUpmObject::LibraryJson() const
{
    /* If the library descriptor JSON file has NOT been loaded, load it */
    if (_json->empty())
        *_json = _json->parse(LibraryJsonRaw());

    /* Perform a quick error check: Library element must be equal to LibraryBaseName() */
    std::string lib_base_name = LibraryBaseName();
    std::string lib_json_name = (*_json)["Library"];
    if (lib_base_name != (*_json)["Library"])
        THROW_RUNTIME("Library base name '" + lib_base_name + "' does NOT match the Library name specified in the JSON file '" + lib_json_name +"'");

    return *_json;
}

std::string iUpmObject::DerivedClassName() const
{
    int status = 0;
    char *name_demangled;
    const std::type_info &this_type = typeid(*this);

    /* Demangle class name */
    name_demangled = abi::__cxa_demangle(this_type.name(), 0, 0, &status);
    if (status)
        THROW_RUNTIME("Failed to demangle class name.");

    std::string name = name_demangled;
    free(name_demangled);

    Dl_info info;
    /* Returns 0 on failure */
    if (!dladdr((const void*)&this_type, &info))
        return NULL;

    /* Return class name only */
    return name.substr(name.find_last_of(":") + 1);
}

std::string iUpmObject::LibraryAbsolutePath() const
{
    Dl_info info;
    const std::type_info &this_type = typeid(*this);

    /* Throw on failure */
    if (!dladdr((const void*)&this_type, &info))
        THROW_RUNTIME("Failed to locate the library for this type.");

    /* Attempt a realpath */
    return realpath(info.dli_fname, NULL);
}

std::string iUpmObject::LibraryBaseName() const
{
    /* First, get the filename */
    std::string filename = LibraryAbsolutePath();

    /* Regex the library *base* name from the library file name */
    std::smatch sm;
    std::regex reg1("libupm-(\\S+)\\.so");
    if (!std::regex_search(filename, sm, reg1))
        THROW_RUNTIME("Could not get base libraaaary name.  UPM library name does not follow the libupm-<library>.so format.");

    return sm.str(1);
}

std::string iUpmObject::LibraryJsonFilename() const
{
    std::string json_file = DataDirectory() + "/" + LibraryBaseName() + ".json";

    if (!exists(json_file))
        THROW_RUNTIME("Failed to locate library JSON definition: " + json_file);

    return json_file;
}

std::string iUpmObject::DataDirectory() const
{
    std::string lib_loc = LibraryAbsolutePath();

    std::string _json_lib_def = lib_loc.substr(0, lib_loc.find_last_of("/\\")) + "/" + LibraryBaseName() + ".json";

    /* Is no local <libname>.json exists, look in DATADIR */
    if (!exists(_json_lib_def))
        _json_lib_def = lib_loc.substr(0, lib_loc.find_last_of("/\\")) + "/share/upm/" + LibraryBaseName() + ".json";

    if (!exists(_json_lib_def))
        THROW_RUNTIME("Data directory for UPM was not found.  Library found: " + lib_loc + ", expected: " + _json_lib_def);

    return _json_lib_def.substr(0, _json_lib_def.find_last_of("/\\"));
}

std::string iUpmObject::LibraryJsonRaw() const
{
    std::string json_file = LibraryJsonFilename();

    /* Return the contents as a string */
    std::string json_str;
    std::ifstream t(json_file);
    json_str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

    return json_str.c_str();
}

std::string iUpmObject::LibraryJsonSources() const
{
    return LibraryJson()["Sensor Class"][Name()]["Sources"];
}

std::string iUpmObject::LibraryVersion() const
{
    return ::LibraryVersion();
}

void iUpmObject::AddSerializer (iUpmObject * instance, t_getJson method)
{ _children[method] = instance; }

