#include <cassert>
#include <iostream>
#include <vector>

#include "siplus/context.hxx"
#include "siplus/parser.hxx"
#include "siplus/stl/functions/dictionary.hxx"
#include "siplus/stl/functions/pair.hxx"
#include "testing.hxx"

using namespace SIPLUS_NAMESPACE;

CATEGORY(Stdlib);

CATEGORY_SUB(Functions, Stdlib);

TEST(Add, Functions) {
    expect::expression("add (.x) (.y.b)", 3L);
    expect::expression("add .x 2.3", 4.3);
    expect::expression(R"(add .x "ab")", "2ab");
    expect::expression(R"(add "a" "b")", "ab");
    expect::expression(R"("a" | add "b")", "ab");
}

TEST(Sub, Functions) {
    expect::expression("sub 1.2 2", -0.8);
    expect::expression("sub 10 4", 6L);
}

TEST(Multiply, Functions) {
    expect::expression("mul 2 3", 6L);
    expect::expression("mul 2.2 5", 11.0);
}

TEST(Div, Functions) {
    expect::expression("div 6 2", 3.0);
    expect::expression("div 10 4", 2.5);
}

TEST(Str, Functions) {
    expect::expression(".x | str", "2");
}

TEST(Map, Functions) {
    expect::expression(R"(.users | map .id)", std::vector<int>{1,2});
}

TEST(Length, Functions) {
    expect::expression(". | length", 3L, std::vector{1,2,3});
    expect::expression(". | length", 1L, std::vector<std::string>{"1"});
    expect::expression(". | length", 5L, "Hello");
}

TEST(Join, Functions) {
    expect::expression(R"(. | join ", ")", "1, 2, 3", std::vector{1,2,3});
    expect::expression(R"(. | join "some text")", "", std::vector<int>{});
    expect::expression(R"(. | join " ")", "1", std::vector<std::string>{"1"});
}

TEST(Contains, Functions) {
    expect::expression(R"([1,2,3] | contains 2)", true);
    expect::expression(R"([1,2,3] | contains 4)", false);
    expect::expression(R"(["apple", "banana", "cherry"] | contains "apple")", true);
}

TEST(Each, Functions) {
    expect::expression(R"(var $set = set_new; [1, 2, 3] | each (set_add $set .); set_has $set 2)", true);
}

TEST(Find, Functions) {
    expect::expression(R"([1, 2, 3] | find (eq . 2))", 2);
    expect::expression(R"(.users | find (eq .id 2) | .email)", "admin@example.com");
}

TEST(Filter, Functions) {
    expect::expression(R"([1, 2, 3] | filter (eq . 2))", std::vector<long>{2});
    expect::expression(R"(.users | filter (true) | map .id)", std::vector<long>{1, 2});
    expect::expression(R"(.users | filter (false))", std::vector<User>{});
}

TEST(All, Functions) {
    expect::expression(R"([false, true, true] | all .)", false);
    expect::expression(R"([true, true, true] | all .)", true);
}

TEST(Any, Functions) {
    expect::expression(R"([false, true, true] | any .)", true);
    expect::expression(R"([false, false, false] | any .)", false);
}

TEST(Sort, Functions) {
    expect::expression(R"([1, 2, 3] | sort (sub .[0] .[1]))", std::vector<int>{1, 2, 3});
    expect::expression(R"([2, 4, 1, 6, 3, 7, 5, 2] | sort (sub .[0] .[1]))", std::vector<int>{1, 2, 2, 3, 4, 5, 6, 7});
}

TEST(And, Functions) {
    expect::expression("and true false", false);
    expect::expression("and true true", true);
    expect::expression("and false false", false);
}

TEST(Or, Functions) {
    expect::expression("not true", false);
    expect::expression("not false", true);
}

TEST(RandStr, Functions) {
    auto first = do_expression(R"(randstr "0123456789abcdef" 3)");
    auto second = do_expression(R"(randstr "abcdefghijklmnopqrstuvwxyz" 12)");

    expect::expect(first.is<types::StringType>() && first.as<types::StringType>().length() == 3,
                  "Expected randstr to generate a string of length 3");

    expect::expect(second.is<types::StringType>() && second.as<types::StringType>().length() == 12,
                  "Expected randstr to generate a string of length 12, generated "
                   + std::to_string(second.as<types::StringType>().length()));
}

