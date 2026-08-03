#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace detail {

template<typename T, typename... Ts>
std::shared_ptr<ValueRetriever> make_retriever(Ts&&... args) {
    return std::static_pointer_cast<ValueRetriever>(
        std::make_shared<T>(std::forward<Ts>(args)...)
    );
}

} /* detail */
} /* SIPLUS_NAMESPACE */
