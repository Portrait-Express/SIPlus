#include "common.hxx"
#include "siplus/parser.h"
#include "siplus/text/data.h"

using namespace SIPLUS_NAMESPACE;

int test_array(int, char**) {
    return test("Arrays", [](const SIPlus::Parser& parser) {
        auto data = test_data{};

        auto expr = parser.get_expression("[1,2,3]");
        auto val = expr->retrieve(text::make_data(test_data{}));

        if(!val.is<std::vector<text::UnknownDataTypeContainer>>()) {
            return 1;
        }

        const auto& vec = val.as<std::vector<text::UnknownDataTypeContainer>>();

        if(!std::all_of(vec.begin(), vec.end(), [](text::UnknownDataTypeContainer val) {
            return val.is<long>();
        })) {
            return 1;
        }

        std::vector<long> result{};
        result.reserve(vec.size());

        std::transform(vec.begin(), vec.end(), std::back_inserter(result), 
                       [](text::UnknownDataTypeContainer val) {
            return val.as<long>();
        });

        return result == std::vector<long>{1,2,3} ? 0 : 1;
    });
}
