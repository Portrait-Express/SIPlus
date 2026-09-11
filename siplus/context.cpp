#include <string>

#include "siplus/context.hxx"
#include "invocation_context_impl.hxx"
#include "stdlib/stl.hxx"

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

SIPlusParserContext::SIPlusParserContext() { 
    attach_stl(*this);
}

Function& SIPlusParserContext::function(const std::string& name) const {
    auto it = functions_.find(name);

    if(it == functions_.end()) {
        throw std::runtime_error{"Function '" + name + "' not found.",};
    }

    return *it->second;
}

ContextInvocationContextBuilder SIPlusParserContext::builder() const {
    return ContextInvocationContextBuilder{shared_from_this()};
}

void SIPlusParserContext::emplace_function(std::string name, std::shared_ptr<Function> function) {
    functions_[name] = function;
}

}
