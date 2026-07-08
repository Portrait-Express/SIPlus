#include <algorithm>
#include <any>
#include <memory>

#include "BufferedTokenStream.h"

#include "block_contents_visitor.hxx"
#include "siplus/data.hxx"
#include "siplus/text/constructor_steps/literal_step.hxx"
#include "siplus/text/constructor_steps/repeated_constructor_step.hxx"
#include "siplus/text/constructor_steps/retriever_step.hxx"
#include "siplus/text/value_retrievers/literal_retriever.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"
#include "siplus/types.hxx"
#include "siplus/util.hxx"
#include "siplus/build_context.hxx"
#include "siplus/context.hxx"
#include "siplus/text/constructor.hxx"

#include "../generated/StringInterpolatorParser.h"
#include "../generated/StringInterpolatorLexer.h"
#include "../retrievers/literal_array_retriever.hxx"
#include "../retrievers/default_data_retriever.hxx"
#include "../retrievers/variable_assignment_retriever.hxx"
#include "../util.hxx"
#include "siplus_visitor.hxx"
#include "expr_suffix_visitor.hxx"
#include "piped_expr_visitor.hxx"

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
int64_t parse_int(std::string text) {
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

} /* anonymous */


siplus_visitor::siplus_visitor(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<BuildContext> buildContext,
    const antlr4::BufferedTokenStream& tokens
) : context_(context), buildContext_(buildContext), tokens_(tokens) {}

