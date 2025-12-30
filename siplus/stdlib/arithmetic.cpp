#include "siplus/stl/functions/arithmetic.h"
#include "siplus/text/data.h"
#include "siplus/text/text.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * @brief Invoke operate::invoke() with template arguments matching the types 
 * in the UnknownDataTypeContainers.
 *
 * Only works if text::is_numeric(lhs) && text::is_numeric(rhs),
 *
 * @param[in] context The context
 * @param[in] lhs Left-hand argument
 * @param[in] rhs Right-hand argument
 */
template<template<typename _T1, typename _T2> typename operate>
text::UnknownDataTypeContainer 
numerically_operate(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer       lhs, 
    text::UnknownDataTypeContainer       rhs
) {
    lhs = text::as_base(context, lhs);
    rhs = text::as_base(context, rhs);

    if(lhs.is<long>()) {
        long val = lhs.as<long>();

        if(rhs.is<long>()) { 
            return text::make_data(operate<long, long>::invoke(val, rhs.as<long>()));
        } else if(rhs.is<double>()) {
            return text::make_data(operate<long, double>::invoke(val, rhs.as<double>()));
        } else {
            throw std::runtime_error{"Cannot add types long and " + text::get_type_name(rhs.type)};
        }
    } else if(lhs.is<double>()) {
        double val = lhs.as<double>();

        if(rhs.is<long>()) { 
            return text::make_data(operate<double, long>::invoke(val, rhs.as<long>()));
        } else if(rhs.is<double>()) {
            return text::make_data(operate<double, double>::invoke(val, rhs.as<double>()));
        } else {
            throw std::runtime_error{"Cannot add types double and " + text::get_type_name(rhs.type)};
        }
    } else {
        throw std::runtime_error{"Cannot add types " + text::get_type_name(lhs.type) 
            + " and " + text::get_type_name(rhs.type)};
    }
}

template<typename _T1, typename _T2>
struct add_operator {
    static inline auto invoke(const _T1& a, const _T2& b) {
        return a + b;
    }
};

text::UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_adder::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer       lhs, 
    text::UnknownDataTypeContainer       rhs
) {
    return numerically_operate<add_operator>(context, lhs, rhs);
}

template<typename _T1, typename _T2>
struct subtract_operator {
    static inline auto invoke(const _T1& a, const _T2& b) {
        return a - b;
    }
};

text::UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_subtractor::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer       lhs, 
    text::UnknownDataTypeContainer       rhs
) {
    return numerically_operate<subtract_operator>(context, lhs, rhs);
}

template<typename _T1, typename _T2>
struct multiply_operator {
    static inline auto invoke(const _T1& a, const _T2& b) {
        return a * b;
    }
};

text::UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_multiplier::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer       lhs, 
    text::UnknownDataTypeContainer       rhs
) {
    return numerically_operate<multiply_operator>(context, lhs, rhs);
}

template<typename _T1, typename _T2>
struct divide_operator {
    static inline auto invoke(const _T1& a, const _T2& b) {
        return static_cast<double>(a) / b;
    }
};

text::UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_divider::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer       lhs, 
    text::UnknownDataTypeContainer       rhs
) {
    return numerically_operate<divide_operator>(context, lhs, rhs);
}

template<typename T1, typename T2>
struct compare_operator {
    static inline long invoke(T1 a, T2 b) {
        if(a < b) {
            return -1;
        } else if(a > b) {
            return 1;
        } else {
            return 0;
        }
    }
};

text::UnknownDataTypeContainer 
numeric_comparator::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer lhs, 
    text::UnknownDataTypeContainer rhs
) {
    return numerically_operate<compare_operator>(context, lhs, rhs);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
