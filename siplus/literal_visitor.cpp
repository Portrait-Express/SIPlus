#include "literal_visitor.h"
#include "Token.h"
#include "generated/StringInterpolatorLexer.h"
#include <sstream>

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

int parse_int(const std::string& text) {
    return 0;
}

float parse_float(const std::string& text) {
    return 0;
}

}

LiteralVisitor::LiteralVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    const antlr4::BufferedTokenStream& tokens) 
: context_(context), tokens_(tokens) {}


bool LiteralVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& currentResult) {
    return dynamic_cast<StringInterpolatorParser::StringContext*>(node) == nullptr && 
        dynamic_cast<StringInterpolatorParser::IntegerContext*>(node) == nullptr && 
        dynamic_cast<StringInterpolatorParser::FloatContext*>(node) == nullptr;
}

std::any LiteralVisitor::visitString(StringInterpolatorParser::StringContext *node) {
    std::stringstream ss;

    auto stop = node->stop->getTokenIndex();
    for(int i = node->start->getTokenIndex(); i < stop; i++) {
        antlr4::Token *token = tokens_.get(i);
        if(token->getType() == StringInterpolatorLexer::STRING_ESCAPE) {
            ss << get_escape(token->getText().substr(1));
        } else {
            ss << token->getText();
        }
    }

    return ss.str();
}

std::any LiteralVisitor::visitInteger(StringInterpolatorParser::IntegerContext *node) {
    return parse_int(node->getText());
}

std::any LiteralVisitor::visitFloat(StringInterpolatorParser::FloatContext *node) {
    return parse_float(node->getText());
}

}
