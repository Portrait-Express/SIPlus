#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_TEXT_H_
#define INCLUDE_SIPLUS_TEXT_TEXT_H_

#include <memory>
#include <string>
#include <typeindex>
#include <vector>

#include "siplus/config.h"
#include "siplus/context.h"
#include "siplus/data.h"
#include "siplus/types/array.h"
#include "siplus/types/float.h"
#include "siplus/types/integer.h"
#include "siplus/types/string.h"

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

#endif  // INCLUDE_SIPLUS_TEXT_TEXT_H_
