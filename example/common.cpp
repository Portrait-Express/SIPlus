#include "common.hxx"

SIPlus::text::UnknownDataTypeContainer PersonAccessor::access(
    const SIPlus::text::UnknownDataTypeContainer& value, 
    const std::string& name
) {
    const Person& person = value.as<Person>();

    if(name == "first_name") {
        return SIPlus::text::make_data(person.first_name);
    }

    throw std::runtime_error{"Unrecognized property name " + name + " for type Person."};
}

bool PersonAccessor::can_access(const SIPlus::text::UnknownDataTypeContainer& value) {
    return value.is<Person>();
}
