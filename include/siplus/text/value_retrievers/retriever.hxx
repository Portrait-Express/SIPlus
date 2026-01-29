#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_RETRIEVER_HXX_
#define INCLUDE_SIPLUS_TEXT_RETRIEVER_HXX_

#include "siplus/config.hxx"
#include "siplus/invocation_context.hxx"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

class ValueRetriever {
public:
    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const = 0;

    virtual ~ValueRetriever() = default;
};

    
} /* text */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_TEXT_RETRIEVER_HXX_
