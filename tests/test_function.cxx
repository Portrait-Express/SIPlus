#include <iostream>

#include "common.hxx"
#include "siplus/parser.h"

int test_function(int, char**) {
    return test("Functions", [](const SIPlus::Parser& parser) {
        auto constructor = parser.get_interpolation("{# .users }Id+2={ add .id 5 }, {//}");
        std::string expected{"Id+2=6, Id+2=7, "};
        std::string text = constructor.construct(test_data{});
        if(text == expected) {
            return 0;
        } else { 
            std::cout << "Invalid result. \nExpected: " << expected << 
                "\nGot: " << text << std::endl;

            return 1;
        }
    });
}
