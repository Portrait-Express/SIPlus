
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

  virtual std::any visitNull(StringInterpolatorParser::NullContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimitive(StringInterpolatorParser::PrimitiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArray(StringInterpolatorParser::ArrayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAccessor(StringInterpolatorParser::AccessorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndexer(StringInterpolatorParser::IndexerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable(StringInterpolatorParser::VariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(StringInterpolatorParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCall(StringInterpolatorParser::CallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable_declaration(StringInterpolatorParser::Variable_declarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariable_assignment(StringInterpolatorParser::Variable_assignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_parameter(StringInterpolatorParser::Function_parameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_parameters(StringInterpolatorParser::Function_parametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunction_definition(StringInterpolatorParser::Function_definitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPiped_suffixable_expr(StringInterpolatorParser::Piped_suffixable_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPiped_expr_part(StringInterpolatorParser::Piped_expr_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPiped_expr(StringInterpolatorParser::Piped_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuffixable_expr(StringInterpolatorParser::Suffixable_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr_suffix(StringInterpolatorParser::Expr_suffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(StringInterpolatorParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock_stmt(StringInterpolatorParser::Block_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock_expr(StringInterpolatorParser::Block_exprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock_contents(StringInterpolatorParser::Block_contentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(StringInterpolatorParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression_program(StringInterpolatorParser::Expression_programContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterp_eval(StringInterpolatorParser::Interp_evalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterp_loop_start(StringInterpolatorParser::Interp_loop_startContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterp_loop_end(StringInterpolatorParser::Interp_loop_endContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterp_loop(StringInterpolatorParser::Interp_loopContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterp_stmt(StringInterpolatorParser::Interp_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterp_normal(StringInterpolatorParser::Interp_normalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterp_part(StringInterpolatorParser::Interp_partContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInterpolated_str(StringInterpolatorParser::Interpolated_strContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProgram(StringInterpolatorParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }


};

