#include "siplus/stl/functions/converting_operator.h"
#include "siplus/text/data.h"
#include "siplus/text/text.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/util.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct converting_operator_impl : text::ValueRetriever {
    converting_operator_impl(
        const converting_operator_function& parent,
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> lhs,
        std::shared_ptr<text::ValueRetriever> rhs
    ) : parent_(parent), ctx_(ctx), lhs_(lhs), rhs_(rhs) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    const converting_operator_function& parent_;
    std::shared_ptr<text::ValueRetriever> lhs_;
    std::shared_ptr<text::ValueRetriever> rhs_;
    std::weak_ptr<SIPlusParserContext> ctx_;
};

} /* anonymous */

bool 
converting_operator_function::has_impl(std::type_index lhs, std::type_index rhs) const {
    return cache_.find(lhs, rhs) != cache_.end();;
}

std::shared_ptr<operator_impl> 
converting_operator_function::find_impl(std::type_index lhs, std::type_index rhs) const {
    return *cache_.find(lhs, rhs);
}

std::shared_ptr<text::ValueRetriever>
converting_operator_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    std::shared_ptr<text::ValueRetriever> lhs;
    std::shared_ptr<text::ValueRetriever> rhs;

    if(parent) {
        lhs = parent;

        if(parameters.size() != 1) {
            throw std::runtime_error{""};
        }

        rhs = parameters[0];
    } else {
        if(parameters.size() != 2) {
            throw std::runtime_error{""};
        }

        lhs = parameters[0];
        rhs = parameters[1];
    }

    return std::make_shared<converting_operator_impl>(*this, context_, lhs, rhs);
}

text::UnknownDataTypeContainer
converting_operator_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    std::shared_ptr<SIPlusParserContext> ctx = ctx_.lock();
    text::UnknownDataTypeContainer lhs = lhs_->retrieve(value);
    text::UnknownDataTypeContainer rhs = rhs_->retrieve(value);

    if(parent_.has_impl(lhs.type, rhs.type)) {
        auto adder = parent_.find_impl(lhs.type, rhs.type);
        return adder->invoke(ctx, lhs, rhs);

    } else if(ctx->try_converter(rhs.type, lhs.type) && parent_.has_impl(lhs.type, lhs.type)) { // Can convert rhs to lhs type
        auto adder = parent_.find_impl(lhs.type, lhs.type);
        return adder->invoke(ctx, lhs, ctx->convert(rhs, lhs.type));

    } else if(ctx->try_converter(lhs.type, rhs.type) && parent_.has_impl(rhs.type, rhs.type)) { // Can convert lhs to rhs type
        auto adder = parent_.find_impl(rhs.type, rhs.type);
        return adder->invoke(ctx, ctx->convert(lhs, rhs.type), rhs);

    } else {
        throw std::runtime_error{"Unsure how to operate on " + 
            text::get_type_name(lhs.type) + " and " + text::get_type_name(rhs.type)};
    }
}

} /* stl */
} /* SIPLUS_NAMESPACE */
