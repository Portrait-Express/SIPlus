#include "siplus/stl/functions/arithmetic.h"
#include "siplus/data.h"
#include "siplus/types/float.h"
#include "siplus/types/integer.h"

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
UnknownDataTypeContainer 
numerically_operate(
    std::shared_ptr<SIPlusParserContext> context,
    UnknownDataTypeContainer       lhs, 
    UnknownDataTypeContainer       rhs
) {
    using int_t = types::IntegerType::data_type;
    using float_t = types::FloatType::data_type;

    if(lhs.is<types::IntegerType>()) {
        int_t val = lhs.as<types::IntegerType>();

        if(rhs.is<types::IntegerType>()) { 
            return make_data(operate<int_t, int_t>::invoke(val, rhs.as<types::IntegerType>()));
        } else if(rhs.is<types::FloatType>()) {
            return make_data(operate<int_t, float_t>::invoke(val, rhs.as<types::FloatType>()));
        } else {
            throw std::runtime_error{"Cannot add types long and " + rhs.type->name()};
        }
    } else if(lhs.is<types::FloatType>()) {
        float_t val = lhs.as<types::FloatType>();

        if(rhs.is<types::IntegerType>()) { 
            return make_data(operate<float_t, int_t>::invoke(val, rhs.as<types::IntegerType>()));
        } else if(rhs.is<types::FloatType>()) {
            return make_data(operate<float_t, float_t>::invoke(val, rhs.as<types::FloatType>()));
        } else {
            throw std::runtime_error{"Cannot add types double and " + rhs.type->name()};
        }
    } else {
        throw std::runtime_error{"Cannot add types " + lhs.type->name() + " and " + rhs.type->name()};
    }
}

template<typename _T1, typename _T2>
struct add_operator {
    static inline auto invoke(const _T1& a, const _T2& b) {
        return a + b;
    }
};

UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_adder::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    UnknownDataTypeContainer       lhs, 
    UnknownDataTypeContainer       rhs
) {
    return numerically_operate<add_operator>(context, lhs, rhs);
}

template<typename _T1, typename _T2>
struct subtract_operator {
    static inline auto invoke(const _T1& a, const _T2& b) {
        return a - b;
    }
};

UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_subtractor::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    UnknownDataTypeContainer       lhs, 
    UnknownDataTypeContainer       rhs
) {
    return numerically_operate<subtract_operator>(context, lhs, rhs);
}

template<typename _T1, typename _T2>
struct multiply_operator {
    static inline auto invoke(const _T1& a, const _T2& b) {
        return a * b;
    }
};

UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_multiplier::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    UnknownDataTypeContainer       lhs, 
    UnknownDataTypeContainer       rhs
) {
    return numerically_operate<multiply_operator>(context, lhs, rhs);
}

template<typename _T1, typename _T2>
struct divide_operator {
    static inline auto invoke(const _T1& a, const _T2& b) {
        return static_cast<types::FloatType::data_type>(a) / b;
    }
};

UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_divider::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    UnknownDataTypeContainer       lhs, 
    UnknownDataTypeContainer       rhs
) {
    return numerically_operate<divide_operator>(context, lhs, rhs);
}

template<typename T1, typename T2>
struct compare_operator {
    static inline types::IntegerType::data_type invoke(T1 a, T2 b) {
        if(a < b) {
            return -1;
        } else if(a > b) {
            return 1;
        } else {
            return 0;
        }
    }
};

UnknownDataTypeContainer 
numeric_comparator::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    UnknownDataTypeContainer lhs, 
    UnknownDataTypeContainer rhs
) {
    return numerically_operate<compare_operator>(context, lhs, rhs);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
