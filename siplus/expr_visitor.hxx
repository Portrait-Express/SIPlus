#ifndef INCLUDE_SIPLUS_EXPR_VISITOR_HXX_
#define INCLUDE_SIPLUS_EXPR_VISITOR_HXX_

#include "BufferedTokenStream.h"

#include "ParseTree.h"
#include "siplus/build_context.hxx"
#include "siplus/config.h"
#include "siplus/context.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"
#include "visitor.hxx"

namespace SIPLUS_NAMESPACE {

SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::ExprContext, std::shared_ptr<text::ValueRetriever>);

class ExpressionVisitor : public SIPlusParseTreeVisitor {
public:
    ExpressionVisitor(
        std::shared_ptr<SIPlusParserContext> context,
        std::shared_ptr<BuildContext> buildContext,
        const antlr4::BufferedTokenStream& tokens
    );

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& current) override;

    virtual std::any visitPiped_expression(StringInterpolatorParser::Piped_expressionContext *ctx) override;
    virtual std::any visitExpr_item(StringInterpolatorParser::Expr_itemContext *ctx) override;
    virtual std::any visitExpr_block(StringInterpolatorParser::Expr_blockContext *ctx) override;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

class PipedExpressionVisitor : public SIPlusParseTreeVisitor {
public:
    PipedExpressionVisitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext,
        const antlr4::BufferedTokenStream& tokens
    );

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& current) override;

    std::any visitFunc(StringInterpolatorParser::FuncContext *ctx) override;
    std::any visitLiteral(StringInterpolatorParser::LiteralContext *ctx) override;
    std::any visitProperty(StringInterpolatorParser::PropertyContext *ctx) override;
    std::any visitArray(StringInterpolatorParser::ArrayContext *ctx) override;
    std::any visitVariable_reference(StringInterpolatorParser::Variable_referenceContext *ctx) override;

private:
    std::shared_ptr<text::ValueRetriever> value_ = 0;
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_EXPR_VISITOR_HXX_
