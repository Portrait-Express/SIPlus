#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_CONVERTER_HXX_
#define INCLUDE_SIPLUS_TEXT_CONVERTER_HXX_

#include <typeindex>

#include "siplus/config.hxx"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class Converter {
public:
    virtual bool can_convert(const TypeInfo& from, const TypeInfo& to) const = 0;

    virtual UnknownDataTypeContainer convert(
        const UnknownDataTypeContainer& from,
        const TypeInfo& to
    ) const = 0;

    virtual ~Converter() = default;
};


} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_CONVERTER_HXX_
