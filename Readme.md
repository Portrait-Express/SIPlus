# SIPlus - Interoperable Sring Templating Library

SIPlus (String Interpolation Plus) is a solution to string templating across multiple platforms. Using this you can create a template in one system and bring it to a different system, and use it there (assuming the two SIPlus instances are configured similarly).

## Usage

WARNING: Current this library is VERY in development. NONE of the APIs are stable. It is recommended to currently pin a commit hash to keep a stable API. Public API aspects will be changing frequently.

Below is a minimal example.

```cpp
#include <siplus/siplus.h>

using namespace SIPlus;

struct Person { std::string name = "Dave"; } person;

struct PersonAccessor : text::Accessor {
    text::UnknownDataTypeContainer access(
        const text::UnknownDataTypeContainer &value, 
        const std::string &name
    ) override {
        const Person& person = value.as<Person>();

        if(name == "name") {
            return text::make_data(person.name);
        }

        throw std::runtime_error("No viable property for " + name);
    }

    bool can_access(const text::UnknownDataTypeContainer& value) override {
        return value.type == typeid(Person);
    }

};

int main() {
    Parser parser;
    c.context().emplace_accessor<PersonAccessor>();

    text::TextConstructor c = parser.get_interpolation("Im sorry { .name }.");

    std::string text = c.construct(person);

    return 0;
}
```

The main problem we have to work around is that, in CPP, there is no way to access a member of an object at runtime if you only have the string name of that member. We get around this by adding `Accessor`s which are type-specific handlers that are able to resolve these properties.  

The accessors require a `can_access` function which compares the runtime types of the data to see if the accessor can process a specific type. Internally accessors are stored in a `vector`, and are iterated over to find an instance where `Accessor::can_access` returns true. This is O(n) so if you have large amounts of accessors it is not good for performance.

More often than not (for us at least) this is used in bindings for other languages, and there are often methods of reflection, or other tricks you can do to only need one `Accessor` for all objects in that language.
