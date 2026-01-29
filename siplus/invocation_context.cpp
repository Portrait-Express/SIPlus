#include "invocation_context_impl.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {

InvocationContextWrapperBuilder& InvocationContextWrapperBuilder::use_default(UnknownDataTypeContainer val) {
    with("0", val);
    return *this;
}

InvocationContextWrapperBuilder& InvocationContextWrapperBuilder::with(std::string name, UnknownDataTypeContainer val) {
    variables_[name] = val;
    return *this;
}

std::shared_ptr<InvocationContext> InvocationContextWrapperBuilder::build() {
    auto ctx = std::make_shared<InvocationContextWrapper>(parent_);

    for(auto [k, v] : variables_) {
        ctx->variables_[k] = v;
    }

    return ctx;
}

InvocationContextWrapperBuilder wrap_scope(std::shared_ptr<InvocationContext> context) {
    return InvocationContextWrapperBuilder{context};
}

UnknownDataTypeContainer InvocationContext::default_data() const {
    return variable("0");
}

bool ContextInvocationContext::variable_defined(std::string key) const {
    return variables_.find(key) != variables_.end();
}

const UnknownDataTypeContainer ContextInvocationContext::variable(std::string key) const {
    auto it = variables_.find(key);

    if(it == variables_.end()) {
        throw std::runtime_error{util::to_string("Variable '", key, "' is not defined")};
    }

    return it->second;
}

void ContextInvocationContext::set_variable(std::string key, const UnknownDataTypeContainer& value) {
    variables_[key] = value;
}

bool InvocationContextWrapper::variable_defined(std::string key) const {
    return variables_.find(key) != variables_.end() || (parent_ && parent_->variable_defined(key));
}

const UnknownDataTypeContainer InvocationContextWrapper::variable(std::string key) const {
    auto it = variables_.find(key);

    if(it == variables_.end()) {
        if(parent_) {
            return parent_->variable(key);
        }
        throw std::runtime_error{util::to_string("Variable '", key, "' is not defined")};
    }

    return it->second;
}

void InvocationContextWrapper::set_variable(std::string key, const UnknownDataTypeContainer& value) {
    auto it = variables_.find(key);

    if(it == variables_.end()) {
        if(parent_ && parent_->variable_defined(key)) {
            parent_->set_variable(key, value);
        } else {
            variables_[key] = value;
        }
    } else {
        it->second = value;
    }
}

} /* SIPLUS_NAMESPACE */
