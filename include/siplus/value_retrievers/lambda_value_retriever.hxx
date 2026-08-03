#pragma once
#ifndef INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_HXX_
#define INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_HXX_

#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {

/**
 * struct LambdaValueRetriever - Generate a value on invocation using a lambda.
 */
struct SIPLUS_EXPORT LambdaValueRetriever : ValueRetriever {
    using func = std::function<UnknownDataTypeContainer (InvocationContext&)>;

    LambdaValueRetriever(func func) : func_(func) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        return func_(value);
    }

private:
    func func_;
};

} /* SIPLUS_NAMESPACE */


#endif  // INCLUDE_VALUE_RETRIEVERS_LAMBDA_VALUE_RETRIEVER_HXX_
