#ifndef INCLUDE_SIPLUS_PARSER_H
#define INCLUDE_SIPLUS_PARSER_H

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "siplus/context.h"
#include "siplus/text/constructor.h"
#include "siplus/config.h"

namespace SIPLUS_NAMESPACE {

struct ParseOpts {
    std::vector<std::string> globals;
};

class ParserImpl;
class Parser {
public:
    Parser();

    Parser(const Parser&) = delete;
    Parser(Parser&& other);

    Parser& operator=(Parser other) {
        swap(*this, other);
        return *this;
    }

    friend void swap(Parser& first, Parser& second) {
        using std::swap;
        swap(first.impl_, second.impl_);
    }

    text::TextConstructor get_interpolation(const std::string& text, const ParseOpts& opts) const;
    std::shared_ptr<text::ValueRetriever> get_expression(const std::string& expression, const ParseOpts& opts) const;


    SIPlusParserContext& context();
    const SIPlusParserContext& context() const;

    ~Parser();

private:
    std::unique_ptr<ParserImpl> impl_;
};

}

#endif // INCLUDE_SIPLUS_PARSER_H
