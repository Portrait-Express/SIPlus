#pragma once
#ifndef INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_H_
#define INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_H_

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.h"

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


#endif  // INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_H_
