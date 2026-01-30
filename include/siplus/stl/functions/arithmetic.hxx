#pragma once
#ifndef INCLUDE_FUNCTIONS_ARITHMETIC_HXX_
#define INCLUDE_FUNCTIONS_ARITHMETIC_HXX_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>

#include "siplus/context.hxx"
#include "siplus/stl/functions/converting_operator.hxx"
#include "siplus/data.hxx"
#include "siplus/text/text.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

//These are meant to be used as implementations for a converting_operator_function

/**
 * struct base_numeric_operator_impl - Base class for numeric operator 
 * implementations. Implements `can_handle`.
 */
struct base_numeric_operator_impl : operator_impl {
    bool can_handle(const TypeInfo& lhs, const TypeInfo& rhs) const override {
        return (lhs.is<types::IntegerType>() || lhs.is<types::FloatType>()) &&
            (rhs.is<types::IntegerType>() || rhs.is<types::FloatType>());
    }
};

struct numeric_adder : base_numeric_operator_impl {
    UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        UnknownDataTypeContainer lhs, 
        UnknownDataTypeContainer rhs
    ) override;
};

struct numeric_subtractor : base_numeric_operator_impl {
    UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        UnknownDataTypeContainer lhs, 
        UnknownDataTypeContainer rhs
    ) override;
};

struct numeric_multiplier : base_numeric_operator_impl {
    UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        UnknownDataTypeContainer lhs, 
        UnknownDataTypeContainer rhs
    ) override;
};

struct numeric_divider : base_numeric_operator_impl {
    UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        UnknownDataTypeContainer lhs, 
        UnknownDataTypeContainer rhs
    ) override;
};

struct numeric_comparator : base_numeric_operator_impl {
    UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        UnknownDataTypeContainer lhs, 
        UnknownDataTypeContainer rhs
    ) override;

};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_ARITHMETIC_HXX_
