#ifndef INCLUDE_FUNCTIONS_COMPARISON_H_
#define INCLUDE_FUNCTIONS_COMPARISON_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB 

#include <memory>
#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

struct cmp_func : Function {
    explicit cmp_func(std::weak_ptr<SIPlusParserContext> context) 
        : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

struct lt_func : Function  {
    explicit lt_func(std::weak_ptr<SIPlusParserContext> context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;
};

struct gt_func : Function  {
    explicit gt_func(std::weak_ptr<SIPlusParserContext> context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;
};


} /* stl */
} /* SIPLUS_NAMESPACE */


#endif

#endif  // INCLUDE_FUNCTIONS_COMPARISON_H_
