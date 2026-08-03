#include "siplus/config.h"
#include "siplus/types/array.hxx"

#include "default_data_retriever.hxx"
#include "indexer_value_retriever.hxx"
#include "literal_array_retriever.hxx"
#include "variable_assignment_retriever.hxx"

namespace SIPLUS_NAMESPACE {

UnknownDataTypeContainer indexer_value_retriever::retrieve(InvocationContext& ctx) const {
    auto list = list_->retrieve(ctx);
    auto index_value = index_->retrieve(ctx);

    return list.index(ctx_, index_value);
}

UnknownDataTypeContainer LiteralArrayValueRetriever::retrieve(InvocationContext& value) const {
    std::vector<UnknownDataTypeContainer> ret;
    ret.reserve(items_.size());

    for(auto item : items_) {
        ret.push_back(item->retrieve(value));
    }

    return make_data<types::ArrayType>(ret);
}
    
UnknownDataTypeContainer default_data_retriever::retrieve(InvocationContext& value) const {
    return value.default_data();
}

UnknownDataTypeContainer variable_assignment_retriever::retrieve(InvocationContext& ctx) const {
    auto value = value_->retrieve(ctx);
    variable_->set_value(ctx, value);
    return value;
}

} /* SIPLUS_NAMESPACE */
