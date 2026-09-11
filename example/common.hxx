#include <siplus/siplus.hxx>

struct User {
    int id;
    std::string first_name;
};

struct UserType : SIPLUS_NAMESPACE::TypeInfo {
    using data_type = User;
    static const SIPlus::TypeInfoDescriptor *const descriptor;

    UserType();

    bool is_iterable(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& data) const override;

    SIPLUS_NAMESPACE::UnknownDataTypeContainer 
    access(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& data, const std::string& name) const override;
};

namespace SIPLUS_NAMESPACE {
SIPLUS_DEFINE_TYPE_INFO(User, UserType);
}
