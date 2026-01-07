#ifndef INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_H_
#define INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_H_

#include <any>
#include <string>

#include "siplus/config.h"
#include "siplus/invocation_context.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class TextConstructorStep {
public:
    virtual std::string getPart(InvocationContext& value) = 0;
};
    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_H_
