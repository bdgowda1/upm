#include <dlfcn.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <regex>


#define xstr(s) str(s)
#define str(s) #s

#include "upm_library_globals.hpp"

#define concat(A, B) A##B
#define define_upm_create(libname, blah) \
    void* concat(upm_create_,libname)(const char * init_str) \
{ \
       return NULL; \
}
define_upm_create(UPM_LIBRARY_BASE_NAME, someotherblah);

/*
const char* LibraryBaseName()
{
    return xstr(UPM_LIBRARY_BASE_NAME);
}
*/

const char* LibraryBaseNameForType(void *Type)
{
  return "";
}

const char* LibraryBaseName()
{
    return LibraryBaseNameForType((void*)LibraryBaseName);
}


const char* LibraryVersion()
{
    return xstr(UPM_VERSION_STRING);
}

static std::map<std::string, std::string> _static_LibraryAbsolutePath;

const char* LibraryAbsolutePathForType(void *Type)
{
    const std::type_info &this_type = typeid(&Type);
    printf("XXX0.5 type: %s\n", this_type.name());

    /* If this has already been called, return the previous value */
    if (!_static_LibraryAbsolutePath[this_type.name()].empty())
        return _static_LibraryAbsolutePath[this_type.name()].c_str();

    Dl_info info;

    /* Returns 0 on failure */
    if (!dladdr((const void*)&this_type, &info))
        return NULL;
    printf("XXX0->%s, %s\n", this_type.name(), info.dli_fname);

    /* Returns 0 on failure */
    if (!dladdr((const void*)&this_type, &info))
        return NULL;

    /* Attempt a realpath */
    _static_LibraryAbsolutePath[this_type.name()] = realpath(info.dli_fname, NULL);

    /* Let this method return a NULL */
    if (_static_LibraryAbsolutePath[this_type.name()].empty())
        return NULL;

    return _static_LibraryAbsolutePath[this_type.name()].c_str();
}

const char* LibraryAbsolutePath()
{
    return LibraryAbsolutePathForType((void*)LibraryAbsolutePath);
}

std::string LibraryLocation()
{
    /* Split out the path */
    std::string full_path = LibraryAbsolutePath();
    std::size_t found = full_path.find_last_of("/\\");
    return full_path.substr(0,found);
}

std::string DataDirectory()
{
    std::string lib_loc = LibraryLocation();

    /* Is the library in the build directory or installed on the system? */
    if (lib_loc.find("build/src/" + std::string(LibraryBaseName())) != std::string::npos)
        return lib_loc.substr(0, lib_loc.find("build/src/" + std::string(LibraryBaseName()))) +
            "src/";
    else
        return lib_loc.substr(0, lib_loc.find_last_of("/\\")) + "/share/upm";
}

static bool exists(const std::string& filename)
{
    std::ifstream f(filename.c_str());
    return f.good();
}

static std::string json_str;
const char* LibraryJson()
{
    printf("XXX1 LIBRARY BASE NAME: %s\n", LibraryBaseName());

    /* Is there a library JSON definition? */
    std::string datadir = DataDirectory();

    /* Let this method return a NULL */
    if (datadir.empty())
        return NULL;

    /* Attempt to build the path to the library JSON file */
    std::string json_file = datadir + std::string("/") + LibraryBaseName() +
        std::string("/") + LibraryBaseName() + std::string(".json");

    /* Make sure the file exists */
    if (!exists(json_file))
        return NULL;

    std::ifstream t(json_file);
    json_str.assign((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());

    return json_str.c_str();
}
