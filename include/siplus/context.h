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

class SIPlusParserContext : public std::enable_shared_from_this<SIPlusParserContext> {
public:
    SIPlusParserContext();

#ifdef SIPLUS_INCLUDE_STDLIB
    void use_stl();
#endif

    Function& function(const std::string& name);
    std::shared_ptr<text::Accessor> accessor(const text::UnknownDataTypeContainer& value);
    std::shared_ptr<text::IteratorProvider> iterator(const text::UnknownDataTypeContainer& value);
    std::shared_ptr<text::Converter> converter(std::type_index from, std::type_index to);

    template<typename T, typename _T = std::remove_cvref_t<T>>
    std::shared_ptr<text::Converter> 
    converter(const text::UnknownDataTypeContainer& from) { 
        return converter(from.type, typeid(_T)); 
    }

    template<typename To, typename _T = std::remove_cvref_t<To>>
    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from) {
        return convert(from, typeid(_T));
    }

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
