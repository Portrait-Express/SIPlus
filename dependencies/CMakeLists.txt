set(ANTLR_BUILD_CPP_TESTS Off)
set(ANTLR_BUILD_SHARED Off)
set(ANTLR_BUILD_STATIC On)
set(DISABLE_WARNINGS On)

add_subdirectory(antlr4/runtime/Cpp)
add_custom_target(LICENSE.antlr4.txt ALL cp "${CMAKE_CURRENT_SOURCE_DIR}/antlr4/LICENSE.txt" "LICENSE.antlr4.txt")
