#ifndef INCLUDE_SIPLUS_BLOCK_VISITOR_HXX_
#define INCLUDE_SIPLUS_BLOCK_VISITOR_HXX_

#include "siplus/build_context.hxx"
#include "siplus/context.hxx"
#include "visitor.hxx"

namespace SIPLUS_NAMESPACE {

struct Statement {
    virtual void invoke(InvocationContext& context) = 0;

    virtual ~Statement() = default;
};

SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Block_contentsContext, std::shared_ptr<text::ValueRetriever>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Block_stmtContext, std::shared_ptr<Statement>);
SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::Block_exprContext, std::shared_ptr<text::ValueRetriever>);

class block_contents_visitor: public SIPlusParseTreeVisitor {
public:
    block_contents_visitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext, 
        const antlr4::BufferedTokenStream& tokens
    );

    std::any visitVariable_declaration(StringInterpolatorParser::Variable_declarationContext *ctx) override;
    std::any visitFunction_definition(StringInterpolatorParser::Function_definitionContext *ctx) override;

    std::any visitBlock_expr(StringInterpolatorParser::Block_exprContext *ctx) override;
    std::any visitBlock_stmt(StringInterpolatorParser::Block_stmtContext *ctx) override;
    std::any visitBlock_contents(StringInterpolatorParser::Block_contentsContext *ctx) override;

private:
    std::shared_ptr<text::ValueRetriever> value_ = 0;
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_BLOCK_VISITOR_HXX_
