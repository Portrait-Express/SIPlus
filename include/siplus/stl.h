#ifndef INCLUDE_SIPLUS_STL_H_
#define INCLUDE_SIPLUS_STL_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/stl/functions.h"
#include "siplus/stl/converters.h"

namespace SIPLUS_NAMESPACE {
namespace stl {
    
void attach_stl(SIPlusParserContext& context);
    
} /* stl */
}

#else 

#warning "SIPlus was compiled with SIPLUS_INCLUDE_STDLIB OFF. STL not included."

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_SIPLUS_STL_H_
