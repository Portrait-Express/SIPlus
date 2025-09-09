#include "common.hxx"
#include "siplus/text/data.h"
#include <algorithm>
#include <iostream>

int test_add() {
    return test("add", [](const SIPlus::Parser& parser) {
        auto expr = parser.get_expression("add .x .y.b");
        auto val = expr->retrieve(SIPlus::text::make_data(test_data{}));
        return (val.is<long>() && val.as<long>() == 3) ? 0 : 1;
    });
}

int test_str() {
    return test("str", [](const SIPlus::Parser& parser) {
        auto expr = parser.get_expression(".x | str");
        auto val = expr->retrieve(SIPlus::text::make_data(test_data{}));
        return (val.is<std::string>() && val.as<std::string>() == "2") ? 0 : 1;
    });
}

int test_map() {
    return test("map", [](const SIPlus::Parser& parser) {
        auto data = test_data{};

        auto expr = parser.get_expression(".users | map .id");
        auto val = expr->retrieve(SIPlus::text::make_data(test_data{}));

        if(!val.is<std::vector<SIPlus::text::UnknownDataTypeContainer>>()) {
            return 1;
        }

        const std::vector<SIPlus::text::UnknownDataTypeContainer>& vec = 
            val.as<std::vector<SIPlus::text::UnknownDataTypeContainer>>();

        if(!std::all_of(vec.begin(), vec.end(), [](SIPlus::text::UnknownDataTypeContainer val) {
            return val.is<int>();
        })) {
            return 1;
        }

        std::vector<int> result{};
        result.reserve(vec.size());

        std::transform(vec.begin(), vec.end(), std::back_inserter(result), 
                       [](SIPlus::text::UnknownDataTypeContainer val) {
               std::cout << val.as<int>() << std::endl;
            return val.as<int>();
        });

        return result == std::vector<int>{1, 2} ? 0 : 1;
    });
}

int test_functions() {
    return group("functions", []() {
        return tests(
            test_add(),
            test_str(),
            test_map()
        );
    });
}

int test_stdlib(int, char**) {
    return group("stdlib", []() {
        return tests(
            test_functions()
        );
    });
}

