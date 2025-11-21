#ifndef INCLUDE_CONVERTERS_NUMERIC_H_
#define INCLUDE_CONVERTERS_NUMERIC_H_

#include "siplus/config.h"
#include "siplus/context.h"
#include <memory>

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/text/converter.h"

namespace SIPLUS_NAMESPACE {
namespace stl {
    
/**
 * struct int_converter - Converts int types to to the common long type
 */
struct int_converter : text::Converter {
    text::UnknownDataTypeContainer 
    convert(const text::UnknownDataTypeContainer& from, std::type_index to) const override;

    bool can_convert(std::type_index from, std::type_index to) const override;
};
    
/**
 * struct float_converter - Converts float types to to the common double type
 */
struct float_converter : text::Converter {
    text::UnknownDataTypeContainer 
    convert(const text::UnknownDataTypeContainer& from, std::type_index to) const override;

    bool can_convert(std::type_index from, std::type_index to) const override;
};
    
/**
 * struct numeric_string_converter - Converts numeric types to a string
 */
struct numeric_string_converter : text::Converter {
    numeric_string_converter(
        std::weak_ptr<const SIPlusParserContext> context
    ) : ctx_(context) {}

    text::UnknownDataTypeContainer 
    convert(const text::UnknownDataTypeContainer& from, std::type_index to) const override;

    bool can_convert(std::type_index from, std::type_index to) const override;

private:
    std::weak_ptr<const SIPlusParserContext> ctx_;
};

/**
 * struct numeric_bool_converter - Converts numeric types to bool
 */
struct numeric_bool_converter : text::Converter {
    numeric_bool_converter(
        std::weak_ptr<const SIPlusParserContext> context
    ) : ctx_(context) {}

    text::UnknownDataTypeContainer 
    convert(const text::UnknownDataTypeContainer& from, std::type_index to) const override;

    bool can_convert(std::type_index from, std::type_index to) const override;

private:
    std::weak_ptr<const SIPlusParserContext> ctx_;
};


} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_CONVERTERS_NUMERIC_H_
