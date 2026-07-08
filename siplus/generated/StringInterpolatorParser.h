
// Generated from StringInterpolatorParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  StringInterpolatorParser : public antlr4::Parser {
public:
  enum {
    NORMAL_TEXT = 1, NORMAL_ESCAPE = 2, OPEN = 3, TRUE = 4, FALSE = 5, NULL_ = 6, 
    VAR = 7, PERSIST = 8, CONST = 9, DOT = 10, HASH = 11, SLASH = 12, CLOSE = 13, 
    OPENP = 14, CLOSEP = 15, OPENB = 16, CLOSEB = 17, COMMA = 18, PIPE = 19, 
    DOLLAR = 20, SEMICOLON = 21, QUESTION = 22, AT = 23, EQUAL = 24, ARROW = 25, 
    BACKSLASH = 26, STRING_START = 27, WS = 28, INT = 29, FLOAT = 30, ID = 31, 
    ANY = 32, STRING_TEXT = 33, STRING_ESCAPE = 34, STRING_END = 35
  };

  enum {
    RuleString = 0, RuleInteger = 1, RuleFloat = 2, RuleBoolean = 3, RuleNull = 4, 
    RulePrimitive = 5, RuleArray = 6, RuleAccessor = 7, RuleIndexer = 8, 
    RuleVariable = 9, RuleLiteral = 10, RuleCall = 11, RuleVariable_declaration = 12, 
    RuleVariable_assignment = 13, RuleFunction_parameter = 14, RuleFunction_parameters = 15, 
    RuleFunction_definition = 16, RulePiped_suffixable_expr = 17, RulePiped_expr_part = 18, 
    RulePiped_expr = 19, RuleSuffixable_expr = 20, RuleExpr_suffix = 21, 
    RuleExpr = 22, RuleBlock_stmt = 23, RuleBlock_expr = 24, RuleBlock_contents = 25, 
    RuleBlock = 26, RuleExpression_program = 27, RuleInterp_eval = 28, RuleInterp_loop_start = 29, 
    RuleInterp_loop_end = 30, RuleInterp_loop = 31, RuleInterp_stmt = 32, 
    RuleInterp_normal = 33, RuleInterp_part = 34, RuleInterpolated_str = 35, 
    RuleProgram = 36
  };

  explicit StringInterpolatorParser(antlr4::TokenStream *input);

  StringInterpolatorParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~StringInterpolatorParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class StringContext;
  class IntegerContext;
  class FloatContext;
  class BooleanContext;
  class NullContext;
  class PrimitiveContext;
  class ArrayContext;
  class AccessorContext;
  class IndexerContext;
  class VariableContext;
  class LiteralContext;
  class CallContext;
  class Variable_declarationContext;
  class Variable_assignmentContext;
  class Function_parameterContext;
  class Function_parametersContext;
  class Function_definitionContext;
  class Piped_suffixable_exprContext;
  class Piped_expr_partContext;
  class Piped_exprContext;
  class Suffixable_exprContext;
  class Expr_suffixContext;
  class ExprContext;
  class Block_stmtContext;
  class Block_exprContext;
  class Block_contentsContext;
  class BlockContext;
  class Expression_programContext;
  class Interp_evalContext;
  class Interp_loop_startContext;
  class Interp_loop_endContext;
  class Interp_loopContext;
  class Interp_stmtContext;
  class Interp_normalContext;
  class Interp_partContext;
  class Interpolated_strContext;
  class ProgramContext; 

  class  StringContext : public antlr4::ParserRuleContext {
  public:
    StringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_START();
    antlr4::tree::TerminalNode *STRING_END();
    std::vector<antlr4::tree::TerminalNode *> STRING_TEXT();
    antlr4::tree::TerminalNode* STRING_TEXT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STRING_ESCAPE();
    antlr4::tree::TerminalNode* STRING_ESCAPE(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringContext* string();

  class  IntegerContext : public antlr4::ParserRuleContext {
  public:
    IntegerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntegerContext* integer();

  class  FloatContext : public antlr4::ParserRuleContext {
  public:
    FloatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FloatContext* float_();

  class  BooleanContext : public antlr4::ParserRuleContext {
  public:
    BooleanContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BooleanContext* boolean();

  class  NullContext : public antlr4::ParserRuleContext {
  public:
    NullContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NULL_();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NullContext* null();

  class  PrimitiveContext : public antlr4::ParserRuleContext {
  public:
    PrimitiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringContext *string();
    IntegerContext *integer();
    FloatContext *float_();
    BooleanContext *boolean();
    NullContext *null();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimitiveContext* primitive();

  class  ArrayContext : public antlr4::ParserRuleContext {
  public:
    ArrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPENB();
    antlr4::tree::TerminalNode *CLOSEB();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayContext* array();

  class  AccessorContext : public antlr4::ParserRuleContext {
  public:
    AccessorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *ID();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AccessorContext* accessor();

  class  IndexerContext : public antlr4::ParserRuleContext {
  public:
    IndexerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPENB();
    ExprContext *expr();
    antlr4::tree::TerminalNode *CLOSEB();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndexerContext* indexer();

  class  VariableContext : public antlr4::ParserRuleContext {
  public:
    VariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOLLAR();
    antlr4::tree::TerminalNode *ID();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableContext* variable();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimitiveContext *primitive();
    ArrayContext *array();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  CallContext : public antlr4::ParserRuleContext {
  public:
    CallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *AT();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallContext* call();

  class  Variable_declarationContext : public antlr4::ParserRuleContext {
  public:
    Variable_declarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VAR();
    antlr4::tree::TerminalNode *DOLLAR();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *PERSIST();
    antlr4::tree::TerminalNode *CONST();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_declarationContext* variable_declaration();

  class  Variable_assignmentContext : public antlr4::ParserRuleContext {
  public:
    Variable_assignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOLLAR();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EQUAL();
    ExprContext *expr();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Variable_assignmentContext* variable_assignment();

  class  Function_parameterContext : public antlr4::ParserRuleContext {
  public:
    Function_parameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *QUESTION();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_parameterContext* function_parameter();

  class  Function_parametersContext : public antlr4::ParserRuleContext {
  public:
    Function_parametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPENP();
    std::vector<Function_parameterContext *> function_parameter();
    Function_parameterContext* function_parameter(size_t i);
    antlr4::tree::TerminalNode *CLOSEP();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_parametersContext* function_parameters();

  class  Function_definitionContext : public antlr4::ParserRuleContext {
  public:
    Function_definitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AT();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *ARROW();
    ExprContext *expr();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);
    Function_parametersContext *function_parameters();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Function_definitionContext* function_definition();

  class  Piped_suffixable_exprContext : public antlr4::ParserRuleContext {
  public:
    Piped_suffixable_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AccessorContext *accessor();
    antlr4::tree::TerminalNode *DOT();
    IndexerContext *indexer();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Piped_suffixable_exprContext* piped_suffixable_expr();

  class  Piped_expr_partContext : public antlr4::ParserRuleContext {
  public:
    Piped_expr_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CallContext *call();
    Piped_suffixable_exprContext *piped_suffixable_expr();
    std::vector<Expr_suffixContext *> expr_suffix();
    Expr_suffixContext* expr_suffix(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Piped_expr_partContext* piped_expr_part();

  class  Piped_exprContext : public antlr4::ParserRuleContext {
  public:
    Piped_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);
    std::vector<Piped_expr_partContext *> piped_expr_part();
    Piped_expr_partContext* piped_expr_part(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Piped_exprContext* piped_expr();

  class  Suffixable_exprContext : public antlr4::ParserRuleContext {
  public:
    Suffixable_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralContext *literal();
    VariableContext *variable();
    BlockContext *block();
    Piped_suffixable_exprContext *piped_suffixable_expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Suffixable_exprContext* suffixable_expr();

  class  Expr_suffixContext : public antlr4::ParserRuleContext {
  public:
    Expr_suffixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AccessorContext *accessor();
    IndexerContext *indexer();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_suffixContext* expr_suffix();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Suffixable_exprContext *suffixable_expr();
    std::vector<Expr_suffixContext *> expr_suffix();
    Expr_suffixContext* expr_suffix(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);
    Variable_assignmentContext *variable_assignment();
    CallContext *call();
    antlr4::tree::TerminalNode *DOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();

  class  Block_stmtContext : public antlr4::ParserRuleContext {
  public:
    Block_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    Piped_exprContext *piped_expr();
    Variable_declarationContext *variable_declaration();
    Function_definitionContext *function_definition();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Block_stmtContext* block_stmt();

  class  Block_exprContext : public antlr4::ParserRuleContext {
  public:
    Block_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    Piped_exprContext *piped_expr();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Block_exprContext* block_expr();

  class  Block_contentsContext : public antlr4::ParserRuleContext {
  public:
    Block_contentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Block_exprContext *block_expr();
    std::vector<Block_stmtContext *> block_stmt();
    Block_stmtContext* block_stmt(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Block_contentsContext* block_contents();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPENP();
    Block_contentsContext *block_contents();
    antlr4::tree::TerminalNode *CLOSEP();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  Expression_programContext : public antlr4::ParserRuleContext {
  public:
    Expression_programContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Block_contentsContext *block_contents();
    antlr4::tree::TerminalNode *EOF();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expression_programContext* expression_program();

  class  Interp_evalContext : public antlr4::ParserRuleContext {
  public:
    Interp_evalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN();
    Block_contentsContext *block_contents();
    antlr4::tree::TerminalNode *CLOSE();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interp_evalContext* interp_eval();

  class  Interp_loop_startContext : public antlr4::ParserRuleContext {
  public:
    Interp_loop_startContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN();
    antlr4::tree::TerminalNode *HASH();
    Block_contentsContext *block_contents();
    antlr4::tree::TerminalNode *CLOSE();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interp_loop_startContext* interp_loop_start();

  class  Interp_loop_endContext : public antlr4::ParserRuleContext {
  public:
    Interp_loop_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN();
    std::vector<antlr4::tree::TerminalNode *> SLASH();
    antlr4::tree::TerminalNode* SLASH(size_t i);
    antlr4::tree::TerminalNode *CLOSE();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interp_loop_endContext* interp_loop_end();

  class  Interp_loopContext : public antlr4::ParserRuleContext {
  public:
    Interp_loopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interp_loop_startContext *interp_loop_start();
    Interpolated_strContext *interpolated_str();
    Interp_loop_endContext *interp_loop_end();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interp_loopContext* interp_loop();

  class  Interp_stmtContext : public antlr4::ParserRuleContext {
  public:
    Interp_stmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interp_evalContext *interp_eval();
    Interp_loopContext *interp_loop();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interp_stmtContext* interp_stmt();

  class  Interp_normalContext : public antlr4::ParserRuleContext {
  public:
    Interp_normalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NORMAL_TEXT();
    antlr4::tree::TerminalNode* NORMAL_TEXT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NORMAL_ESCAPE();
    antlr4::tree::TerminalNode* NORMAL_ESCAPE(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interp_normalContext* interp_normal();

  class  Interp_partContext : public antlr4::ParserRuleContext {
  public:
    Interp_partContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interp_normalContext *interp_normal();
    Interp_stmtContext *interp_stmt();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interp_partContext* interp_part();

  class  Interpolated_strContext : public antlr4::ParserRuleContext {
  public:
    Interpolated_strContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Interp_partContext *> interp_part();
    Interp_partContext* interp_part(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interpolated_strContext* interpolated_str();

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interpolated_strContext *interpolated_str();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

