#ifndef INCLUDE_VALUE_RETRIEVERS_SETTABLE_VALUE_RETRIEVER_H_
#define INCLUDE_VALUE_RETRIEVERS_SETTABLE_VALUE_RETRIEVER_H_

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.h"

namespace SIPLUS_NAMESPACE {
namespace text {
    
struct SettableValueRetriever : text::ValueRetriever {
    struct clear_binding {
        clear_binding(SettableValueRetriever& parent) : parent_(parent) {}

        ~clear_binding() {
            parent_.clear();
        }

    private:
        SettableValueRetriever& parent_;
    };

    SettableValueRetriever() {}

    text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override {
        if(!is_set_) {
            throw std::runtime_error{"value not set"};
        }

        return value_;
    }

    clear_binding set_value(const text::UnknownDataTypeContainer& container) {
        is_set_ = true;
        value_ = container;

        return clear_binding{*this};
    }

    void clear() {
        value_ = text::UnknownDataTypeContainer{};
        is_set_ = false;
    }

private:
    text::UnknownDataTypeContainer value_;
    bool is_set_ = false;
};

} /* text */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_VALUE_RETRIEVERS_SETTABLE_VALUE_RETRIEVER_H_
