
// Generated from StringInterpolatorLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  StringInterpolatorLexer : public antlr4::Lexer {
public:
  enum {
    NORMAL_TEXT = 1, NORMAL_ESCAPE = 2, OPEN = 3, TRUE = 4, FALSE = 5, VAR = 6, 
    PERSIST = 7, CONST = 8, DOT = 9, HASH = 10, SLASH = 11, CLOSE = 12, 
    OPENP = 13, CLOSEP = 14, OPENB = 15, CLOSEB = 16, COMMA = 17, PIPE = 18, 
    DOLLAR = 19, SEMICOLON = 20, QUESTION = 21, AT = 22, EQUAL = 23, ARROW = 24, 
    BACKSLASH = 25, STRING_START = 26, WS = 27, INT = 28, FLOAT = 29, ID = 30, 
    ANY = 31, STRING_TEXT = 32, STRING_ESCAPE = 33, STRING_END = 34
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

