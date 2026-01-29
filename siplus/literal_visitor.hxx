#ifndef INCLUDE_SIPLUS_LITERAL_VISITOR_HXX_
#define INCLUDE_SIPLUS_LITERAL_VISITOR_HXX_

#include "BufferedTokenStream.h"

#include "siplus/build_context.hxx"
#include "siplus/context.hxx"
#include "visitor.hxx"

namespace SIPLUS_NAMESPACE {

class LiteralVisitor : public SIPlusParseTreeVisitor {
public:
    LiteralVisitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext, 
        const antlr4::BufferedTokenStream& tokens
    );

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) override;

    std::any visitString(StringInterpolatorParser::StringContext *ctx) override;
    std::any visitFloat(StringInterpolatorParser::FloatContext *ctx) override;
    std::any visitInteger(StringInterpolatorParser::IntegerContext *ctx) override;
    std::any visitBoolean(StringInterpolatorParser::BooleanContext *ctx) override;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_LITERAL_VISITOR_HXX_
