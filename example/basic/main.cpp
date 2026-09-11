#include "siplus/context.hxx"
#include <siplus/siplus.hxx>
#include <iostream>

using namespace SIPLUS_NAMESPACE;

struct Person { std::string name = "Dave"; } person;

/**
 * struct PersonType - Each object you wish to include in a macro needs a TypeInfo
 * implementation. This class contains the logic required for the templates to 
 * interact with your data properly.
 *
 * Each unique type needs a descriptor, created with `new TypeInfoDescriptor`.
 * The pointer to this descriptor will be used to identify a specific type.
 * Types with equivalent descriptors are considered the same type implementation.
 *
 * Hopefully C++26 should allow us to create these automatically with 
 * reflection, but for now they must be done by hand.
 */
struct PersonType : public TypeInfo {
    // data_type and Type::descriptor are optional, but HIGHLY recommended as 
    // they make most operations much easier. 
    //
    // Providing these allows you to use as<>() with this type. See concept 
    // simple_value_retrievable_type<T> in context.hxx
    using data_type = Person; 
    static const TypeInfoDescriptor *const descriptor;

    PersonType() : TypeInfo(descriptor) {}

    virtual bool is_iterable(const UnknownDataTypeContainer& data) const {
        //This is not an iterable type, it has no sub elements you can iterate 
        //over. If your type *is* iterable, implement text::Iterator, and 
        //iterate() on it's TypeInfo implementation.
        return false;
    }

    virtual UnknownDataTypeContainer access(const UnknownDataTypeContainer& data, const std::string& name) const {
        //The as() method is only available if you specify YourType::data_type.
        //Otherwise use the void* in data directly.
        Person &person = data.as<PersonType>();
                                                        

        if(name == "name") {
            return make_data(person.name);
        }

        throw std::runtime_error{"Unrecognized Person property " + name};
    }
};

// The definition of the descriptor has to be done out of line since inline
// initializers have to be constant expressions.
const TypeInfoDescriptor *const PersonType::descriptor = new TypeInfoDescriptor("Person");

//This makes PersonType info able to be looked up in 
//SIPlus::type_info_for_t<Person>, and therefore we do not have to specify
//PersonType when calling make_data on a Person. This is optional, but also 
//highly recommended, similar to TypeInfo::data_type.
namespace SIPLUS_NAMESPACE { // SIPLUS_DEFINE_TYPE_INFO *Must* be in ::SIPLUS_NAMESPACE
SIPLUS_DEFINE_TYPE_INFO(Person, PersonType);
}

int main() {
    //This is the template to invoke
    std::string templateText = "Im sorry { .name }.";

    //Create a new parser
    Parser c;

    //Parse and build the template
    text::TextConstructor constructor = c.get_interpolation(templateText);
    
    //Build an InvocationContext
    auto data = c
        .context()
        .builder()
        // SIPLUS_DEFINE_TYPE_INFO allows us to use make_data instead of 
        // building a container by hand.
        .use_default(make_data(person))
        .build();

    //Invoke the template
    std::string text = constructor.construct_with(data);

    std::cout 
        << "Template: " << templateText << '\n'
        << "Result:   " << text << std::endl;

    return 0;
}
