add_library(example_lib common.cpp)

target_link_libraries(example_lib siplus)

add_subdirectory(basic)
add_subdirectory(function)
