#ifndef INCLUDE_SIPLUS_VISITOR_H_
#define INCLUDE_SIPLUS_VISITOR_H_

#include "ErrorNode.h"
#include "generated/StringInterpolatorParserBaseVisitor.h"
#include "ParseTree.h"

#include "siplus/config.h"
#include <any>

#define SIPLUS_DECLARE_NODE_RESULT(context, result) template<> struct NodeResultType<context> { using result_type = result; }

namespace SIPLUS_NAMESPACE {

template<typename T>
struct NodeResultType { };

class SIPlusParseTreeVisitor : public StringInterpolatorParserBaseVisitor {
    std::any visitChildren(antlr4::tree::ParseTree *node) override;
    std::any visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override;
    std::any aggregateResult(std::any oldValue, std::any newValue) override;

public:
    template<typename T> requires std::is_base_of_v<antlr4::ParserRuleContext, T> 
    NodeResultType<T>::result_type visit(T* ctx) {
        auto result = ctx->accept(this);
        return std::any_cast<typename NodeResultType<T>::result_type>(result);
    }
};

}

#endif  // INCLUDE_SIPLUS_VISITOR_H_
