#include "ANTLRInputStream.h"
#include "BaseErrorListener.h"
#include "ConsoleErrorListener.h"
#include "DFA.h"
#include "Recognizer.h"
#include "expr_visitor.h"
#include "generated/StringInterpolatorLexer.h"
#include "generated/StringInterpolatorParser.h"

#include "siplus/parser.h"
#include "siplus/context.h"
#include "siplus/text/constructor.h"

#include "parser_impl.h"
#include "interpolation_visitor.h"
#include <format>

namespace SIPLUS_NAMESPACE {

namespace {

struct ErrorListener : public antlr4::BaseErrorListener {

    void syntaxError(
        antlr4::Recognizer *recognizer, 
        antlr4::Token * offendingSymbol, 
        size_t line, 
        size_t charPositionInLine,
        const std::string &msg, 
        std::exception_ptr e) override;

    void reportAmbiguity(
        antlr4::Parser *recognizer, 
        const antlr4::dfa::DFA &dfa, 
        size_t startIndex, 
        size_t stopIndex, bool exact,
        const antlrcpp::BitSet &ambigAlts, 
        antlr4::atn::ATNConfigSet *configs) override;

    void reportAttemptingFullContext(
        antlr4::Parser *recognizer, 
        const antlr4::dfa::DFA &dfa, 
        size_t startIndex, 
        size_t stopIndex,
        const antlrcpp::BitSet &conflictingAlts, 
        antlr4::atn::ATNConfigSet *configs) override;

    void reportContextSensitivity(
        antlr4::Parser *recognizer, 
        const antlr4::dfa::DFA &dfa, 
        size_t startIndex, 
        size_t stopIndex,
        size_t prediction, 
        antlr4::atn::ATNConfigSet *configs) override;

};

void ErrorListener::syntaxError(
    antlr4::Recognizer *recognizer, 
    antlr4::Token * offendingSymbol, 
    size_t line, 
    size_t charPositionInLine,
    const std::string &msg, 
    std::exception_ptr e) {

    throw std::runtime_error{std::format("line {}:{} {}", line, charPositionInLine, msg)};
}

void ErrorListener::reportAmbiguity(
    antlr4::Parser *recognizer, 
    const antlr4::dfa::DFA &dfa, 
    size_t startIndex, 
    size_t stopIndex, bool exact,
    const antlrcpp::BitSet &ambigAlts, 
    antlr4::atn::ATNConfigSet *configs) {

}

void ErrorListener::reportAttemptingFullContext(
    antlr4::Parser *recognizer, 
    const antlr4::dfa::DFA &dfa, 
    size_t startIndex, 
    size_t stopIndex,
    const antlrcpp::BitSet &conflictingAlts, 
    antlr4::atn::ATNConfigSet *configs) {

}

void ErrorListener::reportContextSensitivity(
    antlr4::Parser *recognizer, 
    const antlr4::dfa::DFA &dfa, 
    size_t startIndex, 
    size_t stopIndex,
    size_t prediction, 
    antlr4::atn::ATNConfigSet *configs) {

}


} /* anonymous */

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

    ErrorListener errors;
    lexer.removeErrorListeners();
    parser.removeErrorListeners();
    lexer.addErrorListener(&errors);
    parser.addErrorListener(&errors);
    
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

    ErrorListener errors;
    lexer.removeErrorListeners();
    parser.removeErrorListeners();
    lexer.addErrorListener(&errors);
    parser.addErrorListener(&errors);
    
    lexer.mode = StringInterpolatorLexer::TEMPLATE;
    antlr4::tree::ParseTree *tree = parser.expression_program();
    ExpressionVisitor visitor{context_, tokens};
    auto val = tree->accept(&visitor);

    return std::any_cast<std::shared_ptr<text::ValueRetriever>>(val);
}


const SIPlusParserContext& ParserImpl::context() const {
    return *context_;
}

SIPlusParserContext& ParserImpl::context() {
    return *context_;
}

}
