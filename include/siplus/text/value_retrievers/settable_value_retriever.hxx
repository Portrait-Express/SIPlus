#pragma once
#ifndef INCLUDE_VALUE_RETRIEVERS_SETTABLE_VALUE_RETRIEVER_HXX_
#define INCLUDE_VALUE_RETRIEVERS_SETTABLE_VALUE_RETRIEVER_HXX_

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.hxx"

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

    UnknownDataTypeContainer retrieve(InvocationContext& value) const override {
        if(!is_set_) {
            throw std::runtime_error{"value not set"};
        }

        return value_;
    }

    clear_binding set_value(const UnknownDataTypeContainer& container) {
        is_set_ = true;
        value_ = container;

        return clear_binding{*this};
    }

    void clear() {
        value_ = UnknownDataTypeContainer{};
        is_set_ = false;
    }

private:
    UnknownDataTypeContainer value_;
    bool is_set_ = false;
};

} /* text */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_VALUE_RETRIEVERS_SETTABLE_VALUE_RETRIEVER_HXX_
