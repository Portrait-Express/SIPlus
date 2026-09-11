#pragma once
#ifndef INCLUDE_TYPES_INTEGRAL_HXX_
#define INCLUDE_TYPES_INTEGRAL_HXX_

#include "siplus/context.hxx"


namespace SIPLUS_NAMESPACE {
namespace types {


struct IntegralAddable : BinaryOperatorTypeExtensionImpl {
    IntegralAddable();

    bool can_handle(const UnknownDataTypeContainer &other) const override;

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer &thisValue, 
        const UnknownDataTypeContainer &other
    ) const override;
};

struct IntegralSubtractable : BinaryOperatorTypeExtensionImpl {
    IntegralSubtractable();

    bool can_handle(const UnknownDataTypeContainer &other) const override;

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer &thisValue, 
        const UnknownDataTypeContainer &other
    ) const override;
};

struct IntegralMultiplicable : BinaryOperatorTypeExtensionImpl {
    IntegralMultiplicable();

    bool can_handle(const UnknownDataTypeContainer &other) const override;

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer &thisValue, 
        const UnknownDataTypeContainer &other
    ) const override;
};

struct IntegralDivisible : BinaryOperatorTypeExtensionImpl {
    IntegralDivisible();

    bool can_handle(const UnknownDataTypeContainer &other) const override;

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer &thisValue, 
        const UnknownDataTypeContainer &other
    ) const override;
};

struct IntegralComparable : BinaryOperatorTypeExtensionImpl {
    IntegralComparable();

    bool can_handle(const UnknownDataTypeContainer &other) const override;

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer &thisValue, 
        const UnknownDataTypeContainer &other
    ) const override;
};

UnknownDataTypeContainer do_integral_binary(
    const UnknownDataTypeContainer& lhs, 
    const UnknownDataTypeContainer& rhs,
    std::function<long (long, long)> iiCallback,
    std::function<double (long, double)> ifCallback,
    std::function<double (double, double)> ffCallback
);


} /* types */
} /* SIPLUS_NAMESPACE */


#endif  // INCLUDE_TYPES_INTEGRAL_HXX_
