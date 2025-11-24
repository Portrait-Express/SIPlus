#include <cstring>

#include "common.hxx"
#include "siplus/parser.h"

int test_expression(int, char**) {
    return test("Expression", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<int>(".x", 2)
        );
    });
}
