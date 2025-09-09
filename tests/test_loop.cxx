#include <iostream>

#include "common.hxx"
#include "siplus/parser.h"

int test_loop(int, char**) {
    return test("Looping statement", [](const SIPlus::Parser& parser) {
        auto constructor = parser.get_interpolation("{# .users } Id { .id } is { .username } - { .email } {//}");
        std::cout << constructor.construct(test_data{}) << std::endl;

        return 0;
    });
}
