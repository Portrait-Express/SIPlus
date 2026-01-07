#ifndef INCLUDE_SIPLUS_TEXT_LITERAL_STEP_H_
#define INCLUDE_SIPLUS_TEXT_LITERAL_STEP_H_

#include "siplus/invocation_context.h"
#include "siplus/text/constructor_steps/constructor_step.h"
#include "siplus/text/value_retrievers/retriever.h"

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

#endif  // INCLUDE_TEXT_LITERAL_STEP_H_
