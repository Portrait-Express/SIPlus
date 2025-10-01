
// Generated from StringInterpolatorLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  StringInterpolatorLexer : public antlr4::Lexer {
public:
  enum {
    NORMAL_TEXT = 1, NORMAL_ESCAPE = 2, OPEN = 3, TRUE = 4, FALSE = 5, DOT = 6, 
    HASH = 7, SLASH = 8, CLOSE = 9, OPENP = 10, CLOSEP = 11, PIPE = 12, 
    BACKSLASH = 13, STRING_START = 14, WS = 15, INT = 16, FLOAT = 17, ID = 18, 
    ANY = 19, STRING_TEXT = 20, STRING_ESCAPE = 21, STRING_END = 22
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

