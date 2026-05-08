#pragma once
#ifndef INCLUDE_SIPLUS_INVOCATION_CONTEXT_HXX_
#define INCLUDE_SIPLUS_INVOCATION_CONTEXT_HXX_

#include <memory>
#include <string>
#include <unordered_map>

#include "siplus/config.h"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
    
/**
 * struct InvocationContext - Represents a context for a single invocation of a template.
 *
 * InvocationContexts must not be reused, but you may call build() multiple times on the 
 * builder to get mutliple instances of the same context.
 */
struct InvocationContext : public std::enable_shared_from_this<InvocationContext> {
    /**
     * @brief Get the default data (The data at '.')
     *
     * @return Data container
     */
    virtual UnknownDataTypeContainer default_data() const;

    /**
     * @brief Checks if a variable is defined.
     *
     * @param[in] key The name of the variable
     * @return true if the variable is defined.
     */
    virtual bool variable_defined(std::string key) const = 0;

    /**
     * @brief Get the value of a variable.
     *
     * @param[in] key The variable name
     * @return The data in the variable
     */
    virtual const UnknownDataTypeContainer variable(std::string key) const = 0;

    /**
     * @brief Set a variable's value. Using this as a side-effect is highly 
     * discouraged.
     *
     * @param[in] key The variable name
     * @param[in] val The value
     */
    virtual void set_variable(std::string key, const UnknownDataTypeContainer& val) = 0;

    virtual ~InvocationContext() = default;
};

/**
 * struct InvocationContextWrapperBuilder - Builder class for `InvocationContextWrapper`
 */
struct InvocationContextWrapperBuilder {
    InvocationContextWrapperBuilder(std::shared_ptr<InvocationContext> context) : parent_(context) { }

    InvocationContextWrapperBuilder& use_default(UnknownDataTypeContainer val);
    InvocationContextWrapperBuilder& with(std::string name, UnknownDataTypeContainer val);
    std::shared_ptr<InvocationContext> build();

private:
    std::shared_ptr<InvocationContext> parent_;
    std::unordered_map<std::string, UnknownDataTypeContainer> variables_;
};

InvocationContextWrapperBuilder wrap_scope(std::shared_ptr<InvocationContext> context);

/**
 * struct InvocationContextWrapper - Wraps another InvocationContext to hold new data, 
 * while still accessing prior data.
 *
 * Implementation for scopes. Wrapping an InvocationContext effectively creates a new scope.
 */
struct InvocationContextWrapper : InvocationContext {
    friend struct InvocationContextWrapperBuilder;

    InvocationContextWrapper(std::shared_ptr<InvocationContext> parent) : parent_(parent) {}
    virtual bool variable_defined(std::string key) const override;
    virtual const UnknownDataTypeContainer variable(std::string key) const override;
    virtual void set_variable(std::string key, const UnknownDataTypeContainer& value) override;
private:
    std::shared_ptr<InvocationContext> parent_;
    std::unordered_map<std::string, UnknownDataTypeContainer> variables_;
};

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_INVOCATION_CONTEXT_HXX_
