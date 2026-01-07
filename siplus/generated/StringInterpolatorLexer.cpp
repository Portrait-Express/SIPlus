
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
      "NORMAL_TEXT", "NORMAL_ESCAPE", "OPEN", "TRUE", "FALSE", "DOT", "HASH", 
      "SLASH", "CLOSE", "OPENP", "CLOSEP", "OPENB", "CLOSEB", "COMMA", "PIPE", 
      "DOLLAR", "SEMICOLON", "QUESTION", "AT", "EQUAL", "ARROW", "BACKSLASH", 
      "STRING_START", "WS", "INT", "FLOAT", "ID", "ANY", "STRING_TEXT", 
      "STRING_ESCAPE", "STRING_END"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "TEMPLATE", "STRING"
    },
    std::vector<std::string>{
      "", "", "", "'{'", "'true'", "'false'", "'.'", "'#'", "'/'", "'}'", 
      "'('", "')'", "'['", "']'", "','", "'|'", "'$'", "';'", "'\\u003F'", 
      "'@'", "'='", "'=>'", "'\\'"
    },
    std::vector<std::string>{
      "", "NORMAL_TEXT", "NORMAL_ESCAPE", "OPEN", "TRUE", "FALSE", "DOT", 
      "HASH", "SLASH", "CLOSE", "OPENP", "CLOSEP", "OPENB", "CLOSEB", "COMMA", 
      "PIPE", "DOLLAR", "SEMICOLON", "QUESTION", "AT", "EQUAL", "ARROW", 
      "BACKSLASH", "STRING_START", "WS", "INT", "FLOAT", "ID", "ANY", "STRING_TEXT", 
      "STRING_ESCAPE", "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,31,184,6,-1,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,
  	7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,
  	7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,
  	7,20,2,21,7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,
  	7,27,2,28,7,28,2,29,7,29,2,30,7,30,1,0,4,0,67,8,0,11,0,12,0,68,1,1,1,
  	1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,5,
  	1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,
  	1,12,1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,19,
  	1,19,1,20,1,20,1,20,1,21,1,21,1,22,1,22,1,22,1,22,1,23,4,23,131,8,23,
  	11,23,12,23,132,1,24,1,24,3,24,137,8,24,1,24,4,24,140,8,24,11,24,12,24,
  	141,1,25,4,25,145,8,25,11,25,12,25,146,1,25,1,25,5,25,151,8,25,10,25,
  	12,25,154,9,25,1,25,1,25,4,25,158,8,25,11,25,12,25,159,3,25,162,8,25,
  	1,26,1,26,5,26,166,8,26,10,26,12,26,169,9,26,1,27,1,27,1,28,4,28,174,
  	8,28,11,28,12,28,175,1,29,1,29,1,29,1,30,1,30,1,30,1,30,0,0,31,3,1,5,
  	2,7,3,9,4,11,5,13,6,15,7,17,8,19,9,21,10,23,11,25,12,27,13,29,14,31,15,
  	33,16,35,17,37,18,39,19,41,20,43,21,45,22,47,23,49,24,51,25,53,26,55,
  	27,57,28,59,29,61,30,63,31,3,0,1,2,8,2,0,92,92,123,123,3,0,9,10,13,13,
  	32,32,6,0,66,66,79,79,88,88,98,98,111,111,120,120,2,0,48,57,95,95,1,0,
  	48,57,2,0,65,90,97,122,4,0,48,57,65,90,95,95,97,122,2,0,34,34,92,92,191,
  	0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,1,9,1,0,0,0,1,11,1,0,0,0,1,13,1,0,
  	0,0,1,15,1,0,0,0,1,17,1,0,0,0,1,19,1,0,0,0,1,21,1,0,0,0,1,23,1,0,0,0,
  	1,25,1,0,0,0,1,27,1,0,0,0,1,29,1,0,0,0,1,31,1,0,0,0,1,33,1,0,0,0,1,35,
  	1,0,0,0,1,37,1,0,0,0,1,39,1,0,0,0,1,41,1,0,0,0,1,43,1,0,0,0,1,45,1,0,
  	0,0,1,47,1,0,0,0,1,49,1,0,0,0,1,51,1,0,0,0,1,53,1,0,0,0,1,55,1,0,0,0,
  	1,57,1,0,0,0,2,59,1,0,0,0,2,61,1,0,0,0,2,63,1,0,0,0,3,66,1,0,0,0,5,70,
  	1,0,0,0,7,73,1,0,0,0,9,77,1,0,0,0,11,82,1,0,0,0,13,88,1,0,0,0,15,90,1,
  	0,0,0,17,92,1,0,0,0,19,94,1,0,0,0,21,98,1,0,0,0,23,100,1,0,0,0,25,102,
  	1,0,0,0,27,104,1,0,0,0,29,106,1,0,0,0,31,108,1,0,0,0,33,110,1,0,0,0,35,
  	112,1,0,0,0,37,114,1,0,0,0,39,116,1,0,0,0,41,118,1,0,0,0,43,120,1,0,0,
  	0,45,123,1,0,0,0,47,125,1,0,0,0,49,130,1,0,0,0,51,136,1,0,0,0,53,161,
  	1,0,0,0,55,163,1,0,0,0,57,170,1,0,0,0,59,173,1,0,0,0,61,177,1,0,0,0,63,
  	180,1,0,0,0,65,67,8,0,0,0,66,65,1,0,0,0,67,68,1,0,0,0,68,66,1,0,0,0,68,
  	69,1,0,0,0,69,4,1,0,0,0,70,71,5,92,0,0,71,72,9,0,0,0,72,6,1,0,0,0,73,
  	74,5,123,0,0,74,75,1,0,0,0,75,76,6,2,0,0,76,8,1,0,0,0,77,78,5,116,0,0,
  	78,79,5,114,0,0,79,80,5,117,0,0,80,81,5,101,0,0,81,10,1,0,0,0,82,83,5,
  	102,0,0,83,84,5,97,0,0,84,85,5,108,0,0,85,86,5,115,0,0,86,87,5,101,0,
  	0,87,12,1,0,0,0,88,89,5,46,0,0,89,14,1,0,0,0,90,91,5,35,0,0,91,16,1,0,
  	0,0,92,93,5,47,0,0,93,18,1,0,0,0,94,95,5,125,0,0,95,96,1,0,0,0,96,97,
  	6,8,1,0,97,20,1,0,0,0,98,99,5,40,0,0,99,22,1,0,0,0,100,101,5,41,0,0,101,
  	24,1,0,0,0,102,103,5,91,0,0,103,26,1,0,0,0,104,105,5,93,0,0,105,28,1,
  	0,0,0,106,107,5,44,0,0,107,30,1,0,0,0,108,109,5,124,0,0,109,32,1,0,0,
  	0,110,111,5,36,0,0,111,34,1,0,0,0,112,113,5,59,0,0,113,36,1,0,0,0,114,
  	115,5,63,0,0,115,38,1,0,0,0,116,117,5,64,0,0,117,40,1,0,0,0,118,119,5,
  	61,0,0,119,42,1,0,0,0,120,121,5,61,0,0,121,122,5,62,0,0,122,44,1,0,0,
  	0,123,124,5,92,0,0,124,46,1,0,0,0,125,126,5,34,0,0,126,127,1,0,0,0,127,
  	128,6,22,2,0,128,48,1,0,0,0,129,131,7,1,0,0,130,129,1,0,0,0,131,132,1,
  	0,0,0,132,130,1,0,0,0,132,133,1,0,0,0,133,50,1,0,0,0,134,135,5,48,0,0,
  	135,137,7,2,0,0,136,134,1,0,0,0,136,137,1,0,0,0,137,139,1,0,0,0,138,140,
  	7,3,0,0,139,138,1,0,0,0,140,141,1,0,0,0,141,139,1,0,0,0,141,142,1,0,0,
  	0,142,52,1,0,0,0,143,145,7,4,0,0,144,143,1,0,0,0,145,146,1,0,0,0,146,
  	144,1,0,0,0,146,147,1,0,0,0,147,148,1,0,0,0,148,152,5,46,0,0,149,151,
  	7,4,0,0,150,149,1,0,0,0,151,154,1,0,0,0,152,150,1,0,0,0,152,153,1,0,0,
  	0,153,162,1,0,0,0,154,152,1,0,0,0,155,157,5,46,0,0,156,158,7,4,0,0,157,
  	156,1,0,0,0,158,159,1,0,0,0,159,157,1,0,0,0,159,160,1,0,0,0,160,162,1,
  	0,0,0,161,144,1,0,0,0,161,155,1,0,0,0,162,54,1,0,0,0,163,167,7,5,0,0,
  	164,166,7,6,0,0,165,164,1,0,0,0,166,169,1,0,0,0,167,165,1,0,0,0,167,168,
  	1,0,0,0,168,56,1,0,0,0,169,167,1,0,0,0,170,171,9,0,0,0,171,58,1,0,0,0,
  	172,174,8,7,0,0,173,172,1,0,0,0,174,175,1,0,0,0,175,173,1,0,0,0,175,176,
  	1,0,0,0,176,60,1,0,0,0,177,178,5,92,0,0,178,179,9,0,0,0,179,62,1,0,0,
  	0,180,181,5,34,0,0,181,182,1,0,0,0,182,183,6,30,0,0,183,64,1,0,0,0,13,
  	0,1,2,68,132,136,141,146,152,159,161,167,175,3,2,1,0,2,0,0,2,2,0
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
