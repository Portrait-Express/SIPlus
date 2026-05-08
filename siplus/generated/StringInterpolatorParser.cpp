
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
      "string", "integer", "float", "boolean", "null", "literal", "argument", 
      "arg_list", "func", "array_item", "array", "expr_item", "piped_expression", 
      "expr", "assign_stmt", "function_parameter", "function_parameters", 
      "function_def_stmt", "simple_expr_stmt", "expr_stmt", "expr_block_contents", 
      "expr_block", "eval", "loop_start", "loop_end", "loop", "stmt", "normal", 
      "interpolated_str", "expression_program", "program"
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
  	4,1,35,457,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,3,2,83,8,2,1,3,1,3,4,3,87,
  	8,3,11,3,12,3,88,3,3,91,8,3,1,4,1,4,1,4,5,4,96,8,4,10,4,12,4,99,9,4,1,
  	5,1,5,5,5,103,8,5,10,5,12,5,106,9,5,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,
  	9,1,9,1,10,1,10,1,10,1,10,1,10,3,10,123,8,10,1,11,1,11,3,11,127,8,11,
  	1,12,3,12,130,8,12,1,12,4,12,133,8,12,11,12,12,12,134,1,12,5,12,138,8,
  	12,10,12,12,12,141,9,12,1,13,3,13,144,8,13,1,13,1,13,4,13,148,8,13,11,
  	13,12,13,149,1,13,3,13,153,8,13,1,14,5,14,156,8,14,10,14,12,14,159,9,
  	14,1,14,1,14,3,14,163,8,14,1,14,5,14,166,8,14,10,14,12,14,169,9,14,1,
  	15,1,15,1,15,1,15,5,15,175,8,15,10,15,12,15,178,9,15,1,15,3,15,181,8,
  	15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,3,16,190,8,16,1,17,1,17,5,17,194,
  	8,17,10,17,12,17,197,9,17,1,17,1,17,5,17,201,8,17,10,17,12,17,204,9,17,
  	1,17,1,17,3,17,208,8,17,1,18,1,18,1,18,3,18,213,8,18,1,19,1,19,4,19,217,
  	8,19,11,19,12,19,218,3,19,221,8,19,1,19,1,19,4,19,225,8,19,11,19,12,19,
  	226,3,19,229,8,19,1,19,1,19,4,19,233,8,19,11,19,12,19,234,3,19,237,8,
  	19,1,19,1,19,1,19,5,19,242,8,19,10,19,12,19,245,9,19,1,19,1,19,5,19,249,
  	8,19,10,19,12,19,252,9,19,1,19,1,19,1,20,1,20,3,20,258,8,20,1,21,1,21,
  	5,21,262,8,21,10,21,12,21,265,9,21,1,21,1,21,5,21,269,8,21,10,21,12,21,
  	272,9,21,1,21,1,21,5,21,276,8,21,10,21,12,21,279,9,21,1,21,1,21,5,21,
  	283,8,21,10,21,12,21,286,9,21,5,21,288,8,21,10,21,12,21,291,9,21,1,21,
  	3,21,294,8,21,1,21,5,21,297,8,21,10,21,12,21,300,9,21,1,21,1,21,1,22,
  	1,22,1,22,5,22,307,8,22,10,22,12,22,310,9,22,1,22,3,22,313,8,22,1,22,
  	5,22,316,8,22,10,22,12,22,319,9,22,1,22,1,22,5,22,323,8,22,10,22,12,22,
  	326,9,22,1,22,1,22,1,23,1,23,1,24,1,24,1,24,3,24,335,8,24,1,24,5,24,338,
  	8,24,10,24,12,24,341,9,24,1,24,1,24,1,25,1,25,5,25,347,8,25,10,25,12,
  	25,350,9,25,5,25,352,8,25,10,25,12,25,355,9,25,1,25,1,25,1,26,1,26,5,
  	26,361,8,26,10,26,12,26,364,9,26,1,26,1,26,5,26,368,8,26,10,26,12,26,
  	371,9,26,1,26,1,26,1,27,1,27,5,27,377,8,27,10,27,12,27,380,9,27,1,27,
  	1,27,5,27,384,8,27,10,27,12,27,387,9,27,1,27,1,27,1,28,1,28,1,28,5,28,
  	394,8,28,10,28,12,28,397,9,28,1,28,1,28,5,28,401,8,28,10,28,12,28,404,
  	9,28,1,28,1,28,1,29,1,29,1,29,1,29,5,29,412,8,29,10,29,12,29,415,9,29,
  	1,29,1,29,1,30,1,30,1,30,1,30,1,31,1,31,3,31,425,8,31,1,32,4,32,428,8,
  	32,11,32,12,32,429,1,33,1,33,5,33,434,8,33,10,33,12,33,437,9,33,1,34,
  	5,34,440,8,34,10,34,12,34,443,9,34,1,34,1,34,5,34,447,8,34,10,34,12,34,
  	450,9,34,1,34,1,34,1,35,1,35,1,35,1,35,0,0,36,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,
  	66,68,70,0,3,1,0,33,34,1,0,4,5,1,0,1,2,488,0,72,1,0,0,0,2,75,1,0,0,0,
  	4,82,1,0,0,0,6,90,1,0,0,0,8,92,1,0,0,0,10,100,1,0,0,0,12,109,1,0,0,0,
  	14,111,1,0,0,0,16,113,1,0,0,0,18,115,1,0,0,0,20,122,1,0,0,0,22,126,1,
  	0,0,0,24,129,1,0,0,0,26,143,1,0,0,0,28,157,1,0,0,0,30,170,1,0,0,0,32,
  	189,1,0,0,0,34,191,1,0,0,0,36,212,1,0,0,0,38,236,1,0,0,0,40,255,1,0,0,
  	0,42,259,1,0,0,0,44,303,1,0,0,0,46,329,1,0,0,0,48,334,1,0,0,0,50,353,
  	1,0,0,0,52,358,1,0,0,0,54,374,1,0,0,0,56,390,1,0,0,0,58,407,1,0,0,0,60,
  	418,1,0,0,0,62,424,1,0,0,0,64,427,1,0,0,0,66,435,1,0,0,0,68,441,1,0,0,
  	0,70,453,1,0,0,0,72,73,5,10,0,0,73,74,5,31,0,0,74,1,1,0,0,0,75,76,5,10,
  	0,0,76,77,5,16,0,0,77,78,5,29,0,0,78,79,5,17,0,0,79,3,1,0,0,0,80,83,3,
  	0,0,0,81,83,3,2,1,0,82,80,1,0,0,0,82,81,1,0,0,0,83,5,1,0,0,0,84,91,5,
  	10,0,0,85,87,3,4,2,0,86,85,1,0,0,0,87,88,1,0,0,0,88,86,1,0,0,0,88,89,
  	1,0,0,0,89,91,1,0,0,0,90,84,1,0,0,0,90,86,1,0,0,0,91,7,1,0,0,0,92,93,
  	5,20,0,0,93,97,5,31,0,0,94,96,3,4,2,0,95,94,1,0,0,0,96,99,1,0,0,0,97,
  	95,1,0,0,0,97,98,1,0,0,0,98,9,1,0,0,0,99,97,1,0,0,0,100,104,5,27,0,0,
  	101,103,7,0,0,0,102,101,1,0,0,0,103,106,1,0,0,0,104,102,1,0,0,0,104,105,
  	1,0,0,0,105,107,1,0,0,0,106,104,1,0,0,0,107,108,5,35,0,0,108,11,1,0,0,
  	0,109,110,5,29,0,0,110,13,1,0,0,0,111,112,5,30,0,0,112,15,1,0,0,0,113,
  	114,7,1,0,0,114,17,1,0,0,0,115,116,5,6,0,0,116,19,1,0,0,0,117,123,3,10,
  	5,0,118,123,3,12,6,0,119,123,3,14,7,0,120,123,3,16,8,0,121,123,3,18,9,
  	0,122,117,1,0,0,0,122,118,1,0,0,0,122,119,1,0,0,0,122,120,1,0,0,0,122,
  	121,1,0,0,0,123,21,1,0,0,0,124,127,3,32,16,0,125,127,3,52,26,0,126,124,
  	1,0,0,0,126,125,1,0,0,0,127,23,1,0,0,0,128,130,3,22,11,0,129,128,1,0,
  	0,0,129,130,1,0,0,0,130,139,1,0,0,0,131,133,5,28,0,0,132,131,1,0,0,0,
  	133,134,1,0,0,0,134,132,1,0,0,0,134,135,1,0,0,0,135,136,1,0,0,0,136,138,
  	3,22,11,0,137,132,1,0,0,0,138,141,1,0,0,0,139,137,1,0,0,0,139,140,1,0,
  	0,0,140,25,1,0,0,0,141,139,1,0,0,0,142,144,5,23,0,0,143,142,1,0,0,0,143,
  	144,1,0,0,0,144,145,1,0,0,0,145,152,5,31,0,0,146,148,5,28,0,0,147,146,
  	1,0,0,0,148,149,1,0,0,0,149,147,1,0,0,0,149,150,1,0,0,0,150,151,1,0,0,
  	0,151,153,3,24,12,0,152,147,1,0,0,0,152,153,1,0,0,0,153,27,1,0,0,0,154,
  	156,5,28,0,0,155,154,1,0,0,0,156,159,1,0,0,0,157,155,1,0,0,0,157,158,
  	1,0,0,0,158,162,1,0,0,0,159,157,1,0,0,0,160,163,3,32,16,0,161,163,3,52,
  	26,0,162,160,1,0,0,0,162,161,1,0,0,0,163,167,1,0,0,0,164,166,5,28,0,0,
  	165,164,1,0,0,0,166,169,1,0,0,0,167,165,1,0,0,0,167,168,1,0,0,0,168,29,
  	1,0,0,0,169,167,1,0,0,0,170,176,5,16,0,0,171,172,3,28,14,0,172,173,5,
  	18,0,0,173,175,1,0,0,0,174,171,1,0,0,0,175,178,1,0,0,0,176,174,1,0,0,
  	0,176,177,1,0,0,0,177,180,1,0,0,0,178,176,1,0,0,0,179,181,3,28,14,0,180,
  	179,1,0,0,0,180,181,1,0,0,0,181,182,1,0,0,0,182,183,5,17,0,0,183,31,1,
  	0,0,0,184,190,3,20,10,0,185,190,3,6,3,0,186,190,3,26,13,0,187,190,3,30,
  	15,0,188,190,3,8,4,0,189,184,1,0,0,0,189,185,1,0,0,0,189,186,1,0,0,0,
  	189,187,1,0,0,0,189,188,1,0,0,0,190,33,1,0,0,0,191,195,3,32,16,0,192,
  	194,5,28,0,0,193,192,1,0,0,0,194,197,1,0,0,0,195,193,1,0,0,0,195,196,
  	1,0,0,0,196,198,1,0,0,0,197,195,1,0,0,0,198,202,5,19,0,0,199,201,5,28,
  	0,0,200,199,1,0,0,0,201,204,1,0,0,0,202,200,1,0,0,0,202,203,1,0,0,0,203,
  	207,1,0,0,0,204,202,1,0,0,0,205,208,3,32,16,0,206,208,3,34,17,0,207,205,
  	1,0,0,0,207,206,1,0,0,0,208,35,1,0,0,0,209,213,3,32,16,0,210,213,3,34,
  	17,0,211,213,3,52,26,0,212,209,1,0,0,0,212,210,1,0,0,0,212,211,1,0,0,
  	0,213,37,1,0,0,0,214,216,5,8,0,0,215,217,5,28,0,0,216,215,1,0,0,0,217,
  	218,1,0,0,0,218,216,1,0,0,0,218,219,1,0,0,0,219,221,1,0,0,0,220,214,1,
  	0,0,0,220,221,1,0,0,0,221,228,1,0,0,0,222,224,5,9,0,0,223,225,5,28,0,
  	0,224,223,1,0,0,0,225,226,1,0,0,0,226,224,1,0,0,0,226,227,1,0,0,0,227,
  	229,1,0,0,0,228,222,1,0,0,0,228,229,1,0,0,0,229,230,1,0,0,0,230,232,5,
  	7,0,0,231,233,5,28,0,0,232,231,1,0,0,0,233,234,1,0,0,0,234,232,1,0,0,
  	0,234,235,1,0,0,0,235,237,1,0,0,0,236,220,1,0,0,0,236,237,1,0,0,0,237,
  	238,1,0,0,0,238,239,5,20,0,0,239,243,5,31,0,0,240,242,5,28,0,0,241,240,
  	1,0,0,0,242,245,1,0,0,0,243,241,1,0,0,0,243,244,1,0,0,0,244,246,1,0,0,
  	0,245,243,1,0,0,0,246,250,5,24,0,0,247,249,5,28,0,0,248,247,1,0,0,0,249,
  	252,1,0,0,0,250,248,1,0,0,0,250,251,1,0,0,0,251,253,1,0,0,0,252,250,1,
  	0,0,0,253,254,3,36,18,0,254,39,1,0,0,0,255,257,5,31,0,0,256,258,5,22,
  	0,0,257,256,1,0,0,0,257,258,1,0,0,0,258,41,1,0,0,0,259,263,5,14,0,0,260,
  	262,5,28,0,0,261,260,1,0,0,0,262,265,1,0,0,0,263,261,1,0,0,0,263,264,
  	1,0,0,0,264,266,1,0,0,0,265,263,1,0,0,0,266,270,3,40,20,0,267,269,5,28,
  	0,0,268,267,1,0,0,0,269,272,1,0,0,0,270,268,1,0,0,0,270,271,1,0,0,0,271,
  	289,1,0,0,0,272,270,1,0,0,0,273,277,5,18,0,0,274,276,5,28,0,0,275,274,
  	1,0,0,0,276,279,1,0,0,0,277,275,1,0,0,0,277,278,1,0,0,0,278,280,1,0,0,
  	0,279,277,1,0,0,0,280,284,3,40,20,0,281,283,5,28,0,0,282,281,1,0,0,0,
  	283,286,1,0,0,0,284,282,1,0,0,0,284,285,1,0,0,0,285,288,1,0,0,0,286,284,
  	1,0,0,0,287,273,1,0,0,0,288,291,1,0,0,0,289,287,1,0,0,0,289,290,1,0,0,
  	0,290,293,1,0,0,0,291,289,1,0,0,0,292,294,5,18,0,0,293,292,1,0,0,0,293,
  	294,1,0,0,0,294,298,1,0,0,0,295,297,5,28,0,0,296,295,1,0,0,0,297,300,
  	1,0,0,0,298,296,1,0,0,0,298,299,1,0,0,0,299,301,1,0,0,0,300,298,1,0,0,
  	0,301,302,5,15,0,0,302,43,1,0,0,0,303,304,5,23,0,0,304,308,5,31,0,0,305,
  	307,5,28,0,0,306,305,1,0,0,0,307,310,1,0,0,0,308,306,1,0,0,0,308,309,
  	1,0,0,0,309,312,1,0,0,0,310,308,1,0,0,0,311,313,3,42,21,0,312,311,1,0,
  	0,0,312,313,1,0,0,0,313,317,1,0,0,0,314,316,5,28,0,0,315,314,1,0,0,0,
  	316,319,1,0,0,0,317,315,1,0,0,0,317,318,1,0,0,0,318,320,1,0,0,0,319,317,
  	1,0,0,0,320,324,5,25,0,0,321,323,5,28,0,0,322,321,1,0,0,0,323,326,1,0,
  	0,0,324,322,1,0,0,0,324,325,1,0,0,0,325,327,1,0,0,0,326,324,1,0,0,0,327,
  	328,3,52,26,0,328,45,1,0,0,0,329,330,3,36,18,0,330,47,1,0,0,0,331,335,
  	3,38,19,0,332,335,3,44,22,0,333,335,3,46,23,0,334,331,1,0,0,0,334,332,
  	1,0,0,0,334,333,1,0,0,0,335,339,1,0,0,0,336,338,5,28,0,0,337,336,1,0,
  	0,0,338,341,1,0,0,0,339,337,1,0,0,0,339,340,1,0,0,0,340,342,1,0,0,0,341,
  	339,1,0,0,0,342,343,5,21,0,0,343,49,1,0,0,0,344,348,3,48,24,0,345,347,
  	5,28,0,0,346,345,1,0,0,0,347,350,1,0,0,0,348,346,1,0,0,0,348,349,1,0,
  	0,0,349,352,1,0,0,0,350,348,1,0,0,0,351,344,1,0,0,0,352,355,1,0,0,0,353,
  	351,1,0,0,0,353,354,1,0,0,0,354,356,1,0,0,0,355,353,1,0,0,0,356,357,3,
  	36,18,0,357,51,1,0,0,0,358,362,5,14,0,0,359,361,5,28,0,0,360,359,1,0,
  	0,0,361,364,1,0,0,0,362,360,1,0,0,0,362,363,1,0,0,0,363,365,1,0,0,0,364,
  	362,1,0,0,0,365,369,3,50,25,0,366,368,5,28,0,0,367,366,1,0,0,0,368,371,
  	1,0,0,0,369,367,1,0,0,0,369,370,1,0,0,0,370,372,1,0,0,0,371,369,1,0,0,
  	0,372,373,5,15,0,0,373,53,1,0,0,0,374,378,5,3,0,0,375,377,5,28,0,0,376,
  	375,1,0,0,0,377,380,1,0,0,0,378,376,1,0,0,0,378,379,1,0,0,0,379,381,1,
  	0,0,0,380,378,1,0,0,0,381,385,3,50,25,0,382,384,5,28,0,0,383,382,1,0,
  	0,0,384,387,1,0,0,0,385,383,1,0,0,0,385,386,1,0,0,0,386,388,1,0,0,0,387,
  	385,1,0,0,0,388,389,5,13,0,0,389,55,1,0,0,0,390,391,5,3,0,0,391,395,5,
  	11,0,0,392,394,5,28,0,0,393,392,1,0,0,0,394,397,1,0,0,0,395,393,1,0,0,
  	0,395,396,1,0,0,0,396,398,1,0,0,0,397,395,1,0,0,0,398,402,3,50,25,0,399,
  	401,5,28,0,0,400,399,1,0,0,0,401,404,1,0,0,0,402,400,1,0,0,0,402,403,
  	1,0,0,0,403,405,1,0,0,0,404,402,1,0,0,0,405,406,5,13,0,0,406,57,1,0,0,
  	0,407,408,5,3,0,0,408,409,5,12,0,0,409,413,5,12,0,0,410,412,5,28,0,0,
  	411,410,1,0,0,0,412,415,1,0,0,0,413,411,1,0,0,0,413,414,1,0,0,0,414,416,
  	1,0,0,0,415,413,1,0,0,0,416,417,5,13,0,0,417,59,1,0,0,0,418,419,3,56,
  	28,0,419,420,3,66,33,0,420,421,3,58,29,0,421,61,1,0,0,0,422,425,3,54,
  	27,0,423,425,3,60,30,0,424,422,1,0,0,0,424,423,1,0,0,0,425,63,1,0,0,0,
  	426,428,7,2,0,0,427,426,1,0,0,0,428,429,1,0,0,0,429,427,1,0,0,0,429,430,
  	1,0,0,0,430,65,1,0,0,0,431,434,3,64,32,0,432,434,3,62,31,0,433,431,1,
  	0,0,0,433,432,1,0,0,0,434,437,1,0,0,0,435,433,1,0,0,0,435,436,1,0,0,0,
  	436,67,1,0,0,0,437,435,1,0,0,0,438,440,5,28,0,0,439,438,1,0,0,0,440,443,
  	1,0,0,0,441,439,1,0,0,0,441,442,1,0,0,0,442,444,1,0,0,0,443,441,1,0,0,
  	0,444,448,3,50,25,0,445,447,5,28,0,0,446,445,1,0,0,0,447,450,1,0,0,0,
  	448,446,1,0,0,0,448,449,1,0,0,0,449,451,1,0,0,0,450,448,1,0,0,0,451,452,
  	5,0,0,1,452,69,1,0,0,0,453,454,3,66,33,0,454,455,5,0,0,1,455,71,1,0,0,
  	0,60,82,88,90,97,104,122,126,129,134,139,143,149,152,157,162,167,176,
  	180,189,195,202,207,212,218,220,226,228,234,236,243,250,257,263,270,277,
  	284,289,293,298,308,312,317,324,334,339,348,353,362,369,378,385,395,402,
  	413,424,429,433,435,441,448
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
    setState(72);
    match(StringInterpolatorParser::DOT);
    setState(73);
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
    setState(75);
    match(StringInterpolatorParser::DOT);
    setState(76);
    match(StringInterpolatorParser::OPENB);
    setState(77);
    match(StringInterpolatorParser::INT);
    setState(78);
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
    setState(82);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(80);
      property_name();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(81);
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
    setState(90);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(84);
      match(StringInterpolatorParser::DOT);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(86); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(85);
        property_item();
        setState(88); 
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
    setState(92);
    match(StringInterpolatorParser::DOLLAR);
    setState(93);
    match(StringInterpolatorParser::ID);
    setState(97);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::DOT) {
      setState(94);
      property_item();
      setState(99);
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
    setState(100);
    match(StringInterpolatorParser::STRING_START);
    setState(104);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::STRING_TEXT

    || _la == StringInterpolatorParser::STRING_ESCAPE) {
      setState(101);
      _la = _input->LA(1);
      if (!(_la == StringInterpolatorParser::STRING_TEXT

      || _la == StringInterpolatorParser::STRING_ESCAPE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(106);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(107);
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
    setState(109);
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
    setState(111);
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
    setState(113);
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

//----------------- NullContext ------------------------------------------------------------------

StringInterpolatorParser::NullContext::NullContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::NullContext::NULL_() {
  return getToken(StringInterpolatorParser::NULL_, 0);
}


size_t StringInterpolatorParser::NullContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleNull;
}


std::any StringInterpolatorParser::NullContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitNull(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::NullContext* StringInterpolatorParser::null() {
  NullContext *_localctx = _tracker.createInstance<NullContext>(_ctx, getState());
  enterRule(_localctx, 18, StringInterpolatorParser::RuleNull);

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
    match(StringInterpolatorParser::NULL_);
   
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

StringInterpolatorParser::NullContext* StringInterpolatorParser::LiteralContext::null() {
  return getRuleContext<StringInterpolatorParser::NullContext>(0);
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
  enterRule(_localctx, 20, StringInterpolatorParser::RuleLiteral);

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
      case StringInterpolatorParser::STRING_START: {
        enterOuterAlt(_localctx, 1);
        setState(117);
        string();
        break;
      }

      case StringInterpolatorParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(118);
        integer();
        break;
      }

      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(119);
        float_();
        break;
      }

      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE: {
        enterOuterAlt(_localctx, 4);
        setState(120);
        boolean();
        break;
      }

      case StringInterpolatorParser::NULL_: {
        enterOuterAlt(_localctx, 5);
        setState(121);
        null();
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
  enterRule(_localctx, 22, StringInterpolatorParser::RuleArgument);

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
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::NULL_:
      case StringInterpolatorParser::DOT:
      case StringInterpolatorParser::OPENB:
      case StringInterpolatorParser::DOLLAR:
      case StringInterpolatorParser::AT:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT:
      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(124);
        expr_item();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        enterOuterAlt(_localctx, 2);
        setState(125);
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
  enterRule(_localctx, 24, StringInterpolatorParser::RuleArg_list);
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

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3901834352) != 0)) {
      setState(128);
      argument();
    }
    setState(139);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(132); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(131);
          match(StringInterpolatorParser::WS);
          setState(134); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == StringInterpolatorParser::WS);
        setState(136);
        argument(); 
      }
      setState(141);
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
  enterRule(_localctx, 26, StringInterpolatorParser::RuleFunc);
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
    setState(143);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::AT) {
      setState(142);
      match(StringInterpolatorParser::AT);
    }
    setState(145);
    match(StringInterpolatorParser::ID);
    setState(152);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      setState(147); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(146);
                match(StringInterpolatorParser::WS);
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(149); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      setState(151);
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
  enterRule(_localctx, 28, StringInterpolatorParser::RuleArray_item);
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
    setState(157);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(154);
      match(StringInterpolatorParser::WS);
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(162);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::NULL_:
      case StringInterpolatorParser::DOT:
      case StringInterpolatorParser::OPENB:
      case StringInterpolatorParser::DOLLAR:
      case StringInterpolatorParser::AT:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT:
      case StringInterpolatorParser::ID: {
        setState(160);
        expr_item();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        setState(161);
        expr_block();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(167);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(164);
      match(StringInterpolatorParser::WS);
      setState(169);
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
  enterRule(_localctx, 30, StringInterpolatorParser::RuleArray);
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
    setState(170);
    match(StringInterpolatorParser::OPENB);
    setState(176);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(171);
        array_item();
        setState(172);
        match(StringInterpolatorParser::COMMA); 
      }
      setState(178);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
    setState(180);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4170269808) != 0)) {
      setState(179);
      array_item();
    }
    setState(182);
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
  enterRule(_localctx, 32, StringInterpolatorParser::RuleExpr_item);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(189);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::NULL_:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(184);
        literal();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(185);
        property();
        break;
      }

      case StringInterpolatorParser::AT:
      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 3);
        setState(186);
        func();
        break;
      }

      case StringInterpolatorParser::OPENB: {
        enterOuterAlt(_localctx, 4);
        setState(187);
        array();
        break;
      }

      case StringInterpolatorParser::DOLLAR: {
        enterOuterAlt(_localctx, 5);
        setState(188);
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
  enterRule(_localctx, 34, StringInterpolatorParser::RulePiped_expression);
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
    setState(191);
    expr_item();
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(192);
      match(StringInterpolatorParser::WS);
      setState(197);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(198);
    match(StringInterpolatorParser::PIPE);
    setState(202);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(199);
      match(StringInterpolatorParser::WS);
      setState(204);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(207);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
    case 1: {
      setState(205);
      expr_item();
      break;
    }

    case 2: {
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
  enterRule(_localctx, 36, StringInterpolatorParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(212);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(209);
      expr_item();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(210);
      piped_expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(211);
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

tree::TerminalNode* StringInterpolatorParser::Assign_stmtContext::VAR() {
  return getToken(StringInterpolatorParser::VAR, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Assign_stmtContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Assign_stmtContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}

tree::TerminalNode* StringInterpolatorParser::Assign_stmtContext::PERSIST() {
  return getToken(StringInterpolatorParser::PERSIST, 0);
}

tree::TerminalNode* StringInterpolatorParser::Assign_stmtContext::CONST() {
  return getToken(StringInterpolatorParser::CONST, 0);
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
  enterRule(_localctx, 38, StringInterpolatorParser::RuleAssign_stmt);
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
    setState(236);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 896) != 0)) {
      setState(220);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == StringInterpolatorParser::PERSIST) {
        setState(214);
        match(StringInterpolatorParser::PERSIST);
        setState(216); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(215);
          match(StringInterpolatorParser::WS);
          setState(218); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == StringInterpolatorParser::WS);
      }
      setState(228);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == StringInterpolatorParser::CONST) {
        setState(222);
        match(StringInterpolatorParser::CONST);
        setState(224); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(223);
          match(StringInterpolatorParser::WS);
          setState(226); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == StringInterpolatorParser::WS);
      }
      setState(230);
      match(StringInterpolatorParser::VAR);
      setState(232); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(231);
        match(StringInterpolatorParser::WS);
        setState(234); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == StringInterpolatorParser::WS);
    }
    setState(238);
    match(StringInterpolatorParser::DOLLAR);
    setState(239);
    match(StringInterpolatorParser::ID);
    setState(243);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(240);
      match(StringInterpolatorParser::WS);
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(246);
    match(StringInterpolatorParser::EQUAL);
    setState(250);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(247);
      match(StringInterpolatorParser::WS);
      setState(252);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(253);
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
  enterRule(_localctx, 40, StringInterpolatorParser::RuleFunction_parameter);
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
    setState(255);
    match(StringInterpolatorParser::ID);
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::QUESTION) {
      setState(256);
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
  enterRule(_localctx, 42, StringInterpolatorParser::RuleFunction_parameters);
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
    setState(259);
    match(StringInterpolatorParser::OPENP);
    setState(263);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(260);
      match(StringInterpolatorParser::WS);
      setState(265);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

    setState(266);
    function_parameter();
    setState(270);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(267);
        match(StringInterpolatorParser::WS); 
      }
      setState(272);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
    setState(289);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(273);
        match(StringInterpolatorParser::COMMA);
        setState(277);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == StringInterpolatorParser::WS) {
          setState(274);
          match(StringInterpolatorParser::WS);
          setState(279);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(280);
        function_parameter();
        setState(284);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(281);
            match(StringInterpolatorParser::WS); 
          }
          setState(286);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
        } 
      }
      setState(291);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    }
    setState(293);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::COMMA) {
      setState(292);
      match(StringInterpolatorParser::COMMA);
    }
    setState(298);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(295);
      match(StringInterpolatorParser::WS);
      setState(300);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(301);
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
  enterRule(_localctx, 44, StringInterpolatorParser::RuleFunction_def_stmt);
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
    setState(303);
    match(StringInterpolatorParser::AT);
    setState(304);
    match(StringInterpolatorParser::ID);
    setState(308);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(305);
        match(StringInterpolatorParser::WS); 
      }
      setState(310);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
    }
    setState(312);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::OPENP) {
      setState(311);
      function_parameters();
    }
    setState(317);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(314);
      match(StringInterpolatorParser::WS);
      setState(319);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(320);
    match(StringInterpolatorParser::ARROW);
    setState(324);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(321);
      match(StringInterpolatorParser::WS);
      setState(326);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(327);
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
  enterRule(_localctx, 46, StringInterpolatorParser::RuleSimple_expr_stmt);

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
  enterRule(_localctx, 48, StringInterpolatorParser::RuleExpr_stmt);
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
    setState(334);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
    case 1: {
      setState(331);
      assign_stmt();
      break;
    }

    case 2: {
      setState(332);
      function_def_stmt();
      break;
    }

    case 3: {
      setState(333);
      simple_expr_stmt();
      break;
    }

    default:
      break;
    }
    setState(339);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(336);
      match(StringInterpolatorParser::WS);
      setState(341);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(342);
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
  enterRule(_localctx, 50, StringInterpolatorParser::RuleExpr_block_contents);
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
    setState(353);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(344);
        expr_stmt();
        setState(348);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == StringInterpolatorParser::WS) {
          setState(345);
          match(StringInterpolatorParser::WS);
          setState(350);
          _errHandler->sync(this);
          _la = _input->LA(1);
        } 
      }
      setState(355);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx);
    }
    setState(356);
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
  enterRule(_localctx, 52, StringInterpolatorParser::RuleExpr_block);
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
    setState(358);
    match(StringInterpolatorParser::OPENP);
    setState(362);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(359);
      match(StringInterpolatorParser::WS);
      setState(364);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(365);
    expr_block_contents();
    setState(369);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(366);
      match(StringInterpolatorParser::WS);
      setState(371);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(372);
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
  enterRule(_localctx, 54, StringInterpolatorParser::RuleEval);
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
    setState(374);
    match(StringInterpolatorParser::OPEN);
    setState(378);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(375);
      match(StringInterpolatorParser::WS);
      setState(380);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(381);
    expr_block_contents();
    setState(385);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(382);
      match(StringInterpolatorParser::WS);
      setState(387);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(388);
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
  enterRule(_localctx, 56, StringInterpolatorParser::RuleLoop_start);
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
    setState(390);
    match(StringInterpolatorParser::OPEN);
    setState(391);
    match(StringInterpolatorParser::HASH);
    setState(395);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(392);
      match(StringInterpolatorParser::WS);
      setState(397);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(398);
    expr_block_contents();
    setState(402);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(399);
      match(StringInterpolatorParser::WS);
      setState(404);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(405);
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
  enterRule(_localctx, 58, StringInterpolatorParser::RuleLoop_end);
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
    setState(407);
    match(StringInterpolatorParser::OPEN);
    setState(408);
    match(StringInterpolatorParser::SLASH);
    setState(409);
    match(StringInterpolatorParser::SLASH);
    setState(413);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(410);
      match(StringInterpolatorParser::WS);
      setState(415);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(416);
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
  enterRule(_localctx, 60, StringInterpolatorParser::RuleLoop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(418);
    loop_start();
    setState(419);
    interpolated_str();
    setState(420);
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
  enterRule(_localctx, 62, StringInterpolatorParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(424);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(422);
      eval();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(423);
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
  enterRule(_localctx, 64, StringInterpolatorParser::RuleNormal);
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
    setState(427); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(426);
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
      setState(429); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
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
  enterRule(_localctx, 66, StringInterpolatorParser::RuleInterpolated_str);

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
    setState(435);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(433);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case StringInterpolatorParser::NORMAL_TEXT:
          case StringInterpolatorParser::NORMAL_ESCAPE: {
            setState(431);
            normal();
            break;
          }

          case StringInterpolatorParser::OPEN: {
            setState(432);
            stmt();
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(437);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx);
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
  enterRule(_localctx, 68, StringInterpolatorParser::RuleExpression_program);
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
    setState(441);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(438);
      match(StringInterpolatorParser::WS);
      setState(443);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(444);
    expr_block_contents();
    setState(448);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(445);
      match(StringInterpolatorParser::WS);
      setState(450);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(451);
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
  enterRule(_localctx, 70, StringInterpolatorParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(453);
    interpolated_str();
    setState(454);
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
