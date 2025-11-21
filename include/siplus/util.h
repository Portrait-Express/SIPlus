#ifndef INCLUDE_SIPLUS_UTIL_H_
#define INCLUDE_SIPLUS_UTIL_H_

#include "siplus/context.h"
#include "siplus/text/data.h"
#include <iostream>
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

namespace detail {

template<size_t N, size_t I, int O, typename... Ts>
auto constexpr get_parameters_first_parent_set(
    std::tuple<Ts...>& tuple,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) {
    if constexpr (N - I == 0) {
        return tuple;
    } else {
        std::get<I>(tuple) = parameters[I + O];
        return get_parameters_first_parent_set<N, I + 1, O>(tuple, parameters);
    }
}

template<size_t, typename T>
using T_ = T;

template<size_t N, size_t... I>
auto constexpr get_parameters_first_parent_(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters,
    std::index_sequence<I...> p
) {
    std::tuple<T_<I, std::shared_ptr<text::ValueRetriever>>...> tuple;

    if(parent) {
        std::get<0>(tuple) = parent;

        if(parameters.size() != N - 1) {
            std::stringstream ss;
            ss << "Expected " << N << " parameters. Got " << parameters.size()+1;
            throw std::runtime_error{ss.str()};
        }

        return get_parameters_first_parent_set<N, 1, -1>(tuple, parameters);
    } else {
        if(parameters.size() != N) {
            std::stringstream ss;
            ss << "Expected " << N << " parameters. Got " << parameters.size();
            throw std::runtime_error{ss.str()};
        }

        return get_parameters_first_parent_set<N, 0, 0>(tuple, parameters);
    }
}

} /* detail */

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

/**
 * @brief Returns a set number of parameters, using the parent as the first 
 * parameter if specified
 *
 * @code
 * auto [first, second] = detail::get_parameters_first_parent<2>(parent, parameters);
 * @endcode
 *
 * @tparam N The number of parameters you expect.
 * @param[in] parent The parent passed to Function::value
 * @param[in] parameters The parameters passed to Function::value
 */
template<size_t N>
auto constexpr get_parameters_first_parent(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) {
    if constexpr (N < 2) {
        std::tuple<std::shared_ptr<text::ValueRetriever>> tuple;

        if(parent) {
            std::get<0>(tuple) = parent;
        } else {
            if(parameters.size() != 1) {
                throw std::runtime_error{"Expected one parameter."};
            }

            std::get<0>(tuple) = parameters[0];
        }

        return tuple;
    } else {
        return detail::get_parameters_first_parent_<N>(parent, parameters, std::make_index_sequence<N>());
    }
}

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_UTIL_H_
