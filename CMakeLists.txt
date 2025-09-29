cmake_minimum_required(VERSION 3.20)


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
    siplus/standardlib.cpp
    siplus/statement_visitor.cpp
    siplus/text.cpp
    siplus/visitor.cpp
)

add_library(siplus ${SIPLUS_SOURCES})

#target_compile_options(siplus PRIVATE -s -ffunction-sections -fdata-sections -fno-unwind-tables -fno-asynchronous-unwind-tables)
#target_link_options(siplus PRIVATE -s -Wl,-s -Wl,-Bsymbolic -Wl,--gc-sections)

target_include_directories(siplus PUBLIC include)
target_link_libraries(siplus antlr4_static)

add_subdirectory(tests)
