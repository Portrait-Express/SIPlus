
// Generated from StringInterpolatorLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  StringInterpolatorLexer : public antlr4::Lexer {
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
    TEMPLATE = 1, STRING = 2
  };

  explicit StringInterpolatorLexer(antlr4::CharStream *input);

  ~StringInterpolatorLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

