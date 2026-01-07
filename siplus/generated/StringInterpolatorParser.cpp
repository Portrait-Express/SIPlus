
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
      "property_name", "property_index", "property_item", "property", "variable_reference", 
      "string", "integer", "float", "boolean", "literal", "argument", "arg_list", 
      "func", "array_item", "array", "expr_item", "piped_expression", "expr", 
      "assign_stmt", "function_parameter", "function_parameters", "function_def_stmt", 
      "simple_expr_stmt", "expr_stmt", "expr_block_contents", "expr_block", 
      "eval", "loop_start", "loop_end", "loop", "stmt", "normal", "interpolated_str", 
      "expression_program", "program"
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
  	4,1,31,428,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,1,
  	0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,3,2,81,8,2,1,3,1,3,4,3,85,8,3,11,3,
  	12,3,86,3,3,89,8,3,1,4,1,4,1,4,5,4,94,8,4,10,4,12,4,97,9,4,1,5,1,5,5,
  	5,101,8,5,10,5,12,5,104,9,5,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,
  	9,1,9,3,9,118,8,9,1,10,1,10,3,10,122,8,10,1,11,3,11,125,8,11,1,11,4,11,
  	128,8,11,11,11,12,11,129,1,11,5,11,133,8,11,10,11,12,11,136,9,11,1,12,
  	3,12,139,8,12,1,12,1,12,4,12,143,8,12,11,12,12,12,144,1,12,3,12,148,8,
  	12,1,13,5,13,151,8,13,10,13,12,13,154,9,13,1,13,1,13,3,13,158,8,13,1,
  	13,5,13,161,8,13,10,13,12,13,164,9,13,1,14,1,14,1,14,1,14,5,14,170,8,
  	14,10,14,12,14,173,9,14,1,14,3,14,176,8,14,1,14,1,14,1,15,1,15,1,15,1,
  	15,1,15,3,15,185,8,15,1,16,1,16,5,16,189,8,16,10,16,12,16,192,9,16,1,
  	16,1,16,5,16,196,8,16,10,16,12,16,199,9,16,1,16,1,16,3,16,203,8,16,1,
  	17,1,17,1,17,3,17,208,8,17,1,18,1,18,1,18,5,18,213,8,18,10,18,12,18,216,
  	9,18,1,18,1,18,5,18,220,8,18,10,18,12,18,223,9,18,1,18,1,18,1,19,1,19,
  	3,19,229,8,19,1,20,1,20,5,20,233,8,20,10,20,12,20,236,9,20,1,20,1,20,
  	5,20,240,8,20,10,20,12,20,243,9,20,1,20,1,20,5,20,247,8,20,10,20,12,20,
  	250,9,20,1,20,1,20,5,20,254,8,20,10,20,12,20,257,9,20,5,20,259,8,20,10,
  	20,12,20,262,9,20,1,20,3,20,265,8,20,1,20,5,20,268,8,20,10,20,12,20,271,
  	9,20,1,20,1,20,1,21,1,21,1,21,5,21,278,8,21,10,21,12,21,281,9,21,1,21,
  	3,21,284,8,21,1,21,5,21,287,8,21,10,21,12,21,290,9,21,1,21,1,21,5,21,
  	294,8,21,10,21,12,21,297,9,21,1,21,1,21,1,22,1,22,1,23,1,23,1,23,3,23,
  	306,8,23,1,23,5,23,309,8,23,10,23,12,23,312,9,23,1,23,1,23,1,24,1,24,
  	5,24,318,8,24,10,24,12,24,321,9,24,5,24,323,8,24,10,24,12,24,326,9,24,
  	1,24,1,24,1,25,1,25,5,25,332,8,25,10,25,12,25,335,9,25,1,25,1,25,5,25,
  	339,8,25,10,25,12,25,342,9,25,1,25,1,25,1,26,1,26,5,26,348,8,26,10,26,
  	12,26,351,9,26,1,26,1,26,5,26,355,8,26,10,26,12,26,358,9,26,1,26,1,26,
  	1,27,1,27,1,27,5,27,365,8,27,10,27,12,27,368,9,27,1,27,1,27,5,27,372,
  	8,27,10,27,12,27,375,9,27,1,27,1,27,1,28,1,28,1,28,1,28,5,28,383,8,28,
  	10,28,12,28,386,9,28,1,28,1,28,1,29,1,29,1,29,1,29,1,30,1,30,3,30,396,
  	8,30,1,31,4,31,399,8,31,11,31,12,31,400,1,32,1,32,5,32,405,8,32,10,32,
  	12,32,408,9,32,1,33,5,33,411,8,33,10,33,12,33,414,9,33,1,33,1,33,5,33,
  	418,8,33,10,33,12,33,421,9,33,1,33,1,33,1,34,1,34,1,34,1,34,0,0,35,0,
  	2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,62,64,66,68,0,4,2,0,25,25,27,27,1,0,29,30,1,0,4,5,1,0,
  	1,2,453,0,70,1,0,0,0,2,73,1,0,0,0,4,80,1,0,0,0,6,88,1,0,0,0,8,90,1,0,
  	0,0,10,98,1,0,0,0,12,107,1,0,0,0,14,109,1,0,0,0,16,111,1,0,0,0,18,117,
  	1,0,0,0,20,121,1,0,0,0,22,124,1,0,0,0,24,138,1,0,0,0,26,152,1,0,0,0,28,
  	165,1,0,0,0,30,184,1,0,0,0,32,186,1,0,0,0,34,207,1,0,0,0,36,209,1,0,0,
  	0,38,226,1,0,0,0,40,230,1,0,0,0,42,274,1,0,0,0,44,300,1,0,0,0,46,305,
  	1,0,0,0,48,324,1,0,0,0,50,329,1,0,0,0,52,345,1,0,0,0,54,361,1,0,0,0,56,
  	378,1,0,0,0,58,389,1,0,0,0,60,395,1,0,0,0,62,398,1,0,0,0,64,406,1,0,0,
  	0,66,412,1,0,0,0,68,424,1,0,0,0,70,71,5,6,0,0,71,72,5,27,0,0,72,1,1,0,
  	0,0,73,74,5,6,0,0,74,75,5,12,0,0,75,76,5,25,0,0,76,77,5,13,0,0,77,3,1,
  	0,0,0,78,81,3,0,0,0,79,81,3,2,1,0,80,78,1,0,0,0,80,79,1,0,0,0,81,5,1,
  	0,0,0,82,89,5,6,0,0,83,85,3,4,2,0,84,83,1,0,0,0,85,86,1,0,0,0,86,84,1,
  	0,0,0,86,87,1,0,0,0,87,89,1,0,0,0,88,82,1,0,0,0,88,84,1,0,0,0,89,7,1,
  	0,0,0,90,91,5,16,0,0,91,95,7,0,0,0,92,94,3,4,2,0,93,92,1,0,0,0,94,97,
  	1,0,0,0,95,93,1,0,0,0,95,96,1,0,0,0,96,9,1,0,0,0,97,95,1,0,0,0,98,102,
  	5,23,0,0,99,101,7,1,0,0,100,99,1,0,0,0,101,104,1,0,0,0,102,100,1,0,0,
  	0,102,103,1,0,0,0,103,105,1,0,0,0,104,102,1,0,0,0,105,106,5,31,0,0,106,
  	11,1,0,0,0,107,108,5,25,0,0,108,13,1,0,0,0,109,110,5,26,0,0,110,15,1,
  	0,0,0,111,112,7,2,0,0,112,17,1,0,0,0,113,118,3,10,5,0,114,118,3,12,6,
  	0,115,118,3,14,7,0,116,118,3,16,8,0,117,113,1,0,0,0,117,114,1,0,0,0,117,
  	115,1,0,0,0,117,116,1,0,0,0,118,19,1,0,0,0,119,122,3,30,15,0,120,122,
  	3,50,25,0,121,119,1,0,0,0,121,120,1,0,0,0,122,21,1,0,0,0,123,125,3,20,
  	10,0,124,123,1,0,0,0,124,125,1,0,0,0,125,134,1,0,0,0,126,128,5,24,0,0,
  	127,126,1,0,0,0,128,129,1,0,0,0,129,127,1,0,0,0,129,130,1,0,0,0,130,131,
  	1,0,0,0,131,133,3,20,10,0,132,127,1,0,0,0,133,136,1,0,0,0,134,132,1,0,
  	0,0,134,135,1,0,0,0,135,23,1,0,0,0,136,134,1,0,0,0,137,139,5,19,0,0,138,
  	137,1,0,0,0,138,139,1,0,0,0,139,140,1,0,0,0,140,147,5,27,0,0,141,143,
  	5,24,0,0,142,141,1,0,0,0,143,144,1,0,0,0,144,142,1,0,0,0,144,145,1,0,
  	0,0,145,146,1,0,0,0,146,148,3,22,11,0,147,142,1,0,0,0,147,148,1,0,0,0,
  	148,25,1,0,0,0,149,151,5,24,0,0,150,149,1,0,0,0,151,154,1,0,0,0,152,150,
  	1,0,0,0,152,153,1,0,0,0,153,157,1,0,0,0,154,152,1,0,0,0,155,158,3,30,
  	15,0,156,158,3,50,25,0,157,155,1,0,0,0,157,156,1,0,0,0,158,162,1,0,0,
  	0,159,161,5,24,0,0,160,159,1,0,0,0,161,164,1,0,0,0,162,160,1,0,0,0,162,
  	163,1,0,0,0,163,27,1,0,0,0,164,162,1,0,0,0,165,171,5,12,0,0,166,167,3,
  	26,13,0,167,168,5,14,0,0,168,170,1,0,0,0,169,166,1,0,0,0,170,173,1,0,
  	0,0,171,169,1,0,0,0,171,172,1,0,0,0,172,175,1,0,0,0,173,171,1,0,0,0,174,
  	176,3,26,13,0,175,174,1,0,0,0,175,176,1,0,0,0,176,177,1,0,0,0,177,178,
  	5,13,0,0,178,29,1,0,0,0,179,185,3,18,9,0,180,185,3,6,3,0,181,185,3,24,
  	12,0,182,185,3,28,14,0,183,185,3,8,4,0,184,179,1,0,0,0,184,180,1,0,0,
  	0,184,181,1,0,0,0,184,182,1,0,0,0,184,183,1,0,0,0,185,31,1,0,0,0,186,
  	190,3,30,15,0,187,189,5,24,0,0,188,187,1,0,0,0,189,192,1,0,0,0,190,188,
  	1,0,0,0,190,191,1,0,0,0,191,193,1,0,0,0,192,190,1,0,0,0,193,197,5,15,
  	0,0,194,196,5,24,0,0,195,194,1,0,0,0,196,199,1,0,0,0,197,195,1,0,0,0,
  	197,198,1,0,0,0,198,202,1,0,0,0,199,197,1,0,0,0,200,203,3,30,15,0,201,
  	203,3,32,16,0,202,200,1,0,0,0,202,201,1,0,0,0,203,33,1,0,0,0,204,208,
  	3,30,15,0,205,208,3,32,16,0,206,208,3,50,25,0,207,204,1,0,0,0,207,205,
  	1,0,0,0,207,206,1,0,0,0,208,35,1,0,0,0,209,210,5,16,0,0,210,214,5,27,
  	0,0,211,213,5,24,0,0,212,211,1,0,0,0,213,216,1,0,0,0,214,212,1,0,0,0,
  	214,215,1,0,0,0,215,217,1,0,0,0,216,214,1,0,0,0,217,221,5,20,0,0,218,
  	220,5,24,0,0,219,218,1,0,0,0,220,223,1,0,0,0,221,219,1,0,0,0,221,222,
  	1,0,0,0,222,224,1,0,0,0,223,221,1,0,0,0,224,225,3,34,17,0,225,37,1,0,
  	0,0,226,228,5,27,0,0,227,229,5,18,0,0,228,227,1,0,0,0,228,229,1,0,0,0,
  	229,39,1,0,0,0,230,234,5,10,0,0,231,233,5,24,0,0,232,231,1,0,0,0,233,
  	236,1,0,0,0,234,232,1,0,0,0,234,235,1,0,0,0,235,237,1,0,0,0,236,234,1,
  	0,0,0,237,241,3,38,19,0,238,240,5,24,0,0,239,238,1,0,0,0,240,243,1,0,
  	0,0,241,239,1,0,0,0,241,242,1,0,0,0,242,260,1,0,0,0,243,241,1,0,0,0,244,
  	248,5,14,0,0,245,247,5,24,0,0,246,245,1,0,0,0,247,250,1,0,0,0,248,246,
  	1,0,0,0,248,249,1,0,0,0,249,251,1,0,0,0,250,248,1,0,0,0,251,255,3,38,
  	19,0,252,254,5,24,0,0,253,252,1,0,0,0,254,257,1,0,0,0,255,253,1,0,0,0,
  	255,256,1,0,0,0,256,259,1,0,0,0,257,255,1,0,0,0,258,244,1,0,0,0,259,262,
  	1,0,0,0,260,258,1,0,0,0,260,261,1,0,0,0,261,264,1,0,0,0,262,260,1,0,0,
  	0,263,265,5,14,0,0,264,263,1,0,0,0,264,265,1,0,0,0,265,269,1,0,0,0,266,
  	268,5,24,0,0,267,266,1,0,0,0,268,271,1,0,0,0,269,267,1,0,0,0,269,270,
  	1,0,0,0,270,272,1,0,0,0,271,269,1,0,0,0,272,273,5,11,0,0,273,41,1,0,0,
  	0,274,275,5,19,0,0,275,279,5,27,0,0,276,278,5,24,0,0,277,276,1,0,0,0,
  	278,281,1,0,0,0,279,277,1,0,0,0,279,280,1,0,0,0,280,283,1,0,0,0,281,279,
  	1,0,0,0,282,284,3,40,20,0,283,282,1,0,0,0,283,284,1,0,0,0,284,288,1,0,
  	0,0,285,287,5,24,0,0,286,285,1,0,0,0,287,290,1,0,0,0,288,286,1,0,0,0,
  	288,289,1,0,0,0,289,291,1,0,0,0,290,288,1,0,0,0,291,295,5,21,0,0,292,
  	294,5,24,0,0,293,292,1,0,0,0,294,297,1,0,0,0,295,293,1,0,0,0,295,296,
  	1,0,0,0,296,298,1,0,0,0,297,295,1,0,0,0,298,299,3,50,25,0,299,43,1,0,
  	0,0,300,301,3,34,17,0,301,45,1,0,0,0,302,306,3,36,18,0,303,306,3,42,21,
  	0,304,306,3,44,22,0,305,302,1,0,0,0,305,303,1,0,0,0,305,304,1,0,0,0,306,
  	310,1,0,0,0,307,309,5,24,0,0,308,307,1,0,0,0,309,312,1,0,0,0,310,308,
  	1,0,0,0,310,311,1,0,0,0,311,313,1,0,0,0,312,310,1,0,0,0,313,314,5,17,
  	0,0,314,47,1,0,0,0,315,319,3,46,23,0,316,318,5,24,0,0,317,316,1,0,0,0,
  	318,321,1,0,0,0,319,317,1,0,0,0,319,320,1,0,0,0,320,323,1,0,0,0,321,319,
  	1,0,0,0,322,315,1,0,0,0,323,326,1,0,0,0,324,322,1,0,0,0,324,325,1,0,0,
  	0,325,327,1,0,0,0,326,324,1,0,0,0,327,328,3,34,17,0,328,49,1,0,0,0,329,
  	333,5,10,0,0,330,332,5,24,0,0,331,330,1,0,0,0,332,335,1,0,0,0,333,331,
  	1,0,0,0,333,334,1,0,0,0,334,336,1,0,0,0,335,333,1,0,0,0,336,340,3,48,
  	24,0,337,339,5,24,0,0,338,337,1,0,0,0,339,342,1,0,0,0,340,338,1,0,0,0,
  	340,341,1,0,0,0,341,343,1,0,0,0,342,340,1,0,0,0,343,344,5,11,0,0,344,
  	51,1,0,0,0,345,349,5,3,0,0,346,348,5,24,0,0,347,346,1,0,0,0,348,351,1,
  	0,0,0,349,347,1,0,0,0,349,350,1,0,0,0,350,352,1,0,0,0,351,349,1,0,0,0,
  	352,356,3,48,24,0,353,355,5,24,0,0,354,353,1,0,0,0,355,358,1,0,0,0,356,
  	354,1,0,0,0,356,357,1,0,0,0,357,359,1,0,0,0,358,356,1,0,0,0,359,360,5,
  	9,0,0,360,53,1,0,0,0,361,362,5,3,0,0,362,366,5,7,0,0,363,365,5,24,0,0,
  	364,363,1,0,0,0,365,368,1,0,0,0,366,364,1,0,0,0,366,367,1,0,0,0,367,369,
  	1,0,0,0,368,366,1,0,0,0,369,373,3,48,24,0,370,372,5,24,0,0,371,370,1,
  	0,0,0,372,375,1,0,0,0,373,371,1,0,0,0,373,374,1,0,0,0,374,376,1,0,0,0,
  	375,373,1,0,0,0,376,377,5,9,0,0,377,55,1,0,0,0,378,379,5,3,0,0,379,380,
  	5,8,0,0,380,384,5,8,0,0,381,383,5,24,0,0,382,381,1,0,0,0,383,386,1,0,
  	0,0,384,382,1,0,0,0,384,385,1,0,0,0,385,387,1,0,0,0,386,384,1,0,0,0,387,
  	388,5,9,0,0,388,57,1,0,0,0,389,390,3,54,27,0,390,391,3,64,32,0,391,392,
  	3,56,28,0,392,59,1,0,0,0,393,396,3,52,26,0,394,396,3,58,29,0,395,393,
  	1,0,0,0,395,394,1,0,0,0,396,61,1,0,0,0,397,399,7,3,0,0,398,397,1,0,0,
  	0,399,400,1,0,0,0,400,398,1,0,0,0,400,401,1,0,0,0,401,63,1,0,0,0,402,
  	405,3,62,31,0,403,405,3,60,30,0,404,402,1,0,0,0,404,403,1,0,0,0,405,408,
  	1,0,0,0,406,404,1,0,0,0,406,407,1,0,0,0,407,65,1,0,0,0,408,406,1,0,0,
  	0,409,411,5,24,0,0,410,409,1,0,0,0,411,414,1,0,0,0,412,410,1,0,0,0,412,
  	413,1,0,0,0,413,415,1,0,0,0,414,412,1,0,0,0,415,419,3,48,24,0,416,418,
  	5,24,0,0,417,416,1,0,0,0,418,421,1,0,0,0,419,417,1,0,0,0,419,420,1,0,
  	0,0,420,422,1,0,0,0,421,419,1,0,0,0,422,423,5,0,0,1,423,67,1,0,0,0,424,
  	425,3,64,32,0,425,426,5,0,0,1,426,69,1,0,0,0,54,80,86,88,95,102,117,121,
  	124,129,134,138,144,147,152,157,162,171,175,184,190,197,202,207,214,221,
  	228,234,241,248,255,260,264,269,279,283,288,295,305,310,319,324,333,340,
  	349,356,366,373,384,395,400,404,406,412,419
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
    setState(70);
    match(StringInterpolatorParser::DOT);
    setState(71);
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
    setState(73);
    match(StringInterpolatorParser::DOT);
    setState(74);
    match(StringInterpolatorParser::OPENB);
    setState(75);
    match(StringInterpolatorParser::INT);
    setState(76);
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
    setState(80);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(78);
      property_name();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(79);
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
    setState(88);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(82);
      match(StringInterpolatorParser::DOT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(84); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(83);
        property_item();
        setState(86); 
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

//----------------- Variable_referenceContext ------------------------------------------------------------------

StringInterpolatorParser::Variable_referenceContext::Variable_referenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Variable_referenceContext::DOLLAR() {
  return getToken(StringInterpolatorParser::DOLLAR, 0);
}

tree::TerminalNode* StringInterpolatorParser::Variable_referenceContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

tree::TerminalNode* StringInterpolatorParser::Variable_referenceContext::INT() {
  return getToken(StringInterpolatorParser::INT, 0);
}

std::vector<StringInterpolatorParser::Property_itemContext *> StringInterpolatorParser::Variable_referenceContext::property_item() {
  return getRuleContexts<StringInterpolatorParser::Property_itemContext>();
}

StringInterpolatorParser::Property_itemContext* StringInterpolatorParser::Variable_referenceContext::property_item(size_t i) {
  return getRuleContext<StringInterpolatorParser::Property_itemContext>(i);
}


size_t StringInterpolatorParser::Variable_referenceContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleVariable_reference;
}


