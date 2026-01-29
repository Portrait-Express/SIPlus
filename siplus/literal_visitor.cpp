#include "literal_visitor.h"
#include "Token.h"
#include "generated/StringInterpolatorLexer.h"
#include "interpolation_visitor.h"
#include "siplus/data.h"
#include "siplus/types/bool.h"
#include "siplus/types/float.h"
#include "siplus/types/integer.h"
#include "siplus/types/string.h"
#include <cstdlib>
#include <string>

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
    return std::stod(text);
}

bool parse_bool(const std::string& text) {
    if(text == "true") {
        return true;
    } else if(text == "false") {
        return false;
    } else {
        throw std::runtime_error{"Boolean parsed text was not a recognized keyword"};
    }
}

}

LiteralVisitor::LiteralVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<BuildContext> buildContext, 
    const antlr4::BufferedTokenStream& tokens) 
: context_(context), buildContext_(buildContext), tokens_(tokens) {}


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

    return make_data<types::StringType>(ss.str());
}

std::any LiteralVisitor::visitInteger(StringInterpolatorParser::IntegerContext *node) {
    return make_data<types::IntegerType>(parse_int(node->getText()));
}

std::any LiteralVisitor::visitFloat(StringInterpolatorParser::FloatContext *node) {
    return make_data<types::FloatType>(parse_float(node->getText()));
}

std::any LiteralVisitor::visitBoolean(StringInterpolatorParser::BooleanContext *node) {
    return make_data<types::BoolType>(parse_bool(node->getText()));
}

}
