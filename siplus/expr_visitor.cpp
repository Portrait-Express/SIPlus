#include "BufferedTokenStream.h"
#include "generated/StringInterpolatorParser.h"

#include <memory>
#include <stdexcept>

#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/accessor_retriever.h"
#include "siplus/text/value_retrievers/dummy_retriever.h"
#include "siplus/text/value_retrievers/literal_retriever.h"

#include "expr_visitor.h"
#include "literal_visitor.h"
#include "util.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

class ArgListVisitor : public SIPlusParseTreeVisitor {
public:
    ArgListVisitor(std::shared_ptr<SIPlusParserContext> context, const antlr4::BufferedTokenStream& tokens)
        : context_(context), tokens_(tokens) {}

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) override {
        return dynamic_cast<StringInterpolatorParser::ArgumentContext*>(node) == nullptr;
    }

    std::any visitArgument(StringInterpolatorParser::ArgumentContext *ctx) override {
        ExpressionVisitor visitor{context_, tokens_};
        auto anyval = ctx->accept(&visitor);
        auto expr = std::any_cast<std::shared_ptr<text::ValueRetriever>>(anyval);
        arguments_.push_back(expr);
        return arguments_;
    }

    std::any defaultResult() override {
        return std::vector<std::shared_ptr<text::ValueRetriever>>{};
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
           dynamic_cast<StringInterpolatorParser::LiteralContext*>(node) == nullptr && 
           dynamic_cast<StringInterpolatorParser::FieldContext*>(node) == nullptr;
}

std::any ExpressionVisitor::visitFunc(StringInterpolatorParser::FuncContext *ctx) {
    auto& function = context_->function(ctx->ID()->getText());
    ArgListVisitor visitor{context_, tokens_};
    auto val = ctx->arg_list()->accept(&visitor);
    auto args = std::any_cast<std::vector<std::shared_ptr<text::ValueRetriever>>>(val);
    value_ = function.value(value_, args);
    return value_;
}

std::any ExpressionVisitor::visitLiteral(StringInterpolatorParser::LiteralContext *ctx) {
    if(value_) {
        throw std::runtime_error{"Literals cannot accept inputs"};
    }

    LiteralVisitor visitor{context_, tokens_};
    auto literal = ctx->accept(&visitor);
    auto data = std::any_cast<text::UnknownDataTypeContainer>(literal);
    value_ = std::make_shared<text::LiteralValueRetriever>(data);
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

    value_ = std::static_pointer_cast<text::ValueRetriever>(existing);
    return value_;
}

}

