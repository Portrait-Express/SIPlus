cmake_minimum_required(VERSION 3.20)


project(siplus)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(dependencies)

file(GLOB lib_sources siplus/*.cpp siplus/**/*.cpp)

add_library(siplus ${lib_sources})

target_include_directories(siplus PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(siplus antlr4_static)

add_subdirectory(tests)
