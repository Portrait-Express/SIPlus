#include "literal_visitor.h"
#include "Token.h"
#include "generated/StringInterpolatorLexer.h"
#include "siplus/text/data.h"

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

//INT: ('0'[xboXBO])?[0-9_]+ ;
long parse_int(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(),
                   [](char c) { return std::tolower(c); });

    text.erase(std::remove(text.begin(), text.end(), '_'), text.end());

    if(text.starts_with("0x")) {
        return strtol(text.c_str() + 2, NULL, 16);
    } else if(text.starts_with("0o")) {
        return strtol(text.c_str() + 2, NULL, 8);
    } else if(text.starts_with("0b")) {
        return strtol(text.c_str() + 2, NULL, 2);
    } else {
        return strtol(text.c_str(), NULL, 10);
    }
}

//FLOAT: ( [0-9]+ '.' [0-9]* ) | ( '.' [0-9]+ ) ;
double parse_float(const std::string& text) {
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
    for(int i = node->start->getTokenIndex() + 1; i < stop; i++) {
        antlr4::Token *token = tokens_.get(i);
        if(token->getType() == StringInterpolatorLexer::STRING_ESCAPE) {
            ss << get_escape(token->getText().substr(1));
        } else {
            ss << token->getText();
        }
    }

    return text::make_data(ss.str());
}

std::any LiteralVisitor::visitInteger(StringInterpolatorParser::IntegerContext *node) {
    return text::make_data(parse_int(node->getText()));
}

std::any LiteralVisitor::visitFloat(StringInterpolatorParser::FloatContext *node) {
    return text::make_data(parse_float(node->getText()));
}

}
