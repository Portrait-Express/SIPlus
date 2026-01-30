#pragma once
#ifndef INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_HXX_
#define INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_HXX_

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

struct LambdaValueRetriever : text::ValueRetriever {
    using func = std::function<UnknownDataTypeContainer (InvocationContext&)>;

    LambdaValueRetriever(func func) : func_(func) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        return func_(value);
    }

private:
    func func_;
};

} /* text */
} /* SIPLUS_NAMESPACE */


#endif  // INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_HXX_
