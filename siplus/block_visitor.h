#ifndef INCLUDE_SIPLUS_BLOCK_VISITOR_H_
#define INCLUDE_SIPLUS_BLOCK_VISITOR_H_

#include "siplus/build_context.h"
#include "siplus/context.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

class BlockVisitor : public SIPlusParseTreeVisitor {
public:
    BlockVisitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext, 
        const antlr4::BufferedTokenStream& tokens
    );

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& current) override;
    std::any visitExpr_block_contents(StringInterpolatorParser::Expr_block_contentsContext *ctx) override;
private:
    std::shared_ptr<text::ValueRetriever> value_ = 0;
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_BLOCK_VISITOR_H_
