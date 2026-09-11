#pragma once
#ifndef INCLUDE_FUNCTIONS_ARITHMETIC_HXX_
#define INCLUDE_FUNCTIONS_ARITHMETIC_HXX_

#include <memory>

#include "siplus/config.h"
#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

struct SIPLUS_EXPORT AddFunction : Function {

    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT SubtractFunction : Function {

    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT MultiplyFunction : Function {

    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT DivideFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_FUNCTIONS_ARITHMETIC_HXX_
