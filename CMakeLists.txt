cmake_minimum_required(VERSION 3.20)

option(SIPLUS_INCLUDE_STDLIB "Include standard library base for siplus. Can be disabled to reduce binary size" ON)
option(SIPLUS_SANITIZE_ADDRESS "Set -fsanitize=address for memory leak testing" OFF)
option(SIPLUS_BUILD_EXAMPLES "Build Examples" On)
option(WITH_STATIC_CRT "(MSVC Visual C++) Enable to statically link CRT, which avoids requiring users to install the redistribution package.
 To disable with: -DWITH_STATIC_CRT=Off" On)
set(SIPLUS_NAMESPACE SIPlus CACHE STRING "Optionally specify a different root namespace")

if(SIPLUS_BUILD_EXAMPLES)
    if(EMSCRIPTEN) 
        message("WARNING: Examples cannot be built when building WASM. Disabling examples.")
        set(SIPLUS_BUILD_EXAMPLES OFF)
    endif()
endif()

if(BUILD_SHARED_LIBS AND WITH_STATIC_CRT)
    message("WARNING: Cannot use static CRT when building shared library. Disabling static CRT")
    set(WITH_STATIC_CRT OFF)
endif()

project(siplus VERSION 2.0.3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB GENERATED_SOURCES siplus/generated/*.cpp)

set(SIPLUS_SOURCES 
    ${GENERATED_SOURCES}
    siplus/block_visitor.cpp
    siplus/build_context.cpp
    siplus/c.cpp
    siplus/context.cpp
    siplus/data.cpp
    siplus/expr_stmt_visitor.cpp
    siplus/expr_visitor.cpp
    siplus/interpolation_visitor.cpp
    siplus/invocation_context.cpp
    siplus/literal_visitor.cpp
    siplus/parser_impl.cpp
    siplus/statement_visitor.cpp
    siplus/text.cpp
    siplus/types.cpp
    siplus/visitor.cpp
)

if(SIPLUS_INCLUDE_STDLIB)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/arithmetic.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/comparison.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/control.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/converting_operator.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/converters.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/iterable.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/set.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/standardlib.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/text.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/type.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/rand.cpp)
endif()

if(BUILD_SHARED_LIBS) 
    message("Building in shared library mode")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(SIPLUS_EXPORTING ON)
endif()

if(MSVC)
# Needed for some ungodly reason. I blame Microsoft.
# MSVC CRT includes a constexpr Mutex constructor that breaks ABI compatibility.
# This is needed to disable it, since antlr uses it.
    add_compile_definitions(_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR)

    if(WITH_STATIC_CRT)
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
      set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
    endif(WITH_STATIC_CRT)

    message("-- Using MSVC ${CMAKE_MSVC_RUNTIME_LIBRARY} Runtime")
endif()

if(EMSCRIPTEN)
    add_compile_options(-fwasm-exceptions)
    add_link_options(-fwasm-exceptions)
endif()

add_subdirectory(dependencies)

add_library(siplus ${SIPLUS_SOURCES})
target_precompile_headers(siplus PRIVATE "${PROJECT_SOURCE_DIR}/include/siplus/pch.hxx")
add_compile_definitions(SIPLUS_BUILD)

target_include_directories(siplus PUBLIC include)
target_link_libraries(siplus antlr4_static)

if(MSVC)
    target_compile_options(siplus PUBLIC -Zc:preprocessor)
endif()

if(SIPLUS_BUILD_EXAMPLES)
    if(EMSCRIPTEN) 
        message("WARNING: Examples cannot be built when building WASM. Disabling examples.")
    else()
        add_subdirectory(example)
    endif()
endif()

if(SIPLUS_SANITIZE_ADDRESS)
    if(MSVC)
        message("WARNING: Due to limitations with MSVC, ASAN on Windows is currently not supported")
    else()
        target_compile_options(siplus PUBLIC -fsanitize=address)
        target_link_options(siplus PUBLIC -fsanitize=address)
    endif()
endif()

add_subdirectory(tests)

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/include/siplus/config.h"
)
