#ifndef INCLUDE_SIPLUS_TEXT_ACCESSOR_H_
#define INCLUDE_SIPLUS_TEXT_ACCESSOR_H_

#include <string>

#include "siplus/config.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class Accessor {
public:
    virtual UnknownDataTypeContainer access(const UnknownDataTypeContainer& value, const std::string& name) = 0;
    virtual bool can_access(const UnknownDataTypeContainer& value) = 0;
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_ACCESSOR_H_
