#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_H_
#define INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_H_

#include <string>

#include "siplus/config.h"
#include "siplus/context.h"
#include "siplus/invocation_context.h"
#include "siplus/text/constructor.h"
#include "siplus/text/constructor_steps/constructor_step.h"
#include "siplus/text/value_retrievers/retriever.h"

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

#endif  // INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_H_
