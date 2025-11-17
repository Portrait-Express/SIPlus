#include <string>

#include "siplus/context.h"
#include "siplus/function.h"
#include "siplus/text/data.h"
#include "siplus/util.h"

#ifdef SIPLUS_INCLUDE_STDLIB
#include "siplus/stl.h"
#endif

namespace SIPLUS_NAMESPACE {

SIPlusParserContext::SIPlusParserContext() { }

Function& SIPlusParserContext::function(const std::string& name) {
    auto it = functions_.find(name);

    if(it == functions_.end()) {
        throw std::runtime_error{"Function '" + name + "' not found.",};
    }

    return *it->second;
}

std::shared_ptr<text::Accessor> 
SIPlusParserContext::accessor(const text::UnknownDataTypeContainer& value) {
    auto it = accessors_cache_.find(value.type);
    if(it != accessors_cache_.end()) {
        return it->second;
    }

    for(auto& accessor : accessors_) {
        if(accessor->can_access(value)) {
            accessors_cache_[value.type] = accessor;
            return accessor;
        }
    }

    throw std::runtime_error{"No accessor available able to handle " + get_type_name(value.type)};
}


std::shared_ptr<text::IteratorProvider> 
SIPlusParserContext::iterator(const text::UnknownDataTypeContainer& value) {
    auto it = iterators_cache_.find(value.type);
    if(it != iterators_cache_.end()) {
        return it->second;
    }

    for(auto& iterator : iterators_) {
        if(iterator->can_iterate(value)) {
            iterators_cache_[value.type] = iterator;
            return iterator;
        }
    }

    throw std::runtime_error{"No iterator provider available able to iterate " 
        + get_type_name(value.type)};
}


std::shared_ptr<text::Converter> 
SIPlusParserContext::converter(std::type_index from, std::type_index to) {
    auto ret = try_converter(from, to);

    if(!ret) {
        throw std::runtime_error{"No converter available to convert from " 
            + get_type_name(from) + " to " + get_type_name(to)};
    }

    return ret;
}

std::shared_ptr<text::Converter> 
SIPlusParserContext::try_converter(std::type_index from, std::type_index to) {
    auto it = converters_.find(from, to);

    if(it == converters_.end()) {
        return nullptr;
    }

    return *it;
}

#ifdef SIPLUS_INCLUDE_STDLIB

void
SIPlusParserContext::use_stl() {
    stl::attach_stl(*this);
}

#endif

}
