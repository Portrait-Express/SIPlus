#pragma once
#ifndef INCLUDE_TEXT_RANGE_ITERATOR_HXX_
#define INCLUDE_TEXT_RANGE_ITERATOR_HXX_

#include "siplus/config.h"
#include "siplus/text/iterator.hxx"

#include <utility>

namespace SIPLUS_NAMESPACE {

/**
 * struct range_iterator - This is a commonly used iterator type in the STL. It is made
 * available here for you to use in your implementations.
 *
 * A simple Iterator Implementation that works with begin() and end() iterators from 
 * std C++.
 *
 * If your <T> for your container is UnknownDataTypeContainer, this returns that 
 * container directly, otherwise it will call make_data for each value.
 *
 * @tparam BIt Type of the beginning iterator. This must be copyable.
 * @tparam EIt Type of the end iterator
 */
template<typename BIt, typename EIt = BIt>
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
            throw std::runtime_error{"next() has not been called. call more() && next()"};
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
    
template<typename It>
using iterator_value_type = std::remove_cvref_t<decltype(*std::declval<It>())>;

template<typename BIt, typename EIt> requires std::is_copy_assignable_v<iterator_value_type<BIt>>
struct value_range_iterator : text::Iterator {
    using value_type = iterator_value_type<BIt>;

    template<typename _BIt, typename _EIt>
    value_range_iterator(
        _BIt&& begin,
        _EIt&& end
    ) : cur(std::forward<_BIt>(begin)), end(std::forward<_EIt>(end)) { }

    bool more() override {
        return cur != end;
    }

    void next() override {
        if(cur == end) {
            throw std::runtime_error{"iterator completed, but next() was called"};
        }

        last = *cur;
        cur++;

        begun_ = true;
    }

    UnknownDataTypeContainer current() override {
        if(!begun_) {
            throw std::runtime_error{"next() has not been called. call more() && next()"};
        }

        //Exception for UnknownDataTypeContainer, as we would return a 
        //container in a container, which is not desirable.
        if constexpr (std::is_same_v<std::remove_cvref_t<decltype(*std::declval<BIt>())>, UnknownDataTypeContainer>) {
            return last;
        } else {
            return make_data(last);
        }
    }

    ~value_range_iterator() override { }

private:
    bool begun_ = false;

    const EIt end;

    value_type last;
    BIt cur;
};

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TEXT_RANGE_ITERATOR_HXX_
