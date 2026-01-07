#include "siplus/context.h"
#include "siplus/parser.h"
#include "siplus/text/constructor.h"
#include "siplus/text/value_retrievers/retriever.h"

#ifndef INCLUDE_SIPLUS_PARSER_INTERNAL_H_
#define INCLUDE_SIPLUS_PARSER_INTERNAL_H_

namespace SIPLUS_NAMESPACE {

class ParserImpl {
public:
    ParserImpl();

    text::TextConstructor get_interpolation(const std::string& expression, const ParseOpts& opts) const;
    std::shared_ptr<text::ValueRetriever> get_expression(const std::string& expression, const ParseOpts& opts) const;

    SIPlusParserContext& context();
    const SIPlusParserContext& context() const;

private:
    std::shared_ptr<SIPlusParserContext> context_;
};

}

#endif  // INCLUDE_SIPLUS_PARSER_INTERNAL_H_
