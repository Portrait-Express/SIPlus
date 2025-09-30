#ifndef INCLUDE_SIPLUS_TEXT_CONVERTER_H_
#define INCLUDE_SIPLUS_TEXT_CONVERTER_H_

#include "siplus/config.h"
#include "siplus/text/data.h"
#include <typeindex>

namespace SIPLUS_NAMESPACE {
namespace text {

class Converter {
public:
    virtual bool can_convert(std::type_index from, std::type_index to) = 0;

    virtual UnknownDataTypeContainer convert(
        UnknownDataTypeContainer from,
        std::type_index to
    ) = 0;

    virtual ~Converter() = default;
};


} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_CONVERTER_H_
