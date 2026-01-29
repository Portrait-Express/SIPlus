#pragma once
#ifndef INCLUDE_FUNCTIONS_ITERABLE_H_
#define INCLUDE_FUNCTIONS_ITERABLE_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>
#include <vector>

#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * struct map_func - Function for mapping an expression over each element 
 * of the iterable. 
 *
 * IMPORTANT:
 * If you include this, and arent using `attach_stl()`, or 
 * `attach_stl_functions()` be sure to add an `IteratorProvider` instance of 
 * `vector_iterator<UnknownDataTypeContainer>`, otherwise the value
 * returned from this function will not be iterable.
 *
 * @code
 * std::vector<int> c = {1, 2, 3}; 
 * parser.get_expression(R"(map . (add . 2))")->retrieve(text::make_data(c));
 * // std::vector<double> result = {3, 4, 5};
 * @endcode
 */
struct map_func : Function  {
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
struct length_func : Function  {
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
struct join_func : Function  {
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

struct contains_func : Function {
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

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_ITERABLE_H_
