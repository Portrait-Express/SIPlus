#ifndef INCLUDE_SIPLUS_VISITOR_H_
#define INCLUDE_SIPLUS_VISITOR_H_

#include "ErrorNode.h"
#include "generated/StringInterpolatorParserBaseVisitor.h"
#include "ParseTree.h"

#include "siplus/_config.h"

namespace SIPLUS_NAMESPACE {

class SIPlusParseTreeVisitor : public StringInterpolatorParserBaseVisitor {
    virtual std::any visitChildren(antlr4::tree::ParseTree *node) override;
    virtual std::any visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override;
};

}

#endif  // INCLUDE_SIPLUS_VISITOR_H_
