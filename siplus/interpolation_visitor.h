#ifndef INCLUDE_SIPLUS_INTERPOLATION_VISITOR_H_
#define INCLUDE_SIPLUS_INTERPOLATION_VISITOR_H_

#include "BufferedTokenStream.h"
#include "build_context.h"

#include "siplus/context.h"
#include "siplus/text/constructor.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

class InterpolationVisitor : public SIPlusParseTreeVisitor {
public:
    InterpolationVisitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext, 
        const antlr4::BufferedTokenStream& tokens
    );

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) override;

    std::any visitStmt(StringInterpolatorParser::StmtContext *ctx) override;
    std::any visitNormal(StringInterpolatorParser::NormalContext *ctx) override;

    std::any defaultResult() override {
        return constructor_;
    }

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
    text::TextConstructor constructor_;
};

}

#endif  // INCLUDE_SIPLUS_INTERPOLATION_VISITOR_H_
