
#include "../si_parser.h"


// Generated from StringInterpolatorParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "StringInterpolatorParserVisitor.h"


/**
 * This class provides an empty implementation of StringInterpolatorParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  StringInterpolatorParserBaseVisitor : public StringInterpolatorParserVisitor {
public:

  virtual std::any visitProperty_name(StringInterpolatorParser::Property_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_index(StringInterpolatorParser::Property_indexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty_item(StringInterpolatorParser::Property_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty(StringInterpolatorParser::PropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString(StringInterpolatorParser::StringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInteger(StringInterpolatorParser::IntegerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFloat(StringInterpolatorParser::FloatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolean(StringInterpolatorParser::BooleanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(StringInterpolatorParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(StringInterpolatorParser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArg_list(StringInterpolatorParser::Arg_listContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunc(StringInterpolatorParser::FuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray_item(StringInterpolatorParser::Array_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray(StringInterpolatorParser::ArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr_item(StringInterpolatorParser::Expr_itemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPiped_expression(StringInterpolatorParser::Piped_expressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(StringInterpolatorParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEval(StringInterpolatorParser::EvalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoop_start(StringInterpolatorParser::Loop_startContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoop_end(StringInterpolatorParser::Loop_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLoop(StringInterpolatorParser::LoopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStmt(StringInterpolatorParser::StmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNormal(StringInterpolatorParser::NormalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterpolated_str(StringInterpolatorParser::Interpolated_strContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression_program(StringInterpolatorParser::Expression_programContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgram(StringInterpolatorParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }


};

