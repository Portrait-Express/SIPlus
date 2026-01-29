#pragma once
#include "siplus/types/float.h"
#include "siplus/types/integer.h"
#include "siplus/types/string.h"
#ifndef INCLUDE_FUNCTIONS_SET_H_
#define INCLUDE_FUNCTIONS_SET_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/function.h"
#include "siplus/context.h"
#include "siplus/data.h"
#include "siplus/text/iterator.h"

#include <unordered_set>

namespace std {

template<>
struct hash<SIPLUS_NAMESPACE::UnknownDataTypeContainer> {
    std::uint64_t operator()(
        const SIPLUS_NAMESPACE::UnknownDataTypeContainer& container
    ) const;

private:
    hash<SIPLUS_NAMESPACE::types::StringType::data_type> string_;
    hash<SIPLUS_NAMESPACE::types::FloatType::data_type> double_;
    hash<SIPLUS_NAMESPACE::types::IntegerType::data_type> long_;
};

template<>
struct equal_to<SIPLUS_NAMESPACE::UnknownDataTypeContainer> {
    equal_to(
        shared_ptr<SIPLUS_NAMESPACE::SIPlusParserContext> context,
        shared_ptr<SIPLUS_NAMESPACE::text::ValueRetriever> comparator
    );

    bool operator()(
        const SIPLUS_NAMESPACE::UnknownDataTypeContainer& lhs,
        const SIPLUS_NAMESPACE::UnknownDataTypeContainer& rhs
    ) const;

private:
    shared_ptr<SIPLUS_NAMESPACE::SIPlusParserContext> context_;
    shared_ptr<SIPLUS_NAMESPACE::text::ValueRetriever> comparator_;
};

} /* std */

namespace SIPLUS_NAMESPACE {
namespace stl {

struct SetType : public TypeInfo {
    using data_type = std::unordered_set<UnknownDataTypeContainer>;
    virtual std::string name() const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;

    virtual std::unique_ptr<text::Iterator> iterate(const UnknownDataTypeContainer& data) const override;
};

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
    set_iterator(SetType::data_type::const_iterator begin, SetType::data_type::const_iterator end) 
        : begin_(begin), end_(end) { }

    bool more() override;
    void next() override;
    UnknownDataTypeContainer current() override;

private:
    SetType::data_type::const_iterator begin_;
    SetType::data_type::const_iterator end_;
    bool next_called_;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB
#endif  // INCLUDE_FUNCTIONS_SET_H_
