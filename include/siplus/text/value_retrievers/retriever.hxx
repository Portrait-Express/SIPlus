#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_RETRIEVER_HXX_
#define INCLUDE_SIPLUS_TEXT_RETRIEVER_HXX_

#include "siplus/config.h"
#include "siplus/invocation_context.hxx"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

/**
 * @brief A ValueRetriever is an object that supplies a value on invocation. This is used
 * to represent Expression templates.
 */
class ValueRetriever {
public:
    /**
     * @brief Override this to provide a value on invocation.
     *
     * @param[in] value The InvocationContext
     * @return The result of your retriever
     */
    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const = 0;

    virtual ~ValueRetriever() = default;
};

    
} /* text */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_TEXT_RETRIEVER_HXX_
