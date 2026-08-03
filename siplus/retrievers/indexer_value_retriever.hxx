#pragma once
#include "siplus/context.hxx"
#include <memory>
#ifndef INCLUDE_RETRIEVERS_INDEXER_VALUE_RETRIEVER_HXX_
#define INCLUDE_RETRIEVERS_INDEXER_VALUE_RETRIEVER_HXX_

#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {

class indexer_value_retriever : public ValueRetriever {
public:
    indexer_value_retriever(
        std::shared_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<ValueRetriever> list,
        std::shared_ptr<ValueRetriever> index
    ) : ctx_(ctx), list_(list), index_(index) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<ValueRetriever> list_;
    std::shared_ptr<ValueRetriever> index_;
};

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_RETRIEVERS_INDEXER_VALUE_RETRIEVER_HXX_
