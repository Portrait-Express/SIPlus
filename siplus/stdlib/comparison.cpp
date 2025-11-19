#include "siplus/stl/functions/comparison.h"
#include "siplus/context.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include <memory>

namespace SIPLUS_NAMESPACE {
namespace stl {



namespace {

struct lt_impl : text::ValueRetriever  {
    explicit lt_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> cmp
    ) : ctx_(context), cmp_(cmp) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const;

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

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> cmp_;
};

struct eq_impl : text::ValueRetriever  {
    explicit eq_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> cmp
    ) : ctx_(context), cmp_(cmp) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const;

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

text::UnknownDataTypeContainer 
lt_impl::retrieve(const text::UnknownDataTypeContainer& val) const {
    auto ctx = ctx_.lock();
    auto cmp_val = cmp_->retrieve(val);
    auto result = ctx->convert<long>(cmp_val).as<long>();
    return text::make_data(result < 0);
}

std::shared_ptr<text::ValueRetriever> gt_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto cmp = cmp_->value(parent, parameters);
    return std::make_shared<gt_impl>(ctx_, cmp);
}

text::UnknownDataTypeContainer 
gt_impl::retrieve(const text::UnknownDataTypeContainer& val) const {
    auto ctx = ctx_.lock();
    auto cmp_val = cmp_->retrieve(val);
    auto result = ctx->convert<long>(cmp_val).as<long>();
    return text::make_data(result > 0);
}

std::shared_ptr<text::ValueRetriever> eq_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto cmp = cmp_->value(parent, parameters);
    return std::make_shared<eq_impl>(ctx_, cmp);
}

text::UnknownDataTypeContainer 
eq_impl::retrieve(const text::UnknownDataTypeContainer& val) const {
    auto ctx = ctx_.lock();
    auto cmp_val = cmp_->retrieve(val);
    auto result = ctx->convert<long>(cmp_val).as<long>();
    return text::make_data(result == 0);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
