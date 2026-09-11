#pragma once
#ifndef INCLUDE_FUNCTIONS_RAND_HXX_
#define INCLUDE_FUNCTIONS_RAND_HXX_

#include <memory>
#include <vector>

#include "siplus/config.h"
#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * struct rand_func - Generate a random number
 */
struct SIPLUS_EXPORT rand_func : Function  {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct rand_str_func - Generate a random string following a template
 */
struct SIPLUS_EXPORT rand_str_func : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_FUNCTIONS_RAND_HXX_
