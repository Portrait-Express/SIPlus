#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_HXX_
#define INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_HXX_

#include "siplus/config.h"
#include "siplus/invocation_context.hxx"
#include "siplus/data.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

/**
 * @brief Retrieves a literal value determined at construction
 */
class SIPLUS_EXPORT LiteralValueRetriever : public ValueRetriever {
public:
    /**
     * @brief Create a new LiteralValueRetriever with specified data
     *
     * @param[in] value The data to return on retrieval
     */
    explicit LiteralValueRetriever(UnknownDataTypeContainer value);

    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    UnknownDataTypeContainer value_;
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_HXX_
