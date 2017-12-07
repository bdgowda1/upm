#include <dlfcn.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <regex>


#include "upm_library_globals.hpp"

const char* LibraryBaseName()
{
    return UPM_LIBRARY_BASE_NAME;
}

const char* LibraryVersion()
{
    return UPM_VERSION_STRING;
}

static std::string _static_LibraryAbsolutePath;
const char* LibraryAbsolutePath()
{
    /* If this has already been called, return the previous value */
    if (!_static_LibraryAbsolutePath.empty())
        return _static_LibraryAbsolutePath.c_str();

    Dl_info info;
    /* Returns 0 on failure */
    if (!dladdr((const void*)&LibraryAbsolutePath, &info))
        return NULL;

    /* Attempt a realpath */
    _static_LibraryAbsolutePath = realpath(info.dli_fname, NULL);

    /* Let this method return a NULL */
    if (_static_LibraryAbsolutePath.empty())
        return NULL;

    return _static_LibraryAbsolutePath.c_str();
}

std::string LibraryLocation()
{
    /* Split out the path */
    std::string full_path = LibraryAbsolutePath();
    std::size_t found = full_path.find_last_of("/\\");
    return full_path.substr(0,found);
}

//static bool ends_with(std::string const &full_string, std::string const &substr)
//{
//    if (substr.size() > full_string.size()) return false;
//    return std::equal(substr.rbegin(), substr.rend(), full_string.rbegin());
//}

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
    exists("");
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
