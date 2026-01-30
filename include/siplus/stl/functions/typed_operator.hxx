#pragma once
#ifndef INCLUDE_FUNCTIONS_BOOLEAN_HXX_
#define INCLUDE_FUNCTIONS_BOOLEAN_HXX_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>
#include <vector>

#include "siplus/data.hxx"
#include "siplus/invocation_context.hxx"
#include "siplus/util.hxx"
#include "siplus/context.hxx"
#include "siplus/function.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

template<simple_value_retrievable_type T, simple_value_retrievable_type V>
struct typed_binary_operator_function : Function {
    using operator_function = std::function<typename V::data_type (typename T::data_type, typename T::data_type)>;

    typed_binary_operator_function(
        std::weak_ptr<SIPlusParserContext> context,
        operator_function operate
    ) : context_(context), operator_(operate) {}

    std::shared_ptr<text::ValueRetriever> 
    value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override {
        auto [a, b] = util::get_parameters_first_parent<2>(parent, parameters);
        return std::make_shared<impl>(context_, operator_, a, b);
    }

    struct impl : text::ValueRetriever {
        impl(
            std::weak_ptr<SIPlusParserContext> context,
            operator_function operate,
            std::shared_ptr<text::ValueRetriever> a,
            std::shared_ptr<text::ValueRetriever> b
        ) : context_(context), operator_(operate), a_(a), b_(b) {}

        UnknownDataTypeContainer
        retrieve(InvocationContext& value) const override {
            auto ctx = context_.lock();

            typename T::data_type a = ctx->convert<T>(a_->retrieve(value)).template as<T>();
            typename T::data_type b = ctx->convert<T>(b_->retrieve(value)).template as<T>();

            return make_data<V>(operator_(a, b));
        }

    private:
        std::weak_ptr<SIPlusParserContext> context_;
        std::shared_ptr<text::ValueRetriever> a_;
        std::shared_ptr<text::ValueRetriever> b_;
        operator_function operator_;
    };

private:
    std::weak_ptr<SIPlusParserContext> context_;
    operator_function operator_;
};

template<simple_value_retrievable_type T, simple_value_retrievable_type V>
struct typed_unary_operator_function : Function {
    using operator_function = std::function<typename V::data_type (typename T::data_type)>;

    typed_unary_operator_function(
        std::weak_ptr<SIPlusParserContext> context,
        operator_function operate
    ) : context_(context), operator_(operate) {}

    std::shared_ptr<text::ValueRetriever> 
    value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override {
        auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
        return std::make_shared<impl>(context_, operator_, input);
    }

    struct impl : text::ValueRetriever {
        impl(
            std::weak_ptr<SIPlusParserContext> context,
            operator_function operate,
            std::shared_ptr<text::ValueRetriever> a
        ) : context_(context), operator_(operate), a_(a) {}

        UnknownDataTypeContainer
        retrieve(InvocationContext& value) const override {
            auto ctx = context_.lock();
            UnknownDataTypeContainer a = ctx->convert<T>(a_->retrieve(value));
            return make_data<V>(operator_(a.as<T>()));
        }

    private:
        std::weak_ptr<SIPlusParserContext> context_;
        std::shared_ptr<text::ValueRetriever> a_;
        operator_function operator_;
    };

private:
    std::weak_ptr<SIPlusParserContext> context_;
    operator_function operator_;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_BOOLEAN_HXX_
