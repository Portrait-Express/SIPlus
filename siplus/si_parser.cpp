#include "si_parser.h"
#include "siplus/_config.h"
#include "token_stream.h"

namespace SIPLUS_NAMESPACE {
namespace internal {

void SIParser::enableChannel(int channel) {
    if(auto ptr = dynamic_cast<MultiChannelTokenStream*>(_input)) {
        ptr->enable(channel);
    }
}

void SIParser::disableChannel(int channel) {
    if(auto ptr = dynamic_cast<MultiChannelTokenStream*>(_input)) {
        ptr->disable(channel);
    }
}

} /* internal */
} /* SIPLUS_NAMESPACE */
