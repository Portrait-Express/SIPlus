#ifndef INCLUDE_ITERATORS_STRING_ITERATOR_PROVIDER_H_
#define INCLUDE_ITERATORS_STRING_ITERATOR_PROVIDER_H_

#include <memory>

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/text/iterator.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * struct string_iterator - IteratorProvider class implementation for a 
 * std::string object
 */
struct string_iterator : public text::IteratorProvider {
    std::unique_ptr<text::Iterator> iterator(const text::UnknownDataTypeContainer &value) override;
    bool can_iterate(const text::UnknownDataTypeContainer &value) override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_ITERATORS_STRING_ITERATOR_PROVIDER_H_
