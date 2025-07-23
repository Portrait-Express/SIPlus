#include "common.hxx"
#include "siplus/context.h"
#include "siplus/parser.h"
#include "siplus/text/data.h"
#include <format>

using namespace SIPLUS_NAMESPACE;

int common(int, char**) { return 0; } //dummy for ctest

struct data_acessor : public SIPlus::text::Accessor {
    text::UnknownDataTypeContainer access(
        const text::UnknownDataTypeContainer &value, 
        const std::string &name) override {
        const test_data& data = value.as<test_data>();

        if(name == "x") {
            return text::make_data(data.x);
        }

        throw std::runtime_error(std::format("No viable property for '{}'", name));
    }

    bool can_access(const text::UnknownDataTypeContainer& value) override {
        return value.type == typeid(test_data);
    }
};

Parser test_context() {
    Parser parser;

    parser.context().emplace_accessor<data_acessor>();

    return parser;
}
