#ifndef INCLUDE_SIPLUS_INVOCATION_CONTEXT_IMPL_H_
#define INCLUDE_SIPLUS_INVOCATION_CONTEXT_IMPL_H_

#include "siplus/context.h"
#include "siplus/invocation_context.h"
#include "siplus/data.h"
#include <memory>
#include <unordered_map>

namespace SIPLUS_NAMESPACE {

/**
 * struct ContextInvocationContext - Base invocation context for SIPlusParserContext.
 */
struct ContextInvocationContext : InvocationContext {
    friend class ContextInvocationContextBuilder;

    ContextInvocationContext(std::shared_ptr<const SIPlusParserContext> context) : context_(context) {}
    virtual bool variable_defined(std::string key) const override;
    virtual const UnknownDataTypeContainer variable(std::string key) const override;
    virtual void set_variable(std::string key, const UnknownDataTypeContainer& value) override;
private:
    std::shared_ptr<const SIPlusParserContext> context_;
    std::unordered_map<std::string, UnknownDataTypeContainer> variables_;
};

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_INVOCATION_CONTEXT_IMPL_H_
