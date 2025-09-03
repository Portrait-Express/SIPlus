#ifndef INCLUDE_FUNCTIONS_STR_H_
#define INCLUDE_FUNCTIONS_STR_H_

#include <memory>

#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

struct str_func : Function  {
    explicit str_func(std::weak_ptr<SIPlusParserContext> context) : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) override;

    std::weak_ptr<SIPlusParserContext> context_;

    struct retriever : public text::ValueRetriever {
        retriever(
            std::shared_ptr<text::ValueRetriever> param,
            std::weak_ptr<SIPlusParserContext> context
        ) : param(param), context_(context) {}

        text::UnknownDataTypeContainer retrieve(const text::UnknownDataTypeContainer& value) override;

        std::shared_ptr<text::ValueRetriever> param;

    private:
        std::weak_ptr<SIPlusParserContext> context_;
    };
private:
};

} /* stl */
} /* SIPLUS_NAMESPACE */



#endif  // INCLUDE_FUNCTIONS_STR_H_
