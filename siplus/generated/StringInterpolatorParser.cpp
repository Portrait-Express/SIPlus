
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
      "string", "integer", "float", "boolean", "null", "primitive", "array", 
      "accessor", "indexer", "variable", "literal", "call", "variable_declaration", 
      "variable_assignment", "function_parameter", "function_parameters", 
      "function_definition", "piped_suffixable_expr", "piped_expr_part", 
      "piped_expr", "suffixable_expr", "expr_suffix", "expr", "block_stmt", 
      "block_expr", "block_contents", "block", "expression_program", "interp_eval", 
      "interp_loop_start", "interp_loop_end", "interp_loop", "interp_stmt", 
      "interp_normal", "interp_part", "interpolated_str", "program"
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
  	4,1,35,514,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,1,0,1,0,5,0,77,8,0,10,0,12,0,80,9,0,1,0,1,0,1,1,1,1,1,2,
  	1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,5,1,5,3,5,97,8,5,1,6,1,6,5,6,101,8,
  	6,10,6,12,6,104,9,6,1,6,1,6,5,6,108,8,6,10,6,12,6,111,9,6,1,6,1,6,5,6,
  	115,8,6,10,6,12,6,118,9,6,1,6,5,6,121,8,6,10,6,12,6,124,9,6,3,6,126,8,
  	6,1,6,5,6,129,8,6,10,6,12,6,132,9,6,1,6,1,6,1,7,1,7,5,7,138,8,7,10,7,
  	12,7,141,9,7,1,7,1,7,1,8,1,8,5,8,147,8,8,10,8,12,8,150,9,8,1,8,1,8,5,
  	8,154,8,8,10,8,12,8,157,9,8,1,8,1,8,1,9,1,9,1,9,1,10,1,10,3,10,166,8,
  	10,1,11,3,11,169,8,11,1,11,1,11,4,11,173,8,11,11,11,12,11,174,1,11,5,
  	11,178,8,11,10,11,12,11,181,9,11,1,12,1,12,4,12,185,8,12,11,12,12,12,
  	186,3,12,189,8,12,1,12,1,12,4,12,193,8,12,11,12,12,12,194,3,12,197,8,
  	12,1,12,1,12,4,12,201,8,12,11,12,12,12,202,1,12,1,12,1,12,5,12,208,8,
  	12,10,12,12,12,211,9,12,1,12,1,12,5,12,215,8,12,10,12,12,12,218,9,12,
  	1,12,3,12,221,8,12,1,13,1,13,1,13,5,13,226,8,13,10,13,12,13,229,9,13,
  	1,13,1,13,5,13,233,8,13,10,13,12,13,236,9,13,1,13,1,13,1,14,1,14,3,14,
  	242,8,14,1,15,1,15,5,15,246,8,15,10,15,12,15,249,9,15,1,15,1,15,5,15,
  	253,8,15,10,15,12,15,256,9,15,1,15,1,15,5,15,260,8,15,10,15,12,15,263,
  	9,15,1,15,1,15,5,15,267,8,15,10,15,12,15,270,9,15,5,15,272,8,15,10,15,
  	12,15,275,9,15,1,15,3,15,278,8,15,1,15,5,15,281,8,15,10,15,12,15,284,
  	9,15,1,15,1,15,1,16,1,16,1,16,5,16,291,8,16,10,16,12,16,294,9,16,1,16,
  	3,16,297,8,16,1,16,5,16,300,8,16,10,16,12,16,303,9,16,1,16,1,16,5,16,
  	307,8,16,10,16,12,16,310,9,16,1,16,1,16,1,17,1,17,1,17,3,17,317,8,17,
  	1,18,1,18,1,18,5,18,322,8,18,10,18,12,18,325,9,18,1,18,5,18,328,8,18,
  	10,18,12,18,331,9,18,3,18,333,8,18,1,19,1,19,5,19,337,8,19,10,19,12,19,
  	340,9,19,1,19,1,19,5,19,344,8,19,10,19,12,19,347,9,19,1,19,4,19,350,8,
  	19,11,19,12,19,351,1,20,1,20,1,20,1,20,3,20,358,8,20,1,21,1,21,3,21,362,
  	8,21,1,22,1,22,5,22,366,8,22,10,22,12,22,369,9,22,1,22,5,22,372,8,22,
  	10,22,12,22,375,9,22,1,22,1,22,1,22,3,22,380,8,22,1,23,1,23,1,23,1,23,
  	3,23,386,8,23,1,24,1,24,3,24,390,8,24,1,25,1,25,5,25,394,8,25,10,25,12,
  	25,397,9,25,1,25,1,25,5,25,401,8,25,10,25,12,25,404,9,25,5,25,406,8,25,
  	10,25,12,25,409,9,25,1,25,1,25,1,26,1,26,5,26,415,8,26,10,26,12,26,418,
  	9,26,1,26,1,26,5,26,422,8,26,10,26,12,26,425,9,26,1,26,1,26,1,27,5,27,
  	430,8,27,10,27,12,27,433,9,27,1,27,1,27,5,27,437,8,27,10,27,12,27,440,
  	9,27,1,27,1,27,1,28,1,28,5,28,446,8,28,10,28,12,28,449,9,28,1,28,1,28,
  	5,28,453,8,28,10,28,12,28,456,9,28,1,28,1,28,1,29,1,29,1,29,5,29,463,
  	8,29,10,29,12,29,466,9,29,1,29,1,29,5,29,470,8,29,10,29,12,29,473,9,29,
  	1,29,1,29,1,30,1,30,1,30,1,30,5,30,481,8,30,10,30,12,30,484,9,30,1,30,
  	1,30,1,31,1,31,1,31,1,31,1,32,1,32,3,32,494,8,32,1,33,4,33,497,8,33,11,
  	33,12,33,498,1,34,1,34,3,34,503,8,34,1,35,5,35,506,8,35,10,35,12,35,509,
  	9,35,1,36,1,36,1,36,1,36,0,0,37,0,2,4,6,8,10,12,14,16,18,20,22,24,26,
  	28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,72,
  	0,3,1,0,33,34,1,0,4,5,1,0,1,2,552,0,74,1,0,0,0,2,83,1,0,0,0,4,85,1,0,
  	0,0,6,87,1,0,0,0,8,89,1,0,0,0,10,96,1,0,0,0,12,98,1,0,0,0,14,135,1,0,
  	0,0,16,144,1,0,0,0,18,160,1,0,0,0,20,165,1,0,0,0,22,168,1,0,0,0,24,188,
  	1,0,0,0,26,222,1,0,0,0,28,239,1,0,0,0,30,243,1,0,0,0,32,287,1,0,0,0,34,
  	316,1,0,0,0,36,332,1,0,0,0,38,334,1,0,0,0,40,357,1,0,0,0,42,361,1,0,0,
  	0,44,379,1,0,0,0,46,385,1,0,0,0,48,389,1,0,0,0,50,407,1,0,0,0,52,412,
  	1,0,0,0,54,431,1,0,0,0,56,443,1,0,0,0,58,459,1,0,0,0,60,476,1,0,0,0,62,
  	487,1,0,0,0,64,493,1,0,0,0,66,496,1,0,0,0,68,502,1,0,0,0,70,507,1,0,0,
  	0,72,510,1,0,0,0,74,78,5,27,0,0,75,77,7,0,0,0,76,75,1,0,0,0,77,80,1,0,
  	0,0,78,76,1,0,0,0,78,79,1,0,0,0,79,81,1,0,0,0,80,78,1,0,0,0,81,82,5,35,
  	0,0,82,1,1,0,0,0,83,84,5,29,0,0,84,3,1,0,0,0,85,86,5,30,0,0,86,5,1,0,
  	0,0,87,88,7,1,0,0,88,7,1,0,0,0,89,90,5,6,0,0,90,9,1,0,0,0,91,97,3,0,0,
  	0,92,97,3,2,1,0,93,97,3,4,2,0,94,97,3,6,3,0,95,97,3,8,4,0,96,91,1,0,0,
  	0,96,92,1,0,0,0,96,93,1,0,0,0,96,94,1,0,0,0,96,95,1,0,0,0,97,11,1,0,0,
  	0,98,102,5,16,0,0,99,101,5,28,0,0,100,99,1,0,0,0,101,104,1,0,0,0,102,
  	100,1,0,0,0,102,103,1,0,0,0,103,125,1,0,0,0,104,102,1,0,0,0,105,122,3,
  	44,22,0,106,108,5,28,0,0,107,106,1,0,0,0,108,111,1,0,0,0,109,107,1,0,
  	0,0,109,110,1,0,0,0,110,112,1,0,0,0,111,109,1,0,0,0,112,116,5,18,0,0,
  	113,115,5,28,0,0,114,113,1,0,0,0,115,118,1,0,0,0,116,114,1,0,0,0,116,
  	117,1,0,0,0,117,119,1,0,0,0,118,116,1,0,0,0,119,121,3,44,22,0,120,109,
  	1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,122,123,1,0,0,0,123,126,1,0,0,
  	0,124,122,1,0,0,0,125,105,1,0,0,0,125,126,1,0,0,0,126,130,1,0,0,0,127,
  	129,5,28,0,0,128,127,1,0,0,0,129,132,1,0,0,0,130,128,1,0,0,0,130,131,
  	1,0,0,0,131,133,1,0,0,0,132,130,1,0,0,0,133,134,5,17,0,0,134,13,1,0,0,
  	0,135,139,5,10,0,0,136,138,5,28,0,0,137,136,1,0,0,0,138,141,1,0,0,0,139,
  	137,1,0,0,0,139,140,1,0,0,0,140,142,1,0,0,0,141,139,1,0,0,0,142,143,5,
  	31,0,0,143,15,1,0,0,0,144,148,5,16,0,0,145,147,5,28,0,0,146,145,1,0,0,
  	0,147,150,1,0,0,0,148,146,1,0,0,0,148,149,1,0,0,0,149,151,1,0,0,0,150,
  	148,1,0,0,0,151,155,3,44,22,0,152,154,5,28,0,0,153,152,1,0,0,0,154,157,
  	1,0,0,0,155,153,1,0,0,0,155,156,1,0,0,0,156,158,1,0,0,0,157,155,1,0,0,
  	0,158,159,5,17,0,0,159,17,1,0,0,0,160,161,5,20,0,0,161,162,5,31,0,0,162,
  	19,1,0,0,0,163,166,3,10,5,0,164,166,3,12,6,0,165,163,1,0,0,0,165,164,
  	1,0,0,0,166,21,1,0,0,0,167,169,5,23,0,0,168,167,1,0,0,0,168,169,1,0,0,
  	0,169,170,1,0,0,0,170,179,5,31,0,0,171,173,5,28,0,0,172,171,1,0,0,0,173,
  	174,1,0,0,0,174,172,1,0,0,0,174,175,1,0,0,0,175,176,1,0,0,0,176,178,3,
  	44,22,0,177,172,1,0,0,0,178,181,1,0,0,0,179,177,1,0,0,0,179,180,1,0,0,
  	0,180,23,1,0,0,0,181,179,1,0,0,0,182,184,5,8,0,0,183,185,5,28,0,0,184,
  	183,1,0,0,0,185,186,1,0,0,0,186,184,1,0,0,0,186,187,1,0,0,0,187,189,1,
  	0,0,0,188,182,1,0,0,0,188,189,1,0,0,0,189,196,1,0,0,0,190,192,5,9,0,0,
  	191,193,5,28,0,0,192,191,1,0,0,0,193,194,1,0,0,0,194,192,1,0,0,0,194,
  	195,1,0,0,0,195,197,1,0,0,0,196,190,1,0,0,0,196,197,1,0,0,0,197,198,1,
  	0,0,0,198,200,5,7,0,0,199,201,5,28,0,0,200,199,1,0,0,0,201,202,1,0,0,
  	0,202,200,1,0,0,0,202,203,1,0,0,0,203,204,1,0,0,0,204,205,5,20,0,0,205,
  	220,5,31,0,0,206,208,5,28,0,0,207,206,1,0,0,0,208,211,1,0,0,0,209,207,
  	1,0,0,0,209,210,1,0,0,0,210,212,1,0,0,0,211,209,1,0,0,0,212,216,5,24,
  	0,0,213,215,5,28,0,0,214,213,1,0,0,0,215,218,1,0,0,0,216,214,1,0,0,0,
  	216,217,1,0,0,0,217,219,1,0,0,0,218,216,1,0,0,0,219,221,3,44,22,0,220,
  	209,1,0,0,0,220,221,1,0,0,0,221,25,1,0,0,0,222,223,5,20,0,0,223,227,5,
  	31,0,0,224,226,5,28,0,0,225,224,1,0,0,0,226,229,1,0,0,0,227,225,1,0,0,
  	0,227,228,1,0,0,0,228,230,1,0,0,0,229,227,1,0,0,0,230,234,5,24,0,0,231,
  	233,5,28,0,0,232,231,1,0,0,0,233,236,1,0,0,0,234,232,1,0,0,0,234,235,
  	1,0,0,0,235,237,1,0,0,0,236,234,1,0,0,0,237,238,3,44,22,0,238,27,1,0,
  	0,0,239,241,5,31,0,0,240,242,5,22,0,0,241,240,1,0,0,0,241,242,1,0,0,0,
  	242,29,1,0,0,0,243,247,5,14,0,0,244,246,5,28,0,0,245,244,1,0,0,0,246,
  	249,1,0,0,0,247,245,1,0,0,0,247,248,1,0,0,0,248,250,1,0,0,0,249,247,1,
  	0,0,0,250,254,3,28,14,0,251,253,5,28,0,0,252,251,1,0,0,0,253,256,1,0,
  	0,0,254,252,1,0,0,0,254,255,1,0,0,0,255,273,1,0,0,0,256,254,1,0,0,0,257,
  	261,5,18,0,0,258,260,5,28,0,0,259,258,1,0,0,0,260,263,1,0,0,0,261,259,
  	1,0,0,0,261,262,1,0,0,0,262,264,1,0,0,0,263,261,1,0,0,0,264,268,3,28,
  	14,0,265,267,5,28,0,0,266,265,1,0,0,0,267,270,1,0,0,0,268,266,1,0,0,0,
  	268,269,1,0,0,0,269,272,1,0,0,0,270,268,1,0,0,0,271,257,1,0,0,0,272,275,
  	1,0,0,0,273,271,1,0,0,0,273,274,1,0,0,0,274,277,1,0,0,0,275,273,1,0,0,
  	0,276,278,5,18,0,0,277,276,1,0,0,0,277,278,1,0,0,0,278,282,1,0,0,0,279,
  	281,5,28,0,0,280,279,1,0,0,0,281,284,1,0,0,0,282,280,1,0,0,0,282,283,
  	1,0,0,0,283,285,1,0,0,0,284,282,1,0,0,0,285,286,5,15,0,0,286,31,1,0,0,
  	0,287,288,5,23,0,0,288,292,5,31,0,0,289,291,5,28,0,0,290,289,1,0,0,0,
  	291,294,1,0,0,0,292,290,1,0,0,0,292,293,1,0,0,0,293,296,1,0,0,0,294,292,
  	1,0,0,0,295,297,3,30,15,0,296,295,1,0,0,0,296,297,1,0,0,0,297,301,1,0,
  	0,0,298,300,5,28,0,0,299,298,1,0,0,0,300,303,1,0,0,0,301,299,1,0,0,0,
  	301,302,1,0,0,0,302,304,1,0,0,0,303,301,1,0,0,0,304,308,5,25,0,0,305,
  	307,5,28,0,0,306,305,1,0,0,0,307,310,1,0,0,0,308,306,1,0,0,0,308,309,
  	1,0,0,0,309,311,1,0,0,0,310,308,1,0,0,0,311,312,3,44,22,0,312,33,1,0,
  	0,0,313,317,3,14,7,0,314,315,5,10,0,0,315,317,3,16,8,0,316,313,1,0,0,
  	0,316,314,1,0,0,0,317,35,1,0,0,0,318,333,3,22,11,0,319,329,3,34,17,0,
  	320,322,5,28,0,0,321,320,1,0,0,0,322,325,1,0,0,0,323,321,1,0,0,0,323,
  	324,1,0,0,0,324,326,1,0,0,0,325,323,1,0,0,0,326,328,3,42,21,0,327,323,
  	1,0,0,0,328,331,1,0,0,0,329,327,1,0,0,0,329,330,1,0,0,0,330,333,1,0,0,
  	0,331,329,1,0,0,0,332,318,1,0,0,0,332,319,1,0,0,0,333,37,1,0,0,0,334,
  	349,3,44,22,0,335,337,5,28,0,0,336,335,1,0,0,0,337,340,1,0,0,0,338,336,
  	1,0,0,0,338,339,1,0,0,0,339,341,1,0,0,0,340,338,1,0,0,0,341,345,5,19,
  	0,0,342,344,5,28,0,0,343,342,1,0,0,0,344,347,1,0,0,0,345,343,1,0,0,0,
  	345,346,1,0,0,0,346,348,1,0,0,0,347,345,1,0,0,0,348,350,3,36,18,0,349,
  	338,1,0,0,0,350,351,1,0,0,0,351,349,1,0,0,0,351,352,1,0,0,0,352,39,1,
  	0,0,0,353,358,3,20,10,0,354,358,3,18,9,0,355,358,3,52,26,0,356,358,3,
  	34,17,0,357,353,1,0,0,0,357,354,1,0,0,0,357,355,1,0,0,0,357,356,1,0,0,
  	0,358,41,1,0,0,0,359,362,3,14,7,0,360,362,3,16,8,0,361,359,1,0,0,0,361,
  	360,1,0,0,0,362,43,1,0,0,0,363,373,3,40,20,0,364,366,5,28,0,0,365,364,
  	1,0,0,0,366,369,1,0,0,0,367,365,1,0,0,0,367,368,1,0,0,0,368,370,1,0,0,
  	0,369,367,1,0,0,0,370,372,3,42,21,0,371,367,1,0,0,0,372,375,1,0,0,0,373,
  	371,1,0,0,0,373,374,1,0,0,0,374,380,1,0,0,0,375,373,1,0,0,0,376,380,3,
  	26,13,0,377,380,3,22,11,0,378,380,5,10,0,0,379,363,1,0,0,0,379,376,1,
  	0,0,0,379,377,1,0,0,0,379,378,1,0,0,0,380,45,1,0,0,0,381,386,3,44,22,
  	0,382,386,3,38,19,0,383,386,3,24,12,0,384,386,3,32,16,0,385,381,1,0,0,
  	0,385,382,1,0,0,0,385,383,1,0,0,0,385,384,1,0,0,0,386,47,1,0,0,0,387,
  	390,3,44,22,0,388,390,3,38,19,0,389,387,1,0,0,0,389,388,1,0,0,0,390,49,
  	1,0,0,0,391,395,3,46,23,0,392,394,5,28,0,0,393,392,1,0,0,0,394,397,1,
  	0,0,0,395,393,1,0,0,0,395,396,1,0,0,0,396,398,1,0,0,0,397,395,1,0,0,0,
  	398,402,5,21,0,0,399,401,5,28,0,0,400,399,1,0,0,0,401,404,1,0,0,0,402,
  	400,1,0,0,0,402,403,1,0,0,0,403,406,1,0,0,0,404,402,1,0,0,0,405,391,1,
  	0,0,0,406,409,1,0,0,0,407,405,1,0,0,0,407,408,1,0,0,0,408,410,1,0,0,0,
  	409,407,1,0,0,0,410,411,3,48,24,0,411,51,1,0,0,0,412,416,5,14,0,0,413,
  	415,5,28,0,0,414,413,1,0,0,0,415,418,1,0,0,0,416,414,1,0,0,0,416,417,
  	1,0,0,0,417,419,1,0,0,0,418,416,1,0,0,0,419,423,3,50,25,0,420,422,5,28,
  	0,0,421,420,1,0,0,0,422,425,1,0,0,0,423,421,1,0,0,0,423,424,1,0,0,0,424,
  	426,1,0,0,0,425,423,1,0,0,0,426,427,5,15,0,0,427,53,1,0,0,0,428,430,5,
  	28,0,0,429,428,1,0,0,0,430,433,1,0,0,0,431,429,1,0,0,0,431,432,1,0,0,
  	0,432,434,1,0,0,0,433,431,1,0,0,0,434,438,3,50,25,0,435,437,5,28,0,0,
  	436,435,1,0,0,0,437,440,1,0,0,0,438,436,1,0,0,0,438,439,1,0,0,0,439,441,
  	1,0,0,0,440,438,1,0,0,0,441,442,5,0,0,1,442,55,1,0,0,0,443,447,5,3,0,
  	0,444,446,5,28,0,0,445,444,1,0,0,0,446,449,1,0,0,0,447,445,1,0,0,0,447,
  	448,1,0,0,0,448,450,1,0,0,0,449,447,1,0,0,0,450,454,3,50,25,0,451,453,
  	5,28,0,0,452,451,1,0,0,0,453,456,1,0,0,0,454,452,1,0,0,0,454,455,1,0,
  	0,0,455,457,1,0,0,0,456,454,1,0,0,0,457,458,5,13,0,0,458,57,1,0,0,0,459,
  	460,5,3,0,0,460,464,5,11,0,0,461,463,5,28,0,0,462,461,1,0,0,0,463,466,
  	1,0,0,0,464,462,1,0,0,0,464,465,1,0,0,0,465,467,1,0,0,0,466,464,1,0,0,
  	0,467,471,3,50,25,0,468,470,5,28,0,0,469,468,1,0,0,0,470,473,1,0,0,0,
  	471,469,1,0,0,0,471,472,1,0,0,0,472,474,1,0,0,0,473,471,1,0,0,0,474,475,
  	5,13,0,0,475,59,1,0,0,0,476,477,5,3,0,0,477,478,5,12,0,0,478,482,5,12,
  	0,0,479,481,5,28,0,0,480,479,1,0,0,0,481,484,1,0,0,0,482,480,1,0,0,0,
  	482,483,1,0,0,0,483,485,1,0,0,0,484,482,1,0,0,0,485,486,5,13,0,0,486,
  	61,1,0,0,0,487,488,3,58,29,0,488,489,3,70,35,0,489,490,3,60,30,0,490,
  	63,1,0,0,0,491,494,3,56,28,0,492,494,3,62,31,0,493,491,1,0,0,0,493,492,
  	1,0,0,0,494,65,1,0,0,0,495,497,7,2,0,0,496,495,1,0,0,0,497,498,1,0,0,
  	0,498,496,1,0,0,0,498,499,1,0,0,0,499,67,1,0,0,0,500,503,3,66,33,0,501,
  	503,3,64,32,0,502,500,1,0,0,0,502,501,1,0,0,0,503,69,1,0,0,0,504,506,
  	3,68,34,0,505,504,1,0,0,0,506,509,1,0,0,0,507,505,1,0,0,0,507,508,1,0,
  	0,0,508,71,1,0,0,0,509,507,1,0,0,0,510,511,3,70,35,0,511,512,5,0,0,1,
  	512,73,1,0,0,0,67,78,96,102,109,116,122,125,130,139,148,155,165,168,174,
  	179,186,188,194,196,202,209,216,220,227,234,241,247,254,261,268,273,277,
  	282,292,296,301,308,316,323,329,332,338,345,351,357,361,367,373,379,385,
  	389,395,402,407,416,423,431,438,447,454,464,471,482,493,498,502,507
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
  enterRule(_localctx, 0, StringInterpolatorParser::RuleString);
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
    setState(74);
    match(StringInterpolatorParser::STRING_START);
    setState(78);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::STRING_TEXT

    || _la == StringInterpolatorParser::STRING_ESCAPE) {
      setState(75);
      _la = _input->LA(1);
      if (!(_la == StringInterpolatorParser::STRING_TEXT

      || _la == StringInterpolatorParser::STRING_ESCAPE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(80);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(81);
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
  enterRule(_localctx, 2, StringInterpolatorParser::RuleInteger);

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
  enterRule(_localctx, 4, StringInterpolatorParser::RuleFloat);

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
  enterRule(_localctx, 6, StringInterpolatorParser::RuleBoolean);
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
    setState(87);
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
  enterRule(_localctx, 8, StringInterpolatorParser::RuleNull);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(89);
    match(StringInterpolatorParser::NULL_);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimitiveContext ------------------------------------------------------------------

StringInterpolatorParser::PrimitiveContext::PrimitiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::StringContext* StringInterpolatorParser::PrimitiveContext::string() {
  return getRuleContext<StringInterpolatorParser::StringContext>(0);
}

StringInterpolatorParser::IntegerContext* StringInterpolatorParser::PrimitiveContext::integer() {
  return getRuleContext<StringInterpolatorParser::IntegerContext>(0);
}

StringInterpolatorParser::FloatContext* StringInterpolatorParser::PrimitiveContext::float_() {
  return getRuleContext<StringInterpolatorParser::FloatContext>(0);
}

StringInterpolatorParser::BooleanContext* StringInterpolatorParser::PrimitiveContext::boolean() {
  return getRuleContext<StringInterpolatorParser::BooleanContext>(0);
}

StringInterpolatorParser::NullContext* StringInterpolatorParser::PrimitiveContext::null() {
  return getRuleContext<StringInterpolatorParser::NullContext>(0);
}


size_t StringInterpolatorParser::PrimitiveContext::getRuleIndex() const {
  return StringInterpolatorParser::RulePrimitive;
}


std::any StringInterpolatorParser::PrimitiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitPrimitive(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::PrimitiveContext* StringInterpolatorParser::primitive() {
  PrimitiveContext *_localctx = _tracker.createInstance<PrimitiveContext>(_ctx, getState());
  enterRule(_localctx, 10, StringInterpolatorParser::RulePrimitive);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(96);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::STRING_START: {
        enterOuterAlt(_localctx, 1);
        setState(91);
        string();
        break;
      }

      case StringInterpolatorParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(92);
        integer();
        break;
      }

      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 3);
        setState(93);
        float_();
        break;
      }

      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE: {
        enterOuterAlt(_localctx, 4);
        setState(94);
        boolean();
        break;
      }

      case StringInterpolatorParser::NULL_: {
        enterOuterAlt(_localctx, 5);
        setState(95);
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

std::vector<tree::TerminalNode *> StringInterpolatorParser::ArrayContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::ArrayContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}

std::vector<StringInterpolatorParser::ExprContext *> StringInterpolatorParser::ArrayContext::expr() {
  return getRuleContexts<StringInterpolatorParser::ExprContext>();
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::ArrayContext::expr(size_t i) {
  return getRuleContext<StringInterpolatorParser::ExprContext>(i);
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
  enterRule(_localctx, 12, StringInterpolatorParser::RuleArray);
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
    setState(98);
    match(StringInterpolatorParser::OPENB);
    setState(102);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(99);
        match(StringInterpolatorParser::WS); 
      }
      setState(104);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
    setState(125);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3901834352) != 0)) {
      setState(105);
      expr();
      setState(122);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(109);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == StringInterpolatorParser::WS) {
            setState(106);
            match(StringInterpolatorParser::WS);
            setState(111);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(112);
          match(StringInterpolatorParser::COMMA);
          setState(116);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == StringInterpolatorParser::WS) {
            setState(113);
            match(StringInterpolatorParser::WS);
            setState(118);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(119);
          expr(); 
        }
        setState(124);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
      }
    }
    setState(130);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(127);
      match(StringInterpolatorParser::WS);
      setState(132);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(133);
    match(StringInterpolatorParser::CLOSEB);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AccessorContext ------------------------------------------------------------------

