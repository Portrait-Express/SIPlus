#include <cstring>

#include "common.hxx"
#include "siplus/parser.h"
#include "siplus/text/data.h"

using namespace SIPLUS_NAMESPACE;

int test_base(int, char**) {
    return tests(
        group("Expression", [](const SIPLUS_NAMESPACE::Parser& parser) {
            return tests(
                test("Accessor", [](const SIPlus::Parser& parser) {
                    return tests(
                        test_expression<int>(".x", 2)
                    );
                }),
                group("Variables", [](const SIPlus::Parser& parser) {
                    auto extra = parser.context().builder()
                        .with("extra", SIPlus::text::make_data(test_data{}))
                        .use_default(SIPlus::text::make_data(test_data{}))
                        .build();

                    ParseOpts extraOpts;
                    extraOpts.globals.push_back("extra");

                    return tests(
                        test_expression<int>("var $A = (.x); $A", 2),
                        test_expression<long>("var $A = 123; $A", 123),
                        test_expression<int>("$extra.x", extraOpts, extra, 2),
                        test("const", [](const SIPLUS_NAMESPACE::Parser& parser) {
                            return tests(
                                test_expression<int>("const var $A = (.x); $A", 2),
                                expect_throw([&]() {
                                    parser.get_expression("const var $a = 2; $a = 5; $a", ParseOpts{});
                                })
                            );
                        }),
                        test("persist", [](const SIPLUS_NAMESPACE::Parser& parser) {
                            auto retriever = parser.get_expression("persist const var $A = rand; $A", ParseOpts{});
                            auto ctx = parser.context().builder().use_default(text::UnknownDataTypeContainer{}).build();
                            auto v1 = retriever->retrieve(*ctx);
                            ctx = parser.context().builder().use_default(text::UnknownDataTypeContainer{}).build();
                            auto v2 = retriever->retrieve(*ctx);

                            bool persisted = v1.is<double>() && v2.is<double>() && v1.as<double>() == v2.as<double>();

                            return tests(
                                persisted ? 0 : 1,
                                test_expression<int>("persist const var $A = (.x); $A", 2),
                                expect_throw([&]() {
                                    parser.get_expression("const var $a = 2; $a = 5; $a", ParseOpts{});
                                })
                            );
                        })
                    );
                }),
                test("Functions", [](const SIPlus::Parser& parser) {
                    return tests(
                        test_expression<long>("@test => ( 2 ); @test", 2)
                    );
                }),
                test("Scope", [](const SIPlus::Parser& parser) {
                    return tests(
                        expect_throw([](){
                            test_expression<long>("@test => ( @a => (2); @a ); @a", 2);
                        }),
                        expect_throw([](){
                            test_expression<long>("@test => ( $a = 2; $a ); $a", 2);
                        })
                    );
                }),
                test("Arrays", [](const SIPlus::Parser& parser) {
                    return tests(
                        test_expression<std::vector<long>, std::vector<text::UnknownDataTypeContainer>>(
                            R"([1,2,3])", std::vector<long>{1,2,3}),
                        test_expression<std::vector<std::string>, std::vector<text::UnknownDataTypeContainer>>(
                            R"(["hello", "test"])", std::vector<std::string>{"hello", "test"}),
                        test_expression<std::string>(R"(["hello", "test"] | .[1])", "test")
                    );
                })
            );
        }),
        group("Interpolation", [](const SIPLUS_NAMESPACE::Parser& parser) {
            return tests(
                test("Accessor", [](const SIPlus::Parser& parser) {
                    return tests(
                        test_interpolation("TEST { .x } HELLO", "TEST 2 HELLO")
                    );
                }),
                test("Variables", [](const SIPlus::Parser& parser) {
                    return tests(
                        test_interpolation("{ var $A = 123; \"\" }{ $A }", "123")
                    );
                }),
                test("Functions", [](const SIPlus::Parser& parser) {
                    return tests(
                        test_interpolation("{ @test => ( 2 ); \"\" }{ @test }", "2")
                    );
                }),
                test("Scope", [](const SIPlus::Parser& parser) {
                    return tests(
                        expect_throw([](){
                            test_interpolation("{ @test => ( @a => (2); @a ); \"\" }{ @a }", "2");
                        }),
                        expect_throw([](){
                            test_interpolation("{ persist var $set = set_new; @test => ( $a = 2; $a ); \"\" }{ $a }", "2");
                        })
                    );
                }),
                test("Looping statement", [](const SIPlus::Parser& parser) {
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
        test("Issue 2", [](const SIPLUS_NAMESPACE::Parser& parser) {
            auto ctx = parser.context().builder()
                .with("job", SIPlus::text::make_data(2))
                .use_default(SIPlus::text::make_data(test_data{}))
                .build();

            SIPLUS_NAMESPACE::ParseOpts opts;
            opts.globals.push_back("job");

            return tests(
                test_interpolation("{ add $job 3 }", opts, ctx,  "5")
            );
        })
    );
}
