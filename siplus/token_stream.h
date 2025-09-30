#ifndef INCLUDE_SIPLUS_TOKEN_STREAM_CPP_
#define INCLUDE_SIPLUS_TOKEN_STREAM_CPP_

#include "BufferedTokenStream.h"
#include "Token.h"
#include "TokenSource.h"
#include "siplus/config.h"

namespace SIPLUS_NAMESPACE {
namespace internal {

struct MultiChannelTokenStream : antlr4::BufferedTokenStream {

	MultiChannelTokenStream(antlr4::TokenSource *tokenSource) 
        : antlr4::BufferedTokenStream(tokenSource) { }

	void enable(int channel);
	void disable(int channel);
	antlr4::Token* LT(ssize_t k) override ;

protected:
	ssize_t adjustSeekIndex(size_t i) override ;
    antlr4::Token* LB(size_t k) override ;

private:
	int getNumberOfOnChannelTokens();
	int nextTokenOnChannel(int i);
	int previousTokenOnChannel(int i);

private:
    std::set<int> enabled_channels_ = { antlr4::Token::DEFAULT_CHANNEL };
};
    
} /* internal */
}

#endif  // INCLUDE_SIPLUS_TOKEN_STREAM_CPP_
