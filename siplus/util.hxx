#pragma once
#ifndef INCLUDE_SIPLUS_INTERNAL_UTIL_HXX_
#define INCLUDE_SIPLUS_INTERNAL_UTIL_HXX_

#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace detail {

template<typename T, typename... Ts>
std::shared_ptr<ValueRetriever> make_retriever(Ts&&... args) {
    return std::static_pointer_cast<ValueRetriever>(
        std::make_shared<T>(std::forward<Ts>(args)...)
    );
}

template<typename Lhs, typename Rhs>
int compare(Lhs lhs, Rhs rhs) {
    if(lhs < rhs) {
        return -1;
    } else if(rhs < lhs) {
        return 1;
    } else {
        return 0;
    }
}


} /* detail */
} /* SIPLUS_NAMESPACE */


#endif  // INCLUDE_SIPLUS_INTERNAL_UTIL_HXX_
