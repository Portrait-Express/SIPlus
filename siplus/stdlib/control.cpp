#include "siplus/stl/functions/control.hxx"
#include "siplus/context.hxx"
#include "siplus/types/bool.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct if_impl : public ValueRetriever {
    if_impl(
        std::shared_ptr<ValueRetriever> condition,
        std::shared_ptr<ValueRetriever> tVal,
        std::shared_ptr<ValueRetriever> fVal,
        std::weak_ptr<SIPlusParserContext> context
    ) : condition(condition), tVal(tVal), fVal(fVal), context_(context) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

    std::shared_ptr<ValueRetriever> condition;
    std::shared_ptr<ValueRetriever> tVal;
    std::shared_ptr<ValueRetriever> fVal;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

UnknownDataTypeContainer
if_impl::retrieve(InvocationContext& value) const {
    auto ctx = context_.lock();
    auto cond = condition->retrieve(value);

    if(ctx->convert<types::BoolType>(cond).as<types::BoolType>()) {
        return tVal->retrieve(value);
    } else {
        return fVal->retrieve(value);
    }
}


struct while_impl : public ValueRetriever {
    while_impl(
        std::shared_ptr<ValueRetriever> condition,
        std::shared_ptr<ValueRetriever> body,
        std::weak_ptr<SIPlusParserContext> context
    ) : condition_(condition), body_(body), context_(context) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> condition_;
    std::shared_ptr<ValueRetriever> body_;
    std::weak_ptr<SIPlusParserContext> context_;
};

UnknownDataTypeContainer
while_impl::retrieve(InvocationContext& value) const {
    auto ctx = context_.lock();
    auto cond = condition_->retrieve(value);
    UnknownDataTypeContainer last;

    while(ctx->convert<types::BoolType>(cond).as<types::BoolType>()) {
        last = body_->retrieve(value);
        cond = condition_->retrieve(value);
    }

    return last;
}

} /* anonymous */

std::shared_ptr<ValueRetriever>
if_func::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [cond, t, f] = util::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<if_impl>(cond, t, f, context_);
}

std::shared_ptr<ValueRetriever>
while_func::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [cond, body] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<while_impl>(cond, body, context_);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
