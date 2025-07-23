#ifndef INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_H_
#define INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_H_

#include <any>
#include <string>

#include "siplus/_config.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class TextConstructorStep {
public:
    virtual std::string getPart(const UnknownDataTypeContainer& value) = 0;
};
    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_STEP_H_
