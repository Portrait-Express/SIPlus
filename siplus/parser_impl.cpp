#include "ANTLRInputStream.h"
#include "expr_visitor.h"
#include "generated/StringInterpolatorLexer.h"
#include "generated/StringInterpolatorParser.h"

#include "siplus/parser.h"
#include "siplus/context.h"
#include "siplus/text/constructor.h"

#include "parser_impl.h"
#include "interpolation_visitor.h"

namespace SIPLUS_NAMESPACE {

Parser::Parser() {
    impl_ = std::make_unique<ParserImpl>();
}

Parser::~Parser() {
    //Add destructor here because Impl class must be complete when unique_ptr 
    //is destroyed.
} 

text::TextConstructor Parser::get_interpolation(const std::string& text) const {
    return impl_->get_interpolation(text);
}

std::shared_ptr<text::ValueRetriever> Parser::get_expression(const std::string& text) const {
    return impl_->get_expression(text);
}

SIPlusParserContext& Parser::context() {
    return impl_->context();
}

ParserImpl::ParserImpl() {
    context_ = std::make_shared<SIPlusParserContext>();
}

text::TextConstructor ParserImpl::get_interpolation(const std::string& text) const {
    antlr4::ANTLRInputStream stream{text};
    StringInterpolatorLexer lexer{&stream};
    antlr4::CommonTokenStream tokens{&lexer};
    StringInterpolatorParser parser{&tokens};
    
    antlr4::tree::ParseTree *tree = parser.program();
    InterpolationVisitor visitor{context_, tokens};
    auto val = tree->accept(&visitor);

    return std::any_cast<text::TextConstructor>(val);
}

std::shared_ptr<text::ValueRetriever> ParserImpl::get_expression(const std::string& text) const {
    antlr4::ANTLRInputStream stream{text};
    StringInterpolatorLexer lexer{&stream};
    antlr4::CommonTokenStream tokens{&lexer};
    StringInterpolatorParser parser{&tokens};
    
    lexer.mode = StringInterpolatorLexer::TEMPLATE;
    antlr4::tree::ParseTree *tree = parser.expr();
    ExpressionVisitor visitor{context_, tokens};
    auto val = tree->accept(&visitor);
    std::cout << val.type().name() << std::endl;

    return std::any_cast<std::shared_ptr<text::ValueRetriever>>(val);
}


const SIPlusParserContext& ParserImpl::context() const {
    return *context_;
}

SIPlusParserContext& ParserImpl::context() {
    return *context_;
}

}
