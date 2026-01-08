#ifndef INCLUDE_SIPLUS_TEXT_CONVERTER_H_
#define INCLUDE_SIPLUS_TEXT_CONVERTER_H_

#include <typeindex>

#include "siplus/config.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class Converter {
public:
    virtual bool can_convert(std::type_index from, std::type_index to) const = 0;

    virtual UnknownDataTypeContainer convert(
        const UnknownDataTypeContainer& from,
        std::type_index to
    ) const = 0;

    virtual ~Converter() = default;
};


} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_CONVERTER_H_
