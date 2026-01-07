#include "block_visitor.h"
#include "expr_stmt_visitor.h"
#include "expr_visitor.h"
#include "generated/StringInterpolatorParser.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include <any>

namespace SIPLUS_NAMESPACE {

namespace {

struct StatementExecutingValueRetriever : public text::ValueRetriever {
    StatementExecutingValueRetriever(
        std::vector<std::shared_ptr<Statement>> stmts,
        std::shared_ptr<text::ValueRetriever> expr
    ) : statements_(stmts), expr_(expr) {}

    text::UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override {
        for(auto stmt : statements_) {
            stmt->invoke(value);
        }

        return expr_->retrieve(value);
    }

private:
    std::vector<std::shared_ptr<Statement>> statements_;
    std::shared_ptr<text::ValueRetriever> expr_;
};

}

BlockVisitor::BlockVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<BuildContext> buildContext, 
    const antlr4::BufferedTokenStream& tokens
) : context_(context), buildContext_(buildContext), tokens_(tokens) {}

bool BlockVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& current) {
    return dynamic_cast<StringInterpolatorParser::Expr_block_contentsContext*>(node) == nullptr;
}

std::any BlockVisitor::visitExpr_block_contents(StringInterpolatorParser::Expr_block_contentsContext *ctx) {
    ExprStmtVisitor stmtVisitor{context_, buildContext_, tokens_};
    ExpressionVisitor visitor{context_, buildContext_, tokens_};
    auto stmtTree = ctx->expr_stmt();

    std::vector<std::shared_ptr<Statement>> stmts{stmtTree.size()};
    std::transform(stmtTree.begin(), stmtTree.end(), stmts.begin(), 
        [&stmtVisitor](StringInterpolatorParser::Expr_stmtContext* ctx){
            return stmtVisitor.visit(ctx);
        });

    //Visit statements first, otherwise dependent variables may not be initialized
    auto expr = visitor.visit(ctx->expr());

    auto retriever = std::make_shared<StatementExecutingValueRetriever>(stmts, expr);
    return std::static_pointer_cast<text::ValueRetriever>(retriever);
}

} /* SIPLUS_NAMESPACE */
