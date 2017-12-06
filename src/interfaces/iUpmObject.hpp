#pragma once

#include <map>
#include <sstream>
#include <string>

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
            virtual ~iUpmObject();
            virtual std::string Name() const = 0;
            virtual std::string Description() const = 0;
            virtual std::string JsonDefinition() const;

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
            std::string LibraryFullPath() const;
            std::string LibraryLocation() const;
            std::string DataDirectory() const;
    };
}
