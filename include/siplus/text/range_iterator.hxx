#pragma once
#include <utility>
#ifndef INCLUDE_TEXT_RANGE_ITERATOR_HXX_
#define INCLUDE_TEXT_RANGE_ITERATOR_HXX_

#include "siplus/config.h"
#include "siplus/text/iterator.hxx"

namespace SIPLUS_NAMESPACE {

template<typename BIt, typename EIt>
struct range_iterator : text::Iterator {
    range_iterator(
        BIt begin,
        EIt end
    ) : cur(begin), last(begin), end(end) { }

    bool more() override {
        return cur != end;
    }

    void next() override {
        if(cur == end) {
            throw std::runtime_error{"iterator completed, but next() was called"};
        }

        if(!begun_) {
            cur++;
        } else {
            last++;
            cur++;
        }

        begun_ = true;
    }

    UnknownDataTypeContainer current() override {
        if(!begun_) {
            throw std::runtime_error{"next() has not been called. call more()&&next()"};
        }

        //Exception for UnknownDataTypeContainer, as we would return a 
        //container in a container, which is not desirable.
        if constexpr (std::is_same_v<std::remove_cvref_t<decltype(*std::declval<BIt>())>, UnknownDataTypeContainer>) {
            return *last;
        } else {
            return make_data(*cur);
        }
    }

    ~range_iterator() override { };

private:
    bool begun_ = false;

    const EIt end;

    BIt last;
    BIt cur;
};
    
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TEXT_RANGE_ITERATOR_HXX_
