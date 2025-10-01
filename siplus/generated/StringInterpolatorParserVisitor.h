
#include "../si_parser.h"


// Generated from StringInterpolatorParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "StringInterpolatorParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by StringInterpolatorParser.
 */
class  StringInterpolatorParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by StringInterpolatorParser.
   */
    virtual std::any visitField(StringInterpolatorParser::FieldContext *context) = 0;

    virtual std::any visitString(StringInterpolatorParser::StringContext *context) = 0;

    virtual std::any visitInteger(StringInterpolatorParser::IntegerContext *context) = 0;

    virtual std::any visitFloat(StringInterpolatorParser::FloatContext *context) = 0;

    virtual std::any visitBoolean(StringInterpolatorParser::BooleanContext *context) = 0;

    virtual std::any visitLiteral(StringInterpolatorParser::LiteralContext *context) = 0;

    virtual std::any visitArgument(StringInterpolatorParser::ArgumentContext *context) = 0;

    virtual std::any visitArg_list(StringInterpolatorParser::Arg_listContext *context) = 0;

    virtual std::any visitFunc(StringInterpolatorParser::FuncContext *context) = 0;

    virtual std::any visitExpr_item(StringInterpolatorParser::Expr_itemContext *context) = 0;

    virtual std::any visitExpr(StringInterpolatorParser::ExprContext *context) = 0;

    virtual std::any visitEval(StringInterpolatorParser::EvalContext *context) = 0;

    virtual std::any visitLoop_start(StringInterpolatorParser::Loop_startContext *context) = 0;

    virtual std::any visitLoop_end(StringInterpolatorParser::Loop_endContext *context) = 0;

    virtual std::any visitLoop(StringInterpolatorParser::LoopContext *context) = 0;

    virtual std::any visitStmt(StringInterpolatorParser::StmtContext *context) = 0;

    virtual std::any visitNormal(StringInterpolatorParser::NormalContext *context) = 0;

    virtual std::any visitInterpolated_str(StringInterpolatorParser::Interpolated_strContext *context) = 0;

    virtual std::any visitExpression_program(StringInterpolatorParser::Expression_programContext *context) = 0;

    virtual std::any visitProgram(StringInterpolatorParser::ProgramContext *context) = 0;


};

