#include "common.hxx"
#include "siplus/parser.h"

int test_interpolate(int, char**) {
    return group("String Interpolation", [](const SIPLUS_NAMESPACE::Parser& parser) {
        return tests(
            test("Accessor", [](const SIPlus::Parser& parser) {
                return tests(
                    test_interpolation("TEST { .x } HELLO", "TEST 2 HELLO")
                );
            }),
            test("Variables", [](const SIPlus::Parser& parser) {
                return tests(
                    test_interpolation("{ $A = 123; \"\" }{ $A }", "123")
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
                        test_interpolation("{ @test => ( $a = 2; $a ); \"\" }{ $a }", "2");
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
    });
}
