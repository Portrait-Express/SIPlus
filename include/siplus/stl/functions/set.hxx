#pragma once
#ifndef INCLUDE_FUNCTIONS_SET_HXX_
#define INCLUDE_FUNCTIONS_SET_HXX_

#include "siplus/config.h"
#include "siplus/context.hxx"

#include <unordered_set>

namespace SIPLUS_NAMESPACE {
namespace stl {

struct SIPLUS_EXPORT SetType : public TypeInfo {
    using data_type = std::unordered_set<UnknownDataTypeContainer>;
    static const TypeInfoDescriptor *const descriptor;

    SetType();

    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;

    virtual std::unique_ptr<Iterator> iterate(const UnknownDataTypeContainer& data) const override;
};

/**
 * struct set_new_func - Function to create a new instance of a set
 */
struct SIPLUS_EXPORT set_new_func : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct set_has_func - Function to check if a set contains an item
 */
struct SIPLUS_EXPORT set_has_func : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

/**
 * struct set_add_func - Function to add an item to a set.
 */
struct SIPLUS_EXPORT set_add_func : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_FUNCTIONS_SET_HXX_
