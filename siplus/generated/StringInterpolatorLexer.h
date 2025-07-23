
// Generated from StringInterpolatorLexer.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  StringInterpolatorLexer : public antlr4::Lexer {
public:
  enum {
    NORMAL_TEXT = 1, NORMAL_ESCAPE = 2, OPEN = 3, DOT = 4, HASH = 5, SLASH = 6, 
    CLOSE = 7, OPENP = 8, CLOSEP = 9, PIPE = 10, BACKSLASH = 11, STRING_START = 12, 
    WS = 13, INT = 14, FLOAT = 15, ID = 16, ANY = 17, STRING_TEXT = 18, 
    STRING_ESCAPE = 19, STRING_END = 20
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