std::any StringInterpolatorParser::Variable_referenceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitVariable_reference(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Variable_referenceContext* StringInterpolatorParser::variable_reference() {
  Variable_referenceContext *_localctx = _tracker.createInstance<Variable_referenceContext>(_ctx, getState());
  enterRule(_localctx, 8, StringInterpolatorParser::RuleVariable_reference);
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
    setState(90);
    match(StringInterpolatorParser::DOLLAR);
    setState(91);
    _la = _input->LA(1);
    if (!(_la == StringInterpolatorParser::INT

    || _la == StringInterpolatorParser::ID)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(95);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::DOT) {
      setState(92);
      property_item();
      setState(97);
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
  enterRule(_localctx, 10, StringInterpolatorParser::RuleString);
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
    setState(98);
    match(StringInterpolatorParser::STRING_START);
    setState(102);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::STRING_TEXT

    || _la == StringInterpolatorParser::STRING_ESCAPE) {
      setState(99);
      _la = _input->LA(1);
      if (!(_la == StringInterpolatorParser::STRING_TEXT

      || _la == StringInterpolatorParser::STRING_ESCAPE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(104);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(105);
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
  enterRule(_localctx, 12, StringInterpolatorParser::RuleInteger);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(107);
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
  enterRule(_localctx, 14, StringInterpolatorParser::RuleFloat);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
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
  enterRule(_localctx, 16, StringInterpolatorParser::RuleBoolean);
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
    setState(111);
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
  enterRule(_localctx, 18, StringInterpolatorParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(117);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::STRING_START: {
        enterOuterAlt(_localctx, 1);
        setState(113);
        string();
        break;
      }

      case StringInterpolatorParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(114);
        integer();
        break;
      }

      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(115);
        float_();
        break;
      }

      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE: {
        enterOuterAlt(_localctx, 4);
        setState(116);
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

StringInterpolatorParser::Expr_blockContext* StringInterpolatorParser::ArgumentContext::expr_block() {
  return getRuleContext<StringInterpolatorParser::Expr_blockContext>(0);
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
  enterRule(_localctx, 20, StringInterpolatorParser::RuleArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::DOT:
      case StringInterpolatorParser::OPENB:
      case StringInterpolatorParser::DOLLAR:
      case StringInterpolatorParser::AT:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT:
      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(119);
        expr_item();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        enterOuterAlt(_localctx, 2);
        setState(120);
        expr_block();
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
  enterRule(_localctx, 22, StringInterpolatorParser::RuleArg_list);
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
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 243864688) != 0)) {
      setState(123);
      argument();
    }
    setState(134);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(127); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(126);
          match(StringInterpolatorParser::WS);
          setState(129); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == StringInterpolatorParser::WS);
        setState(131);
        argument(); 
      }
      setState(136);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
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

tree::TerminalNode* StringInterpolatorParser::FuncContext::AT() {
  return getToken(StringInterpolatorParser::AT, 0);
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
  enterRule(_localctx, 24, StringInterpolatorParser::RuleFunc);
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
    setState(138);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::AT) {
      setState(137);
      match(StringInterpolatorParser::AT);
    }
    setState(140);
    match(StringInterpolatorParser::ID);
    setState(147);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(142); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(141);
                match(StringInterpolatorParser::WS);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(144); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(146);
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

StringInterpolatorParser::Expr_itemContext* StringInterpolatorParser::Array_itemContext::expr_item() {
  return getRuleContext<StringInterpolatorParser::Expr_itemContext>(0);
}

StringInterpolatorParser::Expr_blockContext* StringInterpolatorParser::Array_itemContext::expr_block() {
  return getRuleContext<StringInterpolatorParser::Expr_blockContext>(0);
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
  enterRule(_localctx, 26, StringInterpolatorParser::RuleArray_item);
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
    setState(152);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(149);
      match(StringInterpolatorParser::WS);
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(157);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::DOT:
      case StringInterpolatorParser::OPENB:
      case StringInterpolatorParser::DOLLAR:
      case StringInterpolatorParser::AT:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT:
      case StringInterpolatorParser::ID: {
        setState(155);
        expr_item();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        setState(156);
        expr_block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(159);
      match(StringInterpolatorParser::WS);
      setState(164);
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
  enterRule(_localctx, 28, StringInterpolatorParser::RuleArray);
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
    setState(165);
    match(StringInterpolatorParser::OPENB);
    setState(171);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(166);
        array_item();
        setState(167);
        match(StringInterpolatorParser::COMMA); 
      }
      setState(173);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
    setState(175);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 260641904) != 0)) {
      setState(174);
      array_item();
    }
    setState(177);
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

