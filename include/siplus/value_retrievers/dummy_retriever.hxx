#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_HXX_
#define INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_HXX_

#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {

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

    
}

#endif  // INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_HXX_
