#include "siplus/stl/functions/comparison.h"
#include "siplus/context.h"
#include "siplus/invocation_context.h"
#include "siplus/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/types/bool.h"
#include "siplus/types/integer.h"
#include <memory>

namespace SIPLUS_NAMESPACE {
namespace stl {



namespace {

struct lt_impl : text::ValueRetriever  {
    explicit lt_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> cmp
    ) : ctx_(context), cmp_(cmp) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> cmp_;
};

struct gt_impl : text::ValueRetriever  {
    explicit gt_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> cmp
    ) : ctx_(context), cmp_(cmp) { }

    explicit gt_impl(std::weak_ptr<SIPlusParserContext> context) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> cmp_;
};

struct eq_impl : text::ValueRetriever  {
    explicit eq_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> cmp
    ) : ctx_(context), cmp_(cmp) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> cmp_;
};

} /* anonymous */

std::shared_ptr<text::ValueRetriever> lt_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto cmp = cmp_->value(parent, parameters);
    return std::make_shared<lt_impl>(ctx_, cmp);
}

UnknownDataTypeContainer 
lt_impl::retrieve(InvocationContext& val) const {
    auto ctx = ctx_.lock();
    auto cmp_val = cmp_->retrieve(val);
    auto result = ctx->convert<types::IntegerType>(cmp_val).as<types::IntegerType>();
    return make_data<types::BoolType>(result < 0);
}

std::shared_ptr<text::ValueRetriever> gt_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto cmp = cmp_->value(parent, parameters);
    return std::make_shared<gt_impl>(ctx_, cmp);
}

UnknownDataTypeContainer 
gt_impl::retrieve(InvocationContext& val) const {
    auto ctx = ctx_.lock();
    auto cmp_val = cmp_->retrieve(val);
    auto result = ctx->convert<types::IntegerType>(cmp_val).as<types::IntegerType>();
    return make_data<types::BoolType>(result > 0);
}

std::shared_ptr<text::ValueRetriever> eq_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto cmp = cmp_->value(parent, parameters);
    return std::make_shared<eq_impl>(ctx_, cmp);
}

UnknownDataTypeContainer 
eq_impl::retrieve(InvocationContext& val) const {
    auto ctx = ctx_.lock();
    auto cmp_val = cmp_->retrieve(val);
    auto result = ctx->convert<types::IntegerType>(cmp_val).as<types::IntegerType>();
    return make_data<types::BoolType>(result == 0);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
