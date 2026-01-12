#include "common.hxx"
#include "siplus/parser.h"

int test_variable(int, char**) {
    return group("Variables", [](const SIPLUS_NAMESPACE::Parser& parser) {
        return tests(
            test_interpolation("TEST { $A = 2; $A } HELLO", "TEST 2 HELLO"),

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
    });
}
