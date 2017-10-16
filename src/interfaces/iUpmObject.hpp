#pragma once

#include <map>
#include <sstream>
#include <string>

#include "version.hpp"

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
            virtual ~iUpmObject() {}
            virtual std::string Name() const = 0;
            virtual std::string Description() const = 0;
            virtual std::string LibraryVersion() const {return ::LibraryVersion();}
            virtual std::string JsonDefinition() const
            {
                std::stringstream ss;
                ss << "{" << std::endl
                   << "  \"name\" : \"" << Name() << "\"," << std::endl
                   << "  \"description\" : \"" << Description() << "\""
                   << std::endl << "}";
                return ss.str();
            }

        protected:
            void AddSerializer(iUpmObject* instance, t_getJson method)
            { _children[method] = instance; }

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
    };
}
