#include "common.hxx"
#include "siplus/parser.h"

int test_interpolate(int, char**) {
    return test("String Interpolation", [](const SIPLUS_NAMESPACE::Parser& parser) {
        return tests(
            test_interpolation("TEST { .x } HELLO", "TEST 2 HELLO")
        );
    });
}
