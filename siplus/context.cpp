#include <string>

#include "siplus/context.h"
#include "invocation_context_impl.h"
#include "siplus/function.h"
#include "siplus/text/text.h"

#ifdef SIPLUS_INCLUDE_STDLIB
#include "siplus/stl.h"
#endif

namespace SIPLUS_NAMESPACE {

ContextInvocationContextBuilder& ContextInvocationContextBuilder::use_default(text::UnknownDataTypeContainer data) {
    with("0", data);
    return *this;
}

ContextInvocationContextBuilder& ContextInvocationContextBuilder::with(std::string name, text::UnknownDataTypeContainer data) {
    variables_["0"] = data;
    return *this;
}

std::shared_ptr<InvocationContext> ContextInvocationContextBuilder::build() const {
    auto ctx = std::make_shared<ContextInvocationContext>(context_);

    for(auto [k, v] : variables_) {
        ctx->variables_[k] = v;
    }

    return ctx;
}

SIPlusParserContext::SIPlusParserContext() { }

Function& SIPlusParserContext::function(const std::string& name) const {
    auto it = functions_.find(name);

    if(it == functions_.end()) {
        throw std::runtime_error{"Function '" + name + "' not found.",};
    }

    return *it->second;
}

std::shared_ptr<text::Accessor> 
SIPlusParserContext::accessor(const text::UnknownDataTypeContainer& value) const {
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

    throw std::runtime_error{"No accessor available able to handle " + text::get_type_name(value.type)};
}


std::shared_ptr<text::IteratorProvider> 
SIPlusParserContext::iterator(const text::UnknownDataTypeContainer& value) const {
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
        + text::get_type_name(value.type)};
}


std::shared_ptr<text::Converter> 
SIPlusParserContext::converter(std::type_index from, std::type_index to) const {
    auto ret = try_converter(from, to);

    if(!ret) {
        throw std::runtime_error{"No converter available to convert from " 
            + text::get_type_name(from) + " to " + text::get_type_name(to)};
    }

    return ret;
}

std::shared_ptr<text::Converter> 
SIPlusParserContext::try_converter(std::type_index from, std::type_index to) const {
    auto it = converters_.find(from, to);

    if(it == converters_.end()) {
        return nullptr;
    }

    return *it;
}

ContextInvocationContextBuilder SIPlusParserContext::builder() const {
    return ContextInvocationContextBuilder{shared_from_this()};
}

#ifdef SIPLUS_INCLUDE_STDLIB

void
SIPlusParserContext::use_stl() {
    stl::attach_stl(*this);
}

#endif

}
