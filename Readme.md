# SIPlus - Interoperable Sring Templating Library

SIPlus (String Interpolation Plus) (placeholder name) is a solution to string templating across multiple platforms. Using this you can 
create a template in one system and bring it to a different system, and use it there (assuming the two SIPlus instances 
are configured similarly).

SIPlus is best used in bindings in other languages that have full reflection, but it is possible to do in C++, although 
it is not trivial. This is implemented in C++ for smaller binary sizes, and platform independence. Special consideration
was taken for WASM compatibility.


## Installation \[Recommended] (CMake)(FetchContent)
```
set(SIPLUS_BUILD_EXAMPLES OFF)
set(SIPLUS_BUILD_TESTS OFF)

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
- (JS) [@portrait-express/siplus](https://github.com/Portrait-Express/siplus-js)
- (C#) [SIPlus.NET](https://github.com/Portrait-Express/SIPlus.NET)

## Language Syntax
Syntax for the language can be found [here](./docs/syntax.md).

## Usage

See [examples](./example).

**NOTE**: This library should be considered BETA. While the API surface for the library is now mostly cemented, there 
still likely are a few uncaught bugs lying around. Some API aspects may change slightly from version to version. 
Major versions will not necessarily mean that there are no breaking changes, but if any, they will be minor. Large API
changes (such as the std::type_index to TypeInfo change) will increment major versions. Patch versions will be 
guaranteed to be interchangable.
