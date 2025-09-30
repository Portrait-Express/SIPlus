#ifndef INCLUDE_SIPLUS_VISITOR_H_
#define INCLUDE_SIPLUS_VISITOR_H_

#include "ErrorNode.h"
#include "generated/StringInterpolatorParserBaseVisitor.h"
#include "ParseTree.h"

#include "siplus/config.h"

namespace SIPLUS_NAMESPACE {

class SIPlusParseTreeVisitor : public StringInterpolatorParserBaseVisitor {
    std::any visitChildren(antlr4::tree::ParseTree *node) override;
    std::any visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override;
    std::any aggregateResult(std::any oldValue, std::any newValue) override;
};

}

#endif  // INCLUDE_SIPLUS_VISITOR_H_
