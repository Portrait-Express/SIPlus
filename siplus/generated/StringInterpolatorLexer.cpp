
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
      "SLASH", "CLOSE", "OPENP", "CLOSEP", "PIPE", "BACKSLASH", "STRING_START", 
      "WS", "INT", "FLOAT", "ID", "ANY", "STRING_TEXT", "STRING_ESCAPE", 
      "STRING_END"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "TEMPLATE", "STRING"
    },
    std::vector<std::string>{
      "", "", "", "'{'", "'true'", "'false'", "'.'", "'#'", "'/'", "'}'", 
      "'('", "')'", "'|'", "'\\'"
    },
    std::vector<std::string>{
      "", "NORMAL_TEXT", "NORMAL_ESCAPE", "OPEN", "TRUE", "FALSE", "DOT", 
      "HASH", "SLASH", "CLOSE", "OPENP", "CLOSEP", "PIPE", "BACKSLASH", 
      "STRING_START", "WS", "INT", "FLOAT", "ID", "ANY", "STRING_TEXT", 
      "STRING_ESCAPE", "STRING_END"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,22,149,6,-1,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,
  	7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,
  	7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,
  	7,20,2,21,7,21,1,0,4,0,49,8,0,11,0,12,0,50,1,1,1,1,1,1,1,2,1,2,1,2,1,
  	2,1,3,1,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,6,1,6,1,7,1,7,
  	1,8,1,8,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,13,
  	1,13,1,14,4,14,94,8,14,11,14,12,14,95,1,14,1,14,1,15,1,15,3,15,102,8,
  	15,1,15,4,15,105,8,15,11,15,12,15,106,1,16,4,16,110,8,16,11,16,12,16,
  	111,1,16,1,16,5,16,116,8,16,10,16,12,16,119,9,16,1,16,1,16,4,16,123,8,
  	16,11,16,12,16,124,3,16,127,8,16,1,17,1,17,5,17,131,8,17,10,17,12,17,
  	134,9,17,1,18,1,18,1,19,4,19,139,8,19,11,19,12,19,140,1,20,1,20,1,20,
  	1,21,1,21,1,21,1,21,0,0,22,3,1,5,2,7,3,9,4,11,5,13,6,15,7,17,8,19,9,21,
  	10,23,11,25,12,27,13,29,14,31,15,33,16,35,17,37,18,39,19,41,20,43,21,
  	45,22,3,0,1,2,8,2,0,92,92,123,123,3,0,9,10,13,13,32,32,6,0,66,66,79,79,
  	88,88,98,98,111,111,120,120,2,0,48,57,95,95,1,0,48,57,2,0,65,90,97,122,
  	4,0,48,57,65,90,95,95,97,122,2,0,34,34,92,92,156,0,3,1,0,0,0,0,5,1,0,
  	0,0,0,7,1,0,0,0,1,9,1,0,0,0,1,11,1,0,0,0,1,13,1,0,0,0,1,15,1,0,0,0,1,
  	17,1,0,0,0,1,19,1,0,0,0,1,21,1,0,0,0,1,23,1,0,0,0,1,25,1,0,0,0,1,27,1,
  	0,0,0,1,29,1,0,0,0,1,31,1,0,0,0,1,33,1,0,0,0,1,35,1,0,0,0,1,37,1,0,0,
  	0,1,39,1,0,0,0,2,41,1,0,0,0,2,43,1,0,0,0,2,45,1,0,0,0,3,48,1,0,0,0,5,
  	52,1,0,0,0,7,55,1,0,0,0,9,59,1,0,0,0,11,64,1,0,0,0,13,70,1,0,0,0,15,72,
  	1,0,0,0,17,74,1,0,0,0,19,76,1,0,0,0,21,80,1,0,0,0,23,82,1,0,0,0,25,84,
  	1,0,0,0,27,86,1,0,0,0,29,88,1,0,0,0,31,93,1,0,0,0,33,101,1,0,0,0,35,126,
  	1,0,0,0,37,128,1,0,0,0,39,135,1,0,0,0,41,138,1,0,0,0,43,142,1,0,0,0,45,
  	145,1,0,0,0,47,49,8,0,0,0,48,47,1,0,0,0,49,50,1,0,0,0,50,48,1,0,0,0,50,
  	51,1,0,0,0,51,4,1,0,0,0,52,53,5,92,0,0,53,54,9,0,0,0,54,6,1,0,0,0,55,
  	56,5,123,0,0,56,57,1,0,0,0,57,58,6,2,0,0,58,8,1,0,0,0,59,60,5,116,0,0,
  	60,61,5,114,0,0,61,62,5,117,0,0,62,63,5,101,0,0,63,10,1,0,0,0,64,65,5,
  	102,0,0,65,66,5,97,0,0,66,67,5,108,0,0,67,68,5,115,0,0,68,69,5,101,0,
  	0,69,12,1,0,0,0,70,71,5,46,0,0,71,14,1,0,0,0,72,73,5,35,0,0,73,16,1,0,
  	0,0,74,75,5,47,0,0,75,18,1,0,0,0,76,77,5,125,0,0,77,78,1,0,0,0,78,79,
  	6,8,1,0,79,20,1,0,0,0,80,81,5,40,0,0,81,22,1,0,0,0,82,83,5,41,0,0,83,
  	24,1,0,0,0,84,85,5,124,0,0,85,26,1,0,0,0,86,87,5,92,0,0,87,28,1,0,0,0,
  	88,89,5,34,0,0,89,90,1,0,0,0,90,91,6,13,2,0,91,30,1,0,0,0,92,94,7,1,0,
  	0,93,92,1,0,0,0,94,95,1,0,0,0,95,93,1,0,0,0,95,96,1,0,0,0,96,97,1,0,0,
  	0,97,98,6,14,3,0,98,32,1,0,0,0,99,100,5,48,0,0,100,102,7,2,0,0,101,99,
  	1,0,0,0,101,102,1,0,0,0,102,104,1,0,0,0,103,105,7,3,0,0,104,103,1,0,0,
  	0,105,106,1,0,0,0,106,104,1,0,0,0,106,107,1,0,0,0,107,34,1,0,0,0,108,
  	110,7,4,0,0,109,108,1,0,0,0,110,111,1,0,0,0,111,109,1,0,0,0,111,112,1,
  	0,0,0,112,113,1,0,0,0,113,117,5,46,0,0,114,116,7,4,0,0,115,114,1,0,0,
  	0,116,119,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,127,1,0,0,0,119,
  	117,1,0,0,0,120,122,5,46,0,0,121,123,7,4,0,0,122,121,1,0,0,0,123,124,
  	1,0,0,0,124,122,1,0,0,0,124,125,1,0,0,0,125,127,1,0,0,0,126,109,1,0,0,
  	0,126,120,1,0,0,0,127,36,1,0,0,0,128,132,7,5,0,0,129,131,7,6,0,0,130,
  	129,1,0,0,0,131,134,1,0,0,0,132,130,1,0,0,0,132,133,1,0,0,0,133,38,1,
  	0,0,0,134,132,1,0,0,0,135,136,9,0,0,0,136,40,1,0,0,0,137,139,8,7,0,0,
  	138,137,1,0,0,0,139,140,1,0,0,0,140,138,1,0,0,0,140,141,1,0,0,0,141,42,
  	1,0,0,0,142,143,5,92,0,0,143,144,9,0,0,0,144,44,1,0,0,0,145,146,5,34,
  	0,0,146,147,1,0,0,0,147,148,6,21,0,0,148,46,1,0,0,0,13,0,1,2,50,95,101,
  	106,111,117,124,126,132,140,4,2,1,0,2,0,0,2,2,0,0,1,0
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
