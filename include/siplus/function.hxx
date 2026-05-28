#pragma once
#ifndef INCLUDE_INCLUDE_FUNCTION_HXX_
#define INCLUDE_INCLUDE_FUNCTION_HXX_

#include <memory>
#include <vector>

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {

/**
 * @brief Base class for a function's implementation. Override this to implement your own function.
 */
class SIPLUS_EXPORT Function {
public:
    /**
     * @brief Get the ValueRetriever for an invocation of a function.
     *
     * This is called when a function is called in a template.
     * Your returned ValueRetriever should call your parameters' .retrieve() methods to 
     * get the actual *values* passed into these parameters.
     *
     * @param[in] parent This is the parameter passed in through '|'. This will be falsy 
     * if there is no such parameter.
     * @param[in] parameters Any values passed in the parameter list.
     */
    virtual std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const = 0;

    virtual ~Function() = default;
};

}

#endif  // INCLUDE_INCLUDE_FUNCTION_HXX_
