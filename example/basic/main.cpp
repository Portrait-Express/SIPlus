#include <siplus/siplus.hxx>
#include <iostream>

using namespace SIPLUS_NAMESPACE;

struct Person { std::string name = "Dave"; } person;

/**
 * struct PersonType - Each object you wish to include in a macro needs a TypeInfo
 * implementation. This class contains the logic required for the templates to 
 * interact with your data properly.
 *
 * Hopefully C++26 should allow us to create these automatically 
 * with reflection, but for now they must be done by hand.
 */
struct PersonType : public TypeInfo {
    // data_type is optional, but HIGHLY recommended as it makes most operations 
    //much easier. 
    //
    //Providing this allows you to use as<>() with this type. 
    using data_type = Person; 
                              
    virtual std::string name() const { 
        //This NEEDS to be unique among all registered types. There are a 
        //handful of builtin types, so ensure that your tyoe name does not 
        //overlap. If two TypeInfo objects have the same name(), they are 
        //considered equivalent. This is not ideal, but a better solution is 
        //not known.
        return "Person"; 
    }

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

    //Attach the STL functions. None of which are used in this example, but you likely will use them.
    c.context().use_stl();

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
