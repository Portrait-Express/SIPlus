#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_HXX_
#define INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_HXX_

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

/**
 * @brief Simply returns the value of '.'. Used in a few locations internally.
 */
class SIPLUS_EXPORT DummyValueRetriever : public ValueRetriever {
public:
    DummyValueRetriever() {}

    UnknownDataTypeContainer retrieve(InvocationContext& value) const override {
        return value.default_data();
    };
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_HXX_
