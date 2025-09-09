#ifndef INCLUDE_FUNCTIONS_MAP_H_
#define INCLUDE_FUNCTIONS_MAP_H_

#include <memory>

#include "siplus/context.h"
#include "siplus/function.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

struct map_func : Function  {
    explicit map_func(std::weak_ptr<SIPlusParserContext> context) 
        : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

} /* stl */
} /* SIPLUS_NAMESPACE */



#endif  // INCLUDE_FUNCTIONS_MAP_H_