std::any siplus_visitor::visitString(StringInterpolatorParser::StringContext *node) {
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

std::any siplus_visitor::visitInteger(StringInterpolatorParser::IntegerContext *node) {
    return make_data<types::IntegerType>(parse_int(node->getText()));
}

std::any siplus_visitor::visitFloat(StringInterpolatorParser::FloatContext *node) {
    return make_data<types::FloatType>(parse_float(node->getText()));
}

std::any siplus_visitor::visitBoolean(StringInterpolatorParser::BooleanContext *node) {
    return make_data<types::BoolType>(parse_bool(node->getText()));
}

std::any siplus_visitor::visitNull(StringInterpolatorParser::NullContext *ctx) {
    return UnknownDataTypeContainer{};
}

std::any siplus_visitor::visitPrimitive(StringInterpolatorParser::PrimitiveContext *ctx) {
    auto value = visitChildren(ctx);

    if(!value.has_value()) {
        throw std::runtime_error{"Unknown primitive syntax"};
    }

    return value;
}

std::any siplus_visitor::visitArray(StringInterpolatorParser::ArrayContext *ctx) {
    auto exprCtxs = ctx->expr();
    std::vector<std::shared_ptr<text::ValueRetriever>> vals;
    vals.reserve(exprCtxs.size());

    siplus_visitor visitor{context_, buildContext_, tokens_};
    std::transform(exprCtxs.begin(), exprCtxs.end(), std::back_inserter(vals),
                [&visitor](auto *ctx) { return visitor.visit(ctx); });

    return detail::make_retriever<LiteralArrayValueRetriever>(vals);
}

std::any siplus_visitor::visitLiteral(StringInterpolatorParser::LiteralContext *ctx) {
    if(ctx->array()) {
        return visitArray(ctx->array());
    } else if(ctx->primitive()) {
        auto val = visit(ctx->primitive());
        return detail::make_retriever<text::LiteralValueRetriever>(val);
    } else {
        throw std::runtime_error{"Unknown literal syntax"};
    }
}

std::any siplus_visitor::visitCall(StringInterpolatorParser::CallContext *ctx) {
    auto name = ctx->ID()->getText();
    bool custom = static_cast<bool>(ctx->AT());
    auto exprCtxs = ctx->expr();
    std::vector<std::shared_ptr<text::ValueRetriever>> args;
    args.reserve(exprCtxs.size());

    std::transform(exprCtxs.begin(), exprCtxs.end(), std::back_inserter(args), [this](auto *ctx) { return visit(ctx); });

    if(custom) {
        return buildContext_->function(name).value(nullptr, args);
    } else {
        return context_->function(name).value(nullptr, args);
    }
}

std::any siplus_visitor::visitVariable(StringInterpolatorParser::VariableContext *ctx) {
    const auto name = ctx->ID()->getText();
    const auto variable = buildContext_->get_variable(name);

    return std::static_pointer_cast<text::ValueRetriever>(variable);
}

std::any siplus_visitor::visitBlock(StringInterpolatorParser::BlockContext *ctx) {
    auto buildContext = make_build_context(buildContext_);
    block_contents_visitor visitor{context_, buildContext, tokens_};
    return visitor.visit(ctx->block_contents());
}

std::any siplus_visitor::visitPiped_suffixable_expr(StringInterpolatorParser::Piped_suffixable_exprContext *ctx) {
    expr_suffix_visitor visitor{detail::make_retriever<default_data_retriever>(), context_, buildContext_, tokens_};
    
    if(auto aCtx = ctx->accessor()) {
        visitor.visitAccessor(aCtx);
    } else if(auto iCtx = ctx->indexer()) {
        visitor.visitIndexer(iCtx);
    }

    return visitor.value;
}

std::any siplus_visitor::visitPiped_expr(StringInterpolatorParser::Piped_exprContext *ctx) {
    const auto expr = visit(ctx->expr());
    piped_expr_parts_visitor visitor{expr, context_, buildContext_, tokens_};
    return visitor.visitMultiple(ctx->piped_expr_part());
}

std::any siplus_visitor::visitSuffixable_expr(StringInterpolatorParser::Suffixable_exprContext *ctx) {
    if(auto literalCtx = ctx->literal()) {
        return visitLiteral(literalCtx);
    } else if(auto variableCtx = ctx->variable()) {
        return visitVariable(variableCtx);
    } else if(auto blockCtx = ctx->block()) {
        return visitBlock(blockCtx);
    } else if(auto pSuffixableCtx = ctx->piped_suffixable_expr()) {
        return visitPiped_suffixable_expr(pSuffixableCtx);
    } else {
        throw std::runtime_error{"Unknown suffxiable_expr syntax"};
    }
}

std::any siplus_visitor::visitVariable_assignment(StringInterpolatorParser::Variable_assignmentContext *ctx) {
    auto expression = visit(ctx->expr());
    std::string varName = ctx->ID()->getText();
    std::shared_ptr<VariableRetriever> variable = buildContext_->get_variable(varName);

    if(variable->is_const()) {
        throw std::runtime_error{util::to_string(
            "Attempted to mutate a const variable '$", varName, "'.")};
    }

    return detail::make_retriever<variable_assignment_retriever>(variable, expression);
}

std::any siplus_visitor::visitExpr(StringInterpolatorParser::ExprContext *ctx) {
    if(auto suffixableCtx = ctx->suffixable_expr()) { // suffixable_expr ( WS* expr_suffix )*
        auto suffixes = ctx->expr_suffix();
        auto base = visit(suffixableCtx);

        expr_suffix_visitor visitor{base, context_, buildContext_, tokens_};
        return visitor.visitMultiple(suffixes);
    } else if(ctx->DOT()) { // DOT
        return detail::make_retriever<default_data_retriever>();
    } else if(auto callCtx = ctx->call()) { // call
        return visitCall(callCtx);
    } else if(auto assignmentCtx = ctx->variable_assignment()) { // assignment
        return visitVariable_assignment(assignmentCtx);
    } else {
        throw std::runtime_error{"Unknown expr syntax"};
    }
}

std::any siplus_visitor::visitInterp_eval(StringInterpolatorParser::Interp_evalContext *ctx) {
    auto value = block_contents_visitor{context_, buildContext_, tokens_}
        .visit(ctx->block_contents());

    return std::static_pointer_cast<text::TextConstructorStep>(
        std::make_shared<text::ValueRetrieverConstructorStep>(context_, value)
    );
}

std::any siplus_visitor::visitInterp_loop(StringInterpolatorParser::Interp_loopContext *ctx) {
    auto value = block_contents_visitor{context_, buildContext_, tokens_}
        .visit(ctx->interp_loop_start()->block_contents());

    auto content = siplus_visitor{context_, make_build_context(buildContext_), tokens_}
        .visit(ctx->interpolated_str());

    return std::static_pointer_cast<text::TextConstructorStep>(
        std::make_shared<text::RepeatedConstructorConstructorStep>(context_, value, content)
    );
}


std::any siplus_visitor::visitInterp_stmt(StringInterpolatorParser::Interp_stmtContext *ctx) {
    if(auto loopCtx = ctx->interp_loop()) {
        return visitInterp_loop(loopCtx);
    } else if(auto evalCtx = ctx->interp_eval()) {
        return visitInterp_eval(ctx->interp_eval());
    } else {
        throw std::runtime_error{"Unknown interp_stmt syntax"};
    }
}

std::any siplus_visitor::visitInterp_normal(StringInterpolatorParser::Interp_normalContext *ctx) {
    std::stringstream ss;

    auto stop = ctx->stop->getTokenIndex();
    for(int i = ctx->start->getTokenIndex(); i <= stop; i++) {
        antlr4::Token *token = tokens_.get(i);
        if(token->getType() == StringInterpolatorLexer::NORMAL_ESCAPE) {
            ss << get_escape(token->getText().substr(1));
        } else {
            ss << token->getText();
        }
    }

    return std::static_pointer_cast<text::TextConstructorStep>(
        std::make_shared<text::LiteralConstructorStep>(ss.str())
    );
}

std::any siplus_visitor::visitInterp_part(StringInterpolatorParser::Interp_partContext *ctx) {
    if(auto stmtCtx = ctx->interp_stmt()) {
        return visitInterp_stmt(stmtCtx);
    } else if(auto normalCtx = ctx->interp_normal()) {
        return visitInterp_normal(normalCtx);
    } else {
        throw std::runtime_error{"Unknown interp_part syntax"};
    }
}

std::any siplus_visitor::visitInterpolated_str(StringInterpolatorParser::Interpolated_strContext *ctx) {
    text::TextConstructor constructor;

    for(auto step : ctx->interp_part()) {
        constructor.addStep(visit(step));
    }

    return constructor;
}

}

