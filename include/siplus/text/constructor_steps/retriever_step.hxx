#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_RETRIEVER_STEP_HXX_
#define INCLUDE_SIPLUS_TEXT_RETRIEVER_STEP_HXX_

#include <memory>

#include "siplus/config.hxx"
#include "siplus/context.hxx"
#include "siplus/text/constructor_steps/constructor_step.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class ValueRetrieverConstructorStep : public TextConstructorStep {
public:
    explicit ValueRetrieverConstructorStep(
        std::shared_ptr<SIPlusParserContext> context, std::shared_ptr<ValueRetriever> retriever);

    std::string getPart(InvocationContext& value) override;

private:
    std::shared_ptr<ValueRetriever> retriever_;
    std::shared_ptr<SIPlusParserContext> context_;
};
    
} /* text */
}

#endif  // INCLUDE_TEXT_RETRIEVER_STEP_HXX_
