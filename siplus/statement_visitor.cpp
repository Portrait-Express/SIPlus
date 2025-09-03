#include <any>
#include <memory>

#include "statement_visitor.h"
#include "expr_visitor.h"
#include "interpolation_visitor.h"

#include "siplus/text/constructor_steps/retriever_step.h"
#include "siplus/text/constructor_steps/repeated_constructor_step.h"

namespace SIPLUS_NAMESPACE {

StatementVisitor::StatementVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    const antlr4::BufferedTokenStream& tokens) 
: context_(context), tokens_(tokens) {}


bool StatementVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) {
    return dynamic_cast<StringInterpolatorParser::LoopContext*>(node) == nullptr &&
           dynamic_cast<StringInterpolatorParser::EvalContext*>(node) == nullptr;
}

std::any StatementVisitor::visitLoop(StringInterpolatorParser::LoopContext *ctx) {
    ExpressionVisitor visitor{context_, tokens_};
    auto expr_value = std::any_cast<std::shared_ptr<text::ValueRetriever>>(
        ctx->loop_start()->expr()->accept(&visitor));

    InterpolationVisitor prog_visitor{context_, tokens_};
    auto sub = std::any_cast<text::TextConstructor>(
        ctx->interpolated_str()->accept(&prog_visitor));

    auto ptr = std::make_shared<text::RepeatedConstructorConstructorStep>(
        context_, expr_value, sub);

    return std::static_pointer_cast<text::TextConstructorStep>(ptr);
}

std::any StatementVisitor::visitEval(StringInterpolatorParser::EvalContext *ctx) {
    ExpressionVisitor visitor{context_, tokens_};
    auto expr_value = std::any_cast<std::shared_ptr<text::ValueRetriever>>(
        ctx->expr()->accept(&visitor));

    auto ptr = std::make_shared<text::ValueRetrieverConstructorStep>(context_, expr_value);
    return std::static_pointer_cast<text::TextConstructorStep>(ptr);
}

}
