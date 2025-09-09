#ifndef INCLUDE_SIPLUS_SI_PARSER_CPP_
#define INCLUDE_SIPLUS_SI_PARSER_CPP_

#include "Parser.h"
#include "TokenStream.h"
#include "siplus/_config.h"

namespace SIPLUS_NAMESPACE {
namespace internal {

struct SIParser : antlr4::Parser {
    SIParser(antlr4::TokenStream *input) : Parser(input) {}

    void enableChannel(int channel);
    void disableChannel(int channel);
};
    
} /* internal */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_SI_PARSER_CPP_
