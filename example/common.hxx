#include <siplus/siplus.h>

#ifndef SIPLUS_EXAMPLE_DONT_NEED_STDLIB
#ifndef SIPLUS_INCLUDE_STDLIB
#error "Examples require SIPLUS_INCLUDE_STDLIB=ON"
#endif
#endif

struct Person {
    std::string first_name;
};

struct PersonAccessor : SIPLUS_NAMESPACE::text::Accessor {
    virtual SIPLUS_NAMESPACE::text::UnknownDataTypeContainer access(
        const SIPLUS_NAMESPACE::text::UnknownDataTypeContainer& value, 
        const std::string& name
    );

    virtual bool can_access(const SIPLUS_NAMESPACE::text::UnknownDataTypeContainer& value);
};

