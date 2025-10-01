
#include "../si_parser.h"


// Generated from StringInterpolatorParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  StringInterpolatorParser : public SIPLUS_NAMESPACE::internal::SIParser {
public:
  enum {
    NORMAL_TEXT = 1, NORMAL_ESCAPE = 2, OPEN = 3, TRUE = 4, FALSE = 5, DOT = 6, 
    HASH = 7, SLASH = 8, CLOSE = 9, OPENP = 10, CLOSEP = 11, PIPE = 12, 
    BACKSLASH = 13, STRING_START = 14, WS = 15, INT = 16, FLOAT = 17, ID = 18, 
    ANY = 19, STRING_TEXT = 20, STRING_ESCAPE = 21, STRING_END = 22
  };

  enum {
    RuleField = 0, RuleString = 1, RuleInteger = 2, RuleFloat = 3, RuleBoolean = 4, 
    RuleLiteral = 5, RuleArgument = 6, RuleArg_list = 7, RuleFunc = 8, RuleExpr_item = 9, 
    RuleExpr = 10, RuleEval = 11, RuleLoop_start = 12, RuleLoop_end = 13, 
    RuleLoop = 14, RuleStmt = 15, RuleNormal = 16, RuleInterpolated_str = 17, 
    RuleExpression_program = 18, RuleProgram = 19
  };

  explicit StringInterpolatorParser(antlr4::TokenStream *input);

  StringInterpolatorParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~StringInterpolatorParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class FieldContext;
  class StringContext;
  class IntegerContext;
  class FloatContext;
  class BooleanContext;
  class LiteralContext;
  class ArgumentContext;
  class Arg_listContext;
  class FuncContext;
  class Expr_itemContext;
  class ExprContext;
  class EvalContext;
  class Loop_startContext;
  class Loop_endContext;
  class LoopContext;
  class StmtContext;
  class NormalContext;
  class Interpolated_strContext;
  class Expression_programContext;
  class ProgramContext; 

  class  FieldContext : public antlr4::ParserRuleContext {
  public:
    FieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldContext* field();

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

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringContext *string();
    IntegerContext *integer();
    FloatContext *float_();
    BooleanContext *boolean();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralContext *literal();
    FieldContext *field();
    antlr4::tree::TerminalNode *OPENP();
    ExprContext *expr();
    antlr4::tree::TerminalNode *CLOSEP();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentContext* argument();

  class  Arg_listContext : public antlr4::ParserRuleContext {
  public:
    Arg_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentContext *> argument();
    ArgumentContext* argument(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Arg_listContext* arg_list();

  class  FuncContext : public antlr4::ParserRuleContext {
  public:
    FuncContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    Arg_listContext *arg_list();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncContext* func();

  class  Expr_itemContext : public antlr4::ParserRuleContext {
  public:
    Expr_itemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralContext *literal();
    FieldContext *field();
    FuncContext *func();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expr_itemContext* expr_item();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_itemContext *expr_item();
    ExprContext *expr();
    antlr4::tree::TerminalNode *PIPE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  EvalContext : public antlr4::ParserRuleContext {
  public:
    EvalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *CLOSE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EvalContext* eval();

  class  Loop_startContext : public antlr4::ParserRuleContext {
  public:
    Loop_startContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN();
    antlr4::tree::TerminalNode *HASH();
    ExprContext *expr();
    antlr4::tree::TerminalNode *CLOSE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Loop_startContext* loop_start();

  class  Loop_endContext : public antlr4::ParserRuleContext {
  public:
    Loop_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN();
    std::vector<antlr4::tree::TerminalNode *> SLASH();
    antlr4::tree::TerminalNode* SLASH(size_t i);
    antlr4::tree::TerminalNode *CLOSE();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Loop_endContext* loop_end();

  class  LoopContext : public antlr4::ParserRuleContext {
  public:
    LoopContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Loop_startContext *loop_start();
    Interpolated_strContext *interpolated_str();
    Loop_endContext *loop_end();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LoopContext* loop();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EvalContext *eval();
    LoopContext *loop();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StmtContext* stmt();

  class  NormalContext : public antlr4::ParserRuleContext {
  public:
    NormalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> NORMAL_TEXT();
    antlr4::tree::TerminalNode* NORMAL_TEXT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NORMAL_ESCAPE();
    antlr4::tree::TerminalNode* NORMAL_ESCAPE(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NormalContext* normal();

  class  Interpolated_strContext : public antlr4::ParserRuleContext {
  public:
    Interpolated_strContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NormalContext *> normal();
    NormalContext* normal(size_t i);
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Interpolated_strContext* interpolated_str();

  class  Expression_programContext : public antlr4::ParserRuleContext {
  public:
    Expression_programContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Expression_programContext* expression_program();

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Interpolated_strContext *interpolated_str();
    antlr4::tree::TerminalNode *EOF();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

