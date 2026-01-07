#ifndef INCLUDE_SIPLUS_STATEMENT_VISITOR_H_
#define INCLUDE_SIPLUS_STATEMENT_VISITOR_H_

#include "BufferedTokenStream.h"

#include "build_context.h"
#include "siplus/context.h"
#include "siplus/text/constructor_steps/constructor_step.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

SIPLUS_DECLARE_NODE_RESULT(StringInterpolatorParser::StmtContext, std::shared_ptr<text::TextConstructorStep>);

class StatementVisitor : public SIPlusParseTreeVisitor {
public:
    StatementVisitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext, 
        const antlr4::BufferedTokenStream& tokens
    );

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) override;

    std::any visitLoop(StringInterpolatorParser::LoopContext *ctx) override;
    std::any visitEval(StringInterpolatorParser::EvalContext *ctx) override;
    
private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_STATEMENT_VISITOR_H_
