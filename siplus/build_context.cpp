#include "build_context.h"
#include "siplus/util.h"

namespace SIPLUS_NAMESPACE {

text::UnknownDataTypeContainer VariableRetriever::retrieve(InvocationContext &value) const {
    return value.variable(name);
}

void VariableRetriever::set_value(
    InvocationContext& context,
    text::UnknownDataTypeContainer value
) const {
    context.set_variable(name, value);
}

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

std::shared_ptr<VariableRetriever> BuildContext::get_variable(std::string name, bool declare) {
    auto it = variables_.find(name);

    if(it == variables_.end()) {
        if(parent_ && parent_->has_variable(name)) {
            return parent_->get_variable(name);
        } else {
            if(declare) {
                auto var = std::make_shared<VariableRetriever>(name);
                variables_[name] = var;
                return var;
            } else {
                throw std::runtime_error{util::to_string("Undefined variable '", name, '\'')};
            }
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
        res->get_variable(global, true);
    }

    return res;
}
     
std::shared_ptr<BuildContext> make_build_context(std::shared_ptr<BuildContext> parent) {
    return std::make_shared<BuildContext>(parent);
}

} /* SIPLUS_NAMESPACE */
