#include "BufferedTokenStream.h"
#include "block_visitor.h"
#include "generated/StringInterpolatorParser.h"

#include <any>
#include <memory>

#include "siplus/invocation_context.h"
#include "siplus/text/data.h"
#include "siplus/util.h"

#include "expr_visitor.h"
#include "literal_visitor.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

namespace {

struct LiteralArrayValueRetriever : public text::ValueRetriever {
    LiteralArrayValueRetriever(std::vector<std::shared_ptr<text::ValueRetriever>> items) : items_(items) {}
    
    text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::vector<std::shared_ptr<text::ValueRetriever>> items_;
};

text::UnknownDataTypeContainer 
LiteralArrayValueRetriever::retrieve(InvocationContext& value) const {
    std::vector<text::UnknownDataTypeContainer> ret;
    ret.reserve(items_.size());

    for(auto item : items_) {
        ret.push_back(item->retrieve(value));
    }

    return text::make_data(ret);
}


/**
 * @brief ValueRetriever to access a property on the parent object.
 */
class AccessorValueRetriever : public text::ValueRetriever {
public:
    AccessorValueRetriever(std::shared_ptr<SIPlusParserContext> context, std::string name);
    AccessorValueRetriever(std::shared_ptr<SIPlusParserContext> context, std::shared_ptr<ValueRetriever> parent, std::string name);

    text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<ValueRetriever> parent_;
    std::string name_;
};

AccessorValueRetriever::AccessorValueRetriever(
    std::shared_ptr<SIPlusParserContext> context, 
    std::string name
) : context_(context), name_(name) {}

AccessorValueRetriever::AccessorValueRetriever(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<ValueRetriever> parent,  
    std::string name
) : context_(context), parent_(parent), name_(name) {}

text::UnknownDataTypeContainer AccessorValueRetriever::retrieve(InvocationContext& value) const {
    if(parent_) {
        auto parent = parent_->retrieve(value);
        auto accessor = context_->accessor(parent);
        return accessor->access(parent, name_);
    } else {
        auto accessor = context_->accessor(value.default_data());
        return accessor->access(value.default_data(), name_);
    }
}

/**
 * @brief ValueRetriever to access an index on an iterable object.
 */
class IndexValueRetriever : public text::ValueRetriever {
public:
    IndexValueRetriever(std::shared_ptr<SIPlusParserContext> context, long index);
    IndexValueRetriever(std::shared_ptr<SIPlusParserContext> context, std::shared_ptr<ValueRetriever> parent, long index);

    text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> parent_;
    long index_;
};

IndexValueRetriever::IndexValueRetriever(
    std::shared_ptr<SIPlusParserContext> context, 
    long index
) : context_(context), index_(index) {}

IndexValueRetriever::IndexValueRetriever(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<text::ValueRetriever> parent,  
    long index
) : context_(context), parent_(parent), index_(index) {}

text::UnknownDataTypeContainer IndexValueRetriever::retrieve(InvocationContext& value) const {
    text::UnknownDataTypeContainer val = parent_ ? parent_->retrieve(value) : value.default_data();

    auto iterator = context_->iterator(val)->iterator(val);

    size_t i = 0;
    bool more = iterator->more();
    while(more) {
        iterator->next();

        if(i == index_) return iterator->current();

        more = iterator->more();
        i++;
    }

    throw std::runtime_error{util::to_string("index ", index_, " out of range")};
}

class LiteralValueRetriever : public text::ValueRetriever {
public:
    explicit LiteralValueRetriever(text::UnknownDataTypeContainer value);

    virtual text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    text::UnknownDataTypeContainer value_;
};

LiteralValueRetriever::LiteralValueRetriever(text::UnknownDataTypeContainer value) : value_(value) {}

text::UnknownDataTypeContainer LiteralValueRetriever::retrieve(InvocationContext& value) const {
    return value_;
}

class DummyValueRetriever : public text::ValueRetriever {
public:
    DummyValueRetriever() {}

    text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override {
        return value.default_data();
    };
};

    
} /* anonymous */

class ArgListVisitor : public SIPlusParseTreeVisitor {
public:
    ArgListVisitor(
        std::shared_ptr<SIPlusParserContext> context, 
        std::shared_ptr<BuildContext> buildContext,
        const antlr4::BufferedTokenStream& tokens
    ) : context_(context), buildContext_(buildContext), tokens_(tokens) {}

    bool shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) override {
        return dynamic_cast<StringInterpolatorParser::ArgumentContext*>(node) == nullptr;
    }

    std::any visitArgument(StringInterpolatorParser::ArgumentContext *ctx) override {
        PipedExpressionVisitor visitor{context_, buildContext_, tokens_};
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
    std::shared_ptr<BuildContext> buildContext_;
    const antlr4::BufferedTokenStream& tokens_;
};


ExpressionVisitor::ExpressionVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<BuildContext> buildContext,
    const antlr4::BufferedTokenStream& tokens
) : context_(context), buildContext_(buildContext), tokens_(tokens) {}