TEST(If, Functions) {
    expect::expression(R"(if (.x) (.y) "" | .b)", 1);
    expect::expression(R"(if (null) (.y) (4))", 4);
}

TEST(While, Functions) {
    expect::expression(R"(var $v = 0; while (lt $v 3) ($v = add $v 1; 0); $v)", 3);
    expect::expression(R"(while false 12 | and true)", false);
}

TEST(Type, Functions) {
    expect::expression(R"(2 | type)", "long");
    expect::expression(R"(2.4 | type)", "double");
    expect::expression(R"(false | type)", "boolean");
    expect::expression(R"([1,2] | type)", "array");
    expect::expression(R"(null | type)", "null");
}

TEST(Replace, Functions) {
    expect::expression(R"(replace "Hello" "e" "a")", "Hallo");
    expect::expression(R"("test" | replace "test" "something")", "something");
    expect::expression(R"(replace "AAAAAa" "A" "BA")", "BABABABABAa");
}

TEST(PadEnd, Functions) {
    expect::expression<std::string>(R"(padEnd "Hello" 8 "o")", "Helloooo");
    expect::expression(R"(padEnd "Long Text" 2 "-")", "Long Text");
    expect::expression(R"(padEnd "" 3 "0")", "000");
}

TEST(PadStart, Functions) {
    expect::expression(R"(padStart "2" 2 "0")", "02");
    expect::expression(R"(padStart "Long Text" 2 "-")", "Long Text");
    expect::expression(R"(padStart "" 3 "0")", "000");
}

TEST(Trim, Functions) {
    expect::expression(R"("  test  " | trim)", "test");
    expect::expression(R"("  " | trim)", "");
    expect::expression(R"("test" | trim)", "test");
}

TEST(Upper, Functions) {
    expect::expression(R"("Test" | upper)", "TEST");
    expect::expression(R"("" | upper)", "");
}

TEST(Lower, Functions) {
    expect::expression(R"("Test" | lower)", "test");
    expect::expression(R"("" | lower)", "");
}

TEST(Split, Functions) {
    expect::expression(R"("2.2.1" | split ".")", std::vector<std::string>{"2", "2", "1"});
    expect::expression(R"("test" | split "")", std::vector<std::string>{"t","e","s","t"});
    expect::expression(R"("banana and orange" | split " and ")", std::vector<std::string>{"banana", "orange"});
    expect::expression(R"("" | split "value")", std::vector<std::string>{""});
}

TEST(Substr, Functions) {
    expect::expression(R"("abcd" | substr 2 4)", "cd");
    expect::expression(R"("Johnathan" | substr 4)", "athan");
}

TEST(Cmp, Functions) {
    expect::expression(R"(cmp 1 0)", 1L);
    expect::expression(R"(cmp "a" "b")", -1L);
}

TEST(Lt, Functions) {
    expect::expression(R"(lt 2 1)", false);
    expect::expression(R"(lt "a" "b")", true);
}

TEST(Lte, Functions) {
    expect::expression(R"(1 | lte 2)", true);
    expect::expression(R"(2 | lte 2)", true);
    expect::expression(R"(3 | lte 2)", false);
}

TEST(Gt, Functions) {
    expect::expression(R"(gt 1 2)", false);
    expect::expression(R"(gt "b" "a")", true);
}

TEST(Gte, Functions) {
    expect::expression(R"(1 | gte 2)", false);
    expect::expression(R"(2 | gte 2)", true);
    expect::expression(R"(3 | gte 2)", true);
}

TEST(Eq, Functions) {
    expect::expression(R"(eq 1 1)", true);
    expect::expression(R"(eq "a" "b")", false);
    expect::expression(R"(eq 1.0 1)", true);
    expect::expression(R"(eq 1 1.0)", true);
}

/**
 * @brief Tests all set-related functions.
 */
