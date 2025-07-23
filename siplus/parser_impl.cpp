#include "siplus/parser.h"
#include "siplus/context.h"
#include "siplus/text/constructor.h"

#include "parser_impl.h"
#include "interpolation_visitor.h"

#include "ANTLRInputStream.h"
#include "generated/StringInterpolatorLexer.h"
#include "generated/StringInterpolatorParser.h"

namespace SIPLUS_NAMESPACE {

Parser::Parser() {
    impl_ = std::make_unique<ParserImpl>();
}

Parser::~Parser() {
    //Add destructor here because Impl class must be complete when unique_ptr 
    //is destroyed.
} 

text::TextConstructor Parser::get_interpolation(const std::string& text, std::shared_ptr<SIPlusParserContext> context) {
    return impl_->get_interpolation(text, context);
}

text::TextConstructor ParserImpl::get_interpolation(const std::string& text, std::shared_ptr<SIPlusParserContext> context) {
    antlr4::ANTLRInputStream stream{text};
    StringInterpolatorLexer lexer{&stream};
    antlr4::CommonTokenStream tokens{&lexer};
    StringInterpolatorParser parser{&tokens};
    
    antlr4::tree::ParseTree *tree = parser.program();
    InterpolationVisitor visitor{context, tokens};
    auto val = tree->accept(&visitor);

    return std::any_cast<text::TextConstructor>(val);
}

}
