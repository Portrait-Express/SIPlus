#include <siplus/siplus.h>

#ifndef SIPLUS_EXAMPLE_DONT_NEED_STDLIB
#ifndef SIPLUS_INCLUDE_STDLIB
#error "Examples require SIPLUS_INCLUDE_STDLIB=ON"
#endif
#endif

struct Person {
    std::string first_name;
};

struct PersonAccessor : SIPlus::text::Accessor {
    virtual SIPlus::text::UnknownDataTypeContainer access(
        const SIPlus::text::UnknownDataTypeContainer& value, 
        const std::string& name
    );

    virtual bool can_access(const SIPlus::text::UnknownDataTypeContainer& value);
};

