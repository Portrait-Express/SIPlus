#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_ITERATOR_H_
#define INCLUDE_SIPLUS_TEXT_ITERATOR_H_

namespace SIPLUS_NAMESPACE::text {
class Iterator;
} /* SIPLUS_NAMESPACE::text */

#include "siplus/config.h"
#include "siplus/data.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class Iterator {
public:
    virtual bool more() = 0;
    virtual void next() = 0;
    virtual UnknownDataTypeContainer current() = 0;

    virtual ~Iterator() = default;
};

} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_ITERATOR_H_
