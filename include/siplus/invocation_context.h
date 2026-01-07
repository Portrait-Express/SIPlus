#ifndef INCLUDE_SIPLUS_INVOCATION_CONTEXT_H_
#define INCLUDE_SIPLUS_INVOCATION_CONTEXT_H_

#include "siplus/text/data.h"
#include <memory>

namespace SIPLUS_NAMESPACE {
    
struct InvocationContext : public std::enable_shared_from_this<InvocationContext> {
    virtual text::UnknownDataTypeContainer default_data() const;
    virtual bool variable_defined(std::string key) const = 0;
    virtual const text::UnknownDataTypeContainer variable(std::string key) const = 0;
    virtual void set_variable(std::string key, const text::UnknownDataTypeContainer& val) = 0;
};

/**
 * struct InvocationContextWrapperBuilder - Builder class for `InvocationContextWrapper`
 */
struct InvocationContextWrapperBuilder {
    InvocationContextWrapperBuilder(std::shared_ptr<InvocationContext> context) : parent_(context) { }

    InvocationContextWrapperBuilder& use_default(text::UnknownDataTypeContainer val);
    InvocationContextWrapperBuilder& with(std::string name, text::UnknownDataTypeContainer val);
    std::shared_ptr<InvocationContext> build();

private:
    std::shared_ptr<InvocationContext> parent_;
    std::unordered_map<std::string, text::UnknownDataTypeContainer> variables_;
};

InvocationContextWrapperBuilder wrap_scope(std::shared_ptr<InvocationContext> context);

/**
 * struct InvocationContextWrapper - Wraps another InvocationContext to hold new data, while still accessing prior data.
 */
struct InvocationContextWrapper : InvocationContext {
    friend struct InvocationContextWrapperBuilder;

    InvocationContextWrapper(std::shared_ptr<InvocationContext> parent) : parent_(parent) {}
    virtual bool variable_defined(std::string key) const override;
    virtual const text::UnknownDataTypeContainer variable(std::string key) const override;
    virtual void set_variable(std::string key, const text::UnknownDataTypeContainer& value) override;
private:
    std::shared_ptr<InvocationContext> parent_;
    std::unordered_map<std::string, text::UnknownDataTypeContainer> variables_;
};

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_INVOCATION_CONTEXT_H_
