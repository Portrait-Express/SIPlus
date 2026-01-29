#include "common.hxx"

using namespace SIPLUS_NAMESPACE;

std::string UserType::name() const { return "User"; }
bool UserType::is_iterable() const { return false; }

SIPLUS_NAMESPACE::UnknownDataTypeContainer 
UserType::access(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& data, const std::string& name) const {
    User& user = data.as<UserType>();

    if(name == "id") {
        return make_data(user.id);
    } else if(name == "first_name") {
        return make_data(user.id);
    }

    throw std::runtime_error{"Unknown user property " + name};
}
