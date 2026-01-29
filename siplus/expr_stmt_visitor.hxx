#ifndef INCLUDE_SIPLUS_EXPR_STMT_VISITOR_HXX_
#define INCLUDE_SIPLUS_EXPR_STMT_VISITOR_HXX_

#include "siplus/build_context.hxx"
#include "siplus/context.hxx"
#include "visitor.hxx"

namespace SIPLUS_NAMESPACE {

struct Statement {
    virtual void invoke(InvocationContext& context) = 0;
};

SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Expr_stmtContext, std::shared_ptr<Statement>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Function_def_stmtContext, std::shared_ptr<Statement>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Assign_stmtContext, std::shared_ptr<Statement>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Simple_expr_stmtContext, std::shared_ptr<Statement>);

class ExprStmtVisitor : public SIPlusParseTreeVisitor {
public:
    ExprStmtVisitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext, 
        const antlr4::BufferedTokenStream& tokens
    );

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& current) override;

    virtual std::any visitFunction_def_stmt(StringInterpolatorParser::Function_def_stmtContext *ctx) override;
    virtual std::any visitAssign_stmt(StringInterpolatorParser::Assign_stmtContext *ctx) override;
    virtual std::any visitSimple_expr_stmt(StringInterpolatorParser::Simple_expr_stmtContext *ctx) override;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_EXPR_STMT_VISITOR_HXX_
