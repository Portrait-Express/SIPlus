
// Generated from StringInterpolatorLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  StringInterpolatorLexer : public antlr4::Lexer {
public:
  enum {
    NORMAL_TEXT = 1, NORMAL_ESCAPE = 2, OPEN = 3, TRUE = 4, FALSE = 5, DOT = 6, 
    HASH = 7, SLASH = 8, CLOSE = 9, OPENP = 10, CLOSEP = 11, OPENB = 12, 
    CLOSEB = 13, COMMA = 14, PIPE = 15, BACKSLASH = 16, STRING_START = 17, 
    WS = 18, INT = 19, FLOAT = 20, ID = 21, ANY = 22, STRING_TEXT = 23, 
    STRING_ESCAPE = 24, STRING_END = 25
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

