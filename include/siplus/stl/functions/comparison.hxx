#pragma once
#ifndef INCLUDE_FUNCTIONS_COMPARISON_HXX_
#define INCLUDE_FUNCTIONS_COMPARISON_HXX_

#include <memory>
#include <vector>

#include "siplus/config.h"
#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {


/**
 * @brief Implementation for the 'lt' function
 */
struct SIPLUS_EXPORT LessThanFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * @brief Implementation for the 'gt' function
 */
struct SIPLUS_EXPORT GreaterThanFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * @brief Implementation for the 'lte' function
 */
struct SIPLUS_EXPORT LessThanEqualFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * @brief Implementation for the 'gte' function.
 */
struct SIPLUS_EXPORT GreaterThanEqualFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * @brief Implementation for the 'eq' function
 */
struct SIPLUS_EXPORT EqualsFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * @brief Implementation for the 'cmp' function. 
 */
struct SIPLUS_EXPORT CompareFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};


} /* stl */
} /* SIPLUS_NAMESPACE */


#endif  // INCLUDE_FUNCTIONS_COMPARISON_HXX_
