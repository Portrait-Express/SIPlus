
#include "../si_parser.h"


// Generated from StringInterpolatorParser.g4 by ANTLR 4.13.2


#include "StringInterpolatorParserVisitor.h"

#include "StringInterpolatorParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct StringInterpolatorParserStaticData final {
  StringInterpolatorParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  StringInterpolatorParserStaticData(const StringInterpolatorParserStaticData&) = delete;
  StringInterpolatorParserStaticData(StringInterpolatorParserStaticData&&) = delete;
  StringInterpolatorParserStaticData& operator=(const StringInterpolatorParserStaticData&) = delete;
  StringInterpolatorParserStaticData& operator=(StringInterpolatorParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag stringinterpolatorparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<StringInterpolatorParserStaticData> stringinterpolatorparserParserStaticData = nullptr;

void stringinterpolatorparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (stringinterpolatorparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(stringinterpolatorparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<StringInterpolatorParserStaticData>(
    std::vector<std::string>{
      "field", "string", "integer", "float", "literal", "argument", "arg_list", 
      "func", "expr_item", "expr", "eval", "loop_start", "loop_end", "loop", 
      "stmt", "normal", "interpolated_str", "expression_program", "program"
    },
    std::vector<std::string>{
      "", "", "", "'{'", "'.'", "'#'", "'/'", "'}'", "'('", "')'", "'|'", 
      "'\\'"
    },
    std::vector<std::string>{
      "", "NORMAL_TEXT", "NORMAL_ESCAPE", "OPEN", "DOT", "HASH", "SLASH", 
      "CLOSE", "OPENP", "CLOSEP", "PIPE", "BACKSLASH", "STRING_START", "WS", 
      "INT", "FLOAT", "ID", "ANY", "STRING_TEXT", "STRING_ESCAPE", "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,20,147,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,1,0,1,0,1,0,1,0,1,0,5,0,44,
  	8,0,10,0,12,0,47,9,0,3,0,49,8,0,1,0,1,0,1,1,1,1,5,1,55,8,1,10,1,12,1,
  	58,9,1,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,4,3,4,69,8,4,1,5,1,5,1,5,1,5,
  	1,5,1,5,3,5,77,8,5,1,6,3,6,80,8,6,1,6,5,6,83,8,6,10,6,12,6,86,9,6,1,7,
  	1,7,1,7,1,8,1,8,1,8,3,8,94,8,8,1,9,1,9,1,9,1,9,1,9,1,9,5,9,102,8,9,10,
  	9,12,9,105,9,9,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,11,1,11,1,12,1,12,
  	1,12,1,12,1,12,1,13,1,13,1,13,1,13,1,14,1,14,3,14,127,8,14,1,15,4,15,
  	130,8,15,11,15,12,15,131,1,16,1,16,5,16,136,8,16,10,16,12,16,139,9,16,
  	1,17,1,17,1,17,1,18,1,18,1,18,1,18,0,1,18,19,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,0,2,1,0,18,19,1,0,1,2,143,0,38,1,0,0,0,2,52,
  	1,0,0,0,4,61,1,0,0,0,6,63,1,0,0,0,8,68,1,0,0,0,10,76,1,0,0,0,12,79,1,
  	0,0,0,14,87,1,0,0,0,16,93,1,0,0,0,18,95,1,0,0,0,20,106,1,0,0,0,22,110,
  	1,0,0,0,24,115,1,0,0,0,26,120,1,0,0,0,28,126,1,0,0,0,30,129,1,0,0,0,32,
  	137,1,0,0,0,34,140,1,0,0,0,36,143,1,0,0,0,38,39,6,0,-1,0,39,48,5,4,0,
  	0,40,45,5,16,0,0,41,42,5,4,0,0,42,44,5,16,0,0,43,41,1,0,0,0,44,47,1,0,
  	0,0,45,43,1,0,0,0,45,46,1,0,0,0,46,49,1,0,0,0,47,45,1,0,0,0,48,40,1,0,
  	0,0,48,49,1,0,0,0,49,50,1,0,0,0,50,51,6,0,-1,0,51,1,1,0,0,0,52,56,5,12,
  	0,0,53,55,7,0,0,0,54,53,1,0,0,0,55,58,1,0,0,0,56,54,1,0,0,0,56,57,1,0,
  	0,0,57,59,1,0,0,0,58,56,1,0,0,0,59,60,5,20,0,0,60,3,1,0,0,0,61,62,5,14,
  	0,0,62,5,1,0,0,0,63,64,5,15,0,0,64,7,1,0,0,0,65,69,3,2,1,0,66,69,3,4,
  	2,0,67,69,3,6,3,0,68,65,1,0,0,0,68,66,1,0,0,0,68,67,1,0,0,0,69,9,1,0,
  	0,0,70,77,3,8,4,0,71,77,3,0,0,0,72,73,5,8,0,0,73,74,3,18,9,0,74,75,5,
  	9,0,0,75,77,1,0,0,0,76,70,1,0,0,0,76,71,1,0,0,0,76,72,1,0,0,0,77,11,1,
  	0,0,0,78,80,3,10,5,0,79,78,1,0,0,0,79,80,1,0,0,0,80,84,1,0,0,0,81,83,
  	3,10,5,0,82,81,1,0,0,0,83,86,1,0,0,0,84,82,1,0,0,0,84,85,1,0,0,0,85,13,
  	1,0,0,0,86,84,1,0,0,0,87,88,5,16,0,0,88,89,3,12,6,0,89,15,1,0,0,0,90,
  	94,3,8,4,0,91,94,3,0,0,0,92,94,3,14,7,0,93,90,1,0,0,0,93,91,1,0,0,0,93,
  	92,1,0,0,0,94,17,1,0,0,0,95,96,6,9,-1,0,96,97,3,16,8,0,97,103,1,0,0,0,
  	98,99,10,1,0,0,99,100,5,10,0,0,100,102,3,16,8,0,101,98,1,0,0,0,102,105,
  	1,0,0,0,103,101,1,0,0,0,103,104,1,0,0,0,104,19,1,0,0,0,105,103,1,0,0,
  	0,106,107,5,3,0,0,107,108,3,18,9,0,108,109,5,7,0,0,109,21,1,0,0,0,110,
  	111,5,3,0,0,111,112,5,5,0,0,112,113,3,18,9,0,113,114,5,7,0,0,114,23,1,
  	0,0,0,115,116,5,3,0,0,116,117,5,6,0,0,117,118,5,6,0,0,118,119,5,7,0,0,
  	119,25,1,0,0,0,120,121,3,22,11,0,121,122,3,32,16,0,122,123,3,24,12,0,
  	123,27,1,0,0,0,124,127,3,20,10,0,125,127,3,26,13,0,126,124,1,0,0,0,126,
  	125,1,0,0,0,127,29,1,0,0,0,128,130,7,1,0,0,129,128,1,0,0,0,130,131,1,
  	0,0,0,131,129,1,0,0,0,131,132,1,0,0,0,132,31,1,0,0,0,133,136,3,30,15,
  	0,134,136,3,28,14,0,135,133,1,0,0,0,135,134,1,0,0,0,136,139,1,0,0,0,137,
  	135,1,0,0,0,137,138,1,0,0,0,138,33,1,0,0,0,139,137,1,0,0,0,140,141,3,
  	18,9,0,141,142,5,0,0,1,142,35,1,0,0,0,143,144,3,32,16,0,144,145,5,0,0,
  	1,145,37,1,0,0,0,13,45,48,56,68,76,79,84,93,103,126,131,135,137
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  stringinterpolatorparserParserStaticData = std::move(staticData);
}

}

StringInterpolatorParser::StringInterpolatorParser(TokenStream *input) : StringInterpolatorParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

StringInterpolatorParser::StringInterpolatorParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : SIPLUS_NAMESPACE::internal::SIParser(input) {
  StringInterpolatorParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *stringinterpolatorparserParserStaticData->atn, stringinterpolatorparserParserStaticData->decisionToDFA, stringinterpolatorparserParserStaticData->sharedContextCache, options);
}

StringInterpolatorParser::~StringInterpolatorParser() {
  delete _interpreter;
}

const atn::ATN& StringInterpolatorParser::getATN() const {
  return *stringinterpolatorparserParserStaticData->atn;
}

std::string StringInterpolatorParser::getGrammarFileName() const {
  return "StringInterpolatorParser.g4";
}

const std::vector<std::string>& StringInterpolatorParser::getRuleNames() const {
  return stringinterpolatorparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& StringInterpolatorParser::getVocabulary() const {
  return stringinterpolatorparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView StringInterpolatorParser::getSerializedATN() const {
  return stringinterpolatorparserParserStaticData->serializedATN;
}


//----------------- FieldContext ------------------------------------------------------------------

StringInterpolatorParser::FieldContext::FieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::FieldContext::DOT() {
  return getTokens(StringInterpolatorParser::DOT);
}

tree::TerminalNode* StringInterpolatorParser::FieldContext::DOT(size_t i) {
  return getToken(StringInterpolatorParser::DOT, i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::FieldContext::ID() {
  return getTokens(StringInterpolatorParser::ID);
}

tree::TerminalNode* StringInterpolatorParser::FieldContext::ID(size_t i) {
  return getToken(StringInterpolatorParser::ID, i);
}


size_t StringInterpolatorParser::FieldContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleField;
}


std::any StringInterpolatorParser::FieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitField(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::FieldContext* StringInterpolatorParser::field() {
  FieldContext *_localctx = _tracker.createInstance<FieldContext>(_ctx, getState());
  enterRule(_localctx, 0, StringInterpolatorParser::RuleField);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    enableChannel(antlr4::Token::HIDDEN_CHANNEL);
    setState(39);
    match(StringInterpolatorParser::DOT);
    setState(48);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      setState(40);
      match(StringInterpolatorParser::ID);
      setState(45);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(41);
          match(StringInterpolatorParser::DOT);
          setState(42);
          match(StringInterpolatorParser::ID); 
        }
        setState(47);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
      }
      break;
    }

    default:
      break;
    }
    disableChannel(antlr4::Token::HIDDEN_CHANNEL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringContext ------------------------------------------------------------------

StringInterpolatorParser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::StringContext::STRING_START() {
  return getToken(StringInterpolatorParser::STRING_START, 0);
}

tree::TerminalNode* StringInterpolatorParser::StringContext::STRING_END() {
  return getToken(StringInterpolatorParser::STRING_END, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::StringContext::STRING_TEXT() {
  return getTokens(StringInterpolatorParser::STRING_TEXT);
}

tree::TerminalNode* StringInterpolatorParser::StringContext::STRING_TEXT(size_t i) {
  return getToken(StringInterpolatorParser::STRING_TEXT, i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::StringContext::STRING_ESCAPE() {
  return getTokens(StringInterpolatorParser::STRING_ESCAPE);
}

tree::TerminalNode* StringInterpolatorParser::StringContext::STRING_ESCAPE(size_t i) {
  return getToken(StringInterpolatorParser::STRING_ESCAPE, i);
}


size_t StringInterpolatorParser::StringContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleString;
}


std::any StringInterpolatorParser::StringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitString(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::StringContext* StringInterpolatorParser::string() {
  StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, getState());
  enterRule(_localctx, 2, StringInterpolatorParser::RuleString);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(52);
    match(StringInterpolatorParser::STRING_START);
    setState(56);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::STRING_TEXT

    || _la == StringInterpolatorParser::STRING_ESCAPE) {
      setState(53);
      _la = _input->LA(1);
      if (!(_la == StringInterpolatorParser::STRING_TEXT

      || _la == StringInterpolatorParser::STRING_ESCAPE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(58);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(59);
    match(StringInterpolatorParser::STRING_END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerContext ------------------------------------------------------------------

StringInterpolatorParser::IntegerContext::IntegerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::IntegerContext::INT() {
  return getToken(StringInterpolatorParser::INT, 0);
}


size_t StringInterpolatorParser::IntegerContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInteger;
}


std::any StringInterpolatorParser::IntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInteger(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::IntegerContext* StringInterpolatorParser::integer() {
  IntegerContext *_localctx = _tracker.createInstance<IntegerContext>(_ctx, getState());
  enterRule(_localctx, 4, StringInterpolatorParser::RuleInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(61);
    match(StringInterpolatorParser::INT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FloatContext ------------------------------------------------------------------

StringInterpolatorParser::FloatContext::FloatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::FloatContext::FLOAT() {
  return getToken(StringInterpolatorParser::FLOAT, 0);
}


size_t StringInterpolatorParser::FloatContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleFloat;
}


std::any StringInterpolatorParser::FloatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitFloat(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::FloatContext* StringInterpolatorParser::float_() {
  FloatContext *_localctx = _tracker.createInstance<FloatContext>(_ctx, getState());
  enterRule(_localctx, 6, StringInterpolatorParser::RuleFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(63);
    match(StringInterpolatorParser::FLOAT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

StringInterpolatorParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::StringContext* StringInterpolatorParser::LiteralContext::string() {
  return getRuleContext<StringInterpolatorParser::StringContext>(0);
}

StringInterpolatorParser::IntegerContext* StringInterpolatorParser::LiteralContext::integer() {
  return getRuleContext<StringInterpolatorParser::IntegerContext>(0);
}

StringInterpolatorParser::FloatContext* StringInterpolatorParser::LiteralContext::float_() {
  return getRuleContext<StringInterpolatorParser::FloatContext>(0);
}


size_t StringInterpolatorParser::LiteralContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleLiteral;
}


std::any StringInterpolatorParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::LiteralContext* StringInterpolatorParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 8, StringInterpolatorParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(68);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::STRING_START: {
        enterOuterAlt(_localctx, 1);
        setState(65);
        string();
        break;
      }

      case StringInterpolatorParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(66);
        integer();
        break;
      }

      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(67);
        float_();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentContext ------------------------------------------------------------------

StringInterpolatorParser::ArgumentContext::ArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::LiteralContext* StringInterpolatorParser::ArgumentContext::literal() {
  return getRuleContext<StringInterpolatorParser::LiteralContext>(0);
}

StringInterpolatorParser::FieldContext* StringInterpolatorParser::ArgumentContext::field() {
  return getRuleContext<StringInterpolatorParser::FieldContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::ArgumentContext::OPENP() {
  return getToken(StringInterpolatorParser::OPENP, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::ArgumentContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::ArgumentContext::CLOSEP() {
  return getToken(StringInterpolatorParser::CLOSEP, 0);
}


size_t StringInterpolatorParser::ArgumentContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleArgument;
}


std::any StringInterpolatorParser::ArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitArgument(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::ArgumentContext* StringInterpolatorParser::argument() {
  ArgumentContext *_localctx = _tracker.createInstance<ArgumentContext>(_ctx, getState());
  enterRule(_localctx, 10, StringInterpolatorParser::RuleArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(70);
        literal();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(71);
        field();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        enterOuterAlt(_localctx, 3);
        setState(72);
        match(StringInterpolatorParser::OPENP);
        setState(73);
        expr(0);
        setState(74);
        match(StringInterpolatorParser::CLOSEP);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Arg_listContext ------------------------------------------------------------------

StringInterpolatorParser::Arg_listContext::Arg_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<StringInterpolatorParser::ArgumentContext *> StringInterpolatorParser::Arg_listContext::argument() {
  return getRuleContexts<StringInterpolatorParser::ArgumentContext>();
}

StringInterpolatorParser::ArgumentContext* StringInterpolatorParser::Arg_listContext::argument(size_t i) {
  return getRuleContext<StringInterpolatorParser::ArgumentContext>(i);
}


size_t StringInterpolatorParser::Arg_listContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleArg_list;
}


std::any StringInterpolatorParser::Arg_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitArg_list(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Arg_listContext* StringInterpolatorParser::arg_list() {
  Arg_listContext *_localctx = _tracker.createInstance<Arg_listContext>(_ctx, getState());
  enterRule(_localctx, 12, StringInterpolatorParser::RuleArg_list);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(79);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(78);
      argument();
      break;
    }

    default:
      break;
    }
    setState(84);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(81);
        argument(); 
      }
      setState(86);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncContext ------------------------------------------------------------------

StringInterpolatorParser::FuncContext::FuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::FuncContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

StringInterpolatorParser::Arg_listContext* StringInterpolatorParser::FuncContext::arg_list() {
  return getRuleContext<StringInterpolatorParser::Arg_listContext>(0);
}


size_t StringInterpolatorParser::FuncContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleFunc;
}


std::any StringInterpolatorParser::FuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitFunc(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::FuncContext* StringInterpolatorParser::func() {
  FuncContext *_localctx = _tracker.createInstance<FuncContext>(_ctx, getState());
  enterRule(_localctx, 14, StringInterpolatorParser::RuleFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(StringInterpolatorParser::ID);
    setState(88);
    arg_list();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr_itemContext ------------------------------------------------------------------

StringInterpolatorParser::Expr_itemContext::Expr_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::LiteralContext* StringInterpolatorParser::Expr_itemContext::literal() {
  return getRuleContext<StringInterpolatorParser::LiteralContext>(0);
}

StringInterpolatorParser::FieldContext* StringInterpolatorParser::Expr_itemContext::field() {
  return getRuleContext<StringInterpolatorParser::FieldContext>(0);
}

StringInterpolatorParser::FuncContext* StringInterpolatorParser::Expr_itemContext::func() {
  return getRuleContext<StringInterpolatorParser::FuncContext>(0);
}


size_t StringInterpolatorParser::Expr_itemContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleExpr_item;
}


std::any StringInterpolatorParser::Expr_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitExpr_item(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Expr_itemContext* StringInterpolatorParser::expr_item() {
  Expr_itemContext *_localctx = _tracker.createInstance<Expr_itemContext>(_ctx, getState());
  enterRule(_localctx, 16, StringInterpolatorParser::RuleExpr_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(93);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(90);
        literal();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(91);
        field();
        break;
      }

      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(92);
        func();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

StringInterpolatorParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Expr_itemContext* StringInterpolatorParser::ExprContext::expr_item() {
  return getRuleContext<StringInterpolatorParser::Expr_itemContext>(0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::ExprContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::ExprContext::PIPE() {
  return getToken(StringInterpolatorParser::PIPE, 0);
}


size_t StringInterpolatorParser::ExprContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleExpr;
}


std::any StringInterpolatorParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


StringInterpolatorParser::ExprContext* StringInterpolatorParser::expr() {
   return expr(0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  StringInterpolatorParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  StringInterpolatorParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 18;
  enterRecursionRule(_localctx, 18, StringInterpolatorParser::RuleExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(96);
    expr_item();
    _ctx->stop = _input->LT(-1);
    setState(103);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleExpr);
        setState(98);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(99);
        match(StringInterpolatorParser::PIPE);
        setState(100);
        expr_item(); 
      }
      setState(105);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EvalContext ------------------------------------------------------------------

StringInterpolatorParser::EvalContext::EvalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::EvalContext::OPEN() {
  return getToken(StringInterpolatorParser::OPEN, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::EvalContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::EvalContext::CLOSE() {
  return getToken(StringInterpolatorParser::CLOSE, 0);
}


size_t StringInterpolatorParser::EvalContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleEval;
}


std::any StringInterpolatorParser::EvalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitEval(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::EvalContext* StringInterpolatorParser::eval() {
  EvalContext *_localctx = _tracker.createInstance<EvalContext>(_ctx, getState());
  enterRule(_localctx, 20, StringInterpolatorParser::RuleEval);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(106);
    match(StringInterpolatorParser::OPEN);
    setState(107);
    expr(0);
    setState(108);
    match(StringInterpolatorParser::CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Loop_startContext ------------------------------------------------------------------

StringInterpolatorParser::Loop_startContext::Loop_startContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Loop_startContext::OPEN() {
  return getToken(StringInterpolatorParser::OPEN, 0);
}

tree::TerminalNode* StringInterpolatorParser::Loop_startContext::HASH() {
  return getToken(StringInterpolatorParser::HASH, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Loop_startContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::Loop_startContext::CLOSE() {
  return getToken(StringInterpolatorParser::CLOSE, 0);
}


size_t StringInterpolatorParser::Loop_startContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleLoop_start;
}


std::any StringInterpolatorParser::Loop_startContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitLoop_start(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Loop_startContext* StringInterpolatorParser::loop_start() {
  Loop_startContext *_localctx = _tracker.createInstance<Loop_startContext>(_ctx, getState());
  enterRule(_localctx, 22, StringInterpolatorParser::RuleLoop_start);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(StringInterpolatorParser::OPEN);
    setState(111);
    match(StringInterpolatorParser::HASH);
    setState(112);
    expr(0);
    setState(113);
    match(StringInterpolatorParser::CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Loop_endContext ------------------------------------------------------------------

StringInterpolatorParser::Loop_endContext::Loop_endContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Loop_endContext::OPEN() {
  return getToken(StringInterpolatorParser::OPEN, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Loop_endContext::SLASH() {
  return getTokens(StringInterpolatorParser::SLASH);
}

tree::TerminalNode* StringInterpolatorParser::Loop_endContext::SLASH(size_t i) {
  return getToken(StringInterpolatorParser::SLASH, i);
}

tree::TerminalNode* StringInterpolatorParser::Loop_endContext::CLOSE() {
  return getToken(StringInterpolatorParser::CLOSE, 0);
}


size_t StringInterpolatorParser::Loop_endContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleLoop_end;
}


std::any StringInterpolatorParser::Loop_endContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitLoop_end(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Loop_endContext* StringInterpolatorParser::loop_end() {
  Loop_endContext *_localctx = _tracker.createInstance<Loop_endContext>(_ctx, getState());
  enterRule(_localctx, 24, StringInterpolatorParser::RuleLoop_end);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    match(StringInterpolatorParser::OPEN);
    setState(116);
    match(StringInterpolatorParser::SLASH);
    setState(117);
    match(StringInterpolatorParser::SLASH);
    setState(118);
    match(StringInterpolatorParser::CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoopContext ------------------------------------------------------------------

StringInterpolatorParser::LoopContext::LoopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Loop_startContext* StringInterpolatorParser::LoopContext::loop_start() {
  return getRuleContext<StringInterpolatorParser::Loop_startContext>(0);
}

StringInterpolatorParser::Interpolated_strContext* StringInterpolatorParser::LoopContext::interpolated_str() {
  return getRuleContext<StringInterpolatorParser::Interpolated_strContext>(0);
}

StringInterpolatorParser::Loop_endContext* StringInterpolatorParser::LoopContext::loop_end() {
  return getRuleContext<StringInterpolatorParser::Loop_endContext>(0);
}


size_t StringInterpolatorParser::LoopContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleLoop;
}


std::any StringInterpolatorParser::LoopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitLoop(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::LoopContext* StringInterpolatorParser::loop() {
  LoopContext *_localctx = _tracker.createInstance<LoopContext>(_ctx, getState());
  enterRule(_localctx, 26, StringInterpolatorParser::RuleLoop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(120);
    loop_start();
    setState(121);
    interpolated_str();
    setState(122);
    loop_end();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

StringInterpolatorParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::EvalContext* StringInterpolatorParser::StmtContext::eval() {
  return getRuleContext<StringInterpolatorParser::EvalContext>(0);
}

StringInterpolatorParser::LoopContext* StringInterpolatorParser::StmtContext::loop() {
  return getRuleContext<StringInterpolatorParser::LoopContext>(0);
}


size_t StringInterpolatorParser::StmtContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleStmt;
}


std::any StringInterpolatorParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::StmtContext* StringInterpolatorParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 28, StringInterpolatorParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(126);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(124);
      eval();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(125);
      loop();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NormalContext ------------------------------------------------------------------

StringInterpolatorParser::NormalContext::NormalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::NormalContext::NORMAL_TEXT() {
  return getTokens(StringInterpolatorParser::NORMAL_TEXT);
}

tree::TerminalNode* StringInterpolatorParser::NormalContext::NORMAL_TEXT(size_t i) {
  return getToken(StringInterpolatorParser::NORMAL_TEXT, i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::NormalContext::NORMAL_ESCAPE() {
  return getTokens(StringInterpolatorParser::NORMAL_ESCAPE);
}

tree::TerminalNode* StringInterpolatorParser::NormalContext::NORMAL_ESCAPE(size_t i) {
  return getToken(StringInterpolatorParser::NORMAL_ESCAPE, i);
}


size_t StringInterpolatorParser::NormalContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleNormal;
}


std::any StringInterpolatorParser::NormalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitNormal(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::NormalContext* StringInterpolatorParser::normal() {
  NormalContext *_localctx = _tracker.createInstance<NormalContext>(_ctx, getState());
  enterRule(_localctx, 30, StringInterpolatorParser::RuleNormal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(129); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(128);
              _la = _input->LA(1);
              if (!(_la == StringInterpolatorParser::NORMAL_TEXT

              || _la == StringInterpolatorParser::NORMAL_ESCAPE)) {
              _errHandler->recoverInline(this);
              }
              else {
                _errHandler->reportMatch(this);
                consume();
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(131); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interpolated_strContext ------------------------------------------------------------------

StringInterpolatorParser::Interpolated_strContext::Interpolated_strContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<StringInterpolatorParser::NormalContext *> StringInterpolatorParser::Interpolated_strContext::normal() {
  return getRuleContexts<StringInterpolatorParser::NormalContext>();
}

StringInterpolatorParser::NormalContext* StringInterpolatorParser::Interpolated_strContext::normal(size_t i) {
  return getRuleContext<StringInterpolatorParser::NormalContext>(i);
}

std::vector<StringInterpolatorParser::StmtContext *> StringInterpolatorParser::Interpolated_strContext::stmt() {
  return getRuleContexts<StringInterpolatorParser::StmtContext>();
}

StringInterpolatorParser::StmtContext* StringInterpolatorParser::Interpolated_strContext::stmt(size_t i) {
  return getRuleContext<StringInterpolatorParser::StmtContext>(i);
}


size_t StringInterpolatorParser::Interpolated_strContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInterpolated_str;
}


std::any StringInterpolatorParser::Interpolated_strContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInterpolated_str(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Interpolated_strContext* StringInterpolatorParser::interpolated_str() {
  Interpolated_strContext *_localctx = _tracker.createInstance<Interpolated_strContext>(_ctx, getState());
  enterRule(_localctx, 32, StringInterpolatorParser::RuleInterpolated_str);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(137);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(135);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case StringInterpolatorParser::NORMAL_TEXT:
          case StringInterpolatorParser::NORMAL_ESCAPE: {
            setState(133);
            normal();
            break;
          }

          case StringInterpolatorParser::OPEN: {
            setState(134);
            stmt();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(139);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expression_programContext ------------------------------------------------------------------

StringInterpolatorParser::Expression_programContext::Expression_programContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Expression_programContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::Expression_programContext::EOF() {
  return getToken(StringInterpolatorParser::EOF, 0);
}


size_t StringInterpolatorParser::Expression_programContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleExpression_program;
}


std::any StringInterpolatorParser::Expression_programContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitExpression_program(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Expression_programContext* StringInterpolatorParser::expression_program() {
  Expression_programContext *_localctx = _tracker.createInstance<Expression_programContext>(_ctx, getState());
  enterRule(_localctx, 34, StringInterpolatorParser::RuleExpression_program);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(140);
    expr(0);
    setState(141);
    match(StringInterpolatorParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgramContext ------------------------------------------------------------------

StringInterpolatorParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Interpolated_strContext* StringInterpolatorParser::ProgramContext::interpolated_str() {
  return getRuleContext<StringInterpolatorParser::Interpolated_strContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::ProgramContext::EOF() {
  return getToken(StringInterpolatorParser::EOF, 0);
}


size_t StringInterpolatorParser::ProgramContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleProgram;
}


std::any StringInterpolatorParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::ProgramContext* StringInterpolatorParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 36, StringInterpolatorParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(143);
    interpolated_str();
    setState(144);
    match(StringInterpolatorParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool StringInterpolatorParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 9: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool StringInterpolatorParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void StringInterpolatorParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  stringinterpolatorparserParserInitialize();
#else
  ::antlr4::internal::call_once(stringinterpolatorparserParserOnceFlag, stringinterpolatorparserParserInitialize);
#endif
}
