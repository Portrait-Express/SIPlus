
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
      "property_name", "property_index", "property_item", "property", "string", 
      "integer", "float", "boolean", "literal", "argument", "arg_list", 
      "func", "array_item", "array", "expr_item", "piped_expression", "expr", 
      "eval", "loop_start", "loop_end", "loop", "stmt", "normal", "interpolated_str", 
      "expression_program", "program"
    },
    std::vector<std::string>{
      "", "", "", "'{'", "'true'", "'false'", "'.'", "'#'", "'/'", "'}'", 
      "'('", "')'", "'['", "']'", "','", "'|'", "'\\'"
    },
    std::vector<std::string>{
      "", "NORMAL_TEXT", "NORMAL_ESCAPE", "OPEN", "TRUE", "FALSE", "DOT", 
      "HASH", "SLASH", "CLOSE", "OPENP", "CLOSEP", "OPENB", "CLOSEB", "COMMA", 
      "PIPE", "BACKSLASH", "STRING_START", "WS", "INT", "FLOAT", "ID", "ANY", 
      "STRING_TEXT", "STRING_ESCAPE", "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,25,193,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,1,0,1,0,1,0,1,1,1,1,1,1,1,
  	1,1,1,1,2,1,2,3,2,63,8,2,1,3,1,3,1,3,4,3,68,8,3,11,3,12,3,69,1,3,1,3,
  	3,3,74,8,3,1,4,1,4,5,4,78,8,4,10,4,12,4,81,9,4,1,4,1,4,1,5,1,5,1,6,1,
  	6,1,7,1,7,1,8,1,8,1,8,1,8,3,8,95,8,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,
  	104,8,9,1,10,3,10,107,8,10,1,10,5,10,110,8,10,10,10,12,10,113,9,10,1,
  	11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,3,12,123,8,12,1,13,1,13,1,13,1,
  	13,5,13,129,8,13,10,13,12,13,132,9,13,1,13,3,13,135,8,13,1,13,1,13,1,
  	14,1,14,1,14,1,14,3,14,143,8,14,1,15,1,15,1,15,1,15,1,16,1,16,3,16,151,
  	8,16,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,
  	1,19,1,20,1,20,1,20,1,20,1,21,1,21,3,21,173,8,21,1,22,4,22,176,8,22,11,
  	22,12,22,177,1,23,1,23,5,23,182,8,23,10,23,12,23,185,9,23,1,24,1,24,1,
  	24,1,25,1,25,1,25,1,25,0,0,26,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,
  	30,32,34,36,38,40,42,44,46,48,50,0,3,1,0,23,24,1,0,4,5,1,0,1,2,189,0,
  	52,1,0,0,0,2,55,1,0,0,0,4,62,1,0,0,0,6,73,1,0,0,0,8,75,1,0,0,0,10,84,
  	1,0,0,0,12,86,1,0,0,0,14,88,1,0,0,0,16,94,1,0,0,0,18,103,1,0,0,0,20,106,
  	1,0,0,0,22,114,1,0,0,0,24,122,1,0,0,0,26,124,1,0,0,0,28,142,1,0,0,0,30,
  	144,1,0,0,0,32,150,1,0,0,0,34,152,1,0,0,0,36,156,1,0,0,0,38,161,1,0,0,
  	0,40,166,1,0,0,0,42,172,1,0,0,0,44,175,1,0,0,0,46,183,1,0,0,0,48,186,
  	1,0,0,0,50,189,1,0,0,0,52,53,5,6,0,0,53,54,5,21,0,0,54,1,1,0,0,0,55,56,
  	5,6,0,0,56,57,5,12,0,0,57,58,5,19,0,0,58,59,5,13,0,0,59,3,1,0,0,0,60,
  	63,3,0,0,0,61,63,3,2,1,0,62,60,1,0,0,0,62,61,1,0,0,0,63,5,1,0,0,0,64,
  	65,6,3,-1,0,65,74,5,6,0,0,66,68,3,4,2,0,67,66,1,0,0,0,68,69,1,0,0,0,69,
  	67,1,0,0,0,69,70,1,0,0,0,70,71,1,0,0,0,71,72,6,3,-1,0,72,74,1,0,0,0,73,
  	64,1,0,0,0,73,67,1,0,0,0,74,7,1,0,0,0,75,79,5,17,0,0,76,78,7,0,0,0,77,
  	76,1,0,0,0,78,81,1,0,0,0,79,77,1,0,0,0,79,80,1,0,0,0,80,82,1,0,0,0,81,
  	79,1,0,0,0,82,83,5,25,0,0,83,9,1,0,0,0,84,85,5,19,0,0,85,11,1,0,0,0,86,
  	87,5,20,0,0,87,13,1,0,0,0,88,89,7,1,0,0,89,15,1,0,0,0,90,95,3,8,4,0,91,
  	95,3,10,5,0,92,95,3,12,6,0,93,95,3,14,7,0,94,90,1,0,0,0,94,91,1,0,0,0,
  	94,92,1,0,0,0,94,93,1,0,0,0,95,17,1,0,0,0,96,104,3,16,8,0,97,104,3,6,
  	3,0,98,104,3,26,13,0,99,100,5,10,0,0,100,101,3,30,15,0,101,102,5,11,0,
  	0,102,104,1,0,0,0,103,96,1,0,0,0,103,97,1,0,0,0,103,98,1,0,0,0,103,99,
  	1,0,0,0,104,19,1,0,0,0,105,107,3,18,9,0,106,105,1,0,0,0,106,107,1,0,0,
  	0,107,111,1,0,0,0,108,110,3,18,9,0,109,108,1,0,0,0,110,113,1,0,0,0,111,
  	109,1,0,0,0,111,112,1,0,0,0,112,21,1,0,0,0,113,111,1,0,0,0,114,115,5,
  	21,0,0,115,116,3,20,10,0,116,23,1,0,0,0,117,123,3,32,16,0,118,119,5,10,
  	0,0,119,120,3,32,16,0,120,121,5,11,0,0,121,123,1,0,0,0,122,117,1,0,0,
  	0,122,118,1,0,0,0,123,25,1,0,0,0,124,130,5,12,0,0,125,126,3,24,12,0,126,
  	127,5,14,0,0,127,129,1,0,0,0,128,125,1,0,0,0,129,132,1,0,0,0,130,128,
  	1,0,0,0,130,131,1,0,0,0,131,134,1,0,0,0,132,130,1,0,0,0,133,135,3,24,
  	12,0,134,133,1,0,0,0,134,135,1,0,0,0,135,136,1,0,0,0,136,137,5,13,0,0,
  	137,27,1,0,0,0,138,143,3,16,8,0,139,143,3,6,3,0,140,143,3,22,11,0,141,
  	143,3,26,13,0,142,138,1,0,0,0,142,139,1,0,0,0,142,140,1,0,0,0,142,141,
  	1,0,0,0,143,29,1,0,0,0,144,145,3,28,14,0,145,146,5,15,0,0,146,147,3,32,
  	16,0,147,31,1,0,0,0,148,151,3,28,14,0,149,151,3,30,15,0,150,148,1,0,0,
  	0,150,149,1,0,0,0,151,33,1,0,0,0,152,153,5,3,0,0,153,154,3,32,16,0,154,
  	155,5,9,0,0,155,35,1,0,0,0,156,157,5,3,0,0,157,158,5,7,0,0,158,159,3,
  	32,16,0,159,160,5,9,0,0,160,37,1,0,0,0,161,162,5,3,0,0,162,163,5,8,0,
  	0,163,164,5,8,0,0,164,165,5,9,0,0,165,39,1,0,0,0,166,167,3,36,18,0,167,
  	168,3,46,23,0,168,169,3,38,19,0,169,41,1,0,0,0,170,173,3,34,17,0,171,
  	173,3,40,20,0,172,170,1,0,0,0,172,171,1,0,0,0,173,43,1,0,0,0,174,176,
  	7,2,0,0,175,174,1,0,0,0,176,177,1,0,0,0,177,175,1,0,0,0,177,178,1,0,0,
  	0,178,45,1,0,0,0,179,182,3,44,22,0,180,182,3,42,21,0,181,179,1,0,0,0,
  	181,180,1,0,0,0,182,185,1,0,0,0,183,181,1,0,0,0,183,184,1,0,0,0,184,47,
  	1,0,0,0,185,183,1,0,0,0,186,187,3,32,16,0,187,188,5,0,0,1,188,49,1,0,
  	0,0,189,190,3,46,23,0,190,191,5,0,0,1,191,51,1,0,0,0,17,62,69,73,79,94,
  	103,106,111,122,130,134,142,150,172,177,181,183
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


//----------------- Property_nameContext ------------------------------------------------------------------

StringInterpolatorParser::Property_nameContext::Property_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Property_nameContext::DOT() {
  return getToken(StringInterpolatorParser::DOT, 0);
}

tree::TerminalNode* StringInterpolatorParser::Property_nameContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}


