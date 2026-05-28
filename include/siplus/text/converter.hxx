#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_CONVERTER_HXX_
#define INCLUDE_SIPLUS_TEXT_CONVERTER_HXX_

#include <typeindex>

#include "siplus/config.h"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

/**
 * @brief Provide converter functionality between types.
 */
class SIPLUS_EXPORT Converter {
public:
    /**
     * @brief This will return true if this converter can convert from `from` to `to`.
     * The result of this is cached internally for future lookups
     *
     * @param[in] from From type
     * @param[in] to To type
     * @return True if this converter can handle the conversion.
     */
    virtual bool can_convert(const TypeInfo& from, const TypeInfo& to) const = 0;

    /**
     * @brief Convert from one type to another
     *
     * @param[in] from The data to convert from
     * @param[in] to The type to convert to
     * @return The converted object. This MUST be an instance of `to`.
     */
    virtual UnknownDataTypeContainer convert(
        const UnknownDataTypeContainer& from,
        const TypeInfo& to
    ) const = 0;

    virtual ~Converter() = default;
};


} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_CONVERTER_HXX_