bool ExpressionVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& current) {
    return dynamic_cast<StringInterpolatorParser::Piped_expressionContext*>(node) == nullptr
        && dynamic_cast<StringInterpolatorParser::Expr_itemContext*>(node) == nullptr
        && dynamic_cast<StringInterpolatorParser::Expr_blockContext*>(node) == nullptr;
}

std::any ExpressionVisitor::visitPiped_expression(StringInterpolatorParser::Piped_expressionContext *ctx) {
    PipedExpressionVisitor visitor{context_, buildContext_, tokens_};
    return ctx->accept(&visitor);
}

std::any ExpressionVisitor::visitExpr_item(StringInterpolatorParser::Expr_itemContext *ctx) {
    PipedExpressionVisitor visitor{context_, buildContext_, tokens_};
    return ctx->accept(&visitor);
}

std::any ExpressionVisitor::visitExpr_block(StringInterpolatorParser::Expr_blockContext *ctx) {
    auto buildContext = make_build_context(buildContext_);
    BlockVisitor visitor{context_, buildContext, tokens_};
    return ctx->expr_block_contents()->accept(&visitor);
}

PipedExpressionVisitor::PipedExpressionVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<BuildContext> buildContext,
    const antlr4::BufferedTokenStream& tokens
) : context_(context), buildContext_(buildContext), tokens_(tokens) {}

bool PipedExpressionVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) {
    return dynamic_cast<StringInterpolatorParser::FuncContext*>(node) == nullptr &&
           dynamic_cast<StringInterpolatorParser::LiteralContext*>(node) == nullptr && 
           dynamic_cast<StringInterpolatorParser::PropertyContext*>(node) == nullptr;
}

std::any PipedExpressionVisitor::visitFunc(StringInterpolatorParser::FuncContext *ctx) {
    auto name = ctx->ID()->getText();
    bool custom = static_cast<bool>(ctx->AT());

    std::any val;
    if(ctx->arg_list()) {
        ArgListVisitor visitor{context_, buildContext_, tokens_};
        val = ctx->arg_list()->accept(&visitor);
    } else {
        val = std::vector<std::shared_ptr<text::ValueRetriever>>{};
    }

    auto args = std::any_cast<std::vector<std::shared_ptr<text::ValueRetriever>>>(val);

    if(custom) {
        value_ = buildContext_->function(name).value(value_, args);
    } else {
        value_ = context_->function(name).value(value_, args);
    }

    return value_;
}

std::any PipedExpressionVisitor::visitLiteral(StringInterpolatorParser::LiteralContext *ctx) {
    if(value_) {
        throw std::runtime_error{"Literals cannot accept inputs"};
    }

    LiteralVisitor visitor{context_, buildContext_, tokens_};
    auto literal = ctx->accept(&visitor);
    auto data = std::any_cast<text::UnknownDataTypeContainer>(literal);
    value_ = std::make_shared<LiteralValueRetriever>(data);
    return value_;
}

std::any PipedExpressionVisitor::visitArray(StringInterpolatorParser::ArrayContext *ctx) {
    std::vector<std::shared_ptr<text::ValueRetriever>> vals;

    for(auto val : ctx->array_item()) {
        PipedExpressionVisitor visitor{context_, buildContext_, tokens_};
        auto result = val->accept(&visitor);
        vals.push_back(std::any_cast<std::shared_ptr<text::ValueRetriever>>(result));
    }

    value_ = std::make_shared<LiteralArrayValueRetriever>(vals);
    return value_;
}

std::shared_ptr<text::ValueRetriever> access_property(
    std::shared_ptr<SIPlusParserContext> ctx,
    std::shared_ptr<text::ValueRetriever> parent, 
    StringInterpolatorParser::Property_itemContext* property
) {
    if(property->property_name()) {
        if(!parent) {
            return std::make_shared<AccessorValueRetriever>(ctx, property->property_name()->ID()->getText());
        } else {
            return std::make_shared<AccessorValueRetriever>(ctx, parent, property->property_name()->ID()->getText());
        }
    } else if(property->property_index()) {
        long idx = std::stoi(property->property_index()->INT()->getText());
        if(!parent) {
            return std::make_shared<IndexValueRetriever>(ctx, idx);
        } else {
            return std::make_shared<IndexValueRetriever>(ctx, parent, idx);
        }
    } else {
        throw std::runtime_error{util::to_string("Unsure how to handle '", property->getText(), "'")};
    }
}

std::any PipedExpressionVisitor::visitProperty(StringInterpolatorParser::PropertyContext *ctx) {
    std::shared_ptr<text::ValueRetriever> existing = value_;

    for(auto& token : ctx->property_item()) {
        existing = access_property(context_, existing, token);
    }

    if(!existing) {
        existing = std::make_shared<DummyValueRetriever>();
    }

    value_ = std::static_pointer_cast<text::ValueRetriever>(existing);
    return value_;
}

std::any PipedExpressionVisitor::visitVariable_reference(StringInterpolatorParser::Variable_referenceContext *ctx) {
    std::shared_ptr<text::ValueRetriever> existing = buildContext_->get_variable(ctx->ID()->getText());

    for(auto& token : ctx->property_item()) {
        existing = access_property(context_, existing, token);
    }

    value_ = existing;
    return existing;
}

}

