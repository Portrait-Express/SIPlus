#include <algorithm>
#include <cassert>
#include <cfloat>
#include <vector>

#include "siplus/parser.h"
#include "siplus/text/data.h"

#include "common.hxx"

using namespace SIPLUS_NAMESPACE;

int test_add() {
    return test("add", [](const Parser& parser) {
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
    return test("str", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(".x | str", "2")
        );
    });
}

int test_map() {
    return test("map", [](const Parser& parser) {
        auto data = test_data{};

        auto expr = parser.get_expression(".users | map .id");
        auto val = expr->retrieve(text::make_data(test_data{}));

        if(!val.is<std::vector<text::UnknownDataTypeContainer>>()) {
            return 1;
        }

        const std::vector<text::UnknownDataTypeContainer>& vec = 
            val.as<std::vector<text::UnknownDataTypeContainer>>();

        if(!std::all_of(vec.begin(), vec.end(), [](text::UnknownDataTypeContainer val) {
            return val.is<int>();
        })) {
            return 1;
        }

        std::vector<int> result{};
        result.reserve(vec.size());

        std::transform(vec.begin(), vec.end(), std::back_inserter(result), 
                       [](text::UnknownDataTypeContainer val) {
            return val.as<int>();
        });

        return result == std::vector<int>{1, 2} ? 0 : 1;
    });
}

int test_length() {
    return test("length", [](const Parser& parser) {
        return tests(
            test_expression(". | length", std::vector{1,2,3}, 3L),
            test_expression(". | length", std::vector<int>{}, 0L),
            test_expression(". | length", std::vector<std::string>{"1"}, 1L),
            test_expression<long, std::string>(". | length", "Hello", 5L)
        );
    });
}

int test_join() {
    return test("join", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(R"(. | join ", ")", std::vector{1,2,3}, "1, 2, 3"),
            test_expression<std::string>(R"(. | join "some text")", std::vector<int>{}, ""),
            test_expression<std::string>(R"(. | join 2)", std::vector<std::string>{"1"}, "1")
        );
    });
}

int test_and() {
    return test("and", [](const Parser& parser) {
        return tests(
            test_expression("and true false", false),
            test_expression("and true true", true),
            test_expression("and false false", false)
        );
    });
}

int test_or() {
    return test("or", [](const Parser& parser) {
        return tests(
            test_expression("or true false", true),
            test_expression("or true true", true),
            test_expression("or false false", false)
        );
    });
}

int test_xor() {
    return test("xor", [](const Parser& parser) {
        return tests(
            test_expression("xor true false", true),
            test_expression("xor true true", false),
            test_expression("xor false false", false)
        );
    });
}

int test_not() {
    return test("not", [](const Parser& parser) {
        return tests(
            test_expression("not true", false),
            test_expression("not false", true)
        );
    });
}

int test_if() {
    return test("if", [](const Parser& parser) {
        auto value = parser.get_expression(R"(if .x .y "" | .b)");
        auto result = value->retrieve(text::make_data(test_data()));

        if(!result.is<short>()) return 1;
        if(result.as<short>() != 1) return 1;

        return 0;
    });
}

int test_replace() { 
    return test("replace", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(R"(replace "Hello" "e" "a")", "Hallo"),
            test_expression<std::string>(R"("test" | replace "test" "something")", "something"),
            test_expression<std::string>(R"(replace "AAAAAa" "A" "BA")", "BABABABABAa")
        );
    });
}

int test_padEnd() { 
    return test("padEnd", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(R"(padEnd "Hello" 8 "o")", "Helloooo"),
            test_expression<std::string>(R"(padEnd "Long Text" 2 "-")", "Long Text"),
            test_expression<std::string>(R"(padEnd "" 3 "0")", "000")
        );
    });
}

int test_padStart() { 
    return test("padStart", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(R"(padStart "2" 2 "0")", "02"),
            test_expression<std::string>(R"(padStart "Long Text" 2 "-")", "Long Text"),
            test_expression<std::string>(R"(padStart "" 3 "0")", "000")
        );
    });
}

int test_trim() { 
    return test("trim", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(R"("  test  " | trim)", "test"),
            test_expression<std::string>(R"("  " | trim)", ""),
            test_expression<std::string>(R"("test" | trim)", "test")
        );
    });
}

int test_upper() { 
    return test("upper", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(R"("Test" | upper)", "TEST"),
            test_expression<std::string>(R"("" | upper)", "")
        );
    });
}

int test_lower() { 
    return test("lower", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(R"("Test" | lower)", "test"),
            test_expression<std::string>(R"("" | lower)", "")
        );
    });
}

int test_split() { 
    return test("split", [](const Parser& parser) {
        using expected = std::vector<text::UnknownDataTypeContainer>;
        return tests(
            test_expression<std::vector<std::string>, expected>(R"("2.2.1" | split ".")", {"2", "2", "1"}),
            test_expression<std::vector<std::string>, expected>(R"("test" | split "")", {"t","e","s","t"}),
            test_expression<std::vector<std::string>, expected>(R"("banana and orange" | split " and ")", {"banana", "orange"}),
            test_expression<std::vector<std::string>, expected>(R"("" | split "value")", {""})
        );
    });
}

