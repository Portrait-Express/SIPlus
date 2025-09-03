#include <cpptrace/from_current.hpp>
#include <iostream>

#include "common.hxx"
#include "siplus/parser.h"
#include "siplus/text/data.h"

int test_expression(int, char**) {
    SIPlus::Parser parser = get_test_context();

    CPPTRACE_TRY {
        auto retriever = parser.get_expression(".x \"awd\"");
        retriever->retrieve(SIPlus::text::make_data(test_data{}));
    } CPPTRACE_CATCH(std::exception& e) {
        std::cout << e.what() << std::endl;
        cpptrace::from_current_exception().print();

        return 1;
    }

    return 0;
}
