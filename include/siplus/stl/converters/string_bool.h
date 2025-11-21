#ifndef INCLUDE_CONVERTERS_STRING_BOOL_H_
#define INCLUDE_CONVERTERS_STRING_BOOL_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/text/converter.h"

namespace SIPLUS_NAMESPACE {
namespace stl {
    
struct string_bool_converter : text::Converter {
public:
    bool can_convert(std::type_index from, std::type_index to) const override;

    text::UnknownDataTypeContainer convert(
        const text::UnknownDataTypeContainer& from,
        std::type_index to
    ) const override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_CONVERTERS_STRING_BOOL_H_
