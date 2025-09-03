#include <cpptrace/from_current.hpp>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include "common.hxx"
#include "siplus/parser.h"
#include "siplus/text/data.h"

int test_expression(int, char**) {
    return test([](const SIPlus::Parser& parser) {
        try {
            auto retriever = parser.get_expression(".x \"awd\"");
            auto data = SIPlus::text::make_data(test_data{});
            retriever->retrieve(data);
            std::cout << "'.x \"awd\"' did not throw" << std::endl;
            return 1;
        } catch(const std::runtime_error& e) {
            std::string err{"line 1:3 mismatched input '\"' expecting <EOF>"};
            if(strcmp(err.c_str(), e.what())) {
                std::cout << "incorrect error message thrown. \nExpected:" << err
                    << "\nGot: " << e.what() << std::endl;
                    
                return 1;
            }
        }

        return 0;
    });
}
