#include "BufferedTokenStream.h"
#include "generated/StringInterpolatorParser.h"

#include <memory>

#include "siplus/text/data.h"
#include "siplus/util.h"

#include "expr_visitor.h"
#include "literal_visitor.h"
#include "visitor.h"

namespace SIPLUS_NAMESPACE {

namespace {

/**
 * @brief ValueRetriever to access a property on the parent object.
 */
class AccessorValueRetriever : public text::ValueRetriever {
public:
    AccessorValueRetriever(std::shared_ptr<SIPlusParserContext> context, std::string name);
    AccessorValueRetriever(std::shared_ptr<SIPlusParserContext> context, std::shared_ptr<ValueRetriever> parent, std::string name);

    text::UnknownDataTypeContainer retrieve(const text::UnknownDataTypeContainer& value) const override;

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

text::UnknownDataTypeContainer AccessorValueRetriever::retrieve(const text::UnknownDataTypeContainer& value) const {
    if(parent_) {
        auto parent = parent_->retrieve(value);
        auto accessor = context_->accessor(parent);
        return accessor->access(parent, name_);
    } else {
        auto accessor = context_->accessor(value);
        return accessor->access(value, name_);
    }
}

/**
 * @brief ValueRetriever to access an index on an iterable object.
 */
class IndexValueRetriever : public text::ValueRetriever {
public:
    IndexValueRetriever(std::shared_ptr<SIPlusParserContext> context, long index);
    IndexValueRetriever(std::shared_ptr<SIPlusParserContext> context, std::shared_ptr<ValueRetriever> parent, long index);

    text::UnknownDataTypeContainer retrieve(const text::UnknownDataTypeContainer& value) const override;

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

text::UnknownDataTypeContainer IndexValueRetriever::retrieve(const text::UnknownDataTypeContainer& value) const {
    text::UnknownDataTypeContainer val = parent_ ? parent_->retrieve(value) : value;

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

    virtual text::UnknownDataTypeContainer retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    text::UnknownDataTypeContainer value_;
};

LiteralValueRetriever::LiteralValueRetriever(text::UnknownDataTypeContainer value) : value_(value) {}

text::UnknownDataTypeContainer LiteralValueRetriever::retrieve(const text::UnknownDataTypeContainer& value) const {
    return value_;
}

class DummyValueRetriever : public text::ValueRetriever {
public:
    DummyValueRetriever() {}

    text::UnknownDataTypeContainer retrieve(const text::UnknownDataTypeContainer& value) const override {
        return value;
    };
};

    
} /* anonymous */

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
           dynamic_cast<StringInterpolatorParser::PropertyContext*>(node) == nullptr;
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
    value_ = std::make_shared<LiteralValueRetriever>(data);
    return value_;
}

std::any ExpressionVisitor::visitProperty(StringInterpolatorParser::PropertyContext *ctx) {
    std::shared_ptr<text::ValueRetriever> existing = value_;

    for(auto& token : ctx->property_item()) {
        if(token->property_name()) {
            if(!existing) {
                existing = std::make_shared<AccessorValueRetriever>(context_, token->property_name()->ID()->getText());
            } else {
                existing = std::make_shared<AccessorValueRetriever>(context_, existing, token->property_name()->ID()->getText());
            }
        } else if(token->property_index()) {
            long idx = std::stoi(token->property_index()->INT()->getText());
            if(!existing) {
                existing = std::make_shared<IndexValueRetriever>(context_, idx);
            } else {
                existing = std::make_shared<IndexValueRetriever>(context_, existing, idx);
            }
        }
    }

    value_ = std::static_pointer_cast<text::ValueRetriever>(existing);
    return value_;
}

struct LiteralArrayValueRetriever : public text::ValueRetriever {
    LiteralArrayValueRetriever(std::vector<std::shared_ptr<text::ValueRetriever>> items) : items_(items) {}
    
    text::UnknownDataTypeContainer retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    std::vector<std::shared_ptr<text::ValueRetriever>> items_;
};

text::UnknownDataTypeContainer 
LiteralArrayValueRetriever::retrieve(const text::UnknownDataTypeContainer& value) const {
    std::vector<text::UnknownDataTypeContainer> ret;
    ret.reserve(items_.size());

    for(auto item : items_) {
        ret.push_back(item->retrieve(value));
    }

    return text::make_data(ret);
}

std::any ExpressionVisitor::visitArray(StringInterpolatorParser::ArrayContext *ctx) {
    std::vector<std::shared_ptr<text::ValueRetriever>> vals;

    for(auto val : ctx->array_item()) {
        ExpressionVisitor visitor{context_, tokens_};
        auto result = val->accept(&visitor);
        vals.push_back(std::any_cast<std::shared_ptr<text::ValueRetriever>>(result));
    }

    value_ = std::make_shared<LiteralArrayValueRetriever>(vals);
    return value_;
}

}

