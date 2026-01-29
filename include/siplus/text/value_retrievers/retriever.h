#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_RETRIEVER_H_
#define INCLUDE_SIPLUS_TEXT_RETRIEVER_H_

#include "siplus/config.h"
#include "siplus/invocation_context.h"
#include "siplus/data.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class ValueRetriever {
public:
    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const = 0;

    virtual ~ValueRetriever() = default;
};

    
} /* text */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_TEXT_RETRIEVER_H_
