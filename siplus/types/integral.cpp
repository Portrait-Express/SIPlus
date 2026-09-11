#include <stdexcept>
#include <tuple>
#include <utility>

#include "siplus/context.hxx"
#include "integral.hxx"
#include "../util.hxx"
#include "siplus/util.hxx"

#define SWITCH_INTEGRAL(value, var, expression) if(value.is<IntegerType>()) { \
        auto var = value.as<IntegerType>(); \
        expression; \
    } else if(value.is<FloatType>()) { \
        auto var = value.as<FloatType>(); \
        expression; \
    } else { \
        throw std::runtime_error{util::to_string( \
            "Unknown type '", value.type->name(), "' passed to integral extension." \
        )}; \
    }

namespace SIPLUS_NAMESPACE {
namespace types {

IntegralAddable::IntegralAddable() 
    : BinaryOperatorTypeExtensionImpl(TypeInfo::Addable) {}

bool IntegralAddable::can_handle(const UnknownDataTypeContainer &other) const {
    return other.is<IntegerType>() || other.is<FloatType>();
}

UnknownDataTypeContainer IntegralAddable::invoke(
    bool isLhs, 
    const UnknownDataTypeContainer &thisValue, 
    const UnknownDataTypeContainer &other
) const {
    auto [lhs, rhs] = resolve_lhs(isLhs, thisValue, other);

    SWITCH_INTEGRAL(lhs, lhsV, SWITCH_INTEGRAL(rhs, rhsV, return make_data(lhsV + rhsV)));
}



IntegralSubtractable::IntegralSubtractable() 
    : BinaryOperatorTypeExtensionImpl(TypeInfo::Subtractable) {}

bool IntegralSubtractable::can_handle(const UnknownDataTypeContainer &other) const {
    return other.is<IntegerType>() || other.is<FloatType>();
}

UnknownDataTypeContainer IntegralSubtractable::invoke(
    bool isLhs, 
    const UnknownDataTypeContainer &thisValue, 
    const UnknownDataTypeContainer &other
) const {
    auto [lhs, rhs] = resolve_lhs(isLhs, thisValue, other);

    SWITCH_INTEGRAL(lhs, lhsV, SWITCH_INTEGRAL(rhs, rhsV, return make_data(lhsV - rhsV)));
}



IntegralMultiplicable::IntegralMultiplicable() 
    : BinaryOperatorTypeExtensionImpl(TypeInfo::Multiplicable) {}

bool IntegralMultiplicable::can_handle(const UnknownDataTypeContainer &other) const {
    return other.is<IntegerType>() || other.is<FloatType>();
}

UnknownDataTypeContainer IntegralMultiplicable::invoke(
    bool isLhs, 
    const UnknownDataTypeContainer &thisValue, 
    const UnknownDataTypeContainer &other
) const {
    auto [lhs, rhs] = resolve_lhs(isLhs, thisValue, other);

    SWITCH_INTEGRAL(lhs, lhsV, SWITCH_INTEGRAL(rhs, rhsV, return make_data(lhsV * rhsV)));
}



IntegralDivisible::IntegralDivisible() 
    : BinaryOperatorTypeExtensionImpl(TypeInfo::Divisible) {}

bool IntegralDivisible::can_handle(const UnknownDataTypeContainer &other) const {
    return other.is<IntegerType>() || other.is<FloatType>();
}

UnknownDataTypeContainer IntegralDivisible::invoke(
    bool isLhs, 
    const UnknownDataTypeContainer &thisValue, 
    const UnknownDataTypeContainer &other
) const {
    auto [lhs, rhs] = resolve_lhs(isLhs, thisValue, other);

    SWITCH_INTEGRAL(lhs, lhsV, SWITCH_INTEGRAL(rhs, rhsV, return make_data((double)lhsV / (double)rhsV)));
}



IntegralComparable::IntegralComparable() 
    : BinaryOperatorTypeExtensionImpl(TypeInfo::Comparable) {}

bool IntegralComparable::can_handle(const UnknownDataTypeContainer &other) const {
    return other.is<IntegerType>() || other.is<FloatType>();
}

UnknownDataTypeContainer IntegralComparable::invoke(
    bool isLhs, 
    const UnknownDataTypeContainer &thisValue, 
    const UnknownDataTypeContainer &other
) const {
    auto [lhs, rhs] = resolve_lhs(isLhs, thisValue, other);

    SWITCH_INTEGRAL(lhs, lhsV, SWITCH_INTEGRAL(rhs, rhsV, return make_data(detail::compare(lhsV, rhsV))));
}



} /* types */
} /* SIPLUS_NAMESPACE */
