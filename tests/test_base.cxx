#include <cstring>

#include "common.hxx"
#include "siplus/parser.hxx"
#include "siplus/types/array.hxx"
#include "siplus/types/float.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"

using namespace SIPLUS_NAMESPACE;

int test_base(int, char**) {
    return tests(
        group("Expression", [](const Parser& parser) {
            return tests(
                test("Accessor", [](const Parser& parser) {
                    return tests(
                        test_expression<types::IntegerType>(".x", 2)
                    );
                }),
                group("Variables", [](const Parser& parser) {
                    auto extra = make_data<test_data_type>(test_data{});

                    return tests(
                        test_expression<types::IntegerType>("var $A = (.x); $A", 2),
                        test_expression<types::IntegerType>("var $A = 123; $A", 123),
                        test_expression<types::IntegerType>("var $A = 123; $A = 234; $A", 234),
                        test_expression<types::IntegerType>("$extra.x", 2, {{"extra", extra}}),
                        test("const", [](const Parser& parser) {
                            return tests(
                                test_expression<types::IntegerType>("const var $A = (.x); $A", 2),
                                expect_throw([&]() {
                                    parser.get_expression("const var $a = 2; $a = 5; $a", ParseOpts{});
                                })
                            );
                        }),
                        test("persist", [](const Parser& parser) {
                            auto retriever = parser.get_expression("persist const var $A = rand; $A", ParseOpts{});
                            auto ctx = parser.context().builder().use_default(UnknownDataTypeContainer{}).build();
                            auto v1 = retriever->retrieve(*ctx);
                            ctx = parser.context().builder().use_default(UnknownDataTypeContainer{}).build();
                            auto v2 = retriever->retrieve(*ctx);

                            bool persisted = v1.is<types::FloatType>() && v2.is<types::FloatType>() 
                                && v1.as<types::FloatType>() == v2.as<types::FloatType>();

                            return tests(
                                persisted ? 0 : 1,
                                test_expression<types::IntegerType>("persist const var $A = (.x); $A", 2),
                                expect_throw([&]() {
                                    parser.get_expression("const var $a = 2; $a = 5; $a", ParseOpts{});
                                })
                            );
                        })
                    );
                }),
                test("Functions", [](const Parser& parser) {
                    return tests(
                        test_expression<types::IntegerType>("@test => ( 2 ); @test", 2),
                        test_expression<types::IntegerType>("@test(val) => ( $val.x ); @test .", 2)
                    );
                }),
                test("Scope", [](const Parser& parser) {
                    return tests(
                        expect_throw([](){
                            test_expression<types::IntegerType>("@test => ( @a => (2); @a ); @a", 2);
                        }),
                        expect_throw([](){
                            test_expression<types::IntegerType>("@test => ( $a = 2; $a ); $a", 2);
                        })
                    );
                }),
                test("Arrays", [](const Parser& parser) {
                    auto a = make_data<std::string>("test");

                    return tests(
                        test_expression<types::ArrayType, std::vector<long>>(R"([1,2,3])", {1,2,3}),
                        test_expression<types::ArrayType, std::vector<std::string>>(R"(["hello", "test"])", {"hello", "test"}),
                        test_expression<types::StringType>(R"(["hello", "test"] | .[1])", "test")
                    );
                })
            );
        }),
        group("Interpolation", [](const Parser& parser) {
            return tests(
                test("Accessor", [](const Parser& parser) {
                    return tests(
                        test_interpolation("TEST { .x } HELLO", "TEST 2 HELLO")
                    );
                }),
                test("Variables", [](const Parser& parser) {
                    return tests(
                        test_interpolation("{ var $A = 123; \"\" }{ $A }", "123")
                    );
                }),
                test("Functions", [](const Parser& parser) {
                    return tests(
                        test_interpolation("{ @test => ( 2 ); \"\" }{ @test }", "2")
                    );
                }),
                test("Scope", [](const Parser& parser) {
                    return tests(
                        expect_throw([](){
                            test_interpolation("{ @test => ( @a => (2); @a ); \"\" }{ @a }", "2");
                        }),
                        expect_throw([](){
                            test_interpolation("{ persist var $set = set_new; @test => ( $a = 2; $a ); \"\" }{ $a }", "2");
                        })
                    );
                }),
                test("Looping statement", [](const Parser& parser) {
                    return tests(
                        test_interpolation(
                            "{# .users } Id { .id } is { .username } - { .email } {//}",
                            " Id 1 is root - root@example.com  Id 2 is Admin - admin@example.com ")
                    );

                    return 0;
                })
            );
        }),

        //Variables not defined in parameters / segfaulting
        test("Issue 2", [](const Parser& parser) {
            return tests(
                test_interpolation("{ add $job 3 }", "5", {{"job", make_data<types::IntegerType>(2)}})
            );
        })
    );
}
