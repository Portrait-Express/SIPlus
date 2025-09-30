#ifndef INCLUDE_SIPLUS_EXPR_VISITOR_H_
#define INCLUDE_SIPLUS_EXPR_VISITOR_H_

#include "BufferedTokenStream.h"

#include "siplus/config.h"
#include "siplus/context.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

class ExpressionVisitor : public SIPlusParseTreeVisitor {
public:
    ExpressionVisitor(std::shared_ptr<SIPlusParserContext> context, const antlr4::BufferedTokenStream& tokens);

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& current) override;

    std::any visitFunc(StringInterpolatorParser::FuncContext *ctx) override;
    std::any visitLiteral(StringInterpolatorParser::LiteralContext *ctx) override;
    std::any visitField(StringInterpolatorParser::FieldContext *ctx) override;

private:
    std::shared_ptr<text::ValueRetriever> value_ = 0;
    std::shared_ptr<SIPlusParserContext> context_;
    const antlr4::BufferedTokenStream& tokens_;
};

}

#endif  // INCLUDE_SIPLUS_EXPR_VISITOR_H_
