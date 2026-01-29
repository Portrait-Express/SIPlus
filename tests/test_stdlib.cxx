#include <cassert>
#include <cfloat>
#include <vector>

#include "siplus/parser.hxx"

#include "common.hxx"
#include "siplus/types/array.hxx"
#include "siplus/types/float.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"

using namespace SIPLUS_NAMESPACE;

int test_add() {
    return test("add", [](const Parser& parser) {
        return tests(
            test_expression("add .x .y.b", 3L),
            test_expression("add .x 2.3", 4.3),
            test_expression(R"(add .x "ab")", "2ab"),
            test_expression(R"(add "a" "b")", "ab"),
            test_expression(R"("a" | add "b")", "ab")
        );
    });
}

int test_sub() {
    return test("sub", [](const Parser& parser) {
        return tests(
            test_expression("sub 1.2 2", -0.8),
            test_expression("sub 10 4", 6L)
        );
    });
}

int test_mul() {
    return test("mul", [](const Parser& parser) {
        return tests(
            test_expression("mul 2 3", 6L),
            test_expression("mul 2.2 5", 11.0)
        );
    });
}

int test_div() {
    return test("div", [](const Parser& parser) {
        return tests(
            test_expression("div 6 2", 3.0),
            test_expression("div 10 4", 2.5)
        );
    });
}

int test_str() {
    return test("str", [](const Parser& parser) {
        return tests(
            test_expression(".x | str", "2")
        );
    });
}

int test_map() {
    return test("map", [](const Parser& parser) {
        return tests(
            test_expression<types::ArrayType, std::vector<int>>(R"(.users | map .id)", {1,2})
        );
    });
}

int test_length() {
    return test("length", [](const Parser& parser) {
        return tests(
            test_expression<types::IntegerType>(". | length", std::vector{1,2,3}, 3L),
            test_expression<types::IntegerType>(". | length", std::vector<int>{}, 0L),
            test_expression<types::IntegerType>(". | length", std::vector<std::string>{"1"}, 1L),
            test_expression<types::IntegerType>(". | length", "Hello", 5L)
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

int test_contains() {
    return test("contains", [](const Parser& parser) {
        return tests(
            test_expression(R"([1,2,3] | contains 2)", true),
            test_expression(R"([1,2,3] | contains 4)", false),
            test_expression(R"(["apple", "banana", "cherry"] | contains "apple")", true)
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

int test_rand() {
    return test("rand", [](const Parser& parser) {
        return tests(
            test_expression<types::FloatType>(
                "rand", 
                [](const double& v) { return v > 0 && v < 1; }
            ),
            test_expression<types::IntegerType>(
                "rand 1 3", 
                [](const long& v) { return v >= 1 && v <= 3; }
            )
        );
    });
}

int test_rand_str() {
    return test("randstr", [](const Parser &parser) {
        return tests(
            test_expression<types::StringType, std::function<bool (const std::string&)>>(
                R"(randstr "0123456789abcdef" 3)", 
                [](const std::string &v) { return v.length() == 3; }
            ),
            test_expression<types::StringType, std::function<bool (const std::string&)>>(
                R"(randstr "abcdefghijklmnopqrstuvwxyz" 12)", 
                [](const std::string &v) { return v.length() == 12; }
            )
        );
    });
}

int test_if() {
    return test("if", [](const Parser& parser) {
        return tests(
            test_expression<short>(R"(if .x .y "" | .b)", 1)
        );
    });
}

int test_while() {
    return test("while", [](const Parser& parser) {
        return tests(
            test_expression<long>(R"(var $v = 0; while (lt $v 3) ($v = add $v 1; 0); $v)", 3)
        );
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
        return tests(
            test_expression<types::ArrayType, std::vector<std::string>>(R"("2.2.1" | split ".")", {"2", "2", "1"}),
            test_expression<types::ArrayType, std::vector<std::string>>(R"("test" | split "")", {"t","e","s","t"}),
            test_expression<types::ArrayType, std::vector<std::string>>(R"("banana and orange" | split " and ")", {"banana", "orange"}),
            test_expression<types::ArrayType, std::vector<std::string>>(R"("" | split "value")", {""})
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

/**
 * @brief Tests all set-related functions.
 */
int test_set() {
    return test("set", [](const Parser& parser) {
        auto expr = parser.get_expression(
            "persist var $set = set_new; set_add $set .; set_has $set 5", 
            ParseOpts{});

        auto ctx = parser.context().builder().use_default(make_data<std::string>("test")).build();
        auto value = expr->retrieve(*ctx);
        expect_equal<types::BoolType>(value, false);

        ctx = parser.context().builder().use_default(make_data(5)).build();
        value = expr->retrieve(*ctx);
        expect_equal<types::BoolType>(value, true);

        ctx = parser.context().builder().use_default(make_data(7)).build();
        value = expr->retrieve(*ctx);
        expect_equal<types::BoolType>(value, true);

        return tests(
            test_expression(R"(set_new | set_add 143 | set_has 143)", true),
            test_expression(R"(set_new | set_add 143 | set_add "test" | set_has 420)", false),
            test_expression(R"(set_new | set_add "test" | set_add 143 | set_has "test")", true),
            test_expression(R"(
                            var $set = set_new;
                            var $i = 0;
                            while (lt $i 10) (
                                set_add $set $i;
                                $i = add $i 1; 0
                            );
                            set_has $set 5
                            )", true)
        );
    });
}

int test_numeric_string_converter() {
    return test("numeric_string_converter", [](const Parser& parser) {
        return tests(
            test_conversion<stl::numeric_string_converter>(1, std::string{"1"}),
            test_conversion<stl::numeric_string_converter>(1.4, std::string{"1.4"})
        );
    });
}

int test_numeric_bool_converter() {
    return test("numeric_bool_converter", [](const Parser& parser) {
        return tests(
            test_conversion<stl::numeric_bool_converter>(1, true),
            test_conversion<stl::numeric_bool_converter>(0, false),
            test_conversion<stl::numeric_bool_converter>(11212521L, true),
            test_conversion<stl::numeric_bool_converter>(0, false),
            test_conversion<stl::numeric_bool_converter>(1.3, true),
            test_conversion<stl::numeric_bool_converter>(0, false)
        );
    });
}

int test_string_bool_converter() {
    return test("string_bool_converter", [](const Parser& parser) {
        return tests(
            test_conversion<stl::string_bool_converter, std::string>(" ", true),
            test_conversion<stl::string_bool_converter, std::string>("Hello, World", true),
            test_conversion<stl::string_bool_converter, std::string>("", false)
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
            test_while(),

            test_set(),

            test_add(),
            test_sub(),
            test_mul(),
            test_div(),

            test_length(),
            test_join(),
            test_map(),

            test_and(),
            test_xor(),
            test_or(),
            test_not(),

            test_rand(),
            test_rand_str(),

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
            test_converters(),
            test("Misc", [](const Parser& parser) {
                return tests(
                    test_expression<std::string>(
                        R"(
                        var $i = 0; 
                        var $str = "a"; 
                        while (lt $i 3) ( 
                            $i = add $i 1; 
                            $str = add $str "a"; 
                            $str
                        ))", 
                        "aaaa")
                );
            })
        );
    });
    return res;
}
