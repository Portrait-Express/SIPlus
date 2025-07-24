#include "visitor.h"
#include <stdexcept>

namespace SIPLUS_NAMESPACE {

std::any SIPlusParseTreeVisitor::visitChildren(antlr4::tree::ParseTree *node) {
    std::any result = defaultResult();

    if (!shouldVisitNextChild(node, result)) {
      return result;
    }

    for (size_t i = 0; i < node->children.size(); i++) {
        std::any childResult = node->children[i]->accept(this);
        result = aggregateResult(std::move(result), std::move(childResult));
    }

    return result;
}

std::any SIPlusParseTreeVisitor::visitErrorNode(antlr4::tree::ErrorNode * node) {
    std::stringstream err;
    err << "Syntax Error: Unexpected '" << node->getText() << "'";
    throw std::runtime_error{err.str()};
}

}

