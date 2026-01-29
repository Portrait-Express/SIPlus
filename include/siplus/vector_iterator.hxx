#pragma once
#ifndef INCLUDE_SIPLUS_VECTOR_ITERATOR_HXX_
#define INCLUDE_SIPLUS_VECTOR_ITERATOR_HXX_

#include "siplus/config.hxx"
#include "siplus/text/iterator.hxx"

namespace SIPLUS_NAMESPACE {

/**
 * struct vector_iterator_impl - Implementation for vector_iterator. Do not 
 * use this class yourself.
 *
 * @tparam T 
 */
template<typename T>
struct vector_iterator : text::Iterator {
public:
    explicit vector_iterator(
        std::vector<T>::const_iterator begin,
        std::vector<T>::const_iterator end
    ) : begin(begin), cur(begin), end(end) { }

    bool more() override {
        if(begun_) {
            return cur < end - 1;
        } else {
            return cur < end;
        }
    }

    void next() override {
        //cur is valid at iterator creation, but we need to eat a next() 
        //to start the iterator as iterators should not have a valid current()
        //if next() has not been called
        if(!begun_) {
            begun_ = true;
            return;
        }

        cur++;

        if(cur >= end) {
            throw std::runtime_error{"next() called on completed iterator"};
        }
    }

    UnknownDataTypeContainer current() override {
        if(!begun_) {
            throw std::runtime_error{"next() has not been called. call more()&&next()"};
        }

        //Exception for UnknownDataTypeContainer, as we would return a 
        //container in a container, which is not desirable.
        if constexpr (std::is_same_v<T, UnknownDataTypeContainer>) {
            return *cur;
        } else {
            return make_data(*cur);
        }
    }

    ~vector_iterator() override { };

private:
    bool begun_ = false;

    const std::vector<T>::const_iterator begin;
    const std::vector<T>::const_iterator end;

    std::vector<T>::const_iterator cur;
};

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_VECTOR_ITERATOR_HXX_
