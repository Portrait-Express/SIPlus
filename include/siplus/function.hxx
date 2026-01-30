#pragma once
#ifndef INCLUDE_INCLUDE_FUNCTION_HXX_
#define INCLUDE_INCLUDE_FUNCTION_HXX_

#include <memory>
#include <vector>

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {

class Function {
public:
    virtual std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const = 0;

    virtual ~Function() = default;
};

}

#endif  // INCLUDE_INCLUDE_FUNCTION_HXX_