TEST(Set, Functions) {
    Parser parser;

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

    //Test for no default data. This was causing variable 0 not defined earlier.
    expr = parser.get_expression(
        "const var $s = set_new; set_add $s 1; set_add $s 2; set_add $s 2; $s | map .", 
        ParseOpts{});

    ctx = parser.context().builder().build();
    value = expr->retrieve(*ctx);

    expect::expression(R"(set_new | set_add 143 | set_has 143)", true);
    expect::expression(R"(set_new | set_add 143 | set_add "test" | set_has 420)", false);
    expect::expression(R"(set_new | set_add "test" | set_add 143 | set_has "test")", true);
    expect::expression(R"(set_new | set_add "test" | set_add 143 | set_has "test")", true);
    expect::expression(R"(set_new | set_add "test" | set_add 143 | map (1) | length)", 2);
    expect::expression(R"(
                    var $set = set_new;
                    var $i = 0;
                    while (lt $i 10) (
                        set_add $set $i;
                        $i = add $i 1; 0
                    );
                    set_has $set 5
                    )", true);
}

TEST(Pair, Functions) {
    expect::expression(R"(pair 1 2)", std::pair<long, long>{1, 2});
    expect::expression(R"(pair 1 2 | .first)", 1);
    expect::expression(R"(pair 1 2 | .second)", 2);
}

TEST(Dictionary, Functions) {
    expect::expression(R"(dict_new; 1)", 1);
    expect::expression(R"(dict_new | dict_set 1 "John" | dict_get 1)", "John");
    expect::expression(R"(dict_new | dict_set 1 "John" | dict_has 1)", true);
    expect::expression(R"(dict_new | dict_set 1 "John" | dict_has 2)", false);
    expect::expression(R"(dict_new | dict_set 1 "John" | length)", 1);
    expect::expression(R"(dict_new | dict_set 1 "John" | dict_set 2 "Jane" | length)", 2);

    auto keys = do_expression(R"(dict_new | dict_set 1 "John" | dict_set 2 "Jane" | dict_keys)");
    auto values = do_expression(R"(dict_new | dict_set 1 "John" | dict_set 2 "Jane" | dict_values)");

    keys.assert_type<types::ArrayType>("<dict_keys result>");
    values.assert_type<types::ArrayType>("<dict_values result>");

    expect::unordered_elements(
        std::vector<long>{1, 2}, 
        keys.as<types::ArrayType>()
    );
    expect::unordered_elements(
        std::vector<std::string>{"John", "Jane"}, 
        values.as<types::ArrayType>()
    );
}


CATEGORY_SUB(Converters, Stdlib);

TEST(IntegerString, Converters) {
    expect::conversion<types::StringType>(1, std::string{"1"});
    expect::conversion<types::StringType>(1.4, std::string{"1.4"});
}

TEST(IntegerBool, Converters) {
    test_conversion<types::BoolType>(1, true);
    test_conversion<types::BoolType>(0, false);
    test_conversion<types::BoolType>(11212521L, true);
    test_conversion<types::BoolType>(0, false);
    test_conversion<types::BoolType>(1.3, true);
    test_conversion<types::BoolType>(0, false);
}

TEST(StringBool, Converters) {
    test_conversion<types::BoolType>(" ", true);
    test_conversion<types::BoolType>("Hello, World", true);
    test_conversion<types::BoolType>("", false);
}

TEST(BoolString, Converters) {
    test_conversion<types::StringType>(true, "true");
    test_conversion<types::StringType>(false, "false");
}

TEST(DictionaryString, Converters) {
    auto val = make_data<stl::DictionaryType>({
        { make_data(1), make_data("Jane") }
    });

    test_conversion<types::StringType>(val, "{ { 1, Jane } }");
}



TEST(Misc, Stdlib) {
    expect::expression(
        R"(
        var $i = 0; 
        var $str = "a"; 
        while (lt $i 3) ( 
            $i = add $i 1; 
            $str = add $str "a"; 
            $str
        ))", 
        "aaaa");
}



int test_stdlib(int, char** const) {
    auto result = RUN_CATEGORY(Stdlib);
    std::cout << result << std::endl;

    return result.passed() ? 0 : 1;
}
