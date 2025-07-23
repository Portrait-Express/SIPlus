
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
      "NORMAL_TEXT", "NORMAL_ESCAPE", "OPEN", "DOT", "HASH", "SLASH", "CLOSE", 
      "OPENP", "CLOSEP", "PIPE", "BACKSLASH", "STRING_START", "WS", "INT", 
      "FLOAT", "ID", "ANY", "STRING_TEXT", "STRING_ESCAPE", "STRING_END"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE", "TEMPLATE", "STRING"
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
  	4,0,20,134,6,-1,6,-1,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,
  	7,5,2,6,7,6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,
  	7,13,2,14,7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,1,0,
  	4,0,45,8,0,11,0,12,0,46,1,1,1,1,1,1,1,2,1,2,1,2,1,2,1,3,1,3,1,4,1,4,1,
  	5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,1,11,
  	1,11,1,12,4,12,79,8,12,11,12,12,12,80,1,12,1,12,1,13,1,13,3,13,87,8,13,
  	1,13,4,13,90,8,13,11,13,12,13,91,1,14,4,14,95,8,14,11,14,12,14,96,1,14,
  	1,14,5,14,101,8,14,10,14,12,14,104,9,14,1,14,1,14,4,14,108,8,14,11,14,
  	12,14,109,3,14,112,8,14,1,15,1,15,5,15,116,8,15,10,15,12,15,119,9,15,
  	1,16,1,16,1,17,4,17,124,8,17,11,17,12,17,125,1,18,1,18,1,18,1,19,1,19,
  	1,19,1,19,0,0,20,3,1,5,2,7,3,9,4,11,5,13,6,15,7,17,8,19,9,21,10,23,11,
  	25,12,27,13,29,14,31,15,33,16,35,17,37,18,39,19,41,20,3,0,1,2,8,2,0,92,
  	92,123,123,3,0,9,10,13,13,32,32,6,0,66,66,79,79,88,88,98,98,111,111,120,
  	120,2,0,48,57,95,95,1,0,48,57,2,0,65,90,97,122,4,0,48,57,65,90,95,95,
  	97,122,2,0,34,34,92,92,141,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,1,9,1,
  	0,0,0,1,11,1,0,0,0,1,13,1,0,0,0,1,15,1,0,0,0,1,17,1,0,0,0,1,19,1,0,0,
  	0,1,21,1,0,0,0,1,23,1,0,0,0,1,25,1,0,0,0,1,27,1,0,0,0,1,29,1,0,0,0,1,
  	31,1,0,0,0,1,33,1,0,0,0,1,35,1,0,0,0,2,37,1,0,0,0,2,39,1,0,0,0,2,41,1,
  	0,0,0,3,44,1,0,0,0,5,48,1,0,0,0,7,51,1,0,0,0,9,55,1,0,0,0,11,57,1,0,0,
  	0,13,59,1,0,0,0,15,61,1,0,0,0,17,65,1,0,0,0,19,67,1,0,0,0,21,69,1,0,0,
  	0,23,71,1,0,0,0,25,73,1,0,0,0,27,78,1,0,0,0,29,86,1,0,0,0,31,111,1,0,
  	0,0,33,113,1,0,0,0,35,120,1,0,0,0,37,123,1,0,0,0,39,127,1,0,0,0,41,130,
  	1,0,0,0,43,45,8,0,0,0,44,43,1,0,0,0,45,46,1,0,0,0,46,44,1,0,0,0,46,47,
  	1,0,0,0,47,4,1,0,0,0,48,49,5,92,0,0,49,50,9,0,0,0,50,6,1,0,0,0,51,52,
  	5,123,0,0,52,53,1,0,0,0,53,54,6,2,0,0,54,8,1,0,0,0,55,56,5,46,0,0,56,
  	10,1,0,0,0,57,58,5,35,0,0,58,12,1,0,0,0,59,60,5,47,0,0,60,14,1,0,0,0,
  	61,62,5,125,0,0,62,63,1,0,0,0,63,64,6,6,1,0,64,16,1,0,0,0,65,66,5,40,
  	0,0,66,18,1,0,0,0,67,68,5,41,0,0,68,20,1,0,0,0,69,70,5,124,0,0,70,22,
  	1,0,0,0,71,72,5,92,0,0,72,24,1,0,0,0,73,74,5,34,0,0,74,75,1,0,0,0,75,
  	76,6,11,2,0,76,26,1,0,0,0,77,79,7,1,0,0,78,77,1,0,0,0,79,80,1,0,0,0,80,
  	78,1,0,0,0,80,81,1,0,0,0,81,82,1,0,0,0,82,83,6,12,3,0,83,28,1,0,0,0,84,
  	85,5,48,0,0,85,87,7,2,0,0,86,84,1,0,0,0,86,87,1,0,0,0,87,89,1,0,0,0,88,
  	90,7,3,0,0,89,88,1,0,0,0,90,91,1,0,0,0,91,89,1,0,0,0,91,92,1,0,0,0,92,
  	30,1,0,0,0,93,95,7,4,0,0,94,93,1,0,0,0,95,96,1,0,0,0,96,94,1,0,0,0,96,
  	97,1,0,0,0,97,98,1,0,0,0,98,102,5,46,0,0,99,101,7,4,0,0,100,99,1,0,0,
  	0,101,104,1,0,0,0,102,100,1,0,0,0,102,103,1,0,0,0,103,112,1,0,0,0,104,
  	102,1,0,0,0,105,107,5,46,0,0,106,108,7,4,0,0,107,106,1,0,0,0,108,109,
  	1,0,0,0,109,107,1,0,0,0,109,110,1,0,0,0,110,112,1,0,0,0,111,94,1,0,0,
  	0,111,105,1,0,0,0,112,32,1,0,0,0,113,117,7,5,0,0,114,116,7,6,0,0,115,
  	114,1,0,0,0,116,119,1,0,0,0,117,115,1,0,0,0,117,118,1,0,0,0,118,34,1,
  	0,0,0,119,117,1,0,0,0,120,121,9,0,0,0,121,36,1,0,0,0,122,124,8,7,0,0,
  	123,122,1,0,0,0,124,125,1,0,0,0,125,123,1,0,0,0,125,126,1,0,0,0,126,38,
  	1,0,0,0,127,128,5,92,0,0,128,129,9,0,0,0,129,40,1,0,0,0,130,131,5,34,
  	0,0,131,132,1,0,0,0,132,133,6,19,0,0,133,42,1,0,0,0,13,0,1,2,46,80,86,
  	91,96,102,109,111,117,125,4,2,1,0,2,0,0,2,2,0,0,1,0
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
