# 2.0.3
- Added converter functions to the C API
- Added emscripten build support
- Added 32 bit support
- Added __declspec(dllim/export) to C++ API objects

# 2.0.2
- Fixed a SEGV that would occur when specifying only 1 parameter to `rand`
- Fixed an issue that was causing `siplus_make_bool` to return a data container of type `long`, not `boolean`
- Changed converting operator functions (`add`|`sub`|etc...) to use proper error messages on invalid parameters

# 2.0.1
- Added `NullType` and new language keyword `null` for first-class null support
- Fixed const reassignment error being thrown after the same template is evaluated a second time
- Added `type` function

# 2.0.0
- Replaced the old `std::type_index` method of handling types with a new `TypeInfo` that will handle type information centrally.
- Added a C API for bindings
- Changed antlr from being included in-tree, to a submodule
- Added examples

# 1.1.4
- Fixed errors when using template-defiend function parameters

# 1.1.3
- Fixed occasional segfault
- Added `while` function
- Added `set_new`, `set_add` and `set_has` functions

# 1.1.2
- Made variable declaration no longer implicit. Use `var` keyword to declare a variable.
- Added `persist` and `const` keywords to variables.

# 1.1.1
- Cleaned up header files to reduce size, include, and organize dependencies properly
- Fixed "undefined variable" errors being thrown in function parameters

# 1.1.0
- Fixed errors related to x86-specific instructions
- Fixed issues with whitespace parsing
- Added `@func => ()` custom function declaration syntax
- Added `$var = ()` variable definitions
- Added predefined global definition for additional variables

# 1.0.2
- Added `rand` function
- Added `randstr` function
- Added `sub` function
- Added `mul` function
- Added `div` function

# 1.0.1
- Added `.[0]` array index accessor syntax.

# 1.0.0
- 1.0.0 version launch
