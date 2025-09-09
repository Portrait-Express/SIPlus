#include "Token.h"
#include "siplus/_config.h"

#include "./token_stream.h"

namespace SIPLUS_NAMESPACE {
namespace internal {

void MultiChannelTokenStream::enable(int channel) {
    if(enabled_channels_.contains(channel)) 
        return;

    enabled_channels_.insert(channel);

    //Move pointer to first token in a valid channel
    int i = _p - 1;
    while (i >= 0) {
        antlr4::Token *token = _tokens[0].get();
        bool tokenThisChannel = token->getChannel() == channel;
        bool tokenValid = enabled_channels_.contains(token->getChannel());
        if (tokenThisChannel || !tokenValid) {
            i--; //step one backwards
        } else {
            break; //token is valid. break
        }
    }
    _p = i + 1; //move token pointer
}

void MultiChannelTokenStream::disable(int channel) {
    enabled_channels_.erase(channel);
    _p = nextTokenOnChannel(_p);
}

antlr4::Token* MultiChannelTokenStream::LT(ssize_t k) {
    lazyInit();
    if (k == 0) {
        return nullptr;
    }
    if (k < 0) {
        return LB(-k);
    }

    int i = _p;
    for (int n = 1;n < k; n++) {
        if (sync(i + 1)) {
            i = nextTokenOnChannel(i + 1);
        }
    }
    return _tokens[i].get();
}

ssize_t MultiChannelTokenStream::adjustSeekIndex(size_t i) {
    return nextTokenOnChannel(i);
}

antlr4::Token* MultiChannelTokenStream::LB(size_t k) {
    if (k == 0 || (_p - k) < 0) {
        return nullptr;
    }
    int i = _p;
    for (int  n = 1; n <= k; n++) {
        i = previousTokenOnChannel(i - 1);
    }
    if (i < 0) {
        return nullptr;
    } else {
        return _tokens[i].get();
    }
}

int MultiChannelTokenStream::getNumberOfOnChannelTokens() {
    int n = 0;
    fill();
    for (int i = 0; i < _tokens.size(); i++) {
        antlr4::Token *t = _tokens[i].get();
        if(enabled_channels_.contains(t->getChannel())) {
            n++;
        }

        if (t->getType() == antlr4::Token::EOF) {
            break;
        }
    }
    return n;
}

int MultiChannelTokenStream::nextTokenOnChannel(int i) {
    sync(i);
    if (i >= size()) {
        return size() - 1;
    }

    antlr4::Token *token = _tokens[i].get();
    while (!enabled_channels_.contains(token->getChannel())) {
        if (token->getType() == antlr4::Token::EOF) {
            return i;
        }
        i++;
        sync(i);
        token = _tokens[i].get();
    }
    return i;
}

int MultiChannelTokenStream::previousTokenOnChannel(int i) {
    sync(i);
    if (i >= size()) {
        return size() - 1;
    }

    while (i >= 0) {
        antlr4::Token *token = _tokens[i].get();
        bool isEOF = token->getType() == antlr4::Token::EOF;
        bool tokenValid = enabled_channels_.contains(token->getChannel());
        if (isEOF || tokenValid) {
            return i;
        }
        i--;
    }
    return i;
}

} /* internal */
}
