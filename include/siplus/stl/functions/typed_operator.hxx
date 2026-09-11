#pragma once
#ifndef INCLUDE_FUNCTIONS_BOOLEAN_HXX_
#define INCLUDE_FUNCTIONS_BOOLEAN_HXX_

#include <memory>
#include <vector>

#include "siplus/config.h"
#include "siplus/context.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * struct typed_binary_operator_function - A Binary operator implementation that 
 * tries to convert its operands to type specified in code prior to operating.
 *
 * @tparam simple_value_retrievable_type The type to convert the operands to
 * @tparam simple_value_retrievable_type The type to make_data with the result
 */
template<simple_value_retrievable_type T, simple_value_retrievable_type V>
struct typed_binary_operator_function : Function {
    using operator_function = std::function<typename V::data_type (typename T::data_type, typename T::data_type)>;

    typed_binary_operator_function(operator_function operate) : operator_(operate) {}

    std::shared_ptr<ValueRetriever> 
    value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override {
        auto [a, b] = util::get_parameters_first_parent<2>(parent, parameters);
        return std::make_shared<impl>(operator_, a, b);
    }

    struct impl : ValueRetriever {
        impl(
            operator_function operate,
            std::shared_ptr<ValueRetriever> a,
            std::shared_ptr<ValueRetriever> b
        ) : operator_(operate), a_(a), b_(b) {}

        UnknownDataTypeContainer
        retrieve(InvocationContext& value) const override {
            typename T::data_type a = a_->retrieve(value).convert<T>().template as<T>();
            typename T::data_type b = b_->retrieve(value).convert<T>().template as<T>();

            return make_data<V>(operator_(a, b));
        }

    private:
        std::shared_ptr<ValueRetriever> a_;
        std::shared_ptr<ValueRetriever> b_;
        operator_function operator_;
    };

private:
    operator_function operator_;
};

/**
 * struct typed_unary_operator_function - Like typed_binary_operator_function, 
 * but for unary operations.
 *
 * @tparam simple_value_retrievable_type The type to convert the operands to
 * @tparam simple_value_retrievable_type The type to make_data with the result
 */
template<simple_value_retrievable_type T, simple_value_retrievable_type V>
struct typed_unary_operator_function : Function {
    using operator_function = std::function<typename V::data_type (typename T::data_type)>;

    typed_unary_operator_function(operator_function operate) : operator_(operate) {}

    std::shared_ptr<ValueRetriever> 
    value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override {
        auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
        return std::make_shared<impl>(operator_, input);
    }

    struct impl : ValueRetriever {
        impl(
            operator_function operate,
            std::shared_ptr<ValueRetriever> a
        ) : operator_(operate), a_(a) {}

        UnknownDataTypeContainer
        retrieve(InvocationContext& value) const override {
            UnknownDataTypeContainer a = a_->retrieve(value).convert<T>();
            return make_data<V>(operator_(a.as<T>()));
        }

    private:
        std::shared_ptr<ValueRetriever> a_;
        operator_function operator_;
    };

private:
    operator_function operator_;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_FUNCTIONS_BOOLEAN_HXX_
