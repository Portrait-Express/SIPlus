#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_HXX_
#define INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_HXX_

#include <string>

#include "siplus/config.hxx"
#include "siplus/invocation_context.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class TextConstructorStep {
public:
    virtual std::string getPart(InvocationContext& value) = 0;
};
    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_HXX_
