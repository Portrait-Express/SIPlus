
// Generated from StringInterpolatorParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "StringInterpolatorParserListener.h"


/**
 * This class provides an empty implementation of StringInterpolatorParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  StringInterpolatorParserBaseListener : public StringInterpolatorParserListener {
public:

  virtual void enterField(StringInterpolatorParser::FieldContext * /*ctx*/) override { }
  virtual void exitField(StringInterpolatorParser::FieldContext * /*ctx*/) override { }

  virtual void enterString(StringInterpolatorParser::StringContext * /*ctx*/) override { }
  virtual void exitString(StringInterpolatorParser::StringContext * /*ctx*/) override { }

  virtual void enterInteger(StringInterpolatorParser::IntegerContext * /*ctx*/) override { }
  virtual void exitInteger(StringInterpolatorParser::IntegerContext * /*ctx*/) override { }

  virtual void enterFloat(StringInterpolatorParser::FloatContext * /*ctx*/) override { }
  virtual void exitFloat(StringInterpolatorParser::FloatContext * /*ctx*/) override { }

  virtual void enterLiteral(StringInterpolatorParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(StringInterpolatorParser::LiteralContext * /*ctx*/) override { }

  virtual void enterArgument(StringInterpolatorParser::ArgumentContext * /*ctx*/) override { }
  virtual void exitArgument(StringInterpolatorParser::ArgumentContext * /*ctx*/) override { }

  virtual void enterArg_list(StringInterpolatorParser::Arg_listContext * /*ctx*/) override { }
  virtual void exitArg_list(StringInterpolatorParser::Arg_listContext * /*ctx*/) override { }

  virtual void enterFunc(StringInterpolatorParser::FuncContext * /*ctx*/) override { }
  virtual void exitFunc(StringInterpolatorParser::FuncContext * /*ctx*/) override { }

  virtual void enterExpr_item(StringInterpolatorParser::Expr_itemContext * /*ctx*/) override { }
  virtual void exitExpr_item(StringInterpolatorParser::Expr_itemContext * /*ctx*/) override { }

  virtual void enterExpr(StringInterpolatorParser::ExprContext * /*ctx*/) override { }
  virtual void exitExpr(StringInterpolatorParser::ExprContext * /*ctx*/) override { }

  virtual void enterEval(StringInterpolatorParser::EvalContext * /*ctx*/) override { }
  virtual void exitEval(StringInterpolatorParser::EvalContext * /*ctx*/) override { }

  virtual void enterLoop_start(StringInterpolatorParser::Loop_startContext * /*ctx*/) override { }
  virtual void exitLoop_start(StringInterpolatorParser::Loop_startContext * /*ctx*/) override { }

  virtual void enterLoop_end(StringInterpolatorParser::Loop_endContext * /*ctx*/) override { }
  virtual void exitLoop_end(StringInterpolatorParser::Loop_endContext * /*ctx*/) override { }

  virtual void enterLoop(StringInterpolatorParser::LoopContext * /*ctx*/) override { }
  virtual void exitLoop(StringInterpolatorParser::LoopContext * /*ctx*/) override { }

  virtual void enterStmt(StringInterpolatorParser::StmtContext * /*ctx*/) override { }
  virtual void exitStmt(StringInterpolatorParser::StmtContext * /*ctx*/) override { }

  virtual void enterNormal(StringInterpolatorParser::NormalContext * /*ctx*/) override { }
  virtual void exitNormal(StringInterpolatorParser::NormalContext * /*ctx*/) override { }

  virtual void enterProgram(StringInterpolatorParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(StringInterpolatorParser::ProgramContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

