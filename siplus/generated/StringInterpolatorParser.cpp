
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
  	4,1,25,292,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,1,0,1,0,1,0,1,1,1,1,1,1,1,
  	1,1,1,1,2,1,2,3,2,63,8,2,1,3,1,3,4,3,67,8,3,11,3,12,3,68,3,3,71,8,3,1,
  	4,1,4,5,4,75,8,4,10,4,12,4,78,9,4,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,1,8,
  	1,8,1,8,1,8,3,8,92,8,8,1,9,1,9,1,9,5,9,97,8,9,10,9,12,9,100,9,9,1,9,1,
  	9,3,9,104,8,9,1,9,5,9,107,8,9,10,9,12,9,110,9,9,1,9,1,9,3,9,114,8,9,1,
  	10,3,10,117,8,10,1,10,4,10,120,8,10,11,10,12,10,121,1,10,5,10,125,8,10,
  	10,10,12,10,128,9,10,1,11,1,11,4,11,132,8,11,11,11,12,11,133,1,11,3,11,
  	137,8,11,1,12,5,12,140,8,12,10,12,12,12,143,9,12,1,12,1,12,1,12,5,12,
  	148,8,12,10,12,12,12,151,9,12,1,12,1,12,5,12,155,8,12,10,12,12,12,158,
  	9,12,1,12,1,12,3,12,162,8,12,1,12,5,12,165,8,12,10,12,12,12,168,9,12,
  	1,13,1,13,1,13,1,13,5,13,174,8,13,10,13,12,13,177,9,13,1,13,3,13,180,
  	8,13,1,13,1,13,1,14,1,14,1,14,1,14,3,14,188,8,14,1,15,1,15,5,15,192,8,
  	15,10,15,12,15,195,9,15,1,15,1,15,5,15,199,8,15,10,15,12,15,202,9,15,
  	1,15,1,15,1,16,1,16,3,16,208,8,16,1,17,1,17,5,17,212,8,17,10,17,12,17,
  	215,9,17,1,17,1,17,5,17,219,8,17,10,17,12,17,222,9,17,1,17,1,17,1,18,
  	1,18,1,18,5,18,229,8,18,10,18,12,18,232,9,18,1,18,1,18,5,18,236,8,18,
  	10,18,12,18,239,9,18,1,18,1,18,1,19,1,19,1,19,1,19,5,19,247,8,19,10,19,
  	12,19,250,9,19,1,19,1,19,1,20,1,20,1,20,1,20,1,21,1,21,3,21,260,8,21,
  	1,22,4,22,263,8,22,11,22,12,22,264,1,23,1,23,5,23,269,8,23,10,23,12,23,
  	272,9,23,1,24,5,24,275,8,24,10,24,12,24,278,9,24,1,24,1,24,5,24,282,8,
  	24,10,24,12,24,285,9,24,1,24,1,24,1,25,1,25,1,25,1,25,0,0,26,0,2,4,6,
  	8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,0,3,
  	1,0,23,24,1,0,4,5,1,0,1,2,305,0,52,1,0,0,0,2,55,1,0,0,0,4,62,1,0,0,0,
  	6,70,1,0,0,0,8,72,1,0,0,0,10,81,1,0,0,0,12,83,1,0,0,0,14,85,1,0,0,0,16,
  	91,1,0,0,0,18,113,1,0,0,0,20,116,1,0,0,0,22,129,1,0,0,0,24,141,1,0,0,
  	0,26,169,1,0,0,0,28,187,1,0,0,0,30,189,1,0,0,0,32,207,1,0,0,0,34,209,
  	1,0,0,0,36,225,1,0,0,0,38,242,1,0,0,0,40,253,1,0,0,0,42,259,1,0,0,0,44,
  	262,1,0,0,0,46,270,1,0,0,0,48,276,1,0,0,0,50,288,1,0,0,0,52,53,5,6,0,
  	0,53,54,5,21,0,0,54,1,1,0,0,0,55,56,5,6,0,0,56,57,5,12,0,0,57,58,5,19,
  	0,0,58,59,5,13,0,0,59,3,1,0,0,0,60,63,3,0,0,0,61,63,3,2,1,0,62,60,1,0,
  	0,0,62,61,1,0,0,0,63,5,1,0,0,0,64,71,5,6,0,0,65,67,3,4,2,0,66,65,1,0,
  	0,0,67,68,1,0,0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,71,1,0,0,0,70,64,1,0,
  	0,0,70,66,1,0,0,0,71,7,1,0,0,0,72,76,5,17,0,0,73,75,7,0,0,0,74,73,1,0,
  	0,0,75,78,1,0,0,0,76,74,1,0,0,0,76,77,1,0,0,0,77,79,1,0,0,0,78,76,1,0,
  	0,0,79,80,5,25,0,0,80,9,1,0,0,0,81,82,5,19,0,0,82,11,1,0,0,0,83,84,5,
  	20,0,0,84,13,1,0,0,0,85,86,7,1,0,0,86,15,1,0,0,0,87,92,3,8,4,0,88,92,
  	3,10,5,0,89,92,3,12,6,0,90,92,3,14,7,0,91,87,1,0,0,0,91,88,1,0,0,0,91,
  	89,1,0,0,0,91,90,1,0,0,0,92,17,1,0,0,0,93,114,3,28,14,0,94,98,5,10,0,
  	0,95,97,5,18,0,0,96,95,1,0,0,0,97,100,1,0,0,0,98,96,1,0,0,0,98,99,1,0,
  	0,0,99,103,1,0,0,0,100,98,1,0,0,0,101,104,3,28,14,0,102,104,3,30,15,0,
  	103,101,1,0,0,0,103,102,1,0,0,0,104,108,1,0,0,0,105,107,5,18,0,0,106,
  	105,1,0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,108,109,1,0,0,0,109,111,1,
  	0,0,0,110,108,1,0,0,0,111,112,5,11,0,0,112,114,1,0,0,0,113,93,1,0,0,0,
  	113,94,1,0,0,0,114,19,1,0,0,0,115,117,3,18,9,0,116,115,1,0,0,0,116,117,
  	1,0,0,0,117,126,1,0,0,0,118,120,5,18,0,0,119,118,1,0,0,0,120,121,1,0,
  	0,0,121,119,1,0,0,0,121,122,1,0,0,0,122,123,1,0,0,0,123,125,3,18,9,0,
  	124,119,1,0,0,0,125,128,1,0,0,0,126,124,1,0,0,0,126,127,1,0,0,0,127,21,
  	1,0,0,0,128,126,1,0,0,0,129,136,5,21,0,0,130,132,5,18,0,0,131,130,1,0,
  	0,0,132,133,1,0,0,0,133,131,1,0,0,0,133,134,1,0,0,0,134,135,1,0,0,0,135,
  	137,3,20,10,0,136,131,1,0,0,0,136,137,1,0,0,0,137,23,1,0,0,0,138,140,
  	5,18,0,0,139,138,1,0,0,0,140,143,1,0,0,0,141,139,1,0,0,0,141,142,1,0,
  	0,0,142,161,1,0,0,0,143,141,1,0,0,0,144,162,3,32,16,0,145,149,5,10,0,
  	0,146,148,5,18,0,0,147,146,1,0,0,0,148,151,1,0,0,0,149,147,1,0,0,0,149,
  	150,1,0,0,0,150,152,1,0,0,0,151,149,1,0,0,0,152,156,3,32,16,0,153,155,
  	5,18,0,0,154,153,1,0,0,0,155,158,1,0,0,0,156,154,1,0,0,0,156,157,1,0,
  	0,0,157,159,1,0,0,0,158,156,1,0,0,0,159,160,5,11,0,0,160,162,1,0,0,0,
  	161,144,1,0,0,0,161,145,1,0,0,0,162,166,1,0,0,0,163,165,5,18,0,0,164,
  	163,1,0,0,0,165,168,1,0,0,0,166,164,1,0,0,0,166,167,1,0,0,0,167,25,1,
  	0,0,0,168,166,1,0,0,0,169,175,5,12,0,0,170,171,3,24,12,0,171,172,5,14,
  	0,0,172,174,1,0,0,0,173,170,1,0,0,0,174,177,1,0,0,0,175,173,1,0,0,0,175,
  	176,1,0,0,0,176,179,1,0,0,0,177,175,1,0,0,0,178,180,3,24,12,0,179,178,
  	1,0,0,0,179,180,1,0,0,0,180,181,1,0,0,0,181,182,5,13,0,0,182,27,1,0,0,
  	0,183,188,3,16,8,0,184,188,3,6,3,0,185,188,3,22,11,0,186,188,3,26,13,
  	0,187,183,1,0,0,0,187,184,1,0,0,0,187,185,1,0,0,0,187,186,1,0,0,0,188,
  	29,1,0,0,0,189,193,3,28,14,0,190,192,5,18,0,0,191,190,1,0,0,0,192,195,
  	1,0,0,0,193,191,1,0,0,0,193,194,1,0,0,0,194,196,1,0,0,0,195,193,1,0,0,
  	0,196,200,5,15,0,0,197,199,5,18,0,0,198,197,1,0,0,0,199,202,1,0,0,0,200,
  	198,1,0,0,0,200,201,1,0,0,0,201,203,1,0,0,0,202,200,1,0,0,0,203,204,3,
  	32,16,0,204,31,1,0,0,0,205,208,3,28,14,0,206,208,3,30,15,0,207,205,1,
  	0,0,0,207,206,1,0,0,0,208,33,1,0,0,0,209,213,5,3,0,0,210,212,5,18,0,0,
  	211,210,1,0,0,0,212,215,1,0,0,0,213,211,1,0,0,0,213,214,1,0,0,0,214,216,
  	1,0,0,0,215,213,1,0,0,0,216,220,3,32,16,0,217,219,5,18,0,0,218,217,1,
  	0,0,0,219,222,1,0,0,0,220,218,1,0,0,0,220,221,1,0,0,0,221,223,1,0,0,0,
  	222,220,1,0,0,0,223,224,5,9,0,0,224,35,1,0,0,0,225,226,5,3,0,0,226,230,
  	5,7,0,0,227,229,5,18,0,0,228,227,1,0,0,0,229,232,1,0,0,0,230,228,1,0,
  	0,0,230,231,1,0,0,0,231,233,1,0,0,0,232,230,1,0,0,0,233,237,3,32,16,0,
  	234,236,5,18,0,0,235,234,1,0,0,0,236,239,1,0,0,0,237,235,1,0,0,0,237,
  	238,1,0,0,0,238,240,1,0,0,0,239,237,1,0,0,0,240,241,5,9,0,0,241,37,1,
  	0,0,0,242,243,5,3,0,0,243,244,5,8,0,0,244,248,5,8,0,0,245,247,5,18,0,
  	0,246,245,1,0,0,0,247,250,1,0,0,0,248,246,1,0,0,0,248,249,1,0,0,0,249,
  	251,1,0,0,0,250,248,1,0,0,0,251,252,5,9,0,0,252,39,1,0,0,0,253,254,3,
  	36,18,0,254,255,3,46,23,0,255,256,3,38,19,0,256,41,1,0,0,0,257,260,3,
  	34,17,0,258,260,3,40,20,0,259,257,1,0,0,0,259,258,1,0,0,0,260,43,1,0,
  	0,0,261,263,7,2,0,0,262,261,1,0,0,0,263,264,1,0,0,0,264,262,1,0,0,0,264,
  	265,1,0,0,0,265,45,1,0,0,0,266,269,3,44,22,0,267,269,3,42,21,0,268,266,
  	1,0,0,0,268,267,1,0,0,0,269,272,1,0,0,0,270,268,1,0,0,0,270,271,1,0,0,
  	0,271,47,1,0,0,0,272,270,1,0,0,0,273,275,5,18,0,0,274,273,1,0,0,0,275,
  	278,1,0,0,0,276,274,1,0,0,0,276,277,1,0,0,0,277,279,1,0,0,0,278,276,1,
  	0,0,0,279,283,3,32,16,0,280,282,5,18,0,0,281,280,1,0,0,0,282,285,1,0,
  	0,0,283,281,1,0,0,0,283,284,1,0,0,0,284,286,1,0,0,0,285,283,1,0,0,0,286,
  	287,5,0,0,1,287,49,1,0,0,0,288,289,3,46,23,0,289,290,5,0,0,1,290,51,1,
  	0,0,0,36,62,68,70,76,91,98,103,108,113,116,121,126,133,136,141,149,156,
  	161,166,175,179,187,193,200,207,213,220,230,237,248,259,264,268,270,276,
  	283
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

