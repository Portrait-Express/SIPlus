#pragma once
#include "siplus/build_context.hxx"
#include "siplus/context.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"
#include "visitor.hxx"
#ifndef INCLUDE_SIPLUS_PIPED_EXPR_VISITOR_HXX_
#define INCLUDE_SIPLUS_PIPED_EXPR_VISITOR_HXX_

#include "siplus/config.h"

namespace SIPLUS_NAMESPACE {

SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Piped_exprContext, std::shared_ptr<text::ValueRetriever>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Piped_expr_partContext, std::shared_ptr<text::ValueRetriever>);

class piped_expr_parts_visitor : public SIPlusParseTreeVisitor {
public:
    explicit piped_expr_parts_visitor(
        std::shared_ptr<text::ValueRetriever> parent,
        std::shared_ptr<SIPlusParserContext> context,
        std::shared_ptr<BuildContext> buildContext,
        const antlr4::BufferedTokenStream& tokens
    ) : value(parent), context_(context), buildContext_(buildContext), tokens_(tokens) {}
 
    std::any visitCall(StringInterpolatorParser::CallContext *ctx) override;
    std::any visitPiped_expr_part(StringInterpolatorParser::Piped_expr_partContext *ctx) override;
    std::shared_ptr<text::ValueRetriever> visitMultiple(const std::vector<StringInterpolatorParser::Piped_expr_partContext*>& ctxs);

    std::shared_ptr<text::ValueRetriever> value;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_PIPED_EXPR_VISITOR_HXX_
