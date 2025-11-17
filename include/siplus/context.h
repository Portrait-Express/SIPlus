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
    Function& function(const std::string& name);

    /**
     * @brief Finds a property accessor for the container passed in. Throws if none found.
     *
     * @param[in] value The container to get an accessor for.
     */
    std::shared_ptr<text::Accessor> accessor(const text::UnknownDataTypeContainer& value);

    /**
     * @brief Gets the `IteratorProvider` for the type held in the container. Throws if none found.
     *
     * @param[in] value The container's type to check
     */
    std::shared_ptr<text::IteratorProvider> iterator(const text::UnknownDataTypeContainer& value);

    /**
     * @brief Tries to find a converter aboe to convert from `from` to `to`. If no usable
     * converter is found, this throws an error.
     * 
     * @param[in] from The type to convert from
     * @param[in] to The type to convert to
     */
    std::shared_ptr<text::Converter> converter(std::type_index from, std::type_index to);

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
    std::shared_ptr<text::Converter> try_converter(std::type_index from, std::type_index to);

    /**
     * @brief Tries to find a converter able to convert from `from` to `to`. If no usable
     * converter is found, this throws an error.
     *
     * @tparam T The type to convert to.
     * @param[in] from The container to convert from.
     */
    template<typename T, typename _T = std::remove_cvref_t<T>>
    std::shared_ptr<text::Converter> 
    converter(const text::UnknownDataTypeContainer& from) { 
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
    try_converter(const text::UnknownDataTypeContainer& from) { 
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
    convert(text::UnknownDataTypeContainer from) {
        return convert(from, typeid(_T));
    }

    /**
     * @brief Tries to convert from the specified object, to the specified type.
     *
     * @param[in] from The container to convert from.
     * @param[in] to The type to convert to
     */
    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from, std::type_index to) {
        if(from.type == to) return from;
        return converter(from.type, to)->convert(from, to);
    }


    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<Function, T>>>
    void emplace_function(std::string name, Ts&&... args) {
        T *ptr = new T{args...};
        std::unique_ptr<Function> unique{ptr};
        functions_[name] = std::move(unique);
    }

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<text::Accessor, T>>>
    void emplace_accessor(Ts&&... args) {
        accessors_.emplace_back(std::make_shared<T>(std::forward<Ts>(args)...));
    }

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<text::IteratorProvider, T>>>
    void emplace_iterator(Ts&&... args) {
        iterators_.emplace_back(std::make_shared<T>(std::forward<Ts>(args)...));
    }

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<text::Converter, T>>>
    void emplace_converter(Ts&&... args) {
        converters_.emplace_item<T>(std::forward<Ts>(args)...);
    }

private:
    //accessing caches
    std::unordered_map<std::type_index, std::shared_ptr<text::Accessor>> accessors_cache_;
    std::unordered_map<std::type_index, std::shared_ptr<text::IteratorProvider>> iterators_cache_;
    internal::BinaryTypeCache<text::Converter, &text::Converter::can_convert> converters_;

    //storage
    std::unordered_map<std::string, std::unique_ptr<Function>> functions_;
    std::vector<std::shared_ptr<text::Accessor>> accessors_;
    std::vector<std::shared_ptr<text::IteratorProvider>> iterators_;
};

}

#endif  // INCLUDE_SIPLUS_TEXT_CONTEXT_H_