StringInterpolatorParser::AccessorContext::AccessorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::AccessorContext::DOT() {
  return getToken(StringInterpolatorParser::DOT, 0);
}

tree::TerminalNode* StringInterpolatorParser::AccessorContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::AccessorContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::AccessorContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::AccessorContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleAccessor;
}


std::any StringInterpolatorParser::AccessorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitAccessor(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::AccessorContext* StringInterpolatorParser::accessor() {
  AccessorContext *_localctx = _tracker.createInstance<AccessorContext>(_ctx, getState());
  enterRule(_localctx, 14, StringInterpolatorParser::RuleAccessor);
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
    setState(135);
    match(StringInterpolatorParser::DOT);
    setState(139);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(136);
      match(StringInterpolatorParser::WS);
      setState(141);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(142);
    match(StringInterpolatorParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexerContext ------------------------------------------------------------------

StringInterpolatorParser::IndexerContext::IndexerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::IndexerContext::OPENB() {
  return getToken(StringInterpolatorParser::OPENB, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::IndexerContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::IndexerContext::CLOSEB() {
  return getToken(StringInterpolatorParser::CLOSEB, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::IndexerContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::IndexerContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::IndexerContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleIndexer;
}


std::any StringInterpolatorParser::IndexerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitIndexer(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::IndexerContext* StringInterpolatorParser::indexer() {
  IndexerContext *_localctx = _tracker.createInstance<IndexerContext>(_ctx, getState());
  enterRule(_localctx, 16, StringInterpolatorParser::RuleIndexer);
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
    setState(144);
    match(StringInterpolatorParser::OPENB);
    setState(148);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(145);
      match(StringInterpolatorParser::WS);
      setState(150);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(151);
    expr();
    setState(155);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(152);
      match(StringInterpolatorParser::WS);
      setState(157);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(158);
    match(StringInterpolatorParser::CLOSEB);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

StringInterpolatorParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::VariableContext::DOLLAR() {
  return getToken(StringInterpolatorParser::DOLLAR, 0);
}

tree::TerminalNode* StringInterpolatorParser::VariableContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}


size_t StringInterpolatorParser::VariableContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleVariable;
}


std::any StringInterpolatorParser::VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitVariable(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::VariableContext* StringInterpolatorParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 18, StringInterpolatorParser::RuleVariable);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(160);
    match(StringInterpolatorParser::DOLLAR);
    setState(161);
    match(StringInterpolatorParser::ID);
   
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

StringInterpolatorParser::PrimitiveContext* StringInterpolatorParser::LiteralContext::primitive() {
  return getRuleContext<StringInterpolatorParser::PrimitiveContext>(0);
}

StringInterpolatorParser::ArrayContext* StringInterpolatorParser::LiteralContext::array() {
  return getRuleContext<StringInterpolatorParser::ArrayContext>(0);
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
    setState(165);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::NULL_:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(163);
        primitive();
        break;
      }

      case StringInterpolatorParser::OPENB: {
        enterOuterAlt(_localctx, 2);
        setState(164);
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

//----------------- CallContext ------------------------------------------------------------------

StringInterpolatorParser::CallContext::CallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::CallContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

tree::TerminalNode* StringInterpolatorParser::CallContext::AT() {
  return getToken(StringInterpolatorParser::AT, 0);
}

std::vector<StringInterpolatorParser::ExprContext *> StringInterpolatorParser::CallContext::expr() {
  return getRuleContexts<StringInterpolatorParser::ExprContext>();
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::CallContext::expr(size_t i) {
  return getRuleContext<StringInterpolatorParser::ExprContext>(i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::CallContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::CallContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::CallContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleCall;
}


std::any StringInterpolatorParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::CallContext* StringInterpolatorParser::call() {
  CallContext *_localctx = _tracker.createInstance<CallContext>(_ctx, getState());
  enterRule(_localctx, 22, StringInterpolatorParser::RuleCall);
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
    setState(168);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::AT) {
      setState(167);
      match(StringInterpolatorParser::AT);
    }
    setState(170);
    match(StringInterpolatorParser::ID);
    setState(179);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(172); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(171);
          match(StringInterpolatorParser::WS);
          setState(174); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == StringInterpolatorParser::WS);
        setState(176);
        expr(); 
      }
      setState(181);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Variable_declarationContext ------------------------------------------------------------------

StringInterpolatorParser::Variable_declarationContext::Variable_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Variable_declarationContext::VAR() {
  return getToken(StringInterpolatorParser::VAR, 0);
}

tree::TerminalNode* StringInterpolatorParser::Variable_declarationContext::DOLLAR() {
  return getToken(StringInterpolatorParser::DOLLAR, 0);
}

tree::TerminalNode* StringInterpolatorParser::Variable_declarationContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

tree::TerminalNode* StringInterpolatorParser::Variable_declarationContext::PERSIST() {
  return getToken(StringInterpolatorParser::PERSIST, 0);
}

tree::TerminalNode* StringInterpolatorParser::Variable_declarationContext::CONST() {
  return getToken(StringInterpolatorParser::CONST, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Variable_declarationContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Variable_declarationContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}

tree::TerminalNode* StringInterpolatorParser::Variable_declarationContext::EQUAL() {
  return getToken(StringInterpolatorParser::EQUAL, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Variable_declarationContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}


size_t StringInterpolatorParser::Variable_declarationContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleVariable_declaration;
}


std::any StringInterpolatorParser::Variable_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitVariable_declaration(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Variable_declarationContext* StringInterpolatorParser::variable_declaration() {
  Variable_declarationContext *_localctx = _tracker.createInstance<Variable_declarationContext>(_ctx, getState());
  enterRule(_localctx, 24, StringInterpolatorParser::RuleVariable_declaration);
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
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::PERSIST) {
      setState(182);
      match(StringInterpolatorParser::PERSIST);
      setState(184); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(183);
        match(StringInterpolatorParser::WS);
        setState(186); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == StringInterpolatorParser::WS);
    }
    setState(196);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::CONST) {
      setState(190);
      match(StringInterpolatorParser::CONST);
      setState(192); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(191);
        match(StringInterpolatorParser::WS);
        setState(194); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == StringInterpolatorParser::WS);
    }
    setState(198);
    match(StringInterpolatorParser::VAR);
    setState(200); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(199);
      match(StringInterpolatorParser::WS);
      setState(202); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == StringInterpolatorParser::WS);
    setState(204);
    match(StringInterpolatorParser::DOLLAR);
    setState(205);
    match(StringInterpolatorParser::ID);
    setState(220);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      setState(209);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == StringInterpolatorParser::WS) {
        setState(206);
        match(StringInterpolatorParser::WS);
        setState(211);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(212);
      match(StringInterpolatorParser::EQUAL);
      setState(216);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == StringInterpolatorParser::WS) {
        setState(213);
        match(StringInterpolatorParser::WS);
        setState(218);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(219);
      expr();
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

//----------------- Variable_assignmentContext ------------------------------------------------------------------

StringInterpolatorParser::Variable_assignmentContext::Variable_assignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Variable_assignmentContext::DOLLAR() {
  return getToken(StringInterpolatorParser::DOLLAR, 0);
}

tree::TerminalNode* StringInterpolatorParser::Variable_assignmentContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

tree::TerminalNode* StringInterpolatorParser::Variable_assignmentContext::EQUAL() {
  return getToken(StringInterpolatorParser::EQUAL, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Variable_assignmentContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Variable_assignmentContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Variable_assignmentContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Variable_assignmentContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleVariable_assignment;
}


std::any StringInterpolatorParser::Variable_assignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitVariable_assignment(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Variable_assignmentContext* StringInterpolatorParser::variable_assignment() {
  Variable_assignmentContext *_localctx = _tracker.createInstance<Variable_assignmentContext>(_ctx, getState());
  enterRule(_localctx, 26, StringInterpolatorParser::RuleVariable_assignment);
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
    setState(222);
    match(StringInterpolatorParser::DOLLAR);
    setState(223);
    match(StringInterpolatorParser::ID);
    setState(227);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(224);
      match(StringInterpolatorParser::WS);
      setState(229);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(230);
    match(StringInterpolatorParser::EQUAL);
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
  enterRule(_localctx, 28, StringInterpolatorParser::RuleFunction_parameter);
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
    setState(239);
    match(StringInterpolatorParser::ID);
    setState(241);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::QUESTION) {
      setState(240);
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

std::vector<StringInterpolatorParser::Function_parameterContext *> StringInterpolatorParser::Function_parametersContext::function_parameter() {
  return getRuleContexts<StringInterpolatorParser::Function_parameterContext>();
}

StringInterpolatorParser::Function_parameterContext* StringInterpolatorParser::Function_parametersContext::function_parameter(size_t i) {
  return getRuleContext<StringInterpolatorParser::Function_parameterContext>(i);
}

tree::TerminalNode* StringInterpolatorParser::Function_parametersContext::CLOSEP() {
  return getToken(StringInterpolatorParser::CLOSEP, 0);
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
  enterRule(_localctx, 30, StringInterpolatorParser::RuleFunction_parameters);
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
    setState(243);
    match(StringInterpolatorParser::OPENP);
    setState(247);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(244);
      match(StringInterpolatorParser::WS);
      setState(249);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(250);
    function_parameter();
    setState(254);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(251);
        match(StringInterpolatorParser::WS); 
      }
      setState(256);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx);
    }
    setState(273);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(257);
        match(StringInterpolatorParser::COMMA);
        setState(261);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == StringInterpolatorParser::WS) {
          setState(258);
          match(StringInterpolatorParser::WS);
          setState(263);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(264);
        function_parameter();
        setState(268);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(265);
            match(StringInterpolatorParser::WS); 
          }
          setState(270);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
        } 
      }
      setState(275);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx);
    }
    setState(277);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::COMMA) {
      setState(276);
      match(StringInterpolatorParser::COMMA);
    }
    setState(282);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(279);
      match(StringInterpolatorParser::WS);
      setState(284);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(285);
    match(StringInterpolatorParser::CLOSEP);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Function_definitionContext ------------------------------------------------------------------

