#include "siplus/stl/functions/type.hxx"
#include "siplus/types/string.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct type_retriever : ValueRetriever {
    type_retriever(std::shared_ptr<ValueRetriever> param) : param_(param) {}

    UnknownDataTypeContainer retrieve(InvocationContext &context) const override {
        auto value = param_->retrieve(context);
        return make_data<types::StringType>(value.type->name());
    }

private:
    std::shared_ptr<ValueRetriever> param_;
};

} /* anonymous */

std::shared_ptr<ValueRetriever> type_function::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [param] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<type_retriever>(param);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
