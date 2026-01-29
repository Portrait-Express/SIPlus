#include "siplus/data.h"
#include <siplus/siplus.h>

#ifndef SIPLUS_EXAMPLE_DONT_NEED_STDLIB
#ifndef SIPLUS_INCLUDE_STDLIB
#error "Examples require SIPLUS_INCLUDE_STDLIB=ON"
#endif
#endif

struct User {
    int id;
    std::string first_name;
};

struct UserType : SIPLUS_NAMESPACE::TypeInfo {
    using data_type = User;

    std::string name() const override;
    bool is_iterable(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& data) const override;

    SIPLUS_NAMESPACE::UnknownDataTypeContainer 
    access(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& data, const std::string& name) const override;
};

namespace SIPLUS_NAMESPACE {
SIPLUS_DEFINE_TYPE_INFO(User, UserType);
}
