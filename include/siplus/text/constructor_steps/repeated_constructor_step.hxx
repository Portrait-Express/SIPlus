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

/**
 * @brief This contains a nested TextConstructor, and a ValueRetriever, which *should* 
 * return an object that is iterable. The nested constructor will be called for each item
 * in the iterator, and concatenated, and returned.
 */
class RepeatedConstructorConstructorStep : public TextConstructorStep {
public:
    /**
     * @brief Create a new RepeatedConstructorConstructorStep
     *
     * @param[[TODO:direction]] context The ParserContext
     * @param[[TODO:direction]] retriever The Retriever that will return an iterable
     * @param[[TODO:direction]] sub The nested template to invoke
     */
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
