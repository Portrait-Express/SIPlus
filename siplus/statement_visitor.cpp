#include "statement_visitor.hxx"
#include "block_visitor.hxx"
#include "interpolation_visitor.hxx"

#include "siplus/text/constructor_steps/retriever_step.hxx"
#include "siplus/text/constructor_steps/repeated_constructor_step.hxx"

#include <any>
#include <memory>

namespace SIPLUS_NAMESPACE {

StatementVisitor::StatementVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<BuildContext> buildContext, 
    const antlr4::BufferedTokenStream& tokens) 
: context_(context), buildContext_(buildContext), tokens_(tokens) {}


bool StatementVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) {
    return dynamic_cast<StringInterpolatorParser::LoopContext*>(node) == nullptr &&
           dynamic_cast<StringInterpolatorParser::EvalContext*>(node) == nullptr;
}

std::any StatementVisitor::visitLoop(StringInterpolatorParser::LoopContext *ctx) {
    BlockVisitor visitor{context_, buildContext_, tokens_};
    auto expr_value = std::any_cast<std::shared_ptr<text::ValueRetriever>>(
        ctx->loop_start()->expr_block_contents()->accept(&visitor));

    InterpolationVisitor prog_visitor{context_, buildContext_, tokens_};
    auto sub = std::any_cast<text::TextConstructor>(
        ctx->interpolated_str()->accept(&prog_visitor));

    auto ptr = std::make_shared<text::RepeatedConstructorConstructorStep>(
        context_, expr_value, sub);

    return std::static_pointer_cast<text::TextConstructorStep>(ptr);
}

std::any StatementVisitor::visitEval(StringInterpolatorParser::EvalContext *ctx) {
    BlockVisitor visitor{context_, buildContext_, tokens_};
    auto expr_value = std::any_cast<std::shared_ptr<text::ValueRetriever>>(ctx->accept(&visitor));

    auto ptr = std::make_shared<text::ValueRetrieverConstructorStep>(context_, expr_value);
    return std::static_pointer_cast<text::TextConstructorStep>(ptr);
}

}
