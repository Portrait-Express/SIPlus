#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_TEXT_HXX_
#define INCLUDE_SIPLUS_TEXT_TEXT_HXX_

#include <memory>
#include <string>
#include <typeindex>
#include <vector>

#include "siplus/config.h"
#include "siplus/context.hxx"
#include "siplus/data.hxx"
#include "siplus/types/array.hxx"
#include "siplus/types/float.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"

#ifdef __GNUG__
#include <cstdlib>
#include <cxxabi.h>
#endif

namespace SIPLUS_NAMESPACE {
namespace text {

template<typename _OStream>
_OStream& operator<<(_OStream& out, const UnknownDataTypeContainer& val) {
    if(val.is<types::IntegerType>()) {
        out << val.as<types::IntegerType>();
    } else if(val.is<types::FloatType>()) {
        out << val.as<types::FloatType>();
    } else if(val.is<types::StringType>()) {
        out << val.as<types::StringType>();
    } else if(val.is<types::ArrayType>()) {
        out << val.as<types::ArrayType>();
    } else {
        out << '{' << val.type->name() << ' ' << val.ptr << '}';
    }

    return out;
}

} /* text */
} /* SIPLUS_NAMESPACE */

namespace std {

template<typename _OStream, typename T>
_OStream& operator<<(_OStream& stream, std::function<T> func) {
    stream << "(function)";
    return stream;
}

template<typename _OStream, typename T>
_OStream& operator<<(_OStream& out, const std::vector<T>& val) {
    out << "std::vector{";

    for(int i = 0; i < val.size(); i++) {
        out << '"' << val << '"';
        
        if(i < val.size() - 1) {
            out << ", ";
        }
    }

    out << '}';

    return out;
}

} /* std */

#endif  // INCLUDE_SIPLUS_TEXT_TEXT_HXX_
