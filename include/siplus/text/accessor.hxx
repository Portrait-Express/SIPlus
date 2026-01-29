#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_ACCESSOR_HXX_
#define INCLUDE_SIPLUS_TEXT_ACCESSOR_HXX_

#include <string>

#include "siplus/config.hxx"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class Accessor {
public:
    virtual UnknownDataTypeContainer access(const UnknownDataTypeContainer& value, const std::string& name) = 0;
    virtual bool can_access(const UnknownDataTypeContainer& value) = 0;
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_ACCESSOR_HXX_
