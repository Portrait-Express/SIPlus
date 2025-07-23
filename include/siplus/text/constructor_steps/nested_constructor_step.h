#ifndef INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_H_
#define INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_H_

#include <string>

#include "siplus/_config.h"
#include "siplus/text/constructor.h"
#include "siplus/text/constructor_steps/constructor_step.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class NestedConstructorConstructorStep : public TextConstructorStep {
public:
    explicit NestedConstructorConstructorStep(text::TextConstructor sub);

    std::string getPart(const UnknownDataTypeContainer& value) override;

private:
    text::TextConstructor sub_;
};
    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_NESTED_CONSTRUCTOR_STEP_H_