size_t StringInterpolatorParser::Property_nameContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleProperty_name;
}


std::any StringInterpolatorParser::Property_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitProperty_name(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Property_nameContext* StringInterpolatorParser::property_name() {
  Property_nameContext *_localctx = _tracker.createInstance<Property_nameContext>(_ctx, getState());
  enterRule(_localctx, 0, StringInterpolatorParser::RuleProperty_name);

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
    match(StringInterpolatorParser::DOT);
    setState(53);
    match(StringInterpolatorParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_indexContext ------------------------------------------------------------------

StringInterpolatorParser::Property_indexContext::Property_indexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Property_indexContext::DOT() {
  return getToken(StringInterpolatorParser::DOT, 0);
}

tree::TerminalNode* StringInterpolatorParser::Property_indexContext::OPENB() {
  return getToken(StringInterpolatorParser::OPENB, 0);
}

tree::TerminalNode* StringInterpolatorParser::Property_indexContext::INT() {
  return getToken(StringInterpolatorParser::INT, 0);
}

tree::TerminalNode* StringInterpolatorParser::Property_indexContext::CLOSEB() {
  return getToken(StringInterpolatorParser::CLOSEB, 0);
}


size_t StringInterpolatorParser::Property_indexContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleProperty_index;
}


std::any StringInterpolatorParser::Property_indexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitProperty_index(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Property_indexContext* StringInterpolatorParser::property_index() {
  Property_indexContext *_localctx = _tracker.createInstance<Property_indexContext>(_ctx, getState());
  enterRule(_localctx, 2, StringInterpolatorParser::RuleProperty_index);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(55);
    match(StringInterpolatorParser::DOT);
    setState(56);
    match(StringInterpolatorParser::OPENB);
    setState(57);
    match(StringInterpolatorParser::INT);
    setState(58);
    match(StringInterpolatorParser::CLOSEB);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_itemContext ------------------------------------------------------------------

StringInterpolatorParser::Property_itemContext::Property_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Property_nameContext* StringInterpolatorParser::Property_itemContext::property_name() {
  return getRuleContext<StringInterpolatorParser::Property_nameContext>(0);
}

StringInterpolatorParser::Property_indexContext* StringInterpolatorParser::Property_itemContext::property_index() {
  return getRuleContext<StringInterpolatorParser::Property_indexContext>(0);
}


size_t StringInterpolatorParser::Property_itemContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleProperty_item;
}


std::any StringInterpolatorParser::Property_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitProperty_item(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Property_itemContext* StringInterpolatorParser::property_item() {
  Property_itemContext *_localctx = _tracker.createInstance<Property_itemContext>(_ctx, getState());
  enterRule(_localctx, 4, StringInterpolatorParser::RuleProperty_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(62);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(60);
      property_name();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(61);
      property_index();
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

//----------------- PropertyContext ------------------------------------------------------------------

StringInterpolatorParser::PropertyContext::PropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::PropertyContext::DOT() {
  return getToken(StringInterpolatorParser::DOT, 0);
}

std::vector<StringInterpolatorParser::Property_itemContext *> StringInterpolatorParser::PropertyContext::property_item() {
  return getRuleContexts<StringInterpolatorParser::Property_itemContext>();
}

StringInterpolatorParser::Property_itemContext* StringInterpolatorParser::PropertyContext::property_item(size_t i) {
  return getRuleContext<StringInterpolatorParser::Property_itemContext>(i);
}


size_t StringInterpolatorParser::PropertyContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleProperty;
}


std::any StringInterpolatorParser::PropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitProperty(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::PropertyContext* StringInterpolatorParser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 6, StringInterpolatorParser::RuleProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(73);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      enableChannel(antlr4::Token::HIDDEN_CHANNEL);
      setState(65);
      match(StringInterpolatorParser::DOT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(67); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(66);
                property_item();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(69); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      disableChannel(antlr4::Token::HIDDEN_CHANNEL);
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
  enterRule(_localctx, 8, StringInterpolatorParser::RuleString);
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
    setState(75);
    match(StringInterpolatorParser::STRING_START);
    setState(79);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::STRING_TEXT

    || _la == StringInterpolatorParser::STRING_ESCAPE) {
      setState(76);
      _la = _input->LA(1);
      if (!(_la == StringInterpolatorParser::STRING_TEXT

      || _la == StringInterpolatorParser::STRING_ESCAPE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(81);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(82);
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
  enterRule(_localctx, 10, StringInterpolatorParser::RuleInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
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
  enterRule(_localctx, 12, StringInterpolatorParser::RuleFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(StringInterpolatorParser::FLOAT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanContext ------------------------------------------------------------------

StringInterpolatorParser::BooleanContext::BooleanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::BooleanContext::TRUE() {
  return getToken(StringInterpolatorParser::TRUE, 0);
}

tree::TerminalNode* StringInterpolatorParser::BooleanContext::FALSE() {
  return getToken(StringInterpolatorParser::FALSE, 0);
}


size_t StringInterpolatorParser::BooleanContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleBoolean;
}


std::any StringInterpolatorParser::BooleanContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitBoolean(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::BooleanContext* StringInterpolatorParser::boolean() {
  BooleanContext *_localctx = _tracker.createInstance<BooleanContext>(_ctx, getState());
  enterRule(_localctx, 14, StringInterpolatorParser::RuleBoolean);
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
    setState(88);
    _la = _input->LA(1);
    if (!(_la == StringInterpolatorParser::TRUE

    || _la == StringInterpolatorParser::FALSE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
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

StringInterpolatorParser::BooleanContext* StringInterpolatorParser::LiteralContext::boolean() {
  return getRuleContext<StringInterpolatorParser::BooleanContext>(0);
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
  enterRule(_localctx, 16, StringInterpolatorParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(94);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::STRING_START: {
        enterOuterAlt(_localctx, 1);
        setState(90);
        string();
        break;
      }

      case StringInterpolatorParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(91);
        integer();
        break;
      }

      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(92);
        float_();
        break;
      }

      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE: {
        enterOuterAlt(_localctx, 4);
        setState(93);
        boolean();
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

StringInterpolatorParser::PropertyContext* StringInterpolatorParser::ArgumentContext::property() {
  return getRuleContext<StringInterpolatorParser::PropertyContext>(0);
}

StringInterpolatorParser::ArrayContext* StringInterpolatorParser::ArgumentContext::array() {
  return getRuleContext<StringInterpolatorParser::ArrayContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::ArgumentContext::OPENP() {
  return getToken(StringInterpolatorParser::OPENP, 0);
}

StringInterpolatorParser::Piped_expressionContext* StringInterpolatorParser::ArgumentContext::piped_expression() {
  return getRuleContext<StringInterpolatorParser::Piped_expressionContext>(0);
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
  enterRule(_localctx, 18, StringInterpolatorParser::RuleArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(103);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(96);
        literal();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(97);
        property();
        break;
      }

      case StringInterpolatorParser::OPENB: {
        enterOuterAlt(_localctx, 3);
        setState(98);
        array();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        enterOuterAlt(_localctx, 4);
        setState(99);
        match(StringInterpolatorParser::OPENP);
        setState(100);
        piped_expression();
        setState(101);
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
  enterRule(_localctx, 20, StringInterpolatorParser::RuleArg_list);
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
    setState(106);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(105);
      argument();
      break;
    }

    default:
      break;
    }
    setState(111);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1709168) != 0)) {
      setState(108);
      argument();
      setState(113);
      _errHandler->sync(this);
      _la = _input->LA(1);
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
  enterRule(_localctx, 22, StringInterpolatorParser::RuleFunc);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(StringInterpolatorParser::ID);
    setState(115);
    arg_list();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Array_itemContext ------------------------------------------------------------------

StringInterpolatorParser::Array_itemContext::Array_itemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Array_itemContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::Array_itemContext::OPENP() {
  return getToken(StringInterpolatorParser::OPENP, 0);
}

tree::TerminalNode* StringInterpolatorParser::Array_itemContext::CLOSEP() {
  return getToken(StringInterpolatorParser::CLOSEP, 0);
}


size_t StringInterpolatorParser::Array_itemContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleArray_item;
}


std::any StringInterpolatorParser::Array_itemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitArray_item(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Array_itemContext* StringInterpolatorParser::array_item() {
  Array_itemContext *_localctx = _tracker.createInstance<Array_itemContext>(_ctx, getState());
  enterRule(_localctx, 24, StringInterpolatorParser::RuleArray_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(122);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::DOT:
      case StringInterpolatorParser::OPENB:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT:
      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(117);
        expr();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        enterOuterAlt(_localctx, 2);
        setState(118);
        match(StringInterpolatorParser::OPENP);
        setState(119);
        expr();
        setState(120);
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

//----------------- ArrayContext ------------------------------------------------------------------

StringInterpolatorParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::ArrayContext::OPENB() {
  return getToken(StringInterpolatorParser::OPENB, 0);
}

tree::TerminalNode* StringInterpolatorParser::ArrayContext::CLOSEB() {
  return getToken(StringInterpolatorParser::CLOSEB, 0);
}

std::vector<StringInterpolatorParser::Array_itemContext *> StringInterpolatorParser::ArrayContext::array_item() {
  return getRuleContexts<StringInterpolatorParser::Array_itemContext>();
}

StringInterpolatorParser::Array_itemContext* StringInterpolatorParser::ArrayContext::array_item(size_t i) {
  return getRuleContext<StringInterpolatorParser::Array_itemContext>(i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::ArrayContext::COMMA() {
  return getTokens(StringInterpolatorParser::COMMA);
}

tree::TerminalNode* StringInterpolatorParser::ArrayContext::COMMA(size_t i) {
  return getToken(StringInterpolatorParser::COMMA, i);
}


size_t StringInterpolatorParser::ArrayContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleArray;
}


std::any StringInterpolatorParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::ArrayContext* StringInterpolatorParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 26, StringInterpolatorParser::RuleArray);
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
    setState(124);
    match(StringInterpolatorParser::OPENB);
    setState(130);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(125);
        array_item();
        setState(126);
        match(StringInterpolatorParser::COMMA); 
      }
      setState(132);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
    setState(134);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3806320) != 0)) {
      setState(133);
      array_item();
    }
    setState(136);
    match(StringInterpolatorParser::CLOSEB);
   
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

StringInterpolatorParser::PropertyContext* StringInterpolatorParser::Expr_itemContext::property() {
  return getRuleContext<StringInterpolatorParser::PropertyContext>(0);
}

StringInterpolatorParser::FuncContext* StringInterpolatorParser::Expr_itemContext::func() {
  return getRuleContext<StringInterpolatorParser::FuncContext>(0);
}

StringInterpolatorParser::ArrayContext* StringInterpolatorParser::Expr_itemContext::array() {
  return getRuleContext<StringInterpolatorParser::ArrayContext>(0);
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
  enterRule(_localctx, 28, StringInterpolatorParser::RuleExpr_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(142);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(138);
        literal();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(139);
        property();
        break;
      }

      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(140);
        func();
        break;
      }

      case StringInterpolatorParser::OPENB: {
        enterOuterAlt(_localctx, 4);
        setState(141);
        array();
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

//----------------- Piped_expressionContext ------------------------------------------------------------------

StringInterpolatorParser::Piped_expressionContext::Piped_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Expr_itemContext* StringInterpolatorParser::Piped_expressionContext::expr_item() {
  return getRuleContext<StringInterpolatorParser::Expr_itemContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::Piped_expressionContext::PIPE() {
  return getToken(StringInterpolatorParser::PIPE, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Piped_expressionContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}


size_t StringInterpolatorParser::Piped_expressionContext::getRuleIndex() const {
  return StringInterpolatorParser::RulePiped_expression;
}


std::any StringInterpolatorParser::Piped_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitPiped_expression(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Piped_expressionContext* StringInterpolatorParser::piped_expression() {
  Piped_expressionContext *_localctx = _tracker.createInstance<Piped_expressionContext>(_ctx, getState());
  enterRule(_localctx, 30, StringInterpolatorParser::RulePiped_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(144);
    expr_item();
    setState(145);
    match(StringInterpolatorParser::PIPE);
    setState(146);
    expr();
   
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

StringInterpolatorParser::Piped_expressionContext* StringInterpolatorParser::ExprContext::piped_expression() {
  return getRuleContext<StringInterpolatorParser::Piped_expressionContext>(0);
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
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 32, StringInterpolatorParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(150);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(148);
      expr_item();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(149);
      piped_expression();
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
  enterRule(_localctx, 34, StringInterpolatorParser::RuleEval);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(152);
    match(StringInterpolatorParser::OPEN);
    setState(153);
    expr();
    setState(154);
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
  enterRule(_localctx, 36, StringInterpolatorParser::RuleLoop_start);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(156);
    match(StringInterpolatorParser::OPEN);
    setState(157);
    match(StringInterpolatorParser::HASH);
    setState(158);
    expr();
    setState(159);
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
  enterRule(_localctx, 38, StringInterpolatorParser::RuleLoop_end);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(StringInterpolatorParser::OPEN);
    setState(162);
    match(StringInterpolatorParser::SLASH);
    setState(163);
    match(StringInterpolatorParser::SLASH);
    setState(164);
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
  enterRule(_localctx, 40, StringInterpolatorParser::RuleLoop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    loop_start();
    setState(167);
    interpolated_str();
    setState(168);
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
  enterRule(_localctx, 42, StringInterpolatorParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(172);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(170);
      eval();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(171);
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
  enterRule(_localctx, 44, StringInterpolatorParser::RuleNormal);
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
    setState(175); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(174);
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
      setState(177); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
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
  enterRule(_localctx, 46, StringInterpolatorParser::RuleInterpolated_str);

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
    setState(183);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(181);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case StringInterpolatorParser::NORMAL_TEXT:
          case StringInterpolatorParser::NORMAL_ESCAPE: {
            setState(179);
            normal();
            break;
          }

          case StringInterpolatorParser::OPEN: {
            setState(180);
            stmt();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(185);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
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
  enterRule(_localctx, 48, StringInterpolatorParser::RuleExpression_program);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    expr();
    setState(187);
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
  enterRule(_localctx, 50, StringInterpolatorParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    interpolated_str();
    setState(190);
    match(StringInterpolatorParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void StringInterpolatorParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  stringinterpolatorparserParserInitialize();
#else
  ::antlr4::internal::call_once(stringinterpolatorparserParserOnceFlag, stringinterpolatorparserParserInitialize);
#endif
}
