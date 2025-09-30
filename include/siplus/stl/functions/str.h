#ifndef INCLUDE_FUNCTIONS_STR_H_
#define INCLUDE_FUNCTIONS_STR_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

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
    ) const override;

    std::weak_ptr<SIPlusParserContext> context_;

};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_STR_H_
