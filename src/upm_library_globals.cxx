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

std::string _static_LibraryAbsolutePath;
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

static bool ends_with(std::string const &full_string, std::string const &substr)
{
    if (substr.size() > full_string.size()) return false;
    return std::equal(substr.rbegin(), substr.rend(), full_string.rbegin());
}

std::string DataDirectory()
{
    std::string lib_loc = LibraryLocation();
    if (ends_with(lib_loc, "interfaces"))
        return lib_loc.substr(0, lib_loc.size() - sizeof("build/src/interfaces")) + "/src";
    else
        return lib_loc.substr(0, lib_loc.find_last_of("/\\")) + "/share/upm";
}

static bool exists(const std::string& filename)
{
    std::ifstream f(filename.c_str());
    return f.good();
}

std::string _static_DataDirectory;
const char* LibraryJson()
{
    exists("");
    /* Is there a library JSON definition? */
    _static_DataDirectory = DataDirectory();

    /* Let this method return a NULL */
    if (_static_DataDirectory.empty())
        return NULL;

    return _static_DataDirectory.c_str();
}
