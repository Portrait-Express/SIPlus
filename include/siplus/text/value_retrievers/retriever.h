#ifndef INCLUDE_SIPLUS_TEXT_RETRIEVER_H_
#define INCLUDE_SIPLUS_TEXT_RETRIEVER_H_

#include "siplus/_config.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class ValueRetriever {
public:
    virtual UnknownDataTypeContainer retrieve(UnknownDataTypeContainer value) = 0;

    virtual ~ValueRetriever() = default;
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_RETRIEVER_H_
