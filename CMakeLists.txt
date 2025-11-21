cmake_minimum_required(VERSION 3.20)

option(SIPLUS_INCLUDE_STDLIB "Include standard library base for siplus. Can be disabled to reduce binary size" ON)
option(SIPLUS_SANITIZE_ADDRESS "Set -fsanitize=address for memory leak testing" OFF)
set(SIPLUS_NAMESPACE SIPlus CACHE STRING "Optionally specify a different root namespace")

project(siplus)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(dependencies)

file(GLOB GENERATED_SOURCES siplus/generated/*.cpp)

set(SIPLUS_SOURCES 
    ${GENERATED_SOURCES}
    siplus/token_stream.cpp
    siplus/si_parser.cpp
    siplus/context.cpp
    siplus/data.cpp
    siplus/expr_visitor.cpp
    siplus/interpolation_visitor.cpp
    siplus/literal_visitor.cpp
    siplus/parser_impl.cpp
    siplus/statement_visitor.cpp
    siplus/text.cpp
    siplus/util.cpp
    siplus/visitor.cpp
)

if(SIPLUS_INCLUDE_STDLIB)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/arithmetic.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/comparison.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/converting_operator.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/converters.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/iterable.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/standardlib.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/text.cpp)
    set(SIPLUS_SOURCES ${SIPLUS_SOURCES} siplus/stdlib/util.cpp)
endif()

add_library(siplus ${SIPLUS_SOURCES})

if(SIPLUS_SANITIZE_ADDRESS)
    target_compile_options(siplus PUBLIC -fsanitize=address)
    target_link_options(siplus PUBLIC -fsanitize=address)
endif()

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_SOURCE_DIR}/include/siplus/config.h"
)

target_include_directories(siplus PUBLIC include)
target_link_libraries(siplus antlr4_static)

add_subdirectory(tests)
