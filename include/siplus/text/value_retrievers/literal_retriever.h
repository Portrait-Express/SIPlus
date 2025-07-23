#ifndef INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_H_
#define INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_H_

#include <any>

#include "siplus/_config.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class LiteralValueRetriever : public ValueRetriever {
public:
    explicit LiteralValueRetriever(UnknownDataTypeContainer value);

    virtual UnknownDataTypeContainer retrieve(UnknownDataTypeContainer value) override;

private:
    UnknownDataTypeContainer value_;
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_LITERAL_RETRIEVER_H_
