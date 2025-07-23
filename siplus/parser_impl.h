#include "siplus/context.h"
#include "siplus/text/constructor.h"
#include "siplus/text/value_retrievers/retriever.h"

#ifndef INCLUDE_SIPLUS_PARSER_INTERNAL_H_
#define INCLUDE_SIPLUS_PARSER_INTERNAL_H_

namespace SIPLUS_NAMESPACE {

class ParserImpl {
public:
    text::TextConstructor get_interpolation(
        const std::string& expression, 
        std::shared_ptr<SIPlusParserContext> context);

    std::shared_ptr<text::ValueRetriever> get_expression(
        const std::string& expression, 
        std::shared_ptr<SIPlusParserContext> context);
};

}

#endif  // INCLUDE_SIPLUS_PARSER_INTERNAL_H_
