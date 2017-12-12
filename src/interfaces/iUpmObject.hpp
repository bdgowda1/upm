#pragma once

#include <map>

#include <sstream>
#include <string>

#include <vector>
#include <stdint.h>
#include <memory>

#ifndef SWIG
/* Forward declare the basic_json class */
namespace nlohmann
{
    template<typename, typename>
        struct adl_serializer;

    template<template<typename, typename, typename...> class ObjectType,
        template<typename, typename...> class ArrayType,
        class StringType,
        class BooleanType,
        class NumberIntegerType,
        class NumberUnsignedType,
        class NumberFloatType,
        template<typename> class AllocatorType,
        template<typename, typename> class JSONSerializer>
            class basic_json;

        using json = basic_json<std::map, std::vector, std::string, bool, std::int64_t, std::uint64_t, double, std::allocator, nlohmann::adl_serializer>;
}
#endif

namespace upm
{
    class iUpmObject;

    /**
     * Function pointer typedef for child-to-parent proxy call
     */
    typedef std::string (*t_getJson)(iUpmObject*);

    class iUpmObject
    {
        public:
            iUpmObject();
            virtual ~iUpmObject();

            virtual std::string Description() const;
            virtual std::string JsonDefinition() const;
            virtual std::string Name() const;

#ifndef SWIG
            nlohmann::json& LibraryJson() const;
#endif

            std::string DataDirectory() const;
            std::string DerivedClassName() const;
            std::string LibraryAbsolutePath() const;
            std::string LibraryBaseName() const;
            std::string LibraryJsonFilename() const;
            std::string LibraryJsonRaw() const;
            std::string LibraryJsonSources() const;
            std::string LibraryVersion() const;

        protected:
            void AddSerializer(iUpmObject* instance, t_getJson method);

            /**
             * Used by child classes for child-to-parent proxy call
             */
            std::map<t_getJson, iUpmObject*> _children;

            ///*
            //friend std::ostream& operator<<(std::ostream& os, const iUpmObject& o)
            //{
            //    return os << "  \"name\" : \"" << o.Name() << "\"," << std::endl
            //        << "  \"description\" : \"" << o.Description() << "\"";
            //}

            //friend std::ostream& operator<<(std::ostream& os, const iUpmObject* o)
            //{ return os << *o; }
            //*/
        private:
            nlohmann::json *_json;
            std::string _Description;
            std::string _LibraryJsonFilename;
            std::string _LibraryJsonRaw;
    };
}
