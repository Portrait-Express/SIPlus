#pragma once
#ifndef INCLUDE_SIPLUS_UTIL_H_
#define INCLUDE_SIPLUS_UTIL_H_

#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "siplus/text/value_retrievers/retriever.h"

namespace SIPLUS_NAMESPACE {
namespace util {

namespace detail {

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

template<typename ...Ts>
std::string to_string(const Ts&... value) {
    std::stringstream ss;
    (ss << ... << value);
    return ss.str();
}

} /* util */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_UTIL_H_
