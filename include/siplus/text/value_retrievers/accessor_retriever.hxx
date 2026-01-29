#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_HXX_
#define INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_HXX_

#include <memory>
#include <string>

#include "siplus/config.hxx"
#include "siplus/context.hxx"
#include "siplus/invocation_context.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class AccessorValueRetriever : public ValueRetriever {
public:
    AccessorValueRetriever(std::shared_ptr<SIPlusParserContext> accessor, std::string name);
    AccessorValueRetriever(std::shared_ptr<SIPlusParserContext> accessor, std::shared_ptr<ValueRetriever> parent, std::string name);

    UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> parent_;
    std::shared_ptr<SIPlusParserContext> context_;
    std::string name_;
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_HXX_
