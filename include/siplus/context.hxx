#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_
#define INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_

#include <memory>
#include <string>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "siplus/internal/binary_type_cache.hxx"
#include "siplus/text/accessor.hxx"
#include "siplus/function.hxx"
#include "siplus/text/converter.hxx"
#include "siplus/data.hxx"
#include "siplus/text/iterator.hxx"

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
    ContextInvocationContextBuilder& use_default(UnknownDataTypeContainer data);

    /**
     * @brief Add an additional variable accessible at `$name`
     *
     * @param name The name of the variable to add
     * @param data The data to use at the variable
     */
    ContextInvocationContextBuilder& with(std::string name, UnknownDataTypeContainer data);

    /**
     * @brief Return the build `InvocationContext`
     */
    std::shared_ptr<InvocationContext> build() const;

private:
    ContextInvocationContextBuilder(std::shared_ptr<const SIPlusParserContext> context) : context_(context) {}

    std::shared_ptr<const SIPlusParserContext> context_;
    std::unordered_map<std::string, UnknownDataTypeContainer> variables_;
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
     * @brief Tries to find a converter aboe to convert from `from` to `to`. If no usable
     * converter is found, this throws an error.
     * 
     * @param[in] from The type to convert from
     * @param[in] to The type to convert to
     */
    std::shared_ptr<text::Converter> converter(const TypeInfo& from, const TypeInfo& to) const;

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
    std::shared_ptr<text::Converter> try_converter(const TypeInfo& from, const TypeInfo& to) const;

    UnknownDataTypeContainer convert(const UnknownDataTypeContainer& data, const TypeInfo& to) const;

    template<typename T> requires std::is_base_of_v<TypeInfo, T>
    UnknownDataTypeContainer convert(const UnknownDataTypeContainer& data) const {
        if(data.is<T>()) return data;
        return convert(data, T{});
    }

    /**
     * @brief Create a builder to make an `InvocationContext`
     *
     * @return A builder object
     */
    ContextInvocationContextBuilder builder() const;

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<Function, T>>>
    std::shared_ptr<T> emplace_function(std::string name, Ts&&... args) {
        auto function = std::make_shared<T>(std::forward<Ts>(args)...);
        functions_[name] = function;
        return function;
    }

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<text::Converter, T>>>
    std::shared_ptr<T> emplace_converter(Ts&&... args) {
        return converters_.emplace_item<T>(std::forward<Ts>(args)...);
    }

private:
    //accessing caches
    internal::BinaryTypeCache<text::Converter, &text::Converter::can_convert> converters_;

    //storage
    std::unordered_map<std::string, std::shared_ptr<Function>> functions_;
};

}

#endif  // INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_