StringInterpolatorParser::Function_definitionContext::Function_definitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Function_definitionContext::AT() {
  return getToken(StringInterpolatorParser::AT, 0);
}

tree::TerminalNode* StringInterpolatorParser::Function_definitionContext::ID() {
  return getToken(StringInterpolatorParser::ID, 0);
}

tree::TerminalNode* StringInterpolatorParser::Function_definitionContext::ARROW() {
  return getToken(StringInterpolatorParser::ARROW, 0);
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Function_definitionContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Function_definitionContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Function_definitionContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}

StringInterpolatorParser::Function_parametersContext* StringInterpolatorParser::Function_definitionContext::function_parameters() {
  return getRuleContext<StringInterpolatorParser::Function_parametersContext>(0);
}


size_t StringInterpolatorParser::Function_definitionContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleFunction_definition;
}


std::any StringInterpolatorParser::Function_definitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitFunction_definition(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Function_definitionContext* StringInterpolatorParser::function_definition() {
  Function_definitionContext *_localctx = _tracker.createInstance<Function_definitionContext>(_ctx, getState());
  enterRule(_localctx, 32, StringInterpolatorParser::RuleFunction_definition);
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
    setState(287);
    match(StringInterpolatorParser::AT);
    setState(288);
    match(StringInterpolatorParser::ID);
    setState(292);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(289);
        match(StringInterpolatorParser::WS); 
      }
      setState(294);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
    setState(296);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == StringInterpolatorParser::OPENP) {
      setState(295);
      function_parameters();
    }
    setState(301);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(298);
      match(StringInterpolatorParser::WS);
      setState(303);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(304);
    match(StringInterpolatorParser::ARROW);
    setState(308);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(305);
      match(StringInterpolatorParser::WS);
      setState(310);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(311);
    expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Piped_suffixable_exprContext ------------------------------------------------------------------

