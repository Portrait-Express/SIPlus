# Building
SIPlus tries to support building in almost any environment, but some options may 
need to be set for certain environments.

## Options
Options can be found listed in the `CMakeLists.txt`, but are listed below for ease of access.

- `SIPLUS_INCLUDE_STDLIB` Include standard library base for siplus. Can be disabled to reduce binary size.
- `SIPLUS_SANITIZE_ADDRESS` Set -fsanitize=address for memory leak testing.
- `SIPLUS_BUILD_EXAMPLES` Whether or not to build examples.
- `WITH_STATIC_CRT` (MSVC Only) Enable to statically link CRT, which avoids requiring users to install the redistribution package.
- `SIPLUS_NAMESPACE` Specifies the root namespace to use if you dont want it to be `SIPlus`.

### Testing Options
These options are defined in `tests/CMakeLists.txt` and apply only to the tests.

- `SIPLUS_BUILD_TESTS` Whether or not to build tests.
- `SIPLUS_RUN_TESTS` Whether or not to run built tests automatically and have it act as a condition for a successful build.
- `SIPLUS_TESTS_USE_CPPTRACE` Include cpptrace in built tests for stack traces.
- `SIPLUS_TESTS_USE_ASAN` Sets -fsanitize=address for tests. Separate from SIPLUS_SANITIZE_ADDRESS.

## Shared Library
You can build a shared library (`dll`/`so`) through enabling the standard cmake flag `BUILD_SHARED_LIBS`.

# WASM
SIPlus supports WebAssembly building with no extra configuration, although `-fwasm-exceptions` 
is required to be enabled, and will be added globally through cmake.