StringInterpolatorParser::Variable_referenceContext* StringInterpolatorParser::Expr_itemContext::variable_reference() {
  return getRuleContext<StringInterpolatorParser::Variable_referenceContext>(0);
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
  enterRule(_localctx, 30, StringInterpolatorParser::RuleExpr_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(184);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(179);
        literal();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(180);
        property();
        break;
      }

      case StringInterpolatorParser::AT:
      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(181);
        func();
        break;
      }

      case StringInterpolatorParser::OPENB: {
        enterOuterAlt(_localctx, 4);
        setState(182);
        array();
        break;
      }

      case StringInterpolatorParser::DOLLAR: {
        enterOuterAlt(_localctx, 5);
        setState(183);
        variable_reference();
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

std::vector<StringInterpolatorParser::Expr_itemContext *> StringInterpolatorParser::Piped_expressionContext::expr_item() {
  return getRuleContexts<StringInterpolatorParser::Expr_itemContext>();
}

StringInterpolatorParser::Expr_itemContext* StringInterpolatorParser::Piped_expressionContext::expr_item(size_t i) {
  return getRuleContext<StringInterpolatorParser::Expr_itemContext>(i);
}

tree::TerminalNode* StringInterpolatorParser::Piped_expressionContext::PIPE() {
  return getToken(StringInterpolatorParser::PIPE, 0);
}

StringInterpolatorParser::Piped_expressionContext* StringInterpolatorParser::Piped_expressionContext::piped_expression() {
  return getRuleContext<StringInterpolatorParser::Piped_expressionContext>(0);
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
  enterRule(_localctx, 32, StringInterpolatorParser::RulePiped_expression);
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
    setState(186);
    expr_item();
    setState(190);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(187);
      match(StringInterpolatorParser::WS);
      setState(192);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(193);
    match(StringInterpolatorParser::PIPE);
    setState(197);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(194);
      match(StringInterpolatorParser::WS);
      setState(199);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(202);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      setState(200);
      expr_item();
      break;
    }

    case 2: {
      setState(201);
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

StringInterpolatorParser::Expr_blockContext* StringInterpolatorParser::ExprContext::expr_block() {
  return getRuleContext<StringInterpolatorParser::Expr_blockContext>(0);
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
  enterRule(_localctx, 34, StringInterpolatorParser::RuleExpr);

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
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(204);
      expr_item();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(205);
      piped_expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(206);
      expr_block();
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

//----------------- Assign_stmtContext ------------------------------------------------------------------

StringInterpolatorParser::Assign_stmtContext::Assign_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Assign_stmtContext::DOLLAR() {
  return getToken(StringInterpolatorParser::DOLLAR, 0);
}

tree::TerminalNode* StringInterpolatorParser::Assign_stmtContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

tree::TerminalNode* StringInterpolatorParser::Assign_stmtContext::EQUAL() {
  return getToken(StringInterpolatorParser::EQUAL, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Assign_stmtContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Assign_stmtContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Assign_stmtContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Assign_stmtContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleAssign_stmt;
}


std::any StringInterpolatorParser::Assign_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitAssign_stmt(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Assign_stmtContext* StringInterpolatorParser::assign_stmt() {
  Assign_stmtContext *_localctx = _tracker.createInstance<Assign_stmtContext>(_ctx, getState());
  enterRule(_localctx, 36, StringInterpolatorParser::RuleAssign_stmt);
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
    match(StringInterpolatorParser::DOLLAR);
    setState(210);
    match(StringInterpolatorParser::ID);
    setState(214);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(211);
      match(StringInterpolatorParser::WS);
      setState(216);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(217);
    match(StringInterpolatorParser::EQUAL);
    setState(221);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(218);
      match(StringInterpolatorParser::WS);
      setState(223);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(224);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_parameterContext ------------------------------------------------------------------

StringInterpolatorParser::Function_parameterContext::Function_parameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Function_parameterContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

tree::TerminalNode* StringInterpolatorParser::Function_parameterContext::QUESTION() {
  return getToken(StringInterpolatorParser::QUESTION, 0);
}


size_t StringInterpolatorParser::Function_parameterContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleFunction_parameter;
}


std::any StringInterpolatorParser::Function_parameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitFunction_parameter(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Function_parameterContext* StringInterpolatorParser::function_parameter() {
  Function_parameterContext *_localctx = _tracker.createInstance<Function_parameterContext>(_ctx, getState());
  enterRule(_localctx, 38, StringInterpolatorParser::RuleFunction_parameter);
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
    setState(226);
    match(StringInterpolatorParser::ID);
    setState(228);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::QUESTION) {
      setState(227);
      match(StringInterpolatorParser::QUESTION);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_parametersContext ------------------------------------------------------------------

StringInterpolatorParser::Function_parametersContext::Function_parametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Function_parametersContext::OPENP() {
  return getToken(StringInterpolatorParser::OPENP, 0);
}

tree::TerminalNode* StringInterpolatorParser::Function_parametersContext::CLOSEP() {
  return getToken(StringInterpolatorParser::CLOSEP, 0);
}

std::vector<StringInterpolatorParser::Function_parameterContext *> StringInterpolatorParser::Function_parametersContext::function_parameter() {
  return getRuleContexts<StringInterpolatorParser::Function_parameterContext>();
}

StringInterpolatorParser::Function_parameterContext* StringInterpolatorParser::Function_parametersContext::function_parameter(size_t i) {
  return getRuleContext<StringInterpolatorParser::Function_parameterContext>(i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Function_parametersContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Function_parametersContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Function_parametersContext::COMMA() {
  return getTokens(StringInterpolatorParser::COMMA);
}

tree::TerminalNode* StringInterpolatorParser::Function_parametersContext::COMMA(size_t i) {
  return getToken(StringInterpolatorParser::COMMA, i);
}


size_t StringInterpolatorParser::Function_parametersContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleFunction_parameters;
}


std::any StringInterpolatorParser::Function_parametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitFunction_parameters(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Function_parametersContext* StringInterpolatorParser::function_parameters() {
  Function_parametersContext *_localctx = _tracker.createInstance<Function_parametersContext>(_ctx, getState());
  enterRule(_localctx, 40, StringInterpolatorParser::RuleFunction_parameters);
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
    setState(230);
    match(StringInterpolatorParser::OPENP);
    setState(234);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(231);
      match(StringInterpolatorParser::WS);
      setState(236);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

    setState(237);
    function_parameter();
    setState(241);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(238);
        match(StringInterpolatorParser::WS); 
      }
      setState(243);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    }
    setState(260);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(244);
        match(StringInterpolatorParser::COMMA);
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
        function_parameter();
        setState(255);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(252);
            match(StringInterpolatorParser::WS); 
          }
          setState(257);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
        } 
      }
      setState(262);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
    setState(264);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::COMMA) {
      setState(263);
      match(StringInterpolatorParser::COMMA);
    }
    setState(269);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(266);
      match(StringInterpolatorParser::WS);
      setState(271);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(272);
    match(StringInterpolatorParser::CLOSEP);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_def_stmtContext ------------------------------------------------------------------

StringInterpolatorParser::Function_def_stmtContext::Function_def_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Function_def_stmtContext::AT() {
  return getToken(StringInterpolatorParser::AT, 0);
}

tree::TerminalNode* StringInterpolatorParser::Function_def_stmtContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

tree::TerminalNode* StringInterpolatorParser::Function_def_stmtContext::ARROW() {
  return getToken(StringInterpolatorParser::ARROW, 0);
}

StringInterpolatorParser::Expr_blockContext* StringInterpolatorParser::Function_def_stmtContext::expr_block() {
  return getRuleContext<StringInterpolatorParser::Expr_blockContext>(0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Function_def_stmtContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Function_def_stmtContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}

StringInterpolatorParser::Function_parametersContext* StringInterpolatorParser::Function_def_stmtContext::function_parameters() {
  return getRuleContext<StringInterpolatorParser::Function_parametersContext>(0);
}


size_t StringInterpolatorParser::Function_def_stmtContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleFunction_def_stmt;
}


std::any StringInterpolatorParser::Function_def_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitFunction_def_stmt(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Function_def_stmtContext* StringInterpolatorParser::function_def_stmt() {
  Function_def_stmtContext *_localctx = _tracker.createInstance<Function_def_stmtContext>(_ctx, getState());
  enterRule(_localctx, 42, StringInterpolatorParser::RuleFunction_def_stmt);
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
    setState(274);
    match(StringInterpolatorParser::AT);
    setState(275);
    match(StringInterpolatorParser::ID);
    setState(279);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(276);
        match(StringInterpolatorParser::WS); 
      }
      setState(281);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
    setState(283);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::OPENP) {
      setState(282);
      function_parameters();
    }
    setState(288);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(285);
      match(StringInterpolatorParser::WS);
      setState(290);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(291);
    match(StringInterpolatorParser::ARROW);
    setState(295);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(292);
      match(StringInterpolatorParser::WS);
      setState(297);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(298);
    expr_block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Simple_expr_stmtContext ------------------------------------------------------------------

StringInterpolatorParser::Simple_expr_stmtContext::Simple_expr_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Simple_expr_stmtContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}


size_t StringInterpolatorParser::Simple_expr_stmtContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleSimple_expr_stmt;
}


std::any StringInterpolatorParser::Simple_expr_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitSimple_expr_stmt(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Simple_expr_stmtContext* StringInterpolatorParser::simple_expr_stmt() {
  Simple_expr_stmtContext *_localctx = _tracker.createInstance<Simple_expr_stmtContext>(_ctx, getState());
  enterRule(_localctx, 44, StringInterpolatorParser::RuleSimple_expr_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(300);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr_stmtContext ------------------------------------------------------------------

StringInterpolatorParser::Expr_stmtContext::Expr_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Expr_stmtContext::SEMICOLON() {
  return getToken(StringInterpolatorParser::SEMICOLON, 0);
}

StringInterpolatorParser::Assign_stmtContext* StringInterpolatorParser::Expr_stmtContext::assign_stmt() {
  return getRuleContext<StringInterpolatorParser::Assign_stmtContext>(0);
}

StringInterpolatorParser::Function_def_stmtContext* StringInterpolatorParser::Expr_stmtContext::function_def_stmt() {
  return getRuleContext<StringInterpolatorParser::Function_def_stmtContext>(0);
}

StringInterpolatorParser::Simple_expr_stmtContext* StringInterpolatorParser::Expr_stmtContext::simple_expr_stmt() {
  return getRuleContext<StringInterpolatorParser::Simple_expr_stmtContext>(0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Expr_stmtContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Expr_stmtContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Expr_stmtContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleExpr_stmt;
}


std::any StringInterpolatorParser::Expr_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitExpr_stmt(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Expr_stmtContext* StringInterpolatorParser::expr_stmt() {
  Expr_stmtContext *_localctx = _tracker.createInstance<Expr_stmtContext>(_ctx, getState());
  enterRule(_localctx, 46, StringInterpolatorParser::RuleExpr_stmt);
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
    setState(305);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      setState(302);
      assign_stmt();
      break;
    }

    case 2: {
      setState(303);
      function_def_stmt();
      break;
    }

    case 3: {
      setState(304);
      simple_expr_stmt();
      break;
    }

    default:
      break;
    }
    setState(310);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(307);
      match(StringInterpolatorParser::WS);
      setState(312);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(313);
    match(StringInterpolatorParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr_block_contentsContext ------------------------------------------------------------------

StringInterpolatorParser::Expr_block_contentsContext::Expr_block_contentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Expr_block_contentsContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

std::vector<StringInterpolatorParser::Expr_stmtContext *> StringInterpolatorParser::Expr_block_contentsContext::expr_stmt() {
  return getRuleContexts<StringInterpolatorParser::Expr_stmtContext>();
}

StringInterpolatorParser::Expr_stmtContext* StringInterpolatorParser::Expr_block_contentsContext::expr_stmt(size_t i) {
  return getRuleContext<StringInterpolatorParser::Expr_stmtContext>(i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Expr_block_contentsContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Expr_block_contentsContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Expr_block_contentsContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleExpr_block_contents;
}


std::any StringInterpolatorParser::Expr_block_contentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitExpr_block_contents(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Expr_block_contentsContext* StringInterpolatorParser::expr_block_contents() {
  Expr_block_contentsContext *_localctx = _tracker.createInstance<Expr_block_contentsContext>(_ctx, getState());
  enterRule(_localctx, 48, StringInterpolatorParser::RuleExpr_block_contents);
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
    setState(324);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(315);
        expr_stmt();
        setState(319);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == StringInterpolatorParser::WS) {
          setState(316);
          match(StringInterpolatorParser::WS);
          setState(321);
          _errHandler->sync(this);
          _la = _input->LA(1);
        } 
      }
      setState(326);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    }
    setState(327);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expr_blockContext ------------------------------------------------------------------

StringInterpolatorParser::Expr_blockContext::Expr_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Expr_blockContext::OPENP() {
  return getToken(StringInterpolatorParser::OPENP, 0);
}

StringInterpolatorParser::Expr_block_contentsContext* StringInterpolatorParser::Expr_blockContext::expr_block_contents() {
  return getRuleContext<StringInterpolatorParser::Expr_block_contentsContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::Expr_blockContext::CLOSEP() {
  return getToken(StringInterpolatorParser::CLOSEP, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Expr_blockContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Expr_blockContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Expr_blockContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleExpr_block;
}


std::any StringInterpolatorParser::Expr_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitExpr_block(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Expr_blockContext* StringInterpolatorParser::expr_block() {
  Expr_blockContext *_localctx = _tracker.createInstance<Expr_blockContext>(_ctx, getState());
  enterRule(_localctx, 50, StringInterpolatorParser::RuleExpr_block);
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
    setState(329);
    match(StringInterpolatorParser::OPENP);
    setState(333);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(330);
      match(StringInterpolatorParser::WS);
      setState(335);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(336);
    expr_block_contents();
    setState(340);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(337);
      match(StringInterpolatorParser::WS);
      setState(342);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(343);
    match(StringInterpolatorParser::CLOSEP);
   
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

StringInterpolatorParser::Expr_block_contentsContext* StringInterpolatorParser::EvalContext::expr_block_contents() {
  return getRuleContext<StringInterpolatorParser::Expr_block_contentsContext>(0);
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
  enterRule(_localctx, 52, StringInterpolatorParser::RuleEval);
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
    setState(345);
    match(StringInterpolatorParser::OPEN);
    setState(349);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(346);
      match(StringInterpolatorParser::WS);
      setState(351);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(352);
    expr_block_contents();
    setState(356);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(353);
      match(StringInterpolatorParser::WS);
      setState(358);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(359);
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

StringInterpolatorParser::Expr_block_contentsContext* StringInterpolatorParser::Loop_startContext::expr_block_contents() {
  return getRuleContext<StringInterpolatorParser::Expr_block_contentsContext>(0);
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
  enterRule(_localctx, 54, StringInterpolatorParser::RuleLoop_start);
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
    setState(361);
    match(StringInterpolatorParser::OPEN);
    setState(362);
    match(StringInterpolatorParser::HASH);
    setState(366);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(363);
      match(StringInterpolatorParser::WS);
      setState(368);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(369);
    expr_block_contents();
    setState(373);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(370);
      match(StringInterpolatorParser::WS);
      setState(375);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(376);
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
  enterRule(_localctx, 56, StringInterpolatorParser::RuleLoop_end);
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
    setState(378);
    match(StringInterpolatorParser::OPEN);
    setState(379);
    match(StringInterpolatorParser::SLASH);
    setState(380);
    match(StringInterpolatorParser::SLASH);
    setState(384);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(381);
      match(StringInterpolatorParser::WS);
      setState(386);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(387);
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
  enterRule(_localctx, 58, StringInterpolatorParser::RuleLoop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(389);
    loop_start();
    setState(390);
    interpolated_str();
    setState(391);
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
  enterRule(_localctx, 60, StringInterpolatorParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(395);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(393);
      eval();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(394);
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
  enterRule(_localctx, 62, StringInterpolatorParser::RuleNormal);
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
    setState(398); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(397);
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
      setState(400); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
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
  enterRule(_localctx, 64, StringInterpolatorParser::RuleInterpolated_str);

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
    setState(406);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(404);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case StringInterpolatorParser::NORMAL_TEXT:
          case StringInterpolatorParser::NORMAL_ESCAPE: {
            setState(402);
            normal();
            break;
          }

          case StringInterpolatorParser::OPEN: {
            setState(403);
            stmt();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(408);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx);
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

StringInterpolatorParser::Expr_block_contentsContext* StringInterpolatorParser::Expression_programContext::expr_block_contents() {
  return getRuleContext<StringInterpolatorParser::Expr_block_contentsContext>(0);
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
  enterRule(_localctx, 66, StringInterpolatorParser::RuleExpression_program);
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
    setState(412);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(409);
      match(StringInterpolatorParser::WS);
      setState(414);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(415);
    expr_block_contents();
    setState(419);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(416);
      match(StringInterpolatorParser::WS);
      setState(421);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(422);
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
  enterRule(_localctx, 68, StringInterpolatorParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(424);
    interpolated_str();
    setState(425);
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
