#ifndef INCLUDE_SIPLUS_LITERAL_VISITOR_H_
#define INCLUDE_SIPLUS_LITERAL_VISITOR_H_

#include "BufferedTokenStream.h"
#include "generated/StringInterpolatorParserBaseVisitor.h"

#include "siplus/context.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

class LiteralVisitor : public SIPlusParseTreeVisitor {
public:
    LiteralVisitor(std::shared_ptr<SIPlusParserContext> context, const antlr4::BufferedTokenStream& tokens);

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) override;

    std::any visitString(StringInterpolatorParser::StringContext *ctx) override;
    std::any visitFloat(StringInterpolatorParser::FloatContext *ctx) override;
    std::any visitInteger(StringInterpolatorParser::IntegerContext *ctx) override;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_LITERAL_VISITOR_H_
