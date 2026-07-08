#pragma once
#ifndef INCLUDE_FUNCTIONS_ITERABLE_HXX_
#define INCLUDE_FUNCTIONS_ITERABLE_HXX_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>
#include <vector>

#include "siplus/context.hxx"
#include "siplus/function.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * struct map_func - Function for mapping an expression over each element 
 * of the iterable. 
 *
 * @code
 * std::vector<int> c = {1, 2, 3}; 
 * parser.get_expression(R"(map . (add . 2))")->retrieve(text::make_data(c));
 * // std::vector<double> result = {3, 4, 5};
 * @endcode
 */
struct SIPLUS_EXPORT map_func : Function  {
    explicit map_func(std::weak_ptr<SIPlusParserContext> context) 
        : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

/**
 * struct length_func - Function that iterates over the set, and counts the 
 * length.
 *
 * @code
 * std::vector<int> c = {1, 2, 3}; 
 * parser.get_expression(R"(length .)")->retrieve(text::make_data(c));
 * // long result = 3;
 * @endcode
 */
struct SIPLUS_EXPORT length_func : Function  {
    explicit length_func(std::weak_ptr<SIPlusParserContext> context) 
        : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

/**
 * struct join_func - Function that joins all elements of a set as a string, 
 * separated by a delimiter
 *
 * @code
 * std::vector<int> c = {1, 2, 3}; 
 * parser.get_expression(R"(join . ",")")->retrieve(text::make_data(c));
 * // std::string result = "1,2,3"
 * @endcode
 */
struct SIPLUS_EXPORT join_func : Function  {
    explicit join_func(
        std::weak_ptr<SIPlusParserContext> context
    ) : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

/**
 * struct contains_func - Checks if an iterable contains another value.
 * Uses `eq` to compare values.
 */
struct SIPLUS_EXPORT contains_func : Function {
    explicit contains_func(
        std::weak_ptr<SIPlusParserContext> context
    ) : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

/**
 * struct each_func - Function for invoking an expression for each element of 
 * a list.
 *
 * @code
 * std::vector<int> c = {1, 2, 3}; 
 * parser.get_expression(R"(var $set = set_new; each . (set_add $set .); set_has 2)")->retrieve(text::make_data(c));
 * // true
 * @endcode
 */
struct SIPLUS_EXPORT each_func : Function  {
    explicit each_func(std::weak_ptr<SIPlusParserContext> context) 
        : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

/**
 * struct all_func - Function that checks if each element in an array matches 
 * a condition a list.
 *
 * @code
 * std::vector<bool> c = {true, false, true}; 
 * parser.get_expression(R"(all . (.))")->retrieve(text::make_data(c));
 * // false
 * @endcode
 */
struct SIPLUS_EXPORT all_func : Function  {
    explicit all_func(std::weak_ptr<SIPlusParserContext> context) 
        : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

/**
 * struct any_func - Function that checks if any element in a list matches a 
 * condition.
 *
 * @code
 * std::vector<int> c = {1, 2, 3}; 
 * parser.get_expression(R"(any . (gt . 3))")->retrieve(text::make_data(c));
 * // false
 * @endcode
 */
struct SIPLUS_EXPORT any_func : Function  {
    explicit any_func(std::weak_ptr<SIPlusParserContext> context) 
        : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_ITERABLE_HXX_
