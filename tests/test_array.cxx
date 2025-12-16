#include "common.hxx"
#include "siplus/parser.h"

using namespace SIPLUS_NAMESPACE;

int test_array(int, char**) {
    return test("Arrays", [](const SIPlus::Parser& parser) {
        return tests(
            test_expression<std::vector<long>, std::vector<text::UnknownDataTypeContainer>>(
                R"([1,2,3])", std::vector<long>{1,2,3}),
            test_expression<std::vector<std::string>, std::vector<text::UnknownDataTypeContainer>>(
                R"(["hello", "test"])", std::vector<std::string>{"hello", "test"}),
            test_expression<std::string>(R"(["hello", "test"] | .[1])", "test")
        );
    });
}
