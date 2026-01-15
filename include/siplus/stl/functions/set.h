#ifndef INCLUDE_FUNCTIONS_SET_H_
#define INCLUDE_FUNCTIONS_SET_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/function.h"
#include "siplus/context.h"
#include "siplus/text/data.h"
#include "siplus/text/iterator.h"
#include "siplus/text/value_retrievers/settable_value_retriever.h"

#include <unordered_set>

namespace std {

template<>
struct hash<SIPLUS_NAMESPACE::text::UnknownDataTypeContainer> {
    hash(shared_ptr<SIPLUS_NAMESPACE::SIPlusParserContext> context);

    std::uint64_t operator()(
        const SIPLUS_NAMESPACE::text::UnknownDataTypeContainer& container
    ) const;

private:
    shared_ptr<SIPLUS_NAMESPACE::SIPlusParserContext> context_;
    hash<std::string> string_;
    hash<double> double_;
    hash<long> long_;
};

template<>
struct equal_to<SIPLUS_NAMESPACE::text::UnknownDataTypeContainer> {
    equal_to(
        shared_ptr<SIPLUS_NAMESPACE::SIPlusParserContext> context,
        shared_ptr<SIPLUS_NAMESPACE::text::ValueRetriever> comparator
    );

    bool operator()(
        const SIPLUS_NAMESPACE::text::UnknownDataTypeContainer& lhs,
        const SIPLUS_NAMESPACE::text::UnknownDataTypeContainer& rhs
    ) const;

private:
    shared_ptr<SIPLUS_NAMESPACE::SIPlusParserContext> context_;
    shared_ptr<SIPLUS_NAMESPACE::text::ValueRetriever> comparator_;
};

} /* std */

namespace SIPLUS_NAMESPACE {
namespace stl {

using set_t = std::unordered_set<text::UnknownDataTypeContainer>;

/**
 * struct set_new_func - Function to create a new instance of a set
 */
struct set_new_func : Function {
    set_new_func(std::weak_ptr<SIPlusParserContext> context) 
        : context_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

/**
 * struct set_has_func - Function to check if a set contains an item
 */
struct set_has_func : Function {
    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;
};

/**
 * struct set_add_func - Function to add an item to a set.
 */
struct set_add_func : Function {
    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;
};

/**
 * struct set_iterator - Iterator implementation for a set
 */
struct set_iterator : text::Iterator {
    set_iterator(set_t::const_iterator begin, set_t::const_iterator end) 
        : begin_(begin), end_(end) { }

    bool more() override;
    void next() override;
    text::UnknownDataTypeContainer current() override;

private:
    set_t::const_iterator begin_;
    set_t::const_iterator end_;
    bool next_called_;
};

/**
 * struct set_iterator_provider - IteratorProvider implementation for a set
 */
struct set_iterator_provider : text::IteratorProvider {
    std::unique_ptr<text::Iterator> iterator(
        const text::UnknownDataTypeContainer& value
    ) override;
    bool can_iterate(const text::UnknownDataTypeContainer& value) override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB
#endif  // INCLUDE_FUNCTIONS_SET_H_
