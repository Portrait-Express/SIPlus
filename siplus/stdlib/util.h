#ifndef INCLUDE_STDLIB_UTIL_H_
#define INCLUDE_STDLIB_UTIL_H_

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.h"
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

namespace SIPLUS_NAMESPACE {
namespace stl {
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

/**
 * @brief Returns a set of parameters up to the specified number, using 
 * the parent as the first parameter if specified
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
        return get_parameters_first_parent_<N>(parent, parameters, std::make_index_sequence<N>());
    }
}

} /* detail */
} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_STDLIB_UTIL_H_
