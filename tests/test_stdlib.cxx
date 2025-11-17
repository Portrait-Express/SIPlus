#include <algorithm>
#include <cassert>
#include <cfloat>

#include "siplus/parser.h"
#include "siplus/stl/converters/numeric.h"
#include "siplus/text/data.h"

#include "common.hxx"

int test_add() {
    return test("add", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression("add .x .y.b", 3L),
            test_expression("add .x 2.3", 4.3),
            test_expression<std::string>(R"(add .x "ab")", "2ab"),
            test_expression<std::string>(R"(add "a" "b")", "ab"),
            test_expression<std::string>(R"("a" | add "b")", "ab")
        );
    });
}

int test_str() {
    return test("str", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<std::string>(".x | str", "2")
        );
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
            return val.as<int>();
        });

        return result == std::vector<int>{1, 2} ? 0 : 1;
    });
}

int test_and() {
    return test("and", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression("and true false", false),
            test_expression("and true true", true),
            test_expression("and false false", false)
        );
    });
}

int test_or() {
    return test("or", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression("or true false", true),
            test_expression("or true true", true),
            test_expression("or false false", false)
        );
    });
}

int test_xor() {
    return test("xor", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression("xor true false", true),
            test_expression("xor true true", false),
            test_expression("xor false false", false)
        );
    });
}

int test_if() {
    return test("if", [](const SIPlus::Parser& parser) {
        auto value = parser.get_expression("if .x .y \"\" | .b");
        auto result = value->retrieve(SIPlus::text::make_data(test_data()));

        if(!result.is<short>()) return 1;
        if(result.as<short>() != 1) return 1;

        return 0;
    });
}

int test_replace() { 
    return test("replace", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<std::string>(R"(replace "Hello" "e" "a")", "Hallo"),
            test_expression<std::string>(R"("test" | replace "test" "something")", "something"),
            test_expression<std::string>(R"(replace "AAAAAa" "A" "BA")", "BABABABABAa")
        );
    });
}

int test_padEnd() { 
    return test("padEnd", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<std::string>(R"(padEnd "Hello" 8 "o")", "Helloooo"),
            test_expression<std::string>(R"(padEnd "Long Text" 2 "-")", "Long Text"),
            test_expression<std::string>(R"(padEnd "" 3 "0")", "000")
        );
    });
}

int test_padStart() { 
    return test("padStart", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<std::string>(R"(padStart "2" 2 "0")", "02"),
            test_expression<std::string>(R"(padStart "Long Text" 2 "-")", "Long Text"),
            test_expression<std::string>(R"(padStart "" 3 "0")", "000")
        );
    });
}

int test_trim() { 
    return test("trim", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<std::string>(R"("  test  " | trim)", "test"),
            test_expression<std::string>(R"("  " | trim)", ""),
            test_expression<std::string>(R"("test" | trim)", "test")
        );
    });
}

int test_upper() { 
    return test("upper", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<std::string>(R"("Test" | upper)", "TEST"),
            test_expression<std::string>(R"("" | upper)", "")
        );
    });
}

int test_lower() { 
    return test("lower", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<std::string>(R"("Test" | lower)", "test"),
            test_expression<std::string>(R"("" | lower)", "")
        );
    });
}

int test_int_converter() {
    return test("int_converter", [](const SIPlus::Parser& parser) {
        SIPlus::stl::int_converter converter;

        return tests(
            test_conversion<SIPlus::stl::int_converter, short, long>(12, 12),
            test_conversion<SIPlus::stl::int_converter, int, long>(42, 42),
            test_conversion<SIPlus::stl::int_converter, long, long>(1337, 1337)
        );
    });
}

int test_float_converter() {
    return test("float_converter", [](const SIPlus::Parser& parser) {
        SIPlus::text::UnknownDataTypeContainer data = SIPlus::text::make_data<double>(2);
        SIPlus::stl::float_converter con;

        return tests(
            test_conversion<SIPlus::stl::float_converter, float, double>(1.124f, 1.124),
            test_conversion<SIPlus::stl::float_converter, double, double>(3.141f, 3.141)
        );
    });
}

int test_numeric_string_converter() {
    return test("numeric_string_converter", [](const SIPlus::Parser& parser) {
        SIPlus::stl::numeric_string_converter converter;

        return tests(
            test_conversion<SIPlus::stl::numeric_string_converter, short, std::string>(1, "1"),
            test_conversion<SIPlus::stl::numeric_string_converter, int, std::string>(1, "1"),
            test_conversion<SIPlus::stl::numeric_string_converter, long, std::string>(1, "1"),
            test_conversion<SIPlus::stl::numeric_string_converter, float, std::string>(1, "1"),
            test_conversion<SIPlus::stl::numeric_string_converter, double, std::string>(1, "1")
        );
    });
}

int test_numeric_bool_converter() {
    return test("numeric_bool_converter", [](const SIPlus::Parser& parser) {
        return tests(
            test_conversion<SIPlus::stl::numeric_bool_converter, short, bool>(1, true),
            test_conversion<SIPlus::stl::numeric_bool_converter, int, bool>(0, false),
            test_conversion<SIPlus::stl::numeric_bool_converter, long, bool>(11212521L, true),
            test_conversion<SIPlus::stl::numeric_bool_converter, long, bool>(0, false),
            test_conversion<SIPlus::stl::numeric_bool_converter, float, bool>(1.3, true),
            test_conversion<SIPlus::stl::numeric_bool_converter, double, bool>(0, false)
        );
    });
}

int test_functions() {
    return group("functions", []() {
        return tests(
            test_add(),
            test_str(),
            test_map(),
            test_if(),
            test_and(),
            test_xor(),
            test_or(),
            test_replace(),
            test_padEnd(),
            test_padStart(),
            test_trim(),
            test_lower(),
            test_upper()
        );
    });
}


int test_converters() {
    return group("converters", []() {
        return tests(
            test_int_converter(),
            test_float_converter(),
            test_numeric_string_converter(),
            test_numeric_bool_converter()
        );
    });
}

int test_stdlib(int, char**) {
    return group("stdlib", []() {
        return tests(
            test_functions(),
            test_converters()
        );
    });
}

