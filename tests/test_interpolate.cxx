#include <cpptrace/from_current.hpp>
#include <iostream>

#include "common.hxx"
#include "siplus/parser.h"

int test_interpolate(int, char**) {
    return test("String Interpolation", [](const SIPLUS_NAMESPACE::Parser& parser) {
        std::string expected{"TEST 2 HELLO"};
        auto constructor = parser.get_interpolation("TEST { .x } HELLO");
        std::string text = constructor.construct_with(SIPLUS_NAMESPACE::text::make_data(test_data{}));

        if(text == expected) {
            return 0;
        } else {
            std::cout << "Expected: " << expected << "\nGot: " << text << std::endl;
            return 1;
        }
    });
}
