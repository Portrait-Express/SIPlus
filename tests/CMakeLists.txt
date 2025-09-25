enable_testing()

option(SIPLUS_RUN_TESTS "Whether or not to run built tests" ON)
option(SIPLUS_BUILD_TESTS "Whether or not to build tests" ON)
option(SIPLUS_TESTS_USE_CPPTRACE "Include cpptrace in built tests for stack traces" ON)

if(NOT SIPLUS_BUILD_TESTS)
return()
endif()

add_subdirectory(util)

set(TEST_SOURCES 
    test_expression.cxx
    test_interpolate.cxx
    test_loop.cxx
    test_function.cxx
    test_stdlib.cxx
)

create_test_sourcelist (
    TESTS runner.cxx common.cxx ${TEST_SOURCES}
    EXTRA_INCLUDE runner_extra.hxx
    FUNCTION initialize
)

# add the executable
add_executable (runner ${TESTS})

if(SIPLUS_TESTS_USE_CPPTRACE) 
    set(SIPLUS_TEST_LIBRARIES ${SIPLUS_TEST_LIBRARIES} cpptrace::cpptrace)
    target_compile_definitions(runner PUBLIC SIPLUS_HAS_CPPTRACE)
endif()

target_link_libraries(runner PRIVATE siplus ${SIPLUS_TEST_LIBRARIES})
target_include_directories(runner PRIVATE ${CMAKE_SOURCE_DIR}/tests)


# Add all the ADD_TEST for each test
foreach (test ${TEST_SOURCES})
  get_filename_component (TName ${test} NAME_WE)
  add_test (NAME ${TName} COMMAND runner ${TName})
endforeach ()

if(SIPLUS_RUN_TESTS) 
    add_custom_command(TARGET runner
                       POST_BUILD
                       COMMAND ctest -C ${CONFIGURATION} --output-on-failure)
endif()
