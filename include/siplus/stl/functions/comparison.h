#ifndef INCLUDE_FUNCTIONS_COMPARISON_H_
#define INCLUDE_FUNCTIONS_COMPARISON_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB 

#include <memory>
#include <vector>

#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

struct lt_func : Function  {
    explicit lt_func(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<Function> cmp_func
    ) : ctx_(context), cmp_(cmp_func) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<Function> cmp_;
};

struct gt_func : Function  {
    explicit gt_func(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<Function> cmp_func
    ) : ctx_(context), cmp_(cmp_func) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<Function> cmp_;
};

struct eq_func : Function  {
    explicit eq_func(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<Function> cmp_func
    ) : ctx_(context), cmp_(cmp_func) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<Function> cmp_;
};


} /* stl */
} /* SIPLUS_NAMESPACE */


#endif

#endif  // INCLUDE_FUNCTIONS_COMPARISON_H_
