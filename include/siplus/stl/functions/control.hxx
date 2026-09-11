#pragma once
#ifndef INCLUDE_FUNCTIONS_IF_HXX_
#define INCLUDE_FUNCTIONS_IF_HXX_

#include <memory>
#include <vector>

#include "siplus/config.h"
#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * struct if_func - If statement
 */
struct SIPLUS_EXPORT if_func : Function  {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct while_func - While loop
 */
struct SIPLUS_EXPORT while_func : Function  {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_FUNCTIONS_IF_HXX_
