#include <vector>

#include "../retrievers/default_data_retriever.hxx"
#include "../util.hxx"
#include "piped_expr_visitor.hxx"
#include "expr_suffix_visitor.hxx"
#include "siplus_visitor.hxx"

namespace SIPLUS_NAMESPACE {

std::any piped_expr_parts_visitor::visitCall(StringInterpolatorParser::CallContext *ctx) {
    siplus_visitor visitor{context_, buildContext_, tokens_};
    const bool custom = ctx->AT();
    const std::string name = ctx->ID()->getText();
    auto exprCtxs = ctx->expr();
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters;

    parameters.reserve(exprCtxs.size());

    std::transform(exprCtxs.begin(), exprCtxs.end(), std::back_inserter(parameters), 
                   [this, &visitor](auto *ctx) { return visitor.visit(ctx); });

    if(custom) {
        value = buildContext_->function(name).value(value, parameters);
    } else {
        value = context_->function(name).value(value, parameters);
    }

    return value;
}

std::any piped_expr_parts_visitor::visitPiped_expr_part(StringInterpolatorParser::Piped_expr_partContext *ctx) {
    if(auto suffixableCtx = ctx->piped_suffixable_expr()) {
        expr_suffix_visitor visitor{value, context_, buildContext_, tokens_};
        auto suffixes = ctx->expr_suffix();
        
        if(auto aCtx = suffixableCtx->accessor()) {
            visitor.visitAccessor(aCtx);
        } else if(auto iCtx = suffixableCtx->indexer()) {
            visitor.visitIndexer(iCtx);
        }

        value = visitor.visitMultiple(suffixes);
        return value;
    } else if(auto callCtx = ctx->call()) { 
        return visitCall(callCtx);
    } else {
        throw std::runtime_error{"Unknown piped_expr syntax"};
    }
}

std::shared_ptr<text::ValueRetriever> piped_expr_parts_visitor::visitMultiple(const std::vector<StringInterpolatorParser::Piped_expr_partContext*>& ctxs) {
    for(auto ctx : ctxs) {
        visit(ctx);
    }

    return value;
}
    
} /* SIPLUS_NAMESPACE */
