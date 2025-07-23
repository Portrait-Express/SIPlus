#ifndef INCLUDE_INCLUDE_FUNCTION_H_
#define INCLUDE_INCLUDE_FUNCTION_H_

#include <memory>
#include <vector>

#include "siplus/_config.h"
#include "siplus/text/value_retrievers/retriever.h"

namespace SIPLUS_NAMESPACE {

class Function {
public:
    virtual std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) = 0;

    virtual ~Function() = default;
};

}

#endif  // INCLUDE_INCLUDE_FUNCTION_H_
