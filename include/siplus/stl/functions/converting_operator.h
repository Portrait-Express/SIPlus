#ifndef INCLUDE_FUNCTIONS_CONVERTING_OPERATOR_H_
#define INCLUDE_FUNCTIONS_CONVERTING_OPERATOR_H_

#include "siplus/config.h"
#include <optional>

#ifdef SIPLUS_INCLUDE_STDLIB

#include "siplus/context.h"
#include "siplus/text/data.h"
#include <memory>

namespace SIPLUS_NAMESPACE {
namespace stl {

struct operator_impl {
    virtual SIPlus::text::UnknownDataTypeContainer invoke(
        std::shared_ptr<SIPlusParserContext>   context,
        text::UnknownDataTypeContainer         lhs, 
        text::UnknownDataTypeContainer         rhs
    ) = 0;

    virtual bool can_handle(std::type_index lhs, std::type_index rhs) const = 0;

    virtual ~operator_impl() = default;
};

struct converting_operator_function : Function {
    explicit converting_operator_function(
        std::weak_ptr<SIPlusParserContext> context
    ) : context_(context) { }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

    template<typename T, typename... Ts>
    converting_operator_function& emplace_impl(const Ts&&... args) {
        cache_.emplace_item<T>(std::forward<Ts>(args)...);
        return *this;
    }

    bool has_impl(std::type_index lhs, std::type_index rhs) const;
    std::shared_ptr<operator_impl> find_impl(std::type_index lhs, std::type_index rhs) const;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    internal::BinaryTypeCache<operator_impl, &operator_impl::can_handle> cache_;
};

} /* stl */
} /* SIPLUS_NAMESPACE  */

#endif // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_CONVERTING_OPERATOR_H_
