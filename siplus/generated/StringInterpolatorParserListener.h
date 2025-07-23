
// Generated from StringInterpolatorParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "StringInterpolatorParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by StringInterpolatorParser.
 */
class  StringInterpolatorParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterField(StringInterpolatorParser::FieldContext *ctx) = 0;
  virtual void exitField(StringInterpolatorParser::FieldContext *ctx) = 0;

  virtual void enterString(StringInterpolatorParser::StringContext *ctx) = 0;
  virtual void exitString(StringInterpolatorParser::StringContext *ctx) = 0;

  virtual void enterInteger(StringInterpolatorParser::IntegerContext *ctx) = 0;
  virtual void exitInteger(StringInterpolatorParser::IntegerContext *ctx) = 0;

  virtual void enterFloat(StringInterpolatorParser::FloatContext *ctx) = 0;
  virtual void exitFloat(StringInterpolatorParser::FloatContext *ctx) = 0;

  virtual void enterLiteral(StringInterpolatorParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(StringInterpolatorParser::LiteralContext *ctx) = 0;

  virtual void enterArgument(StringInterpolatorParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(StringInterpolatorParser::ArgumentContext *ctx) = 0;

  virtual void enterArg_list(StringInterpolatorParser::Arg_listContext *ctx) = 0;
  virtual void exitArg_list(StringInterpolatorParser::Arg_listContext *ctx) = 0;

  virtual void enterFunc(StringInterpolatorParser::FuncContext *ctx) = 0;
  virtual void exitFunc(StringInterpolatorParser::FuncContext *ctx) = 0;

  virtual void enterExpr_item(StringInterpolatorParser::Expr_itemContext *ctx) = 0;
  virtual void exitExpr_item(StringInterpolatorParser::Expr_itemContext *ctx) = 0;

  virtual void enterExpr(StringInterpolatorParser::ExprContext *ctx) = 0;
  virtual void exitExpr(StringInterpolatorParser::ExprContext *ctx) = 0;

  virtual void enterEval(StringInterpolatorParser::EvalContext *ctx) = 0;
  virtual void exitEval(StringInterpolatorParser::EvalContext *ctx) = 0;

  virtual void enterLoop_start(StringInterpolatorParser::Loop_startContext *ctx) = 0;
  virtual void exitLoop_start(StringInterpolatorParser::Loop_startContext *ctx) = 0;

  virtual void enterLoop_end(StringInterpolatorParser::Loop_endContext *ctx) = 0;
  virtual void exitLoop_end(StringInterpolatorParser::Loop_endContext *ctx) = 0;

  virtual void enterLoop(StringInterpolatorParser::LoopContext *ctx) = 0;
  virtual void exitLoop(StringInterpolatorParser::LoopContext *ctx) = 0;

  virtual void enterStmt(StringInterpolatorParser::StmtContext *ctx) = 0;
  virtual void exitStmt(StringInterpolatorParser::StmtContext *ctx) = 0;

  virtual void enterNormal(StringInterpolatorParser::NormalContext *ctx) = 0;
  virtual void exitNormal(StringInterpolatorParser::NormalContext *ctx) = 0;

  virtual void enterProgram(StringInterpolatorParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(StringInterpolatorParser::ProgramContext *ctx) = 0;


};

