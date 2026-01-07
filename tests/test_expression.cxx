#include <chrono>
#include <cstring>

#include "common.hxx"
#include "siplus/parser.h"

using namespace SIPLUS_NAMESPACE;

int test_expression(int, char**) {
    return group("Expression", [](const SIPLUS_NAMESPACE::Parser& parser) {
        return tests(
            test("Accessor", [](const SIPlus::Parser& parser) {
                return tests(
                    test_expression<int>(".x", 2)
                );
            }),
            test("Variables", [](const SIPlus::Parser& parser) {
                auto extra = parser.context().builder()
                    .with("extra", SIPlus::text::make_data(test_data{}))
                    .use_default(SIPlus::text::make_data(test_data{}))
                    .build();

                ParseOpts extraOpts;
                extraOpts.globals.push_back("extra");

                return tests(
                    test_expression<int>("$A = (.x); $A", 2),
                    test_expression<long>("$A = 123; $A", 123),
                    test_expression<int>("$extra.x", extraOpts, extra, 2)
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
            })
        );
    });
}
