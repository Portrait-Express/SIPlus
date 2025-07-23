#include "BufferedTokenStream.h"
#include "generated/StringInterpolatorParserBaseVisitor.h"

#include <memory>
#include <stdexcept>

#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/accessor_retriever.h"
#include "siplus/text/value_retrievers/dummy_retriever.h"
#include "siplus/text/value_retrievers/literal_retriever.h"

#include "expr_visitor.h"
#include "literal_visitor.h"

namespace SIPLUS_NAMESPACE {

class ArgListVisitor : public StringInterpolatorParserBaseVisitor {
public:
    ArgListVisitor(std::shared_ptr<SIPlusParserContext> context, const antlr4::BufferedTokenStream& tokens)
        : context_(context), tokens_(tokens) {}

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) override {
        return dynamic_cast<StringInterpolatorParser::ArgumentContext*>(node) != nullptr;
    }

    std::any visitArgument(StringInterpolatorParser::ArgumentContext *ctx) override {
        ExpressionVisitor visitor{context_, tokens_};
        visitor.visit(ctx);
        return arguments_;
    }

private:
    std::vector<std::shared_ptr<text::ValueRetriever>> arguments_;
    std::shared_ptr<SIPlusParserContext> context_;
    const antlr4::BufferedTokenStream& tokens_;
};

ExpressionVisitor::ExpressionVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    const antlr4::BufferedTokenStream& tokens) 
: context_(context), tokens_(tokens) {}

bool ExpressionVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) {
    return dynamic_cast<StringInterpolatorParser::FuncContext*>(node) == nullptr &&
           dynamic_cast<StringInterpolatorParser::LiteralContext*>(node) == nullptr;
}

std::any ExpressionVisitor::visitFunc(StringInterpolatorParser::FuncContext *ctx) {
    auto& function = context_->function(ctx->ID()->getText());
    ArgListVisitor visitor{context_, tokens_};
    auto args = std::any_cast<std::vector<std::shared_ptr<text::ValueRetriever>>>(visitor.visit(ctx->arg_list()));
    value_ = function.value(value_, args);
    return value_;
}

std::any ExpressionVisitor::visitLiteral(StringInterpolatorParser::LiteralContext *ctx) {
    if(value_) {
        throw std::runtime_error{"Literals cannot accept inputs"};
    }

    LiteralVisitor visitor{context_, tokens_};
    value_ = std::make_shared<text::LiteralValueRetriever>(std::any_cast<text::UnknownDataTypeContainer>(visitor.visit(ctx)));
    return value_;
}

std::any ExpressionVisitor::visitField(StringInterpolatorParser::FieldContext *ctx) {
    std::shared_ptr<text::AccessorValueRetriever> existing;

    for(auto& token : ctx->ID()) {
        if(!existing) {
            existing = std::make_shared<text::AccessorValueRetriever>(context_, token->getText());
        } else {
            existing = std::make_shared<text::AccessorValueRetriever>(context_, existing, token->getText());
        }
    }

    if(!existing)
        return std::make_shared<text::DummyValueRetriever>();

    return std::static_pointer_cast<text::ValueRetriever>(existing);
}

}