StringInterpolatorParser::Piped_suffixable_exprContext::Piped_suffixable_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::AccessorContext* StringInterpolatorParser::Piped_suffixable_exprContext::accessor() {
  return getRuleContext<StringInterpolatorParser::AccessorContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::Piped_suffixable_exprContext::DOT() {
  return getToken(StringInterpolatorParser::DOT, 0);
}

StringInterpolatorParser::IndexerContext* StringInterpolatorParser::Piped_suffixable_exprContext::indexer() {
  return getRuleContext<StringInterpolatorParser::IndexerContext>(0);
}


size_t StringInterpolatorParser::Piped_suffixable_exprContext::getRuleIndex() const {
  return StringInterpolatorParser::RulePiped_suffixable_expr;
}


std::any StringInterpolatorParser::Piped_suffixable_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitPiped_suffixable_expr(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Piped_suffixable_exprContext* StringInterpolatorParser::piped_suffixable_expr() {
  Piped_suffixable_exprContext *_localctx = _tracker.createInstance<Piped_suffixable_exprContext>(_ctx, getState());
  enterRule(_localctx, 34, StringInterpolatorParser::RulePiped_suffixable_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(316);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(313);
      accessor();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(314);
      match(StringInterpolatorParser::DOT);
      setState(315);
      indexer();
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

//----------------- Piped_expr_partContext ------------------------------------------------------------------

StringInterpolatorParser::Piped_expr_partContext::Piped_expr_partContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::CallContext* StringInterpolatorParser::Piped_expr_partContext::call() {
  return getRuleContext<StringInterpolatorParser::CallContext>(0);
}

StringInterpolatorParser::Piped_suffixable_exprContext* StringInterpolatorParser::Piped_expr_partContext::piped_suffixable_expr() {
  return getRuleContext<StringInterpolatorParser::Piped_suffixable_exprContext>(0);
}

std::vector<StringInterpolatorParser::Expr_suffixContext *> StringInterpolatorParser::Piped_expr_partContext::expr_suffix() {
  return getRuleContexts<StringInterpolatorParser::Expr_suffixContext>();
}

StringInterpolatorParser::Expr_suffixContext* StringInterpolatorParser::Piped_expr_partContext::expr_suffix(size_t i) {
  return getRuleContext<StringInterpolatorParser::Expr_suffixContext>(i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Piped_expr_partContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Piped_expr_partContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Piped_expr_partContext::getRuleIndex() const {
  return StringInterpolatorParser::RulePiped_expr_part;
}


std::any StringInterpolatorParser::Piped_expr_partContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitPiped_expr_part(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Piped_expr_partContext* StringInterpolatorParser::piped_expr_part() {
  Piped_expr_partContext *_localctx = _tracker.createInstance<Piped_expr_partContext>(_ctx, getState());
  enterRule(_localctx, 36, StringInterpolatorParser::RulePiped_expr_part);
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
    setState(332);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::AT:
      case StringInterpolatorParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(318);
        call();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 2);
        setState(319);
        piped_suffixable_expr();
        setState(329);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(323);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == StringInterpolatorParser::WS) {
              setState(320);
              match(StringInterpolatorParser::WS);
              setState(325);
              _errHandler->sync(this);
              _la = _input->LA(1);
            }
            setState(326);
            expr_suffix(); 
          }
          setState(331);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx);
        }
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

//----------------- Piped_exprContext ------------------------------------------------------------------

StringInterpolatorParser::Piped_exprContext::Piped_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Piped_exprContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Piped_exprContext::PIPE() {
  return getTokens(StringInterpolatorParser::PIPE);
}

tree::TerminalNode* StringInterpolatorParser::Piped_exprContext::PIPE(size_t i) {
  return getToken(StringInterpolatorParser::PIPE, i);
}

std::vector<StringInterpolatorParser::Piped_expr_partContext *> StringInterpolatorParser::Piped_exprContext::piped_expr_part() {
  return getRuleContexts<StringInterpolatorParser::Piped_expr_partContext>();
}

StringInterpolatorParser::Piped_expr_partContext* StringInterpolatorParser::Piped_exprContext::piped_expr_part(size_t i) {
  return getRuleContext<StringInterpolatorParser::Piped_expr_partContext>(i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Piped_exprContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Piped_exprContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Piped_exprContext::getRuleIndex() const {
  return StringInterpolatorParser::RulePiped_expr;
}


std::any StringInterpolatorParser::Piped_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitPiped_expr(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Piped_exprContext* StringInterpolatorParser::piped_expr() {
  Piped_exprContext *_localctx = _tracker.createInstance<Piped_exprContext>(_ctx, getState());
  enterRule(_localctx, 38, StringInterpolatorParser::RulePiped_expr);
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
    setState(334);
    expr();
    setState(349); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(338);
              _errHandler->sync(this);
              _la = _input->LA(1);
              while (_la == StringInterpolatorParser::WS) {
                setState(335);
                match(StringInterpolatorParser::WS);
                setState(340);
                _errHandler->sync(this);
                _la = _input->LA(1);
              }
              setState(341);
              match(StringInterpolatorParser::PIPE);
              setState(345);
              _errHandler->sync(this);
              _la = _input->LA(1);
              while (_la == StringInterpolatorParser::WS) {
                setState(342);
                match(StringInterpolatorParser::WS);
                setState(347);
                _errHandler->sync(this);
                _la = _input->LA(1);
              }
              setState(348);
              piped_expr_part();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(351); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Suffixable_exprContext ------------------------------------------------------------------

StringInterpolatorParser::Suffixable_exprContext::Suffixable_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::LiteralContext* StringInterpolatorParser::Suffixable_exprContext::literal() {
  return getRuleContext<StringInterpolatorParser::LiteralContext>(0);
}

StringInterpolatorParser::VariableContext* StringInterpolatorParser::Suffixable_exprContext::variable() {
  return getRuleContext<StringInterpolatorParser::VariableContext>(0);
}

StringInterpolatorParser::BlockContext* StringInterpolatorParser::Suffixable_exprContext::block() {
  return getRuleContext<StringInterpolatorParser::BlockContext>(0);
}

StringInterpolatorParser::Piped_suffixable_exprContext* StringInterpolatorParser::Suffixable_exprContext::piped_suffixable_expr() {
  return getRuleContext<StringInterpolatorParser::Piped_suffixable_exprContext>(0);
}


size_t StringInterpolatorParser::Suffixable_exprContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleSuffixable_expr;
}


std::any StringInterpolatorParser::Suffixable_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitSuffixable_expr(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Suffixable_exprContext* StringInterpolatorParser::suffixable_expr() {
  Suffixable_exprContext *_localctx = _tracker.createInstance<Suffixable_exprContext>(_ctx, getState());
  enterRule(_localctx, 40, StringInterpolatorParser::RuleSuffixable_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(357);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::TRUE:
      case StringInterpolatorParser::FALSE:
      case StringInterpolatorParser::NULL_:
      case StringInterpolatorParser::OPENB:
      case StringInterpolatorParser::STRING_START:
      case StringInterpolatorParser::INT:
      case StringInterpolatorParser::FLOAT: {
        enterOuterAlt(_localctx, 1);
        setState(353);
        literal();
        break;
      }

      case StringInterpolatorParser::DOLLAR: {
        enterOuterAlt(_localctx, 2);
        setState(354);
        variable();
        break;
      }

      case StringInterpolatorParser::OPENP: {
        enterOuterAlt(_localctx, 3);
        setState(355);
        block();
        break;
      }

      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 4);
        setState(356);
        piped_suffixable_expr();
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

//----------------- Expr_suffixContext ------------------------------------------------------------------

StringInterpolatorParser::Expr_suffixContext::Expr_suffixContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::AccessorContext* StringInterpolatorParser::Expr_suffixContext::accessor() {
  return getRuleContext<StringInterpolatorParser::AccessorContext>(0);
}

StringInterpolatorParser::IndexerContext* StringInterpolatorParser::Expr_suffixContext::indexer() {
  return getRuleContext<StringInterpolatorParser::IndexerContext>(0);
}


size_t StringInterpolatorParser::Expr_suffixContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleExpr_suffix;
}


std::any StringInterpolatorParser::Expr_suffixContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitExpr_suffix(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Expr_suffixContext* StringInterpolatorParser::expr_suffix() {
  Expr_suffixContext *_localctx = _tracker.createInstance<Expr_suffixContext>(_ctx, getState());
  enterRule(_localctx, 42, StringInterpolatorParser::RuleExpr_suffix);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(361);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::DOT: {
        enterOuterAlt(_localctx, 1);
        setState(359);
        accessor();
        break;
      }

      case StringInterpolatorParser::OPENB: {
        enterOuterAlt(_localctx, 2);
        setState(360);
        indexer();
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

StringInterpolatorParser::Suffixable_exprContext* StringInterpolatorParser::ExprContext::suffixable_expr() {
  return getRuleContext<StringInterpolatorParser::Suffixable_exprContext>(0);
}

std::vector<StringInterpolatorParser::Expr_suffixContext *> StringInterpolatorParser::ExprContext::expr_suffix() {
  return getRuleContexts<StringInterpolatorParser::Expr_suffixContext>();
}

StringInterpolatorParser::Expr_suffixContext* StringInterpolatorParser::ExprContext::expr_suffix(size_t i) {
  return getRuleContext<StringInterpolatorParser::Expr_suffixContext>(i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::ExprContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::ExprContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}

StringInterpolatorParser::Variable_assignmentContext* StringInterpolatorParser::ExprContext::variable_assignment() {
  return getRuleContext<StringInterpolatorParser::Variable_assignmentContext>(0);
}

StringInterpolatorParser::CallContext* StringInterpolatorParser::ExprContext::call() {
  return getRuleContext<StringInterpolatorParser::CallContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::ExprContext::DOT() {
  return getToken(StringInterpolatorParser::DOT, 0);
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
  enterRule(_localctx, 44, StringInterpolatorParser::RuleExpr);
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
    setState(379);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(363);
      suffixable_expr();
      setState(373);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(367);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == StringInterpolatorParser::WS) {
            setState(364);
            match(StringInterpolatorParser::WS);
            setState(369);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(370);
          expr_suffix(); 
        }
        setState(375);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(376);
      variable_assignment();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(377);
      call();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(378);
      match(StringInterpolatorParser::DOT);
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

//----------------- Block_stmtContext ------------------------------------------------------------------

StringInterpolatorParser::Block_stmtContext::Block_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Block_stmtContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

StringInterpolatorParser::Piped_exprContext* StringInterpolatorParser::Block_stmtContext::piped_expr() {
  return getRuleContext<StringInterpolatorParser::Piped_exprContext>(0);
}

StringInterpolatorParser::Variable_declarationContext* StringInterpolatorParser::Block_stmtContext::variable_declaration() {
  return getRuleContext<StringInterpolatorParser::Variable_declarationContext>(0);
}

StringInterpolatorParser::Function_definitionContext* StringInterpolatorParser::Block_stmtContext::function_definition() {
  return getRuleContext<StringInterpolatorParser::Function_definitionContext>(0);
}


size_t StringInterpolatorParser::Block_stmtContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleBlock_stmt;
}


std::any StringInterpolatorParser::Block_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitBlock_stmt(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Block_stmtContext* StringInterpolatorParser::block_stmt() {
  Block_stmtContext *_localctx = _tracker.createInstance<Block_stmtContext>(_ctx, getState());
  enterRule(_localctx, 46, StringInterpolatorParser::RuleBlock_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(385);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(381);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(382);
      piped_expr();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(383);
      variable_declaration();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(384);
      function_definition();
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

//----------------- Block_exprContext ------------------------------------------------------------------

StringInterpolatorParser::Block_exprContext::Block_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::ExprContext* StringInterpolatorParser::Block_exprContext::expr() {
  return getRuleContext<StringInterpolatorParser::ExprContext>(0);
}

StringInterpolatorParser::Piped_exprContext* StringInterpolatorParser::Block_exprContext::piped_expr() {
  return getRuleContext<StringInterpolatorParser::Piped_exprContext>(0);
}


size_t StringInterpolatorParser::Block_exprContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleBlock_expr;
}


std::any StringInterpolatorParser::Block_exprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitBlock_expr(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Block_exprContext* StringInterpolatorParser::block_expr() {
  Block_exprContext *_localctx = _tracker.createInstance<Block_exprContext>(_ctx, getState());
  enterRule(_localctx, 48, StringInterpolatorParser::RuleBlock_expr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(389);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(387);
      expr();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(388);
      piped_expr();
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

//----------------- Block_contentsContext ------------------------------------------------------------------

StringInterpolatorParser::Block_contentsContext::Block_contentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Block_exprContext* StringInterpolatorParser::Block_contentsContext::block_expr() {
  return getRuleContext<StringInterpolatorParser::Block_exprContext>(0);
}

std::vector<StringInterpolatorParser::Block_stmtContext *> StringInterpolatorParser::Block_contentsContext::block_stmt() {
  return getRuleContexts<StringInterpolatorParser::Block_stmtContext>();
}

StringInterpolatorParser::Block_stmtContext* StringInterpolatorParser::Block_contentsContext::block_stmt(size_t i) {
  return getRuleContext<StringInterpolatorParser::Block_stmtContext>(i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Block_contentsContext::SEMICOLON() {
  return getTokens(StringInterpolatorParser::SEMICOLON);
}

tree::TerminalNode* StringInterpolatorParser::Block_contentsContext::SEMICOLON(size_t i) {
  return getToken(StringInterpolatorParser::SEMICOLON, i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Block_contentsContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Block_contentsContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Block_contentsContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleBlock_contents;
}


std::any StringInterpolatorParser::Block_contentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitBlock_contents(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Block_contentsContext* StringInterpolatorParser::block_contents() {
  Block_contentsContext *_localctx = _tracker.createInstance<Block_contentsContext>(_ctx, getState());
  enterRule(_localctx, 50, StringInterpolatorParser::RuleBlock_contents);
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
    setState(407);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(391);
        block_stmt();
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
        match(StringInterpolatorParser::SEMICOLON);
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
      }
      setState(409);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    }
    setState(410);
    block_expr();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

StringInterpolatorParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::BlockContext::OPENP() {
  return getToken(StringInterpolatorParser::OPENP, 0);
}

StringInterpolatorParser::Block_contentsContext* StringInterpolatorParser::BlockContext::block_contents() {
  return getRuleContext<StringInterpolatorParser::Block_contentsContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::BlockContext::CLOSEP() {
  return getToken(StringInterpolatorParser::CLOSEP, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::BlockContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::BlockContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::BlockContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleBlock;
}


std::any StringInterpolatorParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::BlockContext* StringInterpolatorParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 52, StringInterpolatorParser::RuleBlock);
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
    match(StringInterpolatorParser::OPENP);
    setState(416);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(413);
      match(StringInterpolatorParser::WS);
      setState(418);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(419);
    block_contents();
    setState(423);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(420);
      match(StringInterpolatorParser::WS);
      setState(425);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(426);
    match(StringInterpolatorParser::CLOSEP);
   
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

StringInterpolatorParser::Block_contentsContext* StringInterpolatorParser::Expression_programContext::block_contents() {
  return getRuleContext<StringInterpolatorParser::Block_contentsContext>(0);
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
  enterRule(_localctx, 54, StringInterpolatorParser::RuleExpression_program);
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
    setState(431);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(428);
      match(StringInterpolatorParser::WS);
      setState(433);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(434);
    block_contents();
    setState(438);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(435);
      match(StringInterpolatorParser::WS);
      setState(440);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(441);
    match(StringInterpolatorParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interp_evalContext ------------------------------------------------------------------

StringInterpolatorParser::Interp_evalContext::Interp_evalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Interp_evalContext::OPEN() {
  return getToken(StringInterpolatorParser::OPEN, 0);
}

StringInterpolatorParser::Block_contentsContext* StringInterpolatorParser::Interp_evalContext::block_contents() {
  return getRuleContext<StringInterpolatorParser::Block_contentsContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::Interp_evalContext::CLOSE() {
  return getToken(StringInterpolatorParser::CLOSE, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Interp_evalContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Interp_evalContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Interp_evalContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInterp_eval;
}


std::any StringInterpolatorParser::Interp_evalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInterp_eval(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Interp_evalContext* StringInterpolatorParser::interp_eval() {
  Interp_evalContext *_localctx = _tracker.createInstance<Interp_evalContext>(_ctx, getState());
  enterRule(_localctx, 56, StringInterpolatorParser::RuleInterp_eval);
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
    setState(443);
    match(StringInterpolatorParser::OPEN);
    setState(447);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(444);
      match(StringInterpolatorParser::WS);
      setState(449);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(450);
    block_contents();
    setState(454);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(451);
      match(StringInterpolatorParser::WS);
      setState(456);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(457);
    match(StringInterpolatorParser::CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interp_loop_startContext ------------------------------------------------------------------

StringInterpolatorParser::Interp_loop_startContext::Interp_loop_startContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Interp_loop_startContext::OPEN() {
  return getToken(StringInterpolatorParser::OPEN, 0);
}

tree::TerminalNode* StringInterpolatorParser::Interp_loop_startContext::HASH() {
  return getToken(StringInterpolatorParser::HASH, 0);
}

StringInterpolatorParser::Block_contentsContext* StringInterpolatorParser::Interp_loop_startContext::block_contents() {
  return getRuleContext<StringInterpolatorParser::Block_contentsContext>(0);
}

tree::TerminalNode* StringInterpolatorParser::Interp_loop_startContext::CLOSE() {
  return getToken(StringInterpolatorParser::CLOSE, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Interp_loop_startContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Interp_loop_startContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Interp_loop_startContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInterp_loop_start;
}


std::any StringInterpolatorParser::Interp_loop_startContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInterp_loop_start(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Interp_loop_startContext* StringInterpolatorParser::interp_loop_start() {
  Interp_loop_startContext *_localctx = _tracker.createInstance<Interp_loop_startContext>(_ctx, getState());
  enterRule(_localctx, 58, StringInterpolatorParser::RuleInterp_loop_start);
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
    setState(459);
    match(StringInterpolatorParser::OPEN);
    setState(460);
    match(StringInterpolatorParser::HASH);
    setState(464);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(461);
      match(StringInterpolatorParser::WS);
      setState(466);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(467);
    block_contents();
    setState(471);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(468);
      match(StringInterpolatorParser::WS);
      setState(473);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(474);
    match(StringInterpolatorParser::CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interp_loop_endContext ------------------------------------------------------------------

StringInterpolatorParser::Interp_loop_endContext::Interp_loop_endContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* StringInterpolatorParser::Interp_loop_endContext::OPEN() {
  return getToken(StringInterpolatorParser::OPEN, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Interp_loop_endContext::SLASH() {
  return getTokens(StringInterpolatorParser::SLASH);
}

tree::TerminalNode* StringInterpolatorParser::Interp_loop_endContext::SLASH(size_t i) {
  return getToken(StringInterpolatorParser::SLASH, i);
}

tree::TerminalNode* StringInterpolatorParser::Interp_loop_endContext::CLOSE() {
  return getToken(StringInterpolatorParser::CLOSE, 0);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Interp_loop_endContext::WS() {
  return getTokens(StringInterpolatorParser::WS);
}

tree::TerminalNode* StringInterpolatorParser::Interp_loop_endContext::WS(size_t i) {
  return getToken(StringInterpolatorParser::WS, i);
}


size_t StringInterpolatorParser::Interp_loop_endContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInterp_loop_end;
}


std::any StringInterpolatorParser::Interp_loop_endContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInterp_loop_end(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Interp_loop_endContext* StringInterpolatorParser::interp_loop_end() {
  Interp_loop_endContext *_localctx = _tracker.createInstance<Interp_loop_endContext>(_ctx, getState());
  enterRule(_localctx, 60, StringInterpolatorParser::RuleInterp_loop_end);
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
    setState(476);
    match(StringInterpolatorParser::OPEN);
    setState(477);
    match(StringInterpolatorParser::SLASH);
    setState(478);
    match(StringInterpolatorParser::SLASH);
    setState(482);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == StringInterpolatorParser::WS) {
      setState(479);
      match(StringInterpolatorParser::WS);
      setState(484);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(485);
    match(StringInterpolatorParser::CLOSE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interp_loopContext ------------------------------------------------------------------

StringInterpolatorParser::Interp_loopContext::Interp_loopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Interp_loop_startContext* StringInterpolatorParser::Interp_loopContext::interp_loop_start() {
  return getRuleContext<StringInterpolatorParser::Interp_loop_startContext>(0);
}

StringInterpolatorParser::Interpolated_strContext* StringInterpolatorParser::Interp_loopContext::interpolated_str() {
  return getRuleContext<StringInterpolatorParser::Interpolated_strContext>(0);
}

StringInterpolatorParser::Interp_loop_endContext* StringInterpolatorParser::Interp_loopContext::interp_loop_end() {
  return getRuleContext<StringInterpolatorParser::Interp_loop_endContext>(0);
}


size_t StringInterpolatorParser::Interp_loopContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInterp_loop;
}


std::any StringInterpolatorParser::Interp_loopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInterp_loop(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Interp_loopContext* StringInterpolatorParser::interp_loop() {
  Interp_loopContext *_localctx = _tracker.createInstance<Interp_loopContext>(_ctx, getState());
  enterRule(_localctx, 62, StringInterpolatorParser::RuleInterp_loop);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(487);
    interp_loop_start();
    setState(488);
    interpolated_str();
    setState(489);
    interp_loop_end();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interp_stmtContext ------------------------------------------------------------------

StringInterpolatorParser::Interp_stmtContext::Interp_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Interp_evalContext* StringInterpolatorParser::Interp_stmtContext::interp_eval() {
  return getRuleContext<StringInterpolatorParser::Interp_evalContext>(0);
}

StringInterpolatorParser::Interp_loopContext* StringInterpolatorParser::Interp_stmtContext::interp_loop() {
  return getRuleContext<StringInterpolatorParser::Interp_loopContext>(0);
}


size_t StringInterpolatorParser::Interp_stmtContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInterp_stmt;
}


std::any StringInterpolatorParser::Interp_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInterp_stmt(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Interp_stmtContext* StringInterpolatorParser::interp_stmt() {
  Interp_stmtContext *_localctx = _tracker.createInstance<Interp_stmtContext>(_ctx, getState());
  enterRule(_localctx, 64, StringInterpolatorParser::RuleInterp_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(493);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(491);
      interp_eval();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(492);
      interp_loop();
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

//----------------- Interp_normalContext ------------------------------------------------------------------

StringInterpolatorParser::Interp_normalContext::Interp_normalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Interp_normalContext::NORMAL_TEXT() {
  return getTokens(StringInterpolatorParser::NORMAL_TEXT);
}

tree::TerminalNode* StringInterpolatorParser::Interp_normalContext::NORMAL_TEXT(size_t i) {
  return getToken(StringInterpolatorParser::NORMAL_TEXT, i);
}

std::vector<tree::TerminalNode *> StringInterpolatorParser::Interp_normalContext::NORMAL_ESCAPE() {
  return getTokens(StringInterpolatorParser::NORMAL_ESCAPE);
}

tree::TerminalNode* StringInterpolatorParser::Interp_normalContext::NORMAL_ESCAPE(size_t i) {
  return getToken(StringInterpolatorParser::NORMAL_ESCAPE, i);
}


size_t StringInterpolatorParser::Interp_normalContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInterp_normal;
}


std::any StringInterpolatorParser::Interp_normalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInterp_normal(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Interp_normalContext* StringInterpolatorParser::interp_normal() {
  Interp_normalContext *_localctx = _tracker.createInstance<Interp_normalContext>(_ctx, getState());
  enterRule(_localctx, 66, StringInterpolatorParser::RuleInterp_normal);
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
    setState(496); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(495);
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
      setState(498); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Interp_partContext ------------------------------------------------------------------

StringInterpolatorParser::Interp_partContext::Interp_partContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

StringInterpolatorParser::Interp_normalContext* StringInterpolatorParser::Interp_partContext::interp_normal() {
  return getRuleContext<StringInterpolatorParser::Interp_normalContext>(0);
}

StringInterpolatorParser::Interp_stmtContext* StringInterpolatorParser::Interp_partContext::interp_stmt() {
  return getRuleContext<StringInterpolatorParser::Interp_stmtContext>(0);
}


size_t StringInterpolatorParser::Interp_partContext::getRuleIndex() const {
  return StringInterpolatorParser::RuleInterp_part;
}


std::any StringInterpolatorParser::Interp_partContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<StringInterpolatorParserVisitor*>(visitor))
    return parserVisitor->visitInterp_part(this);
  else
    return visitor->visitChildren(this);
}

StringInterpolatorParser::Interp_partContext* StringInterpolatorParser::interp_part() {
  Interp_partContext *_localctx = _tracker.createInstance<Interp_partContext>(_ctx, getState());
  enterRule(_localctx, 68, StringInterpolatorParser::RuleInterp_part);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(502);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case StringInterpolatorParser::NORMAL_TEXT:
      case StringInterpolatorParser::NORMAL_ESCAPE: {
        enterOuterAlt(_localctx, 1);
        setState(500);
        interp_normal();
        break;
      }

      case StringInterpolatorParser::OPEN: {
        enterOuterAlt(_localctx, 2);
        setState(501);
        interp_stmt();
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

//----------------- Interpolated_strContext ------------------------------------------------------------------

StringInterpolatorParser::Interpolated_strContext::Interpolated_strContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<StringInterpolatorParser::Interp_partContext *> StringInterpolatorParser::Interpolated_strContext::interp_part() {
  return getRuleContexts<StringInterpolatorParser::Interp_partContext>();
}

StringInterpolatorParser::Interp_partContext* StringInterpolatorParser::Interpolated_strContext::interp_part(size_t i) {
  return getRuleContext<StringInterpolatorParser::Interp_partContext>(i);
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
  enterRule(_localctx, 70, StringInterpolatorParser::RuleInterpolated_str);

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
    setState(507);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(504);
        interp_part(); 
      }
      setState(509);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
    }
   
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
  enterRule(_localctx, 72, StringInterpolatorParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(510);
    interpolated_str();
    setState(511);
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
