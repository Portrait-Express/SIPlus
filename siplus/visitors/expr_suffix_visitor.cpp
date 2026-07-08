#include "../util.hxx"
#include "../retrievers/indexer_value_retriever.hxx"
#include "siplus_visitor.hxx"
#include "siplus/text/value_retrievers/accessor_retriever.hxx"
#include "expr_suffix_visitor.hxx"

namespace SIPLUS_NAMESPACE {

std::any expr_suffix_visitor::visitAccessor(StringInterpolatorParser::AccessorContext *ctx) {
    value = detail::make_retriever<text::AccessorValueRetriever>(value, ctx->ID()->getText());
    return value;
}

std::any expr_suffix_visitor::visitIndexer(StringInterpolatorParser::IndexerContext *ctx) {
    siplus_visitor visitor{context_, buildContext_, tokens_};
    auto index = visitor.visit(ctx->expr());

    value = detail::make_retriever<indexer_value_retriever>(value, index);
    return value;
}

std::any expr_suffix_visitor::visitExpr_suffix(StringInterpolatorParser::Expr_suffixContext *ctx) {
    if(auto aCtx = ctx->accessor()) {
        return visitAccessor(aCtx);
    } else if(auto iCtx = ctx->indexer()) {
        return visitIndexer(iCtx);
    } else {
        throw std::runtime_error{"Unknown expr_suffix syntax"};
    }
}

std::shared_ptr<text::ValueRetriever> expr_suffix_visitor::visitMultiple(const std::vector<StringInterpolatorParser::Expr_suffixContext*>& ctxs) {
    for(auto ctx : ctxs) {
        visit(ctx);
    }

    return value;
}
    
} /* SIPLUS_NAMESPACE */

