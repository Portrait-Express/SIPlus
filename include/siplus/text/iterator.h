#ifndef INCLUDE_SIPLUS_TEXT_ITERATOR_H_
#define INCLUDE_SIPLUS_TEXT_ITERATOR_H_

#include "siplus/config.h"
#include "siplus/text/data.h"
#include <memory>

namespace SIPLUS_NAMESPACE {
namespace text {

class Iterator {
public:
    virtual bool more() = 0;
    virtual void next() = 0;
    virtual UnknownDataTypeContainer current() = 0;

    virtual ~Iterator() = default;
};

class IteratorProvider {
public:
    virtual std::unique_ptr<Iterator> iterator(const UnknownDataTypeContainer& value) = 0;
    virtual bool can_iterate(const UnknownDataTypeContainer& value) = 0;
};


} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_ITERATOR_H_
