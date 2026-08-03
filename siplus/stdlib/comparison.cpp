#include "siplus/stl/functions/comparison.hxx"
#include "siplus/context.hxx"
#include "siplus/types/bool.hxx"
#include "siplus/types/integer.hxx"
#include <memory>

namespace SIPLUS_NAMESPACE {
namespace stl {



namespace {

struct lt_impl : ValueRetriever  {
    explicit lt_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<ValueRetriever> cmp
    ) : ctx_(context), cmp_(cmp) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<ValueRetriever> cmp_;
};

struct gt_impl : ValueRetriever  {
    explicit gt_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<ValueRetriever> cmp
    ) : ctx_(context), cmp_(cmp) { }

    explicit gt_impl(std::weak_ptr<SIPlusParserContext> context) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<ValueRetriever> cmp_;
};

struct eq_impl : ValueRetriever  {
    explicit eq_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<ValueRetriever> cmp
    ) : ctx_(context), cmp_(cmp) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<ValueRetriever> cmp_;
};

} /* anonymous */

std::shared_ptr<ValueRetriever> lt_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
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

std::shared_ptr<ValueRetriever> gt_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
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

std::shared_ptr<ValueRetriever> eq_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
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
