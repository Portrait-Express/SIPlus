#include "common.hxx"
#include "siplus/context.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include <format>

using namespace SIPLUS_NAMESPACE;

int common(int, char**) { return 0; } //dummy for ctest

struct data_acessor : public SIPlus::text::Accessor {
    text::UnknownDataTypeContainer access(
        const text::UnknownDataTypeContainer &value, 
        const std::string &name) override {
        const test_data *data = reinterpret_cast<const test_data*>(value.ptr);

        if(name == "x") {
            return text::make_data(data->x);
        }

        throw std::runtime_error(std::format("No viable property for '{}'", name));
    }

    bool can_access(const text::UnknownDataTypeContainer& value) override {
        return value.type == typeid(test_data);
    }
};

std::shared_ptr<SIPlus::SIPlusParserContext> test_context() {
    static std::shared_ptr<SIPlusParserContext> context;

    if(!context) {
        context = std::make_shared<SIPlusParserContext>();

        context->emplace_accessor<data_acessor>();
    }

    return context;
}