StringInterpolatorParser::StringInterpolatorParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
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
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(70);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(64);
      match(StringInterpolatorParser::DOT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(66); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(65);
        property_item();
        setState(68); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == StringInterpolatorParser::DOT);
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
    setState(72);
    match(StringInterpolatorParser::STRING_START);
    setState(76);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::STRING_TEXT

    || _la == StringInterpolatorParser::STRING_ESCAPE) {
      setState(73);
      _la = _input->LA(1);
      if (!(_la == StringInterpolatorParser::STRING_TEXT

      || _la == StringInterpolatorParser::STRING_ESCAPE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(78);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(79);
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
    setState(81);
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
    setState(83);
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
    setState(85);
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
    setState(91);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::STRING_START: {
        enterOuterAlt(_localctx, 1);
        setState(87);
        string();
        break;
      }

      case StringInterpolatorParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(88);
        integer();
        break;
      }

      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(89);
        float_();
        break;
      }

      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE: {
        enterOuterAlt(_localctx, 4);
        setState(90);
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

StringInterpolatorParser::Expr_itemContext* StringInterpolatorParser::ArgumentContext::expr_item() {
  return getRuleContext<StringInterpolatorParser::Expr_itemContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::ArgumentContext::OPENP() {
  return getToken(StringInterpolatorParser::OPENP, 0);
}

tree::TerminalNode* StringInterpolatorParser::ArgumentContext::CLOSEP() {
  return getToken(StringInterpolatorParser::CLOSEP, 0);
}

StringInterpolatorParser::Piped_expressionContext* StringInterpolatorParser::ArgumentContext::piped_expression() {
  return getRuleContext<StringInterpolatorParser::Piped_expressionContext>(0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::ArgumentContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::ArgumentContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(113);
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
        setState(93);
        expr_item();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        enterOuterAlt(_localctx, 2);
        setState(94);
        match(StringInterpolatorParser::OPENP);
        setState(98);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == StringInterpolatorParser::WS) {
          setState(95);
          match(StringInterpolatorParser::WS);
          setState(100);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(103);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
          setState(101);
          expr_item();
          break;
        }

        case 2: {
          setState(102);
          piped_expression();
          break;
        }

        default:
          break;
        }
        setState(108);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == StringInterpolatorParser::WS) {
          setState(105);
          match(StringInterpolatorParser::WS);
          setState(110);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(111);
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::Arg_listContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Arg_listContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(116);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3806320) != 0)) {
      setState(115);
      argument();
    }
    setState(126);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(119); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(118);
          match(StringInterpolatorParser::WS);
          setState(121); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == StringInterpolatorParser::WS);
        setState(123);
        argument(); 
      }
      setState(128);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::FuncContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::FuncContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(129);
    match(StringInterpolatorParser::ID);
    setState(136);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(131); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(130);
                match(StringInterpolatorParser::WS);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(133); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(135);
      arg_list();
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::Array_itemContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Array_itemContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
    setState(141);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(138);
      match(StringInterpolatorParser::WS);
      setState(143);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(161);
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
        setState(144);
        expr();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        setState(145);
        match(StringInterpolatorParser::OPENP);
        setState(149);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == StringInterpolatorParser::WS) {
          setState(146);
          match(StringInterpolatorParser::WS);
          setState(151);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(152);
        expr();
        setState(156);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == StringInterpolatorParser::WS) {
          setState(153);
          match(StringInterpolatorParser::WS);
          setState(158);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(159);
        match(StringInterpolatorParser::CLOSEP);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(166);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(163);
      match(StringInterpolatorParser::WS);
      setState(168);
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
    setState(169);
    match(StringInterpolatorParser::OPENB);
    setState(175);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(170);
        array_item();
        setState(171);
        match(StringInterpolatorParser::COMMA); 
      }
      setState(177);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
    setState(179);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4068464) != 0)) {
      setState(178);
      array_item();
    }
    setState(181);
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
    setState(187);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(183);
        literal();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(184);
        property();
        break;
      }

      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(185);
        func();
        break;
      }

      case StringInterpolatorParser::OPENB: {
        enterOuterAlt(_localctx, 4);
        setState(186);
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::Piped_expressionContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Piped_expressionContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
    setState(189);
    expr_item();
    setState(193);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(190);
      match(StringInterpolatorParser::WS);
      setState(195);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(196);
    match(StringInterpolatorParser::PIPE);
    setState(200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(197);
      match(StringInterpolatorParser::WS);
      setState(202);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(203);
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
    setState(207);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(205);
      expr_item();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(206);
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::EvalContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::EvalContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
    setState(209);
    match(StringInterpolatorParser::OPEN);
    setState(213);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(210);
      match(StringInterpolatorParser::WS);
      setState(215);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(216);
    expr();
    setState(220);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(217);
      match(StringInterpolatorParser::WS);
      setState(222);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(223);
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::Loop_startContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Loop_startContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
    setState(225);
    match(StringInterpolatorParser::OPEN);
    setState(226);
    match(StringInterpolatorParser::HASH);
    setState(230);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(227);
      match(StringInterpolatorParser::WS);
      setState(232);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(233);
    expr();
    setState(237);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(234);
      match(StringInterpolatorParser::WS);
      setState(239);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(240);
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::Loop_endContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Loop_endContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
    setState(242);
    match(StringInterpolatorParser::OPEN);
    setState(243);
    match(StringInterpolatorParser::SLASH);
    setState(244);
    match(StringInterpolatorParser::SLASH);
    setState(248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(245);
      match(StringInterpolatorParser::WS);
      setState(250);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(251);
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
    setState(253);
    loop_start();
    setState(254);
    interpolated_str();
    setState(255);
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
    setState(259);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(257);
      eval();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(258);
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
    setState(262); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(261);
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
      setState(264); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx);
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
    setState(270);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(268);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case StringInterpolatorParser::NORMAL_TEXT:
          case StringInterpolatorParser::NORMAL_ESCAPE: {
            setState(266);
            normal();
            break;
          }

          case StringInterpolatorParser::OPEN: {
            setState(267);
            stmt();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(272);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::Expression_programContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Expression_programContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
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
    setState(276);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(273);
      match(StringInterpolatorParser::WS);
      setState(278);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(279);
    expr();
    setState(283);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(280);
      match(StringInterpolatorParser::WS);
      setState(285);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(286);
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
    setState(288);
    interpolated_str();
    setState(289);
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
