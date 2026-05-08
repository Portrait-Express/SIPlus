#pragma once
#ifndef INCLUDE_SIPLUS_STL_HXX_
#define INCLUDE_SIPLUS_STL_HXX_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/stl/converters.hxx"
#include "siplus/stl/functions.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {
    
/**
 * @brief Attach the standard library functions and converters to the context.
 *
 * @param[in] context The context to attach to
 */
void attach_stl(SIPlusParserContext& context);
// Should this be implicit? Is there really a case where it wont be called?
    
} /* stl */
}

#else 

#ifndef SIPLUS_SUPRESS_WARN_NO_STL

#warning "SIPlus was compiled with SIPLUS_INCLUDE_STDLIB OFF. STL not included."

#endif

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_SIPLUS_STL_HXX_
