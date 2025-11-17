#ifndef INCLUDE_FUNCTIONS_TEXT_H_
#define INCLUDE_FUNCTIONS_TEXT_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {
 
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

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB
#endif  // INCLUDE_FUNCTIONS_TEXT_H_
