#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_ITERATOR_HXX_
#define INCLUDE_SIPLUS_TEXT_ITERATOR_HXX_

#include "siplus/config.h"

namespace SIPLUS_NAMESPACE::text {
class SIPLUS_EXPORT Iterator;
} /* SIPLUS_NAMESPACE::text */

#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

/**
 * @brief Iterator is used to provide functionality for lists of objects.
 *
 * The standard loop used to interact with an Iterator goes more()->next()->current():
 * 
 * More is called to check if the first item is available, next() is called to move 
 * to that first item, and current is called to access it(). The loop continues for 
 * the second item and so on... Calling next() if more() is false is UB.
 *
 * @code
 * while(iterator.more()) {
 *     iterator.next();
 *     auto value = iterator.current();
 *     // Use value...
 * }
 * @endcode
 */
class SIPLUS_EXPORT Iterator {
public:
    /**
     * @brief Check if the next item is available
     *
     * @return True if next() can be called
     */
    virtual bool more() = 0;

    /**
     * @brief Move to the next item. Do not call this if more() is false.
     */
    virtual void next() = 0;

    /**
     * @brief Get the item at the current iterator position
     *
     * @return The data
     */
    virtual UnknownDataTypeContainer current() = 0;

    virtual ~Iterator() = default;
};

} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_ITERATOR_HXX_
