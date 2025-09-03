#include <iostream>

#include "common.hxx"
#include "siplus/parser.h"

int test_function(int, char**) {
    return test([](const SIPlus::Parser& parser) {
        auto constructor = parser.get_interpolation("{# .users } Idx2= { add .id 2 } is { add .id  \": \" .username \" - \" .email }\n{//}");
        std::cout << constructor.construct(test_data{}) << std::endl;

        return 0;
    });
}
