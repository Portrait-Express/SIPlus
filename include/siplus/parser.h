#ifndef INCLUDE_SIPLUS_PARSER_H
#define INCLUDE_SIPLUS_PARSER_H

#include <memory>

#include "siplus/context.h"
#include "siplus/text/constructor.h"
#include "siplus/_config.h"

namespace SIPLUS_NAMESPACE {

class ParserImpl;
class Parser {
public:
    Parser();

    text::TextConstructor get_interpolation(
        const std::string& text, std::shared_ptr<SIPlusParserContext> context);

    std::shared_ptr<text::ValueRetriever> get_expression( 
        const std::string& expression, std::shared_ptr<SIPlusParserContext> context);

    ~Parser();

private:
    std::unique_ptr<ParserImpl> impl_;
};

}

#endif // INCLUDE_SIPLUS_PARSER_H
