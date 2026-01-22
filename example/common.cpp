#include "common.hxx"

using namespace SIPLUS_NAMESPACE;

text::UnknownDataTypeContainer PersonAccessor::access(
    const text::UnknownDataTypeContainer& value, 
    const std::string& name
) {
    const Person& person = value.as<Person>();

    if(name == "first_name") {
        return text::make_data(person.first_name);
    }

    throw std::runtime_error{"Unrecognized property name " + name + " for type Person."};
}

bool PersonAccessor::can_access(const text::UnknownDataTypeContainer& value) {
    return value.is<Person>();
}
