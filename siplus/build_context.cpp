#include "siplus/build_context.h"
#include "siplus/data.h"

namespace SIPLUS_NAMESPACE {

namespace {

struct VariableRetrieverImpl : VariableRetriever {
    VariableRetrieverImpl(
        std::string name,
        bool is_const
    ) : name_(name), is_const_(is_const) {}

    virtual bool is_persist() const override;
    virtual bool is_const() const override;
    virtual std::string name() const override;

    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const override;
    virtual void set_value(InvocationContext& context, UnknownDataTypeContainer value) override;

private:
    std::string name_;
    bool is_const_:1 = false;
    bool initialized_:1 = false;
};

bool VariableRetrieverImpl::is_persist() const { return false; }
bool VariableRetrieverImpl::is_const() const { return is_const_; }
std::string VariableRetrieverImpl::name() const { return name_; }

UnknownDataTypeContainer VariableRetrieverImpl::retrieve(
    InvocationContext& context
) const {
    return context.variable(name_);
}

void VariableRetrieverImpl::set_value(
    InvocationContext& context, 
    UnknownDataTypeContainer value
) {
    if(is_const() && initialized_) {
        throw std::runtime_error{util::to_string(
            "Attempted to mutate a const variable '$", name(), "'."
        )};
    }

    initialized_ = true;
    context.set_variable(name_, value);
}

struct PersistentVariableRetrieverImpl : VariableRetriever {
    PersistentVariableRetrieverImpl(
        std::string name,
        bool is_const
    ) : name_(name), is_const_(is_const) {}

    virtual bool is_persist() const override;
    virtual bool is_const() const override;
    virtual std::string name() const override;

    UnknownDataTypeContainer retrieve(InvocationContext& context) const override;
    virtual void set_value(InvocationContext& context, UnknownDataTypeContainer value) override;

private:
    std::string name_;
    UnknownDataTypeContainer data_;
    bool is_const_:1 = false;
    bool initialized_:1 = false;
};

bool PersistentVariableRetrieverImpl::is_persist() const { return true; }
bool PersistentVariableRetrieverImpl::is_const() const { return is_const_; }
std::string PersistentVariableRetrieverImpl::name() const { return name_; }

UnknownDataTypeContainer 
PersistentVariableRetrieverImpl::retrieve(InvocationContext& context) const {
    return data_;
}

void PersistentVariableRetrieverImpl::set_value(
    InvocationContext& context, 
    UnknownDataTypeContainer value
) {
    if(is_const() && initialized_) {
        throw std::runtime_error{util::to_string(
            "Attempted to mutate a const variable '$", name(), "'."
        )};
    }

    initialized_ = true;
    data_ = value;
}

} /* anonymous */

bool BuildContext::has_variable(std::string name) {
    auto it = variables_.find(name);

    if(it == variables_.end()) {
        if(parent_) {
            return parent_->has_variable(name);
        }

        return false;
    }

    return true;
}

std::shared_ptr<VariableRetriever> BuildContext::declare_variable(
    std::string name,
    const VariableOpts& opts
) {
    std::shared_ptr<VariableRetriever> variable;

    if(variables_.contains(name)) {
        throw std::runtime_error{util::to_string("Redefinition of '$", name, "'")};
    }

    if(opts.is_persist) {
        variable = std::make_shared<PersistentVariableRetrieverImpl>(name, opts.is_const);
    } else {
        variable = std::make_shared<VariableRetrieverImpl>(name, opts.is_const);
    }

    variables_[name] = variable;
    return variable;
}

std::shared_ptr<VariableRetriever> BuildContext::get_variable(std::string name) {
    auto it = variables_.find(name);

    if(it == variables_.end()) {
        if(parent_) {
            return parent_->get_variable(name);
        } else {
            throw std::runtime_error{util::to_string("Undefined variable '", name, '\'')};
        }
    }

    return it->second;
}

bool BuildContext::has_function(const std::string& name) {
    auto it = functions_.find(name);

    if(it == functions_.end()) {
        return parent_ && parent_->has_function(name);
    } else {
        return true;
    }
}

Function& BuildContext::function(const std::string& name) {
    auto it = functions_.find(name);

    if(it == functions_.end()) {
        if(parent_) {
            return parent_->function(name);
        } else {
            throw std::runtime_error{util::to_string("Function '@", name, "' not defined")};
        }
    } else {
        return *it->second;
    }
}

std::shared_ptr<BuildContext> make_build_context(const ParseOpts opts) {
    auto res = std::make_shared<BuildContext>();

    for(auto global : opts.globals) {
        VariableOpts varOpts;
        varOpts.is_const = true;
        res->declare_variable(global, varOpts);
    }

    return res;
}
     
std::shared_ptr<BuildContext> make_build_context(std::shared_ptr<BuildContext> parent) {
    return std::make_shared<BuildContext>(parent);
}

} /* SIPLUS_NAMESPACE */
