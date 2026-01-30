#pragma once
#ifndef INCLUDE_FUNCTIONS_TEXT_HXX_
#define INCLUDE_FUNCTIONS_TEXT_HXX_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>
#include <vector>

#include "siplus/context.hxx"
#include "siplus/function.hxx"
#include "siplus/stl/functions/converting_operator.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {
 
struct str_func : Function  {
    explicit str_func(std::weak_ptr<SIPlusParserContext> context) : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

    std::weak_ptr<SIPlusParserContext> context_;

};

/**
 * struct replace_function - Function to replace text in the string with another string
 */
struct replace_function : Function {
    replace_function(std::weak_ptr<SIPlusParserContext> context) : ctx_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
};

/**
 * struct pad_end_function - Function to pad the end of a string to a specified length
 */
struct pad_end_function : Function {
    pad_end_function(std::weak_ptr<SIPlusParserContext> context) : ctx_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
};

/**
 * struct pad_start_function - Function to pad the start of a string to a specified length
 */
struct pad_start_function : Function {
    pad_start_function(std::weak_ptr<SIPlusParserContext> context) : ctx_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
};

/**
 * struct trim_function - Function to trim the leading and trailing whitespace from the text
 */
struct trim_function : Function {
    trim_function(std::weak_ptr<SIPlusParserContext> context) : ctx_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
};

/**
 * struct upper_function - Function to convert the text to uppercase
 */
struct upper_function : Function {
    upper_function(std::weak_ptr<SIPlusParserContext> context) : ctx_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
};

/**
 * struct lower_function - Function to convert the text to lowercase.
 */
struct lower_function : Function {
    lower_function(std::weak_ptr<SIPlusParserContext> context) : ctx_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
};

struct split_function : Function {
    split_function(std::weak_ptr<SIPlusParserContext> context) : ctx_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
};

struct substr_function : Function {
    substr_function(std::weak_ptr<SIPlusParserContext> context) : ctx_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
};

struct string_concatenator : operator_impl {
    UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        UnknownDataTypeContainer lhs, 
        UnknownDataTypeContainer rhs
    ) override;

    bool can_handle(const TypeInfo& lhs, const TypeInfo& rhs) const override;
};

struct string_comparator : operator_impl {
    UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        UnknownDataTypeContainer lhs, 
        UnknownDataTypeContainer rhs
    ) override;

    bool can_handle(const TypeInfo& lhs, const TypeInfo& rhs) const override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB
#endif  // INCLUDE_FUNCTIONS_TEXT_HXX_
