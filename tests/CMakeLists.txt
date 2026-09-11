if(EMSCRIPTEN) 
    message("WARNING!!! Tests cannot be built when building WASM. Disabling tests.")
    return()
endif()

enable_testing()

option(SIPLUS_RUN_TESTS "Whether or not to run built tests" ON)
option(SIPLUS_BUILD_TESTS "Whether or not to build tests" ON)

if(NOT SIPLUS_BUILD_TESTS)
return()
endif()

set(TEST_SOURCES 

    test_data.cxx 
    test_base.cxx 
    test_c.cxx
    test_stdlib.cxx
)


create_test_sourcelist (
    TESTS runner.cxx common.cxx ${TEST_SOURCES}
    EXTRA_INCLUDE runner_extra.hxx
    FUNCTION initialize
)

# add the executable
add_executable (runner ${TESTS} testing.cxx)

if(SIPLUS_TESTS_USE_CPPTRACE) 
    set(SIPLUS_TEST_LIBRARIES ${SIPLUS_TEST_LIBRARIES})
    target_compile_definitions(runner PUBLIC SIPLUS_HAS_CPPTRACE)
endif()

target_link_libraries(runner PRIVATE siplus ${SIPLUS_TEST_LIBRARIES})

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU") 
    target_link_libraries(runner PRIVATE stdc++exp)
    target_link_options(runner PRIVATE "-Wl,--wrap=__cxa_throw")
endif()

target_include_directories(runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Add all the ADD_TEST for each test
foreach (test ${TEST_SOURCES})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME ${TName} COMMAND runner ${TName})
endforeach ()

if(SIPLUS_RUN_TESTS) 
    add_custom_command(TARGET runner
                       POST_BUILD
                       COMMAND ctest -C "$<IF:$<CONFIG:Debug>,Debug,Release>" --output-on-failure)
endif()
