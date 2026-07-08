#include "siplus/config.h"
#include "siplus/data.hxx"
#include "siplus/types/array.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/util.hxx"

#include "default_data_retriever.hxx"
#include "indexer_value_retriever.hxx"
#include "literal_array_retriever.hxx"
#include "variable_assignment_retriever.hxx"

namespace SIPLUS_NAMESPACE {

UnknownDataTypeContainer indexer_value_retriever::retrieve(InvocationContext& ctx) const {
    auto list = list_->retrieve(ctx);
    auto index = ctx_->convert<types::IntegerType>(index_->retrieve(ctx)).as<types::IntegerType>();

    if(!list.is_iterable()) {
        throw std::runtime_error{util::to_string(
            "Tried to index position ", index, " of a non-iterable type ", list.type->name()
        )};
    }

    auto i = 0;
    auto iterator = list.iterate();
    while(iterator->more()) {
        iterator->next();

        if(i == index) return iterator->current();

        i++;
    }

    throw std::runtime_error{util::to_string(
        "Index out of bounds: index ", index, " is out of range of list of size ", i
    )};
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
