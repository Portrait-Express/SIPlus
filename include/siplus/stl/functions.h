#ifndef INCLUDE_STL_FUNCTIONS_H_
#define INCLUDE_STL_FUNCTIONS_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/stl/functions/add.h"
#include "siplus/stl/functions/map.h"
#include "siplus/stl/functions/str.h"
#include "siplus/stl/functions/if.h"

namespace SIPLUS_NAMESPACE {
namespace stl {
    
void attach_stl_functions(SIPlusParserContext& context);

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif

#endif  // INCLUDE_STL_FUNCTIONS_H_
