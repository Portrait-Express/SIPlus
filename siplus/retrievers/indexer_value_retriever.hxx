#pragma once
#include "siplus/context.hxx"
#include <memory>
#ifndef INCLUDE_RETRIEVERS_INDEXER_VALUE_RETRIEVER_HXX_
#define INCLUDE_RETRIEVERS_INDEXER_VALUE_RETRIEVER_HXX_

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {

class indexer_value_retriever : public text::ValueRetriever {
public:
    indexer_value_retriever(
        std::shared_ptr<text::ValueRetriever> list,
        std::shared_ptr<text::ValueRetriever> index
    ) : list_(list), index_(index) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> list_;
    std::shared_ptr<text::ValueRetriever> index_;
};

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_RETRIEVERS_INDEXER_VALUE_RETRIEVER_HXX_
