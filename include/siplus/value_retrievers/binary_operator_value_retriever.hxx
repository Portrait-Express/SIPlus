#pragma once
#ifndef INCLUDE_VALUE_RETRIEVERS_BINARY_OPERATOR_VALUE_RETRIEVER_HXX_
#define INCLUDE_VALUE_RETRIEVERS_BINARY_OPERATOR_VALUE_RETRIEVER_HXX_


#include "siplus/config.h"
#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {

struct BinaryOperatorFunctionRetriever : ValueRetriever {
    BinaryOperatorFunctionRetriever (
        const BinaryOperatorTypeExtension *descriptor,
        std::shared_ptr<ValueRetriever> lhs,
        std::shared_ptr<ValueRetriever> rhs
    ) : descriptor_(descriptor), lhs_(lhs), rhs_(rhs) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override;

private:
    const BinaryOperatorTypeExtension *descriptor_;
    std::shared_ptr<ValueRetriever> lhs_;
    std::shared_ptr<ValueRetriever> rhs_;
};

} /* namespace SIPLUS_NAMESPACE */


#endif  // INCLUDE_VALUE_RETRIEVERS_BINARY_OPERATOR_VALUE_RETRIEVER_HXX_
