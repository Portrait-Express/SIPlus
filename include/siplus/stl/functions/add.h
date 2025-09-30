#ifndef INCLUDE_FUNCTIONS_ADD_H_
#define INCLUDE_FUNCTIONS_ADD_H_

#include "siplus/config.h"

#ifdef SIPLUS_INCLUDE_STDLIB

#include <memory>

#include "siplus/context.h"
#include "siplus/function.h"
#include "siplus/internal/binary_type_cache.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

struct AdditionImpl {
    virtual text::UnknownDataTypeContainer 
    add(std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer sum, 
        text::UnknownDataTypeContainer add) = 0;

    virtual bool 
    can_add(std::type_index sum, std::type_index add) = 0;

    virtual ~AdditionImpl() = default;
};

struct DefaultAdder : AdditionImpl {
    text::UnknownDataTypeContainer 
    add(std::shared_ptr<SIPlusParserContext> context,
        text::UnknownDataTypeContainer sum, 
        text::UnknownDataTypeContainer add) override;

    bool can_add(std::type_index sum, std::type_index add) override;
};

struct add_func : Function  {
    explicit add_func(std::weak_ptr<SIPlusParserContext> context) : context_(context) { 
        emplace_adder<DefaultAdder>();
    }

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

    template<typename T, typename... Ts>
    void emplace_adder(const Ts&&... args) {
        cache_.emplace_item<T>(std::forward<Ts>(args)...);
    }

private:
    std::weak_ptr<SIPlusParserContext> context_;
    internal::BinaryTypeCache<AdditionImpl, &AdditionImpl::can_add> cache_;
};

} /* stl */
} /* SIPLUS_NAMESPACE */

#endif  // SIPLUS_INCLUDE_STDLIB

#endif  // INCLUDE_FUNCTIONS_ADD_H_
