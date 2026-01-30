#include <string>

#include "siplus/context.hxx"
#include "invocation_context_impl.hxx"
#include "siplus/data.hxx"
#include "siplus/function.hxx"
#include "siplus/text/text.hxx"

#ifdef SIPLUS_INCLUDE_STDLIB
#include "siplus/stl.hxx"
#endif

namespace SIPLUS_NAMESPACE {

ContextInvocationContextBuilder& ContextInvocationContextBuilder::use_default(UnknownDataTypeContainer data) {
    with("0", data);
    return *this;
}

ContextInvocationContextBuilder& ContextInvocationContextBuilder::with(std::string name, UnknownDataTypeContainer data) {
    variables_[name] = data;
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

std::shared_ptr<text::Converter> 
SIPlusParserContext::converter(const TypeInfo& from, const TypeInfo& to) const {
    auto ret = try_converter(from, to);

    if(!ret) {
        throw std::runtime_error{
            "No converter available to convert from " + from.name() + " to " + to.name()
        };
    }

    return ret;
}

std::shared_ptr<text::Converter> 
SIPlusParserContext::try_converter(const TypeInfo& from, const TypeInfo& to) const {
    auto it = converters_.find(from, to);

    if(it == converters_.end()) {
        return nullptr;
    }

    return *it;
}

UnknownDataTypeContainer SIPlusParserContext::convert(const UnknownDataTypeContainer& data, const TypeInfo& to) const {
    if(*data.type == to) return data;

    auto converter = this->converter(*data.type, to);
    return converter->convert(data, to);
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
