#pragma once
#ifndef INCLUDE_FUNCTIONS_TYPE_HXX_
#define INCLUDE_FUNCTIONS_TYPE_HXX_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/function.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * struct type_function - Function to get the type name of the parameter
 */
struct SIPLUS_EXPORT type_function : Function {
    virtual std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;
};
    
} /* stl */
} /* SIPLUS_NAMESPACE */

#endif

#endif  // INCLUDE_FUNCTIONS_TYPE_HXX_
