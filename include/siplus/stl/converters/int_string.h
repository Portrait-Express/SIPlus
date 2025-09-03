#ifndef INCLUDE_CONVERTERS_INT_STRING_H_
#define INCLUDE_CONVERTERS_INT_STRING_H_

#include "siplus/_config.h"
#include "siplus/text/converter.h"
#include <string>

namespace SIPLUS_NAMESPACE {
namespace stl {
    
struct int_converter : text::Converter {
    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from, std::type_index to) override;

    bool can_convert(std::type_index from, std::type_index to) override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_CONVERTERS_INT_STRING_H_
