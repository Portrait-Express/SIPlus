#ifndef INCLUDE_SIPLUS_EXPR_VISITOR_HXX_
#define INCLUDE_SIPLUS_EXPR_VISITOR_HXX_

#include "BufferedTokenStream.h"

#include "siplus/build_context.hxx"
#include "siplus/config.h"
#include "siplus/context.hxx"
#include "siplus/data.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"
#include "visitor.hxx"

namespace SIPLUS_NAMESPACE {

SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Piped_exprContext, std::shared_ptr<text::ValueRetriever>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::ExprContext, std::shared_ptr<text::ValueRetriever>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Suffixable_exprContext, std::shared_ptr<text::ValueRetriever>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::PrimitiveContext, UnknownDataTypeContainer);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Interpolated_strContext, text::TextConstructor);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Interp_stmtContext, std::shared_ptr<text::TextConstructorStep>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Interp_normalContext, std::shared_ptr<text::TextConstructorStep>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Interp_partContext, std::shared_ptr<text::TextConstructorStep>);

class siplus_visitor : public SIPlusParseTreeVisitor {
public:
    siplus_visitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext,
        const antlr4::BufferedTokenStream& tokens
    );

    std::any visitString(StringInterpolatorParser::StringContext *ctx) override;
    std::any visitFloat(StringInterpolatorParser::FloatContext *ctx) override;
    std::any visitInteger(StringInterpolatorParser::IntegerContext *ctx) override;
    std::any visitBoolean(StringInterpolatorParser::BooleanContext *ctx) override;
    std::any visitNull(StringInterpolatorParser::NullContext *ctx) override;

    std::any visitArray(StringInterpolatorParser::ArrayContext *ctx) override;
    std::any visitPrimitive(StringInterpolatorParser::PrimitiveContext *ctx) override;

    std::any visitVariable(StringInterpolatorParser::VariableContext *ctx) override;
    std::any visitLiteral(StringInterpolatorParser::LiteralContext *ctx) override;

    std::any visitCall(StringInterpolatorParser::CallContext *ctx) override;
    std::any visitVariable_assignment(StringInterpolatorParser::Variable_assignmentContext *ctx) override;
    std::any visitBlock(StringInterpolatorParser::BlockContext *ctx) override;

    std::any visitPiped_suffixable_expr(StringInterpolatorParser::Piped_suffixable_exprContext *ctx) override;
    std::any visitPiped_expr(StringInterpolatorParser::Piped_exprContext *ctx) override;
    std::any visitSuffixable_expr(StringInterpolatorParser::Suffixable_exprContext *ctx) override;
    std::any visitExpr(StringInterpolatorParser::ExprContext *ctx) override;

    std::any visitInterp_eval(StringInterpolatorParser::Interp_evalContext *ctx) override;
    std::any visitInterp_loop(StringInterpolatorParser::Interp_loopContext *ctx) override;

    std::any visitInterp_stmt(StringInterpolatorParser::Interp_stmtContext *ctx) override;
    std::any visitInterp_normal(StringInterpolatorParser::Interp_normalContext *ctx) override;

    std::any visitInterp_part(StringInterpolatorParser::Interp_partContext *ctx) override;
    std::any visitInterpolated_str(StringInterpolatorParser::Interpolated_strContext *ctx) override;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_EXPR_VISITOR_HXX_
