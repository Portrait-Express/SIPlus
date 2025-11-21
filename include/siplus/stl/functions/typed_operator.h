
#ifndef INCLUDE_FUNCTIONS_BOOLEAN_H_
#define INCLUDE_FUNCTIONS_BOOLEAN_H_

#include "siplus/config.h"
#include "siplus/text/data.h"
#include "siplus/util.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>

#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

template<typename T, typename V>
struct typed_binary_operator_function : Function {
    using operator_function = std::function<V (T,T)>;

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

        text::UnknownDataTypeContainer
        retrieve(const text::UnknownDataTypeContainer &value) const override {
            auto ctx = context_.lock();

            T a = ctx->convert<T>(a_->retrieve(value)).template as<T>();
            T b = ctx->convert<T>(b_->retrieve(value)).template as<T>();

            return text::make_data(operator_(a, b));
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

template<typename T, typename V>
struct typed_unary_operator_function : Function {
    using operator_function = std::function<V (T)>;

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

        text::UnknownDataTypeContainer
        retrieve(const text::UnknownDataTypeContainer &value) const override {
            auto ctx = context_.lock();
            text::UnknownDataTypeContainer a = ctx->convert<T>(a_->retrieve(value));
            return text::make_data(operator_(a.as<T>()));
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

#endif  // INCLUDE_FUNCTIONS_BOOLEAN_H_
