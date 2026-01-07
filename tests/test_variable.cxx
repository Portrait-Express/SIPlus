#include "common.hxx"
#include "siplus/parser.h"

int test_variable(int, char**) {
    return test("Variables", [](const SIPLUS_NAMESPACE::Parser& parser) {
        return tests(
            test_interpolation("TEST { $A = 2; $A } HELLO", "TEST 2 HELLO")
        );
    });
}
