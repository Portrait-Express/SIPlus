# SIPlus - Interoperable Sring Templating Library

SIPlus (String Interpolation Plus) (placeholder name) is a solution to string templating across multiple platforms. Using this you can 
create a template in one system and bring it to a different system, and use it there (assuming the two SIPlus instances 
are configured similarly).

SIPlus is best used in bindings in other languages that have full reflection, but it is possible to do in C++, although 
it is not trivial. This is implemented in C++ for smaller binary sizes, and platform independence. Special consideration
was taken for WASM compatibility.


## Installation \[Recommended] (CMake)(FetchContent)
```
FetchContent_Declare(
  siplus
  GIT_REPOSITORY https://github.com/Portrait-Express/siplus
  GIT_TAG        1.1.0
)

FetchContent_MakeAvailable(siplus)

target_link_libraries(myproject siplus)
```

## Installation (Other languages)
(Limited) Bindings are available for some other languages.
- @portrait-express/siplus [siplus-js](https://github.com/Portrait-Express/siplus-js)

## Language Syntax
Syntax for the language can be found [here](./docs/syntax.md).

## Usage

WARNING: Current this library is still in development (despite a >1.0.0 semver). It is recommended to currently pin a commit hash to keep a stable API. Public API aspects will be changing frequently until a good patern is decided.

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
    Parser c;
    c.context().use_stl();
    c.context().emplace_accessor<PersonAccessor>();

    auto data = c.context().builder().use_default(text::make_data(person)).build();

    text::TextConstructor c = parser.get_interpolation("Im sorry { .name }.");
    std::string text = c.construct(data);

    return 0;
}
```

---
## Issues in CPP

The main problem we have to work around is that, in CPP, there is no way to access a member of an object at runtime if you only have the string name of that member. We get around this by adding `Accessor`s which are type-specific handlers that are able to resolve these properties.  

The accessors require a `can_access` function which compares the runtime types of the data to see if the accessor can process a specific type. Internally accessors are stored in a `vector`, and are iterated over to find an instance where `Accessor::can_access` returns true. This is O(n) so if you have large amounts of accessors it is not good for performance.

More often than not (for us at least) this is used in bindings for other languages, and there are often methods of reflection, or other tricks you can do to only need one `Accessor` for all objects in that language.
