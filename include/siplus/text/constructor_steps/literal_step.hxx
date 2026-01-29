#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_LITERAL_STEP_HXX_
#define INCLUDE_SIPLUS_TEXT_LITERAL_STEP_HXX_

#include <string>

#include "siplus/invocation_context.hxx"
#include "siplus/text/constructor_steps/constructor_step.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class LiteralConstructorStep : public TextConstructorStep {
public:
    explicit LiteralConstructorStep(std::string part);

    virtual std::string getPart(InvocationContext& value) override;

private:
    std::string part_;
};
    
} /* text */
}

#endif  // INCLUDE_TEXT_LITERAL_STEP_HXX_
