#ifndef INCLUDE_ITERATORS_VECTOR_ITERATOR_PROVIDER_H_
#define INCLUDE_ITERATORS_VECTOR_ITERATOR_PROVIDER_H_

#include "siplus/config.h"

// Not checking SIPLUS_INCLUDE_STDLIB as nothing here relies on STL object files.
// Users are free to include and instantiate the classes below, as they are 
// contained in their entirety due to being templates

#include "siplus/text/iterator.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

/**
 * struct vector_iterator_impl - Implementation for vector_iterator. Do not 
 * use this class yourself.
 *
 * @tparam T 
 */
template<typename T>
struct vector_iterator_impl : text::Iterator {
public:
    explicit vector_iterator_impl(
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

    text::UnknownDataTypeContainer current() override {
        if(!begun_) {
            throw std::runtime_error{"next() has not been called. call more()&&next()"};
        }

        //Exception for text::UnknownDataTypeContainer, as we would return a 
        //container in a container, which is not desirable.
        return text::make_data(*cur);
    }

    ~vector_iterator_impl() override { };

private:
    bool begun_ = false;

    const std::vector<T>::const_iterator begin;
    const std::vector<T>::const_iterator end;

    std::vector<T>::const_iterator cur;
};

} /* anonymous */

/**
 * struct vector_iterator - IteratorProvider class implementation for a 
 * std::vector holding any type.
 *
 * @tparam T Contents of the vector.
 */
template<typename T>
struct vector_iterator : public SIPLUS_NAMESPACE::text::IteratorProvider {
    std::unique_ptr<text::Iterator> iterator(const text::UnknownDataTypeContainer &value) override {
        const auto& ref = value.as<std::vector<T>>();

        auto ptr = new vector_iterator_impl<T>{ref.begin(), ref.end()};
        return std::unique_ptr<text::Iterator>{ptr};
    }

    bool can_iterate(const text::UnknownDataTypeContainer &value) override {
        return value.type == typeid(std::vector<T>);
    }
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_ITERATORS_VECTOR_ITERATOR_PROVIDER_H_
