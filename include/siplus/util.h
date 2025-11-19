#ifndef INCLUDE_SIPLUS_UTIL_H_
#define INCLUDE_SIPLUS_UTIL_H_

#include "siplus/context.h"
#include "siplus/text/data.h"
#include <memory>
#include <sstream>
#include <typeindex>

#ifdef __GNUG__
#include <cstdlib>
#include <cxxabi.h>
#endif

template<typename ...Ts>
std::string to_string(const Ts&... value) {
    std::stringstream ss;
    (ss << ... << value);
    return ss.str();
}


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


namespace SIPLUS_NAMESPACE {
namespace util {

bool is_numeric(std::type_index type);

text::UnknownDataTypeContainer as_base(
    std::shared_ptr<SIPlusParserContext> ctx,
    text::UnknownDataTypeContainer       value
);

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_UTIL_H_
