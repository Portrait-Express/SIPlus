#include "ANTLRInputStream.h"
#include "BaseErrorListener.h"
#include "BufferedTokenStream.h"
#include "ConsoleErrorListener.h"
#include "DFA.h"
#include "Recognizer.h"
#include "block_visitor.h"
#include "build_context.h"
#include "expr_visitor.h"
#include "generated/StringInterpolatorLexer.h"
#include "generated/StringInterpolatorParser.h"

#include "siplus/invocation_context.h"
#include "siplus/parser.h"
#include "siplus/context.h"
#include "siplus/text/constructor.h"

#include "parser_impl.h"
#include "interpolation_visitor.h"
#include "siplus/text/data.h"
#include <sstream>

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

    std::stringstream ss;
    ss << "line " << line << ':' << charPositionInLine << ' ' << msg;

    throw std::runtime_error{ss.str()};
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

/**
 * struct NewScopeValueRetriever - Wraps the passed scope in a new scope to avoid variable propagation.
 */
struct NewScopeValueRetriever : text::ValueRetriever {
    NewScopeValueRetriever(std::shared_ptr<text::ValueRetriever> expr) : expr_(expr) {}

    text::UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto wrapped = wrap_scope(value.shared_from_this()).build();
        return expr_->retrieve(*wrapped);
    }

private:
    std::shared_ptr<text::ValueRetriever> expr_;
};

} /* anonymous */

Parser::Parser() {
    impl_ = std::make_unique<ParserImpl>();
}

Parser::~Parser() {
    //Add destructor here because Impl class must be complete when unique_ptr 
    //is destroyed.
} 

text::TextConstructor Parser::get_interpolation(const std::string& text, const ParseOpts& opts) const {
    return impl_->get_interpolation(text, opts);
}

std::shared_ptr<text::ValueRetriever> Parser::get_expression(const std::string& text, const ParseOpts& opts) const {
    return impl_->get_expression(text, opts);
}

SIPlusParserContext& Parser::context() {
    return impl_->context();
}

const SIPlusParserContext& Parser::context() const {
    return impl_->context();
}

ParserImpl::ParserImpl() {
    context_ = std::make_shared<SIPlusParserContext>();
}

text::TextConstructor ParserImpl::get_interpolation(const std::string& text, const ParseOpts& opts) const {
    antlr4::ANTLRInputStream stream{text};
    StringInterpolatorLexer lexer{&stream};
    antlr4::BufferedTokenStream tokens{&lexer};
    StringInterpolatorParser parser{&tokens};

    ErrorListener errors;
    lexer.removeErrorListeners();
    parser.removeErrorListeners();
    lexer.addErrorListener(&errors);
    parser.addErrorListener(&errors);
    
    antlr4::tree::ParseTree *tree = parser.program();
    std::shared_ptr<BuildContext> buildContext = std::make_shared<BuildContext>();
    InterpolationVisitor visitor{context_, make_build_context(opts), tokens};
    auto val = tree->accept(&visitor);

    return std::any_cast<text::TextConstructor>(val);
}

std::shared_ptr<text::ValueRetriever> ParserImpl::get_expression(const std::string& text, const ParseOpts& opts) const {
    antlr4::ANTLRInputStream stream{text};
    StringInterpolatorLexer lexer{&stream};
    antlr4::BufferedTokenStream tokens{&lexer};
    StringInterpolatorParser parser{&tokens};

    ErrorListener errors;
    lexer.removeErrorListeners();
    parser.removeErrorListeners();
    lexer.addErrorListener(&errors);
    parser.addErrorListener(&errors);
    
    lexer.mode = StringInterpolatorLexer::TEMPLATE;
    auto tree = parser.expression_program();
    BlockVisitor visitor{context_, make_build_context(opts), tokens};
    auto val = tree->accept(&visitor);

    auto retriever = std::any_cast<std::shared_ptr<text::ValueRetriever>>(val);
    return std::make_shared<NewScopeValueRetriever>(retriever);
}


const SIPlusParserContext& ParserImpl::context() const {
    return *context_;
}

SIPlusParserContext& ParserImpl::context() {
    return *context_;
}

}
