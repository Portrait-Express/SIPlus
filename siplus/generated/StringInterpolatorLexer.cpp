
// Generated from StringInterpolatorLexer.g4 by ANTLR 4.13.2


#include "StringInterpolatorLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct StringInterpolatorLexerStaticData final {
  StringInterpolatorLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  StringInterpolatorLexerStaticData(const StringInterpolatorLexerStaticData&) = delete;
  StringInterpolatorLexerStaticData(StringInterpolatorLexerStaticData&&) = delete;
  StringInterpolatorLexerStaticData& operator=(const StringInterpolatorLexerStaticData&) = delete;
  StringInterpolatorLexerStaticData& operator=(StringInterpolatorLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag stringinterpolatorlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<StringInterpolatorLexerStaticData> stringinterpolatorlexerLexerStaticData = nullptr;

void stringinterpolatorlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (stringinterpolatorlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(stringinterpolatorlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<StringInterpolatorLexerStaticData>(
    std::vector<std::string>{
      "NORMAL_TEXT", "NORMAL_ESCAPE", "OPEN", "TRUE", "FALSE", "NULL", "VAR", 
      "PERSIST", "CONST", "DOT", "HASH", "SLASH", "CLOSE", "OPENP", "CLOSEP", 
      "OPENB", "CLOSEB", "COMMA", "PIPE", "DOLLAR", "SEMICOLON", "QUESTION", 
      "AT", "EQUAL", "ARROW", "BACKSLASH", "STRING_START", "WS", "INT", 
      "FLOAT", "ID", "ANY", "STRING_TEXT", "STRING_ESCAPE", "STRING_END"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "TEMPLATE", "STRING"
    },
    std::vector<std::string>{
      "", "", "", "'{'", "'true'", "'false'", "'null'", "'var'", "'persist'", 
      "'const'", "'.'", "'#'", "'/'", "'}'", "'('", "')'", "'['", "']'", 
      "','", "'|'", "'$'", "';'", "'\\u003F'", "'@'", "'='", "'=>'", "'\\'"
    },
    std::vector<std::string>{
      "", "NORMAL_TEXT", "NORMAL_ESCAPE", "OPEN", "TRUE", "FALSE", "NULL", 
      "VAR", "PERSIST", "CONST", "DOT", "HASH", "SLASH", "CLOSE", "OPENP", 
      "CLOSEP", "OPENB", "CLOSEB", "COMMA", "PIPE", "DOLLAR", "SEMICOLON", 
      "QUESTION", "AT", "EQUAL", "ARROW", "BACKSLASH", "STRING_START", "WS", 
      "INT", "FLOAT", "ID", "ANY", "STRING_TEXT", "STRING_ESCAPE", "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,35,215,6,-1,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,
  	7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,
  	7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,
  	7,20,2,21,7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,
  	7,27,2,28,7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,
  	7,34,1,0,4,0,75,8,0,11,0,12,0,76,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,
  	1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,
  	6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,9,1,10,
  	1,10,1,11,1,11,1,12,1,12,1,12,1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,
  	1,16,1,17,1,17,1,18,1,18,1,19,1,19,1,20,1,20,1,21,1,21,1,22,1,22,1,23,
  	1,23,1,24,1,24,1,24,1,25,1,25,1,26,1,26,1,26,1,26,1,27,4,27,162,8,27,
  	11,27,12,27,163,1,28,1,28,3,28,168,8,28,1,28,4,28,171,8,28,11,28,12,28,
  	172,1,29,4,29,176,8,29,11,29,12,29,177,1,29,1,29,5,29,182,8,29,10,29,
  	12,29,185,9,29,1,29,1,29,4,29,189,8,29,11,29,12,29,190,3,29,193,8,29,
  	1,30,1,30,5,30,197,8,30,10,30,12,30,200,9,30,1,31,1,31,1,32,4,32,205,
  	8,32,11,32,12,32,206,1,33,1,33,1,33,1,34,1,34,1,34,1,34,0,0,35,3,1,5,
  	2,7,3,9,4,11,5,13,6,15,7,17,8,19,9,21,10,23,11,25,12,27,13,29,14,31,15,
  	33,16,35,17,37,18,39,19,41,20,43,21,45,22,47,23,49,24,51,25,53,26,55,
  	27,57,28,59,29,61,30,63,31,65,32,67,33,69,34,71,35,3,0,1,2,8,2,0,92,92,
  	123,123,3,0,9,10,13,13,32,32,6,0,66,66,79,79,88,88,98,98,111,111,120,
  	120,2,0,48,57,95,95,1,0,48,57,2,0,65,90,97,122,4,0,48,57,65,90,95,95,
  	97,122,2,0,34,34,92,92,222,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,1,9,1,
  	0,0,0,1,11,1,0,0,0,1,13,1,0,0,0,1,15,1,0,0,0,1,17,1,0,0,0,1,19,1,0,0,
  	0,1,21,1,0,0,0,1,23,1,0,0,0,1,25,1,0,0,0,1,27,1,0,0,0,1,29,1,0,0,0,1,
  	31,1,0,0,0,1,33,1,0,0,0,1,35,1,0,0,0,1,37,1,0,0,0,1,39,1,0,0,0,1,41,1,
  	0,0,0,1,43,1,0,0,0,1,45,1,0,0,0,1,47,1,0,0,0,1,49,1,0,0,0,1,51,1,0,0,
  	0,1,53,1,0,0,0,1,55,1,0,0,0,1,57,1,0,0,0,1,59,1,0,0,0,1,61,1,0,0,0,1,
  	63,1,0,0,0,1,65,1,0,0,0,2,67,1,0,0,0,2,69,1,0,0,0,2,71,1,0,0,0,3,74,1,
  	0,0,0,5,78,1,0,0,0,7,81,1,0,0,0,9,85,1,0,0,0,11,90,1,0,0,0,13,96,1,0,
  	0,0,15,101,1,0,0,0,17,105,1,0,0,0,19,113,1,0,0,0,21,119,1,0,0,0,23,121,
  	1,0,0,0,25,123,1,0,0,0,27,125,1,0,0,0,29,129,1,0,0,0,31,131,1,0,0,0,33,
  	133,1,0,0,0,35,135,1,0,0,0,37,137,1,0,0,0,39,139,1,0,0,0,41,141,1,0,0,
  	0,43,143,1,0,0,0,45,145,1,0,0,0,47,147,1,0,0,0,49,149,1,0,0,0,51,151,
  	1,0,0,0,53,154,1,0,0,0,55,156,1,0,0,0,57,161,1,0,0,0,59,167,1,0,0,0,61,
  	192,1,0,0,0,63,194,1,0,0,0,65,201,1,0,0,0,67,204,1,0,0,0,69,208,1,0,0,
  	0,71,211,1,0,0,0,73,75,8,0,0,0,74,73,1,0,0,0,75,76,1,0,0,0,76,74,1,0,
  	0,0,76,77,1,0,0,0,77,4,1,0,0,0,78,79,5,92,0,0,79,80,9,0,0,0,80,6,1,0,
  	0,0,81,82,5,123,0,0,82,83,1,0,0,0,83,84,6,2,0,0,84,8,1,0,0,0,85,86,5,
  	116,0,0,86,87,5,114,0,0,87,88,5,117,0,0,88,89,5,101,0,0,89,10,1,0,0,0,
  	90,91,5,102,0,0,91,92,5,97,0,0,92,93,5,108,0,0,93,94,5,115,0,0,94,95,
  	5,101,0,0,95,12,1,0,0,0,96,97,5,110,0,0,97,98,5,117,0,0,98,99,5,108,0,
  	0,99,100,5,108,0,0,100,14,1,0,0,0,101,102,5,118,0,0,102,103,5,97,0,0,
  	103,104,5,114,0,0,104,16,1,0,0,0,105,106,5,112,0,0,106,107,5,101,0,0,
  	107,108,5,114,0,0,108,109,5,115,0,0,109,110,5,105,0,0,110,111,5,115,0,
  	0,111,112,5,116,0,0,112,18,1,0,0,0,113,114,5,99,0,0,114,115,5,111,0,0,
  	115,116,5,110,0,0,116,117,5,115,0,0,117,118,5,116,0,0,118,20,1,0,0,0,
  	119,120,5,46,0,0,120,22,1,0,0,0,121,122,5,35,0,0,122,24,1,0,0,0,123,124,
  	5,47,0,0,124,26,1,0,0,0,125,126,5,125,0,0,126,127,1,0,0,0,127,128,6,12,
  	1,0,128,28,1,0,0,0,129,130,5,40,0,0,130,30,1,0,0,0,131,132,5,41,0,0,132,
  	32,1,0,0,0,133,134,5,91,0,0,134,34,1,0,0,0,135,136,5,93,0,0,136,36,1,
  	0,0,0,137,138,5,44,0,0,138,38,1,0,0,0,139,140,5,124,0,0,140,40,1,0,0,
  	0,141,142,5,36,0,0,142,42,1,0,0,0,143,144,5,59,0,0,144,44,1,0,0,0,145,
  	146,5,63,0,0,146,46,1,0,0,0,147,148,5,64,0,0,148,48,1,0,0,0,149,150,5,
  	61,0,0,150,50,1,0,0,0,151,152,5,61,0,0,152,153,5,62,0,0,153,52,1,0,0,
  	0,154,155,5,92,0,0,155,54,1,0,0,0,156,157,5,34,0,0,157,158,1,0,0,0,158,
  	159,6,26,2,0,159,56,1,0,0,0,160,162,7,1,0,0,161,160,1,0,0,0,162,163,1,
  	0,0,0,163,161,1,0,0,0,163,164,1,0,0,0,164,58,1,0,0,0,165,166,5,48,0,0,
  	166,168,7,2,0,0,167,165,1,0,0,0,167,168,1,0,0,0,168,170,1,0,0,0,169,171,
  	7,3,0,0,170,169,1,0,0,0,171,172,1,0,0,0,172,170,1,0,0,0,172,173,1,0,0,
  	0,173,60,1,0,0,0,174,176,7,4,0,0,175,174,1,0,0,0,176,177,1,0,0,0,177,
  	175,1,0,0,0,177,178,1,0,0,0,178,179,1,0,0,0,179,183,5,46,0,0,180,182,
  	7,4,0,0,181,180,1,0,0,0,182,185,1,0,0,0,183,181,1,0,0,0,183,184,1,0,0,
  	0,184,193,1,0,0,0,185,183,1,0,0,0,186,188,5,46,0,0,187,189,7,4,0,0,188,
  	187,1,0,0,0,189,190,1,0,0,0,190,188,1,0,0,0,190,191,1,0,0,0,191,193,1,
  	0,0,0,192,175,1,0,0,0,192,186,1,0,0,0,193,62,1,0,0,0,194,198,7,5,0,0,
  	195,197,7,6,0,0,196,195,1,0,0,0,197,200,1,0,0,0,198,196,1,0,0,0,198,199,
  	1,0,0,0,199,64,1,0,0,0,200,198,1,0,0,0,201,202,9,0,0,0,202,66,1,0,0,0,
  	203,205,8,7,0,0,204,203,1,0,0,0,205,206,1,0,0,0,206,204,1,0,0,0,206,207,
  	1,0,0,0,207,68,1,0,0,0,208,209,5,92,0,0,209,210,9,0,0,0,210,70,1,0,0,
  	0,211,212,5,34,0,0,212,213,1,0,0,0,213,214,6,34,0,0,214,72,1,0,0,0,13,
  	0,1,2,76,163,167,172,177,183,190,192,198,206,3,2,1,0,2,0,0,2,2,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  stringinterpolatorlexerLexerStaticData = std::move(staticData);
}

}

StringInterpolatorLexer::StringInterpolatorLexer(CharStream *input) : Lexer(input) {
  StringInterpolatorLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *stringinterpolatorlexerLexerStaticData->atn, stringinterpolatorlexerLexerStaticData->decisionToDFA, stringinterpolatorlexerLexerStaticData->sharedContextCache);
}

StringInterpolatorLexer::~StringInterpolatorLexer() {
  delete _interpreter;
}

std::string StringInterpolatorLexer::getGrammarFileName() const {
  return "StringInterpolatorLexer.g4";
}

const std::vector<std::string>& StringInterpolatorLexer::getRuleNames() const {
  return stringinterpolatorlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& StringInterpolatorLexer::getChannelNames() const {
  return stringinterpolatorlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& StringInterpolatorLexer::getModeNames() const {
  return stringinterpolatorlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& StringInterpolatorLexer::getVocabulary() const {
  return stringinterpolatorlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView StringInterpolatorLexer::getSerializedATN() const {
  return stringinterpolatorlexerLexerStaticData->serializedATN;
}

const atn::ATN& StringInterpolatorLexer::getATN() const {
  return *stringinterpolatorlexerLexerStaticData->atn;
}




void StringInterpolatorLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  stringinterpolatorlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(stringinterpolatorlexerLexerOnceFlag, stringinterpolatorlexerLexerInitialize);
#endif
}
