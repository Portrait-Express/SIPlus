#include "siplus/context.hxx"
#include "testing.hxx"
#include <iostream>

using namespace SIPLUS_NAMESPACE;

CATEGORY(DataContainerEquatable);
TEST(IntegerEquatable, DataContainerEquatable) {
    auto foo = make_data(1);
    auto bar = make_data(1);
    auto baz = make_data(3);

    EXPECT_TRUE_S(foo == bar, "Expected foo(IntegerType 1) to equal bar(IntegerType 1).");
    EXPECT_TRUE_S(foo != baz, "Expected foo(IntegerType 1) to not equal baz(IntegerType 3).");

    return true;
}

int test_data(int argc, char **argv) {
    auto results = test_detail::CategoryDataContainerEquatable->run_all();

    std::cout << results << std::endl;

    return results.passed() ? 0 : 1;
}
