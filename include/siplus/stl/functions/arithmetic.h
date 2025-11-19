#ifndef INCLUDE_FUNCTIONS_ARITHMETIC_H_
#define INCLUDE_FUNCTIONS_ARITHMETIC_H_

#include "siplus/config.h"
#include "siplus/stl/functions/converting_operator.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>

#include "siplus/context.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

struct numeric_adder : operator_impl {
    text::UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer lhs, 
        text::UnknownDataTypeContainer rhs
    ) override;

    bool can_handle(std::type_index lhs, std::type_index rhs) const override;
};

struct numeric_comparator : operator_impl {
    text::UnknownDataTypeContainer 
    invoke(
        std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer lhs, 
        text::UnknownDataTypeContainer rhs
    ) override;

    bool can_handle(std::type_index lhs, std::type_index rhs) const override;

private:
    template<typename T1, typename T2>
    long compare(T1 a, T2 b) {
        if(a < b) {
            return -1;
        } else if(a > b) {
            return 1;
        } else {
            return 0;
        }
    }
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_ARITHMETIC_H_
