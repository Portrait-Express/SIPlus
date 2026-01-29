#include "BufferedTokenStream.h"
#include "generated/StringInterpolatorLexer.h"
#include "generated/StringInterpolatorParser.h"
#include "Token.h"

#include "siplus/text/constructor_steps/literal_step.hxx"

#include "interpolation_visitor.hxx"
#include "statement_visitor.hxx"

namespace SIPLUS_NAMESPACE {

namespace {

std::string get_escape(const std::string& escape) {
    if(escape.size() == 1) {
        char ch = escape.at(0);
        switch(ch) {
            case 'n': return "\n";
            case 't': return "\t";
            case 'v': return "\v";
            default: return std::string{ch};
        }
    } 

    return escape;
}

}

InterpolationVisitor::InterpolationVisitor(
    std::shared_ptr<SIPlusParserContext> context,
    std::shared_ptr<BuildContext> buildContext, 
    const antlr4::BufferedTokenStream& tokens
) : context_(context), buildContext_(buildContext), tokens_(tokens) {}

bool InterpolationVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) {
    return dynamic_cast<StringInterpolatorParser::NormalContext*>(node) == nullptr && 
           dynamic_cast<StringInterpolatorParser::StmtContext*>(node) == nullptr;
}

std::any InterpolationVisitor::visitNormal(StringInterpolatorParser::NormalContext *ctx) {
    std::stringstream ss;

    auto stop = ctx->stop->getTokenIndex();
    for(int i = ctx->start->getTokenIndex(); i <= stop; i++) {
        antlr4::Token *token = tokens_.get(i);
        if(token->getType() == StringInterpolatorLexer::NORMAL_ESCAPE) {
            ss << get_escape(token->getText().substr(1));
        } else {
            ss << token->getText();
        }
    }

    auto step = std::make_shared<text::LiteralConstructorStep>(ss.str());
    constructor_.addStep(step);

    return constructor_;
}

std::any InterpolationVisitor::visitStmt(StringInterpolatorParser::StmtContext *ctx) {
    StatementVisitor visitor{context_, buildContext_, tokens_};
    auto step = visitor.visit(ctx);
    constructor_.addStep(step);

    return constructor_;
}

}
