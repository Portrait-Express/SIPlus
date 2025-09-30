#ifndef INCLUDE_STL_CONVERTERS_H_
#define INCLUDE_STL_CONVERTERS_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/context.h"

namespace SIPLUS_NAMESPACE {
namespace stl {
    
void attach_stl_converters(SIPlusParserContext& context);

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_STL_CONVERTERS_H_
