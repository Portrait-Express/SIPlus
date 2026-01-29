#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_H_
#define INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_H_

#include <memory>
#include <string>

#include "siplus/config.h"
#include "siplus/context.h"
#include "siplus/invocation_context.h"
#include "siplus/text/value_retrievers/retriever.h"

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

#endif  // INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_H_
