#include <iostream>

#include "common.hxx"
#include "siplus/parser.h"

int test_loop(int, char**) {
    return test("Looping statement", [](const SIPlus::Parser& parser) {
        return tests(
            test_interpolation(
                "{# .users } Id { .id } is { .username } - { .email } {//}",
                " Id 1 is root - root@example.com  Id 2 is Admin - admin@example.com ")
        );

        return 0;
    });
}
