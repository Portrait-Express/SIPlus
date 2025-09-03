#ifndef INCLUDE_FUNCTIONS_ADD_H_
#define INCLUDE_FUNCTIONS_ADD_H_

#include <memory>

#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

struct add_func : Function  {
    explicit add_func(std::weak_ptr<SIPlusParserContext> context) : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) override;

private:
    std::weak_ptr<SIPlusParserContext> context_;

    struct retriever : public text::ValueRetriever {
        retriever(
            std::vector<std::shared_ptr<text::ValueRetriever>> params,
            std::weak_ptr<SIPlusParserContext> context
        ) : params(params), context_(context) {}

        text::UnknownDataTypeContainer retrieve(text::UnknownDataTypeContainer value) override;

        std::vector<std::shared_ptr<text::ValueRetriever>> params;

    private:
        std::weak_ptr<SIPlusParserContext> context_;
    };
};

} /* stl */
} /* SIPLUS_NAMESPACE */



#endif  // INCLUDE_FUNCTIONS_ADD_H_
