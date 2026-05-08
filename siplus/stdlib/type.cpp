#include "siplus/stl/functions/type.hxx"
#include "siplus/types/string.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct type_retriever : text::ValueRetriever {
    type_retriever(std::shared_ptr<text::ValueRetriever> param) : param_(param) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        return make_data<types::StringType>(param_->retrieve(value).type->name());
    }

private:
    std::shared_ptr<text::ValueRetriever> param_;
};

} /* anonymous */

std::shared_ptr<text::ValueRetriever> type_function::value(std::shared_ptr<text::ValueRetriever> parent, std::vector<std::shared_ptr<text::ValueRetriever>> parameters) const {
    auto [param] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<type_retriever>(param);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
