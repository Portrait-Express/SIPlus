#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_HXX_
#define INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_HXX_

#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {

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

    
}

#endif  // INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_HXX_
