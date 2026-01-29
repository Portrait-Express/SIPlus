#pragma once
#ifndef INCLUDE_CONVERTERS_NUMERIC_HXX_
#define INCLUDE_CONVERTERS_NUMERIC_HXX_

#include "siplus/config.hxx"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>

#include "siplus/context.hxx"
#include "siplus/text/converter.hxx"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {
    
/**
 * struct int_float_converter - Converts int to a float. We dont allow the 
 * other way around implicitly, as that leads to data loss from the floating 
 * point truncation.
 */
struct int_float_converter : text::Converter {
    UnknownDataTypeContainer 
    convert(const UnknownDataTypeContainer& from, const TypeInfo& to) const override;

    bool can_convert(const TypeInfo& from, const TypeInfo& to) const override;
};
    
/**
 * struct numeric_string_converter - Converts numeric types to a string
 */
struct numeric_string_converter : text::Converter {
    numeric_string_converter() {}

    UnknownDataTypeContainer 
    convert(const UnknownDataTypeContainer& from, const TypeInfo& to) const override;

    bool can_convert(const TypeInfo& from, const TypeInfo& to) const override;
};

/**
 * struct numeric_bool_converter - Converts numeric types to bool
 */
struct numeric_bool_converter : text::Converter {
    numeric_bool_converter() {}

    UnknownDataTypeContainer 
    convert(const UnknownDataTypeContainer& from, const TypeInfo& to) const override;

    bool can_convert(const TypeInfo& from, const TypeInfo& to) const override;
};


} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_CONVERTERS_NUMERIC_HXX_
