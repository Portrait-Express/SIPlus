
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
    virtual std::any visitString(StringInterpolatorParser::StringContext *context) = 0;

    virtual std::any visitInteger(StringInterpolatorParser::IntegerContext *context) = 0;

    virtual std::any visitFloat(StringInterpolatorParser::FloatContext *context) = 0;

    virtual std::any visitBoolean(StringInterpolatorParser::BooleanContext *context) = 0;

    virtual std::any visitNull(StringInterpolatorParser::NullContext *context) = 0;

    virtual std::any visitPrimitive(StringInterpolatorParser::PrimitiveContext *context) = 0;

    virtual std::any visitArray(StringInterpolatorParser::ArrayContext *context) = 0;

    virtual std::any visitAccessor(StringInterpolatorParser::AccessorContext *context) = 0;

    virtual std::any visitIndexer(StringInterpolatorParser::IndexerContext *context) = 0;

    virtual std::any visitVariable(StringInterpolatorParser::VariableContext *context) = 0;

    virtual std::any visitLiteral(StringInterpolatorParser::LiteralContext *context) = 0;

    virtual std::any visitCall(StringInterpolatorParser::CallContext *context) = 0;

    virtual std::any visitVariable_declaration(StringInterpolatorParser::Variable_declarationContext *context) = 0;

    virtual std::any visitVariable_assignment(StringInterpolatorParser::Variable_assignmentContext *context) = 0;

    virtual std::any visitFunction_parameter(StringInterpolatorParser::Function_parameterContext *context) = 0;

    virtual std::any visitFunction_parameters(StringInterpolatorParser::Function_parametersContext *context) = 0;

    virtual std::any visitFunction_definition(StringInterpolatorParser::Function_definitionContext *context) = 0;

    virtual std::any visitPiped_suffixable_expr(StringInterpolatorParser::Piped_suffixable_exprContext *context) = 0;

    virtual std::any visitPiped_expr_part(StringInterpolatorParser::Piped_expr_partContext *context) = 0;

    virtual std::any visitPiped_expr(StringInterpolatorParser::Piped_exprContext *context) = 0;

    virtual std::any visitSuffixable_expr(StringInterpolatorParser::Suffixable_exprContext *context) = 0;

    virtual std::any visitExpr_suffix(StringInterpolatorParser::Expr_suffixContext *context) = 0;

    virtual std::any visitExpr(StringInterpolatorParser::ExprContext *context) = 0;

    virtual std::any visitBlock_stmt(StringInterpolatorParser::Block_stmtContext *context) = 0;

    virtual std::any visitBlock_expr(StringInterpolatorParser::Block_exprContext *context) = 0;

    virtual std::any visitBlock_contents(StringInterpolatorParser::Block_contentsContext *context) = 0;

    virtual std::any visitBlock(StringInterpolatorParser::BlockContext *context) = 0;

    virtual std::any visitExpression_program(StringInterpolatorParser::Expression_programContext *context) = 0;

    virtual std::any visitInterp_eval(StringInterpolatorParser::Interp_evalContext *context) = 0;

    virtual std::any visitInterp_loop_start(StringInterpolatorParser::Interp_loop_startContext *context) = 0;

    virtual std::any visitInterp_loop_end(StringInterpolatorParser::Interp_loop_endContext *context) = 0;

    virtual std::any visitInterp_loop(StringInterpolatorParser::Interp_loopContext *context) = 0;

    virtual std::any visitInterp_stmt(StringInterpolatorParser::Interp_stmtContext *context) = 0;

    virtual std::any visitInterp_normal(StringInterpolatorParser::Interp_normalContext *context) = 0;

    virtual std::any visitInterp_part(StringInterpolatorParser::Interp_partContext *context) = 0;

    virtual std::any visitInterpolated_str(StringInterpolatorParser::Interpolated_strContext *context) = 0;

    virtual std::any visitProgram(StringInterpolatorParser::ProgramContext *context) = 0;


};

