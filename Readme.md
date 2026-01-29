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
  GIT_TAG        1.2.0
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

WARNING: Current this library is still in development (despite a >1.0.0 semver). It is recommended to currently pin an exact version to keep a stable API. Public API aspects will be changing frequently.

See examples in the [example/](example/) folder.
- [Minimal](example/basic/main.cpp)
- [Custom Function](example/function/main.cpp)