int test_substr() { 
    return test("substr", [](const Parser& parser) {
        return tests(
            test_expression<std::string>(R"("abcd" | substr 2 4)", "cd"),
            test_expression<std::string>(R"("Johnathan" | substr 4)", "athan")
        );
    });
}

int test_cmp() { 
    return test("cmp", [](const Parser& parser) {
        return tests(
            test_expression(R"(cmp 1 0)", 1L),
            test_expression(R"(cmp "a" "b")", -1L)
        );
    });
}

int test_lt() { 
    return test("lt", [](const Parser& parser) {
        return tests(
            test_expression(R"(lt 2 1)", false),
            test_expression(R"(lt "a" "b")", true)
        );
    });
}

int test_gt() { 
    return test("gt", [](const Parser& parser) {
        return tests(
            test_expression(R"(gt 1 2)", false),
            test_expression(R"(gt "b" "a")", true)
        );
    });
}

int test_eq() { 
    return test("eq", [](const Parser& parser) {
        return tests(
            test_expression(R"(eq 1 1)", true),
            test_expression(R"(eq "a" "b")", false),
            test_expression(R"(eq "1" 1)", true),
            test_expression(R"(eq 1 "1")", true)
        );
    });
}

int test_int_converter() {
    return test("int_converter", [](const Parser& parser) {
        stl::int_converter converter;

        return tests(
            test_conversion<stl::int_converter, short, long>(12, 12),
            test_conversion<stl::int_converter, int, long>(42, 42),
            test_conversion<stl::int_converter, long, long>(1337, 1337)
        );
    });
}

int test_float_converter() {
    return test("float_converter", [](const Parser& parser) {
        text::UnknownDataTypeContainer data = text::make_data<double>(2);
        stl::float_converter con;

        return tests(
            test_conversion<stl::float_converter, float, double>(1.124f, 1.124),
            test_conversion<stl::float_converter, double, double>(3.141f, 3.141)
        );
    });
}

int test_numeric_string_converter() {
    return test("numeric_string_converter", [](const Parser& parser) {
        stl::numeric_string_converter converter{parser.context().shared_from_this()};

        return tests(
            test_conversion<stl::numeric_string_converter, short, std::string>(converter, 1, "1"),
            test_conversion<stl::numeric_string_converter, int, std::string>(converter, 1, "1"),
            test_conversion<stl::numeric_string_converter, long, std::string>(converter, 1, "1"),
            test_conversion<stl::numeric_string_converter, float, std::string>(converter, 1, "1"),
            test_conversion<stl::numeric_string_converter, double, std::string>(converter, 1, "1")
        );
    });
}

int test_numeric_bool_converter() {
    return test("numeric_bool_converter", [](const Parser& parser) {
        stl::numeric_bool_converter converter{parser.context().shared_from_this()};

        return tests(
            test_conversion<stl::numeric_bool_converter, short, bool>(converter, 1, true),
            test_conversion<stl::numeric_bool_converter, int, bool>(converter, 0, false),
            test_conversion<stl::numeric_bool_converter, long, bool>(converter, 11212521L, true),
            test_conversion<stl::numeric_bool_converter, long, bool>(converter, 0, false),
            test_conversion<stl::numeric_bool_converter, float, bool>(converter, 1.3, true),
            test_conversion<stl::numeric_bool_converter, double, bool>(converter, 0, false)
        );
    });
}

int test_string_bool_converter() {
    return test("string_bool_converter", [](const Parser& parser) {
        return tests(
            test_conversion<stl::string_bool_converter, std::string, bool>(" ", true),
            test_conversion<stl::string_bool_converter, std::string, bool>("Hello, World", true),
            test_conversion<stl::string_bool_converter, std::string, bool>("", false)
        );
    });
}

int test_bool_string_converter() {
    return test("bool_string_converter", [](const Parser& parser) {
        return tests(
            test_conversion<stl::bool_string_converter, bool, std::string>(true, "true"),
            test_conversion<stl::bool_string_converter, bool, std::string>(false, "false")
        );
    });
}

int test_functions() {
    return group("functions", []() {
        return tests(
            test_str(),
            test_if(),

            test_add(),

            test_length(),
            test_join(),
            test_map(),

            test_and(),
            test_xor(),
            test_or(),
            test_not(),

            test_replace(),
            test_padEnd(),
            test_padStart(),
            test_trim(),
            test_lower(),
            test_upper(),
            test_split(),
            test_substr(),

            test_cmp(),
            test_lt(),
            test_gt(),
            test_eq()
        );
    });
}


int test_converters() {
    return group("converters", []() {
        return tests(
            test_int_converter(),
            test_float_converter(),
            test_numeric_string_converter(),
            test_numeric_bool_converter(),
            test_string_bool_converter(),
            test_bool_string_converter()
        );
    });
}

int test_stdlib(int, char**) {
    auto ctx = get_test_context().context().shared_from_this();
    auto res = group("stdlib", []() {
        return tests(
            test_functions(),
            test_converters()
        );
    });
    return res;
}
