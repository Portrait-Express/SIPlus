#include "siplus/context.hxx"
#include "siplus/parser.hxx"
#include "siplus/text/constructor.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"

#ifndef INCLUDE_SIPLUS_PARSER_INTERNAL_HXX_
#define INCLUDE_SIPLUS_PARSER_INTERNAL_HXX_

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

#endif  // INCLUDE_SIPLUS_PARSER_INTERNAL_HXX_
