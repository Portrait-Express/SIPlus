#pragma once
#ifndef INCLUDE_SIPLUS_PARSER_HXX_
#define INCLUDE_SIPLUS_PARSER_HXX_

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "siplus/context.hxx"
#include "siplus/text/constructor.hxx"
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

    text::TextConstructor get_interpolation(const std::string& text, const ParseOpts& opts = ParseOpts{}) const;
    std::shared_ptr<text::ValueRetriever> get_expression(const std::string& expression, const ParseOpts& opts = ParseOpts{}) const;


    SIPlusParserContext& context();
    const SIPlusParserContext& context() const;

    ~Parser();

private:
    std::unique_ptr<ParserImpl> impl_;
};

}

#endif // INCLUDE_SIPLUS_PARSER_HXX_
