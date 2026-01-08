#ifndef INCLUDE_SIPLUS_TEXT_TEXT_H_
#define INCLUDE_SIPLUS_TEXT_TEXT_H_

#include <memory>
#include <string>
#include <typeindex>
#include <vector>

#include "siplus/config.h"
#include "siplus/context.h"
#include "siplus/text/data.h"

#ifdef __GNUG__
#include <cstdlib>
#include <cxxabi.h>
#endif

namespace SIPLUS_NAMESPACE {
namespace text {

/**
 * @brief Returns true if the type is one of the recognized numeric types
 * double, float, long, int, or short
 *
 * @param type The type to check
 * @return True if the type is numeric, false otherwise
 */
bool is_numeric(std::type_index type);

/**
 * @brief Converts any numeric type to its 'base' common form. Check 
 * `is_numeric` first.
 * double -> double;
 * float -> double;
 * long -> long;
 * int -> long;
 * short -> long;
 *
 * @param ctx Context for conversion
 * @param value The value to convert.
 */
text::UnknownDataTypeContainer as_base(
    std::shared_ptr<const SIPlusParserContext> ctx,
    text::UnknownDataTypeContainer       value
);

inline std::string get_type_name(const std::type_index& type) {
    std::string name{type.name()};

#ifdef __GNUG__
    int status = -2;
    char *buf = __cxxabiv1::__cxa_demangle(name.c_str(), NULL, NULL, &status);
    if(status == 0) {
        name = buf;
    }
    std::free(buf);
#endif

    return name;
}

template<typename _OStream>
_OStream& operator<<(_OStream& out, const UnknownDataTypeContainer& val) {
    if(val.is<short>()) {
        out << val.as<short>();

    } else if(val.is<int>()) {
        out << val.as<int>();

    } else if(val.is<long>()) {
        out << val.as<long>();

    } else if(val.is<float>()) {
        out << val.as<float>();

    } else if(val.is<double>()) {
        out << val.as<double>();

    } else if(val.is<std::string>()) {
        out << val.as<std::string>();

    } else if(val.is<std::vector<UnknownDataTypeContainer>>()) {
        out << val.as<std::vector<UnknownDataTypeContainer>>();

    } else {
        out << '{' << get_type_name(val.type) << ' ' << val.ptr << '}';
    }

    return out;
}

} /* text */
} /* SIPLUS_NAMESPACE */

namespace std {

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
