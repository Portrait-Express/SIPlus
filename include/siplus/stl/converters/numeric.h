#ifndef INCLUDE_CONVERTERS_NUMERIC_H_
#define INCLUDE_CONVERTERS_NUMERIC_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/text/converter.h"

namespace SIPLUS_NAMESPACE {
namespace stl {
    
/**
 * struct int_converter - Converts int types to to the common long type
 */
struct int_converter : text::Converter {
    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from, std::type_index to) override;

    bool can_convert(std::type_index from, std::type_index to) override;
};
    
/**
 * struct float_converter - Converts float types to to the common double type
 */
struct float_converter : text::Converter {
    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from, std::type_index to) override;

    bool can_convert(std::type_index from, std::type_index to) override;
};
    
/**
 * struct int_converter - Converts numeric types to a string
 */
struct numeric_string_converter : text::Converter {
    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from, std::type_index to) override;

    bool can_convert(std::type_index from, std::type_index to) override;

private:
    float_converter float_converter_;
    int_converter int_converter_;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_CONVERTERS_NUMERIC_H_
