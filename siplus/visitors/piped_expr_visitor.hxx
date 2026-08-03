#pragma once
#ifndef INCLUDE_SIPLUS_PIPED_EXPR_VISITOR_HXX_
#define INCLUDE_SIPLUS_PIPED_EXPR_VISITOR_HXX_

#include "siplus/config.h"
#include "siplus/context.hxx"
#include "visitor.hxx"

namespace SIPLUS_NAMESPACE {

SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Piped_expr_partContext, std::shared_ptr<ValueRetriever>);

class piped_expr_parts_visitor : public SIPlusParseTreeVisitor {
public:
    explicit piped_expr_parts_visitor(
        std::shared_ptr<ValueRetriever> parent,
        std::shared_ptr<SIPlusParserContext> context,
        std::shared_ptr<BuildContext> buildContext,
        const antlr4::BufferedTokenStream& tokens
    ) : value(parent), context_(context), buildContext_(buildContext), tokens_(tokens) {}
 
    std::any visitCall(StringInterpolatorParser::CallContext *ctx) override;
    std::any visitPiped_expr_part(StringInterpolatorParser::Piped_expr_partContext *ctx) override;
    std::shared_ptr<ValueRetriever> visitMultiple(const std::vector<StringInterpolatorParser::Piped_expr_partContext*>& ctxs);

    std::shared_ptr<ValueRetriever> value;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_PIPED_EXPR_VISITOR_HXX_
