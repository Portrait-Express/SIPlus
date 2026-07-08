#ifndef INCLUDE_SIPLUS_VISITOR_HXX_
#define INCLUDE_SIPLUS_VISITOR_HXX_

#include "ErrorNode.h"
#include "../generated/StringInterpolatorParserBaseVisitor.h"
#include "ParseTree.h"

#include "siplus/config.h"
#include "siplus/util.hxx"
#include <any>
#include <cassert>
#include <typeindex>

#define SIPLUS_DECLARE_NODE_RESULT(context, result) template<> struct NodeResultType<context> { using result_type = result; }

namespace SIPLUS_NAMESPACE {

template<typename T>
struct NodeResultType { };

class SIPlusParseTreeVisitor : public StringInterpolatorParserBaseVisitor {
protected:
    std::any visitChildren(antlr4::tree::ParseTree *node) override;
    std::any visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override;
    std::any aggregateResult(std::any oldValue, std::any newValue) override;

public:
    template<typename T> requires std::is_base_of_v<antlr4::ParserRuleContext, T> 
    NodeResultType<T>::result_type visit(T* ctx) {
        auto result = ctx->accept(this);
        std::type_index type = typeid(typename NodeResultType<T>::result_type);

        if(result.type() != type) {
            throw std::runtime_error{util::to_string(
                "Value returned from visiting ", typeid(T).name(), " was not the expected type. ",
                "Expecting ", type.name(), " but got ", result.type().name()
            )};
        }

        return std::any_cast<typename NodeResultType<T>::result_type>(result);
    }
};

}

#endif  // INCLUDE_SIPLUS_VISITOR_HXX_
