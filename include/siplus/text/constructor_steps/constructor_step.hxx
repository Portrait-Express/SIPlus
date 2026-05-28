#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_HXX_
#define INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_HXX_

#include <string>

#include "siplus/config.h"
#include "siplus/invocation_context.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

/**
 * @brief This is one step in the TextConstructor sequence
 */
class SIPLUS_EXPORT TextConstructorStep {
public:
    /**
     * @brief Get the next part of the Template to append to the text
     *
     * @param[in] value The InvocationContext
     * @return The next part of the template
     */
    virtual std::string getPart(InvocationContext& value) = 0;

    virtual ~TextConstructorStep() = default;
};
    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_HXX_
