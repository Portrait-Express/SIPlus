#ifndef INCLUDE_SIPLUS_STATEMENT_VISITOR_H_
#define INCLUDE_SIPLUS_STATEMENT_VISITOR_H_

#include "BufferedTokenStream.h"
#include "generated/StringInterpolatorParserBaseVisitor.h"

#include "siplus/context.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

class StatementVisitor : public SIPlusParseTreeVisitor {
public:
    StatementVisitor(std::shared_ptr<SIPlusParserContext> context, const antlr4::BufferedTokenStream& tokens);

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) override;

    std::any visitLoop(StringInterpolatorParser::LoopContext *ctx) override;
    std::any visitEval(StringInterpolatorParser::EvalContext *ctx) override;
    
private:
    std::shared_ptr<SIPlusParserContext> context_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_STATEMENT_VISITOR_H_
