#pragma once
#ifndef INCLUDE_FUNCTIONS_TEXT_HXX_
#define INCLUDE_FUNCTIONS_TEXT_HXX_

#include <memory>
#include <vector>

#include "siplus/config.h"
#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {
 
/**
 * struct str_func - Explicitly convert a value to a string
 */
struct SIPLUS_EXPORT str_func : Function  {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct replace_function - Function to replace text in the string with another string
 */
struct SIPLUS_EXPORT replace_function : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct pad_end_function - Function to pad the end of a string to a specified length
 */
struct SIPLUS_EXPORT pad_end_function : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct pad_start_function - Function to pad the start of a string to a specified length
 */
struct SIPLUS_EXPORT pad_start_function : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct trim_function - Function to trim the leading and trailing whitespace from the text
 */
struct SIPLUS_EXPORT trim_function : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct upper_function - Function to convert the text to uppercase
 */
struct SIPLUS_EXPORT upper_function : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct lower_function - Function to convert the text to lowercase.
 */
struct SIPLUS_EXPORT lower_function : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct split_function - Split a string on a delimiter
 */
struct SIPLUS_EXPORT split_function : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct substr_function - Get a substring from a string
 */
struct SIPLUS_EXPORT substr_function : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};


} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_FUNCTIONS_TEXT_HXX_
