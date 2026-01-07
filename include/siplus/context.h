#ifndef INCLUDE_SIPLUS_TEXT_CONTEXT_H_
#define INCLUDE_SIPLUS_TEXT_CONTEXT_H_

#include <memory>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "siplus/internal/binary_type_cache.h"
#include "siplus/text/accessor.h"
#include "siplus/function.h"
#include "siplus/text/converter.h"
#include "siplus/text/data.h"
#include "siplus/text/iterator.h"

namespace SIPLUS_NAMESPACE {

/**
 * @brief The context object passed around between SIPlus objects to communicate converters,
 * accesors, iterators, and other data related information.
 */
class SIPlusParserContext;

/**
 * struct ContextInvocationContextBuilder - Builder class for a root `InvocationContext`
 */
struct ContextInvocationContextBuilder {
    friend class SIPlusParserContext;

    /**
     * @brief Set the default data for this invocation. The data accessible at `$0` or `.`.
     * Calling `with("0", data)`, is an equivalent call, but prefer this.
     *
     * @param data The data to use
     */
    ContextInvocationContextBuilder& use_default(text::UnknownDataTypeContainer data);

    /**
     * @brief Add an additional variable accessible at `$name`
     *
     * @param name The name of the variable to add
     * @param data The data to use at the variable
     */
    ContextInvocationContextBuilder& with(std::string name, text::UnknownDataTypeContainer data);

    /**
     * @brief Return the build `InvocationContext`
     */
    std::shared_ptr<InvocationContext> build() const;

private:
    ContextInvocationContextBuilder(std::shared_ptr<const SIPlusParserContext> context) : context_(context) {}

    std::shared_ptr<const SIPlusParserContext> context_;
    std::unordered_map<std::string, text::UnknownDataTypeContainer> variables_;
};

class SIPlusParserContext : public std::enable_shared_from_this<SIPlusParserContext> {
public:
    SIPlusParserContext();

#ifdef SIPLUS_INCLUDE_STDLIB
    /**
     * @brief Attaches the STL library of functions and converters, and iterators to this context.
     */
    void use_stl();
#endif

    /**
     * @brief Finds a function instance with the specified name.
     *
     * @param[int] name The name of the function to find.
     */
    Function& function(const std::string& name) const;

    /**
     * @brief Finds a property accessor for the container passed in. Throws if none found.
     *
     * @param[in] value The container to get an accessor for.
     */
    std::shared_ptr<text::Accessor> accessor(const text::UnknownDataTypeContainer& value) const;

    /**
     * @brief Gets the `IteratorProvider` for the type held in the container. Throws if none found.
     *
     * @param[in] value The container's type to check
     */
    std::shared_ptr<text::IteratorProvider> iterator(const text::UnknownDataTypeContainer& value) const;

    /**
     * @brief Tries to find a converter aboe to convert from `from` to `to`. If no usable
     * converter is found, this throws an error.
     * 
     * @param[in] from The type to convert from
     * @param[in] to The type to convert to
     */
    std::shared_ptr<text::Converter> converter(std::type_index from, std::type_index to) const;

    /**
     * @brief Tries to find a converter aboe to convert from `from` to `to`. Returned 
     * `shared_ptr` will be nullptr if none is found. Use `std::shared_ptr::operator bool()` 
     * to check validity.
     *
     * Use this as a way to check if a conversion is legal.
     *
     * @code
     * if(ctx->try_converter(container.type, typeid(long))) {
     *     ctx->convert<long>(container);
     *     //...
     * }
     * @endcode
     *
     * @param[in] from The type to convert from
     * @param[in] to The type to convert to
     */
    std::shared_ptr<text::Converter> try_converter(std::type_index from, std::type_index to) const;

    /**
     * @brief Create a builder to make an `InvocationContext`
     *
     * @return A builder object
     */
    ContextInvocationContextBuilder builder() const;

    /**
     * @brief Tries to find a converter able to convert from `from` to `to`. If no usable
     * converter is found, this throws an error.
     *
     * @tparam T The type to convert to.
     * @param[in] from The container to convert from.
     */
    template<typename T, typename _T = std::remove_cvref_t<T>>
    std::shared_ptr<text::Converter> 
    converter(const text::UnknownDataTypeContainer& from) const { 
        return converter(from.type, typeid(_T)); 
    }

    /**
     * @brief Tries to find a converter aboe to convert from `from` to `to`. Returned 
     * `shared_ptr` will be nullptr if none is found. Use `std::shared_ptr::operator bool()` 
     * to check validity.
     *
     * Use this as a way to check if a conversion is legal.
     *
     * @code
     * if(ctx->try_converter<long>(container.type)) {
     *     ctx->convert<long>(container);
     *     //...
     * }
     * @endcode
     *
     * @tparam T The type to convert to
     * @param[in] from The type to convert from
     */
    template<typename T>
    std::shared_ptr<text::Converter> 
    try_converter(const text::UnknownDataTypeContainer& from) const { 
        return try_converter(from.type, typeid(T));
    }

    /**
     * @brief Tries to convert from the specified object, to the specified type.
     *
     * @tparam T The type to convert to.
     * @param[in] from The container to convert from.
     */
    template<typename To, typename _T = std::remove_cvref_t<To>>
    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from) const {
        return convert(from, typeid(_T));
    }

    /**
     * @brief Tries to convert from the specified object, to the specified type.
     *
     * @param[in] from The container to convert from.
     * @param[in] to The type to convert to
     */
    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from, std::type_index to) const {
        if(from.type == to) return from;
        return converter(from.type, to)->convert(from, to);
    }


    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<Function, T>>>
    std::shared_ptr<T> emplace_function(std::string name, Ts&&... args) {
        auto function = std::make_shared<T>(std::forward<Ts>(args)...);
        functions_[name] = function;
        return function;
    }

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<text::Accessor, T>>>
    std::shared_ptr<T> emplace_accessor(Ts&&... args) {
        auto accessor = std::make_shared<T>(std::forward<Ts>(args)...);
        accessors_.emplace_back(accessor);
        return accessor;
    }

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<text::IteratorProvider, T>>>
    std::shared_ptr<T> emplace_iterator(Ts&&... args) {
        auto iterator = std::make_shared<T>(std::forward<Ts>(args)...);
        iterators_.emplace_back(iterator);
        return iterator;
    }

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<text::Converter, T>>>
    std::shared_ptr<T> emplace_converter(Ts&&... args) {
        return converters_.emplace_item<T>(std::forward<Ts>(args)...);
    }

private:
    //accessing caches
    mutable std::unordered_map<std::type_index, std::shared_ptr<text::Accessor>> accessors_cache_;
    mutable std::unordered_map<std::type_index, std::shared_ptr<text::IteratorProvider>> iterators_cache_;
    internal::BinaryTypeCache<text::Converter, &text::Converter::can_convert> converters_;

    //storage
    std::unordered_map<std::string, std::shared_ptr<Function>> functions_;
    std::vector<std::shared_ptr<text::Accessor>> accessors_;
    std::vector<std::shared_ptr<text::IteratorProvider>> iterators_;
};

}

#endif  // INCLUDE_SIPLUS_TEXT_CONTEXT_H_
