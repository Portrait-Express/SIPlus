
#ifndef INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_H_
#define INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_H_

#include "siplus/_config.h"
#include "siplus/text/value_retrievers/retriever.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class DummyValueRetriever : public ValueRetriever {
public:
    DummyValueRetriever() {}

    UnknownDataTypeContainer retrieve(UnknownDataTypeContainer value) override {
        return value;
    };
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_DUMMY_RETRIEVER_H_
