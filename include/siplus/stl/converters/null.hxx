#pragma once
#include "siplus/data.hxx"
#include "siplus/text/converter.hxx"
#ifndef INCLUDE_CONVERTERS_NULL_HXX_
#define INCLUDE_CONVERTERS_NULL_HXX_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * struct null_bool_converter - Converts null to a bool. The result is always false.
 */
struct null_bool_converter : text::Converter {
    UnknownDataTypeContainer 
    convert(const UnknownDataTypeContainer& from, const TypeInfo& to) const override;

    bool can_convert(const TypeInfo& from, const TypeInfo& to) const override;
};

/**
 * struct null_string_converter - Converts null to an empty string.
 */
struct null_string_converter : text::Converter {
    UnknownDataTypeContainer 
    convert(const UnknownDataTypeContainer& from, const TypeInfo& to) const override;

    bool can_convert(const TypeInfo& from, const TypeInfo& to) const override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_CONVERTERS_NULL_HXX_
