#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_HXX_
#define INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_HXX_

#include <string>

#include "siplus/config.h"
#include "siplus/context.hxx"
#include "siplus/invocation_context.hxx"
#include "siplus/text/constructor.hxx"
#include "siplus/text/constructor_steps/constructor_step.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class RepeatedConstructorConstructorStep : public TextConstructorStep {
public:
    explicit RepeatedConstructorConstructorStep(
        std::shared_ptr<SIPlusParserContext> context,
        std::shared_ptr<ValueRetriever> retriever,
        text::TextConstructor sub);

    std::string getPart(InvocationContext& value) override;

private:
    TextConstructor sub_;
    std::shared_ptr<ValueRetriever> retriever_;
    std::shared_ptr<SIPlusParserContext> context_;
};
    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_HXX_
