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

/**
 * struct ParseOpts - Parse options for an expression or interpolation.
 */
struct ParseOpts {
    /**
     * @globals A list of global variables that will be accessible at the root scope with $<name>
     */
    std::vector<std::string> globals;
};

class ParserImpl;

/**
 * @brief Parser class. This is the entry point to the library.
 */
class Parser {
public:
    /**
     * @brief Create a new parser
     */
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

    /**
     * @brief Get a text interpolation constructor. Called with default options.
     *
     * @param[in] text The template text
     */
    text::TextConstructor get_interpolation(const std::string& text) const;

    /**
     * @brief Get a text interpolation constructor.
     *
     * @param[in] text The template text
     * @param[in] opts Parse options
     */
    text::TextConstructor get_interpolation(const std::string& text, const ParseOpts& opts) const;

    /**
     * @brief Get an expression value retriever. Called with default options.
     *
     * @param[in] expression The expression 
     */
    std::shared_ptr<text::ValueRetriever> get_expression(const std::string& expression) const;

    /**
     * @brief Get an expression value retriever.
     *
     * @param[in] expression The expression 
     * @param[in] opts The parse options
     */
    std::shared_ptr<text::ValueRetriever> get_expression(const std::string& expression, const ParseOpts& opts) const;


    /**
     * @brief Get the context from this parser.
     */
    SIPlusParserContext& context();

    /**
     * @brief Get the context from this parser.
     */
    const SIPlusParserContext& context() const;

    ~Parser();

private:
    std::unique_ptr<ParserImpl> impl_;
};

}

#endif // INCLUDE_SIPLUS_PARSER_HXX_
