#pragma once
#ifndef INCLUDE_RETRIEVERS_LITERAL_ARRAY_RETRIEVER_HXX_
#define INCLUDE_RETRIEVERS_LITERAL_ARRAY_RETRIEVER_HXX_

#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {

struct LiteralArrayValueRetriever : public ValueRetriever {
    LiteralArrayValueRetriever(std::vector<std::shared_ptr<ValueRetriever>> items) : items_(items) {}
    
    UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::vector<std::shared_ptr<ValueRetriever>> items_;
};

}

#endif  // INCLUDE_RETRIEVERS_LITERAL_ARRAY_RETRIEVER_HXX_

