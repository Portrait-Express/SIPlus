#ifndef INCLUDE_FUNCTIONS_ARITHMETIC_H_
#define INCLUDE_FUNCTIONS_ARITHMETIC_H_

#include "siplus/config.h"
#include "siplus/stl/functions/converting_operator.h"
#include "siplus/text/text.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>

#include "siplus/context.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

//These are meant to be used as implementations for a converting_operator_function

/**
 * struct base_numeric_operator_impl - Base class for numeric operator 
 * implementations. Implements `can_handle`.
 */
struct base_numeric_operator_impl : operator_impl {
    bool can_handle(std::type_index lhs, std::type_index rhs) const override {
        return text::is_numeric(lhs) && text::is_numeric(rhs);
    }
};

struct numeric_adder : base_numeric_operator_impl {
    text::UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer lhs, 
        text::UnknownDataTypeContainer rhs
    ) override;
};

struct numeric_subtractor : base_numeric_operator_impl {
    text::UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer lhs, 
        text::UnknownDataTypeContainer rhs
    ) override;
};

struct numeric_multiplier : base_numeric_operator_impl {
    text::UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer lhs, 
        text::UnknownDataTypeContainer rhs
    ) override;
};

struct numeric_divider : base_numeric_operator_impl {
    text::UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer lhs, 
        text::UnknownDataTypeContainer rhs
    ) override;
};

struct numeric_comparator : base_numeric_operator_impl {
    text::UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer lhs, 
        text::UnknownDataTypeContainer rhs
    ) override;

};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_ARITHMETIC_H_
