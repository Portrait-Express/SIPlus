#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_HXX_
#define INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_HXX_

#include <memory>
#include <string>
#include <vector>

#include "siplus/config.h"
#include "siplus/invocation_context.hxx"
#include "siplus/text/constructor_steps/constructor_step.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class TextConstructor {
public:
    void addStep(std::shared_ptr<TextConstructorStep>);

    std::string construct_with(std::shared_ptr<InvocationContext> data);
private:

    std::vector<std::shared_ptr<TextConstructorStep>> steps_;
};

}
}

#endif  // INCLUDE_TEXT_CONSTRUCTOR_HXX_
