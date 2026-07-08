#pragma once
#ifndef INCLUDE_VISITORS_EXPR_SUFFIX_VISITOR_HXX_
#define INCLUDE_VISITORS_EXPR_SUFFIX_VISITOR_HXX_

#include "BufferedTokenStream.h"

#include "siplus/build_context.hxx"
#include "siplus/config.h"
#include "siplus/context.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"

#include "visitor.hxx"

namespace SIPLUS_NAMESPACE {

SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Expr_suffixContext, std::shared_ptr<SIPlus::text::ValueRetriever>);

class expr_suffix_visitor : public SIPlusParseTreeVisitor {
public:
    explicit expr_suffix_visitor(
        std::shared_ptr<text::ValueRetriever> parent,
        std::shared_ptr<SIPlusParserContext> context,
        std::shared_ptr<BuildContext> buildContext,
        const antlr4::BufferedTokenStream& tokens
    ) : value(parent), context_(context), buildContext_(buildContext), tokens_(tokens) {}

    virtual std::any visitAccessor(StringInterpolatorParser::AccessorContext *ctx) override;
    virtual std::any visitIndexer(StringInterpolatorParser::IndexerContext *ctx) override;

    virtual std::any visitExpr_suffix(StringInterpolatorParser::Expr_suffixContext *ctx) override;

    std::shared_ptr<text::ValueRetriever> visitMultiple(const std::vector<StringInterpolatorParser::Expr_suffixContext*>& ctxs);

    std::shared_ptr<text::ValueRetriever> value;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_VISITORS_EXPR_SUFFIX_VISITOR_HX
