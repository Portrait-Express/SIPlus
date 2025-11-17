
#ifndef INCLUDE_FUNCTIONS_BOOLEAN_H_
#define INCLUDE_FUNCTIONS_BOOLEAN_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>

#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

template<typename T>
struct typed_operator_function : Function {
    typed_operator_function(
        std::weak_ptr<SIPlusParserContext> context,
        std::function<T(T,T)> comparator
    ) : context_(context), comparator_(comparator) {}

    std::shared_ptr<text::ValueRetriever> 
    value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override {
        std::shared_ptr<text::ValueRetriever> a;
        std::shared_ptr<text::ValueRetriever> b;

        if(parent) {
            if(parameters.size() != 1) {
                throw std::runtime_error{"Expected one parameter"};
            }

            a = parent;
            b = parameters[0];
        } else {
            if(parameters.size() != 2) {
                throw std::runtime_error{"Expected two parameters"};
            }

            a = parameters[0];
            b = parameters[1];
        }

        return std::make_shared<impl>(context_, comparator_, a, b);
    }

    struct impl : text::ValueRetriever {
        impl(
            std::weak_ptr<SIPlusParserContext> context,
            std::function<T(T,T)> comparator,
            std::shared_ptr<text::ValueRetriever> a,
            std::shared_ptr<text::ValueRetriever> b
        ) : context_(context), comparator_(comparator), a_(a), b_(b) {}

        text::UnknownDataTypeContainer
        retrieve(const text::UnknownDataTypeContainer &value) const override {
            auto ctx = context_.lock();

            T a = ctx->convert<T>(a_->retrieve(value)).template as<T>();
            T b = ctx->convert<T>(b_->retrieve(value)).template as<T>();

            return text::make_data(comparator_(a, b));
        }

    private:
        std::weak_ptr<SIPlusParserContext> context_;
        std::shared_ptr<text::ValueRetriever> a_;
        std::shared_ptr<text::ValueRetriever> b_;
        std::function<T(T,T)> comparator_;
    };

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::function<T(T,T)> comparator_;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_BOOLEAN_H_
