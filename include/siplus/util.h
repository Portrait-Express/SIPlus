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

template<typename T>
std::stringstream& operator<<(std::stringstream& out, const std::vector<T>& val) {
    out << '{';

    for(int i = 0; i < val.size(); i++) {
        out << '"' << val[i] << '"';
        
        if(i < val.size() - 1) {
            out << ", ";
        }
    }

    out << '}';

    return out;
}

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

template<size_t A, size_t B>
auto constexpr tmin() {
    if constexpr (A < B) {
        return A;
    } else {
        return B;
    }
}

template<
    size_t N, 
    size_t __TupleStart, 
    size_t __CurrentIndex = 0, 
    typename... Ts
>
std::tuple<Ts...> constexpr get_parameters_first_parent_set(
    std::tuple<Ts...>& tuple,
    const std::vector<std::shared_ptr<text::ValueRetriever>>& parameters
) {
    if constexpr (__CurrentIndex >= N) {
        return tuple;
    } else {
        if(__CurrentIndex < parameters.size()) {
            std::get<__TupleStart + __CurrentIndex>(tuple) = parameters[__CurrentIndex];
        }
        return get_parameters_first_parent_set<N, __TupleStart, __CurrentIndex + 1>(tuple, parameters);
    }
}

template<size_t, typename T>
using T_ = T;

template<size_t N, size_t NO, size_t... I>
std::tuple<T_<I, std::shared_ptr<text::ValueRetriever>>...> 
constexpr get_parameters_first_parent_(
    const std::shared_ptr<text::ValueRetriever>& parent,
    const std::vector<std::shared_ptr<text::ValueRetriever>>& parameters,
    std::index_sequence<I...> p
) {
    std::tuple<T_<I, std::shared_ptr<text::ValueRetriever>>...> tuple;
    size_t num_params = parameters.size();

    if(parent) {
        std::get<0>(tuple) = parent;

        if(num_params < N - 1) {
            std::stringstream ss;
            ss << "Expected at least " << N << " parameters. Got " << num_params+1;
            throw std::runtime_error{ss.str()};
        }

        if(num_params > N + NO - 1) {
            std::stringstream ss;
            ss << "Expected at most " << N + NO << " parameters. Got " << num_params+1;
            throw std::runtime_error{ss.str()};
        }

        return get_parameters_first_parent_set<N + NO - 1, 1>(tuple, parameters);
    } else {
        if(num_params < N) {
            std::stringstream ss;
            ss << "Expected at least " << N << " parameters. Got " << num_params;
            throw std::runtime_error{ss.str()};
        }

        if(num_params > N + NO) {
            std::stringstream ss;
            ss << "Expected at most " << N + NO << " parameters. Got " << num_params;
            throw std::runtime_error{ss.str()};
        }

        return get_parameters_first_parent_set<N + NO, 0>(tuple, parameters);
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
 * @tparam NO The number of optional parameters that can be specified after the last parameter.
 * @param[in] parent The parent passed to Function::value
 * @param[in] parameters The parameters passed to Function::value
 */
template<size_t N, size_t NO = 0>
auto constexpr get_parameters_first_parent(
    const std::shared_ptr<text::ValueRetriever>& parent,
    const std::vector<std::shared_ptr<text::ValueRetriever>>& parameters
) {
    return detail::get_parameters_first_parent_<N, NO>(parent, parameters, std::make_index_sequence<N+NO>());
}

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_UTIL_H_
