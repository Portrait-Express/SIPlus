#include <cpptrace/from_current.hpp>
#include <iostream>

#include "common.hxx"
#include "siplus/parser.h"

int test_interpolate(int, char**) {
    SIPlus::Parser parser = test_context();

    CPPTRACE_TRY {
        auto constructor = parser.get_interpolation("TEST { .x } HELLO");
        std::cout << constructor.construct(test_data{}) << std::endl;
    } CPPTRACE_CATCH(std::exception& e) {
        std::cout << e.what() << std::endl;
        cpptrace::from_current_exception().print();

        return 1;
    }

    return 0;
}
