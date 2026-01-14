#ifndef INCLUDE_SIPLUS_BUILD_CONTEXT_H_
#define INCLUDE_SIPLUS_BUILD_CONTEXT_H_

#include "siplus/function.h"
#include "siplus/invocation_context.h"
#include "siplus/parser.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/util.h"
#include <memory>

namespace SIPLUS_NAMESPACE {

struct VariableOpts {
    bool is_persist:1 = false;
    bool is_const:1 = false;
};

struct VariableRetriever : public text::ValueRetriever {
    virtual bool is_persist() const = 0;
    virtual bool is_const() const = 0;
    virtual std::string name() const = 0;

    virtual void set_value(InvocationContext& context, text::UnknownDataTypeContainer value) = 0;
};

struct BuildContext : public std::enable_shared_from_this<BuildContext> {
    BuildContext() {}
    explicit BuildContext(std::shared_ptr<BuildContext> parent) : parent_(parent) {}

    /**
     * @brief Returns true if the specified variable is declared in the current scope 
     * (including parent scopes)
     *
     * @param name the name of the variable
     * @return `true` if declared, `false` otherwise
     */
    bool has_variable(std::string name);

    /**
     * @brief Get a `VariableRetriever` by name.
     *
     * @param name The name of the variable.
     * @param declare If set to `true` this will declare the variable in the 
     * current scope, if not defined.
     */
    std::shared_ptr<VariableRetriever> get_variable(std::string name);

    /**
     * @brief Declare a variable in the current scope
     *
     * @param name The name of the variable.
     * @param opts The options of the variable.
     * @return The created variable
     */
    std::shared_ptr<VariableRetriever> declare_variable(
        std::string name, 
        const VariableOpts& opts
    );

    bool has_function(const std::string& name);
    Function& function(const std::string& name);

    template<typename T, typename... Ts>
    void emplace_function(const std::string& name, Ts&&... args) {
        if(has_function(name)) {
            throw std::runtime_error{util::to_string("Function '@", name, "' already defined")};
        }

        functions_[name] = std::make_unique<T>(std::forward<Ts>(args)...);
    }

private:
    std::shared_ptr<BuildContext> parent_;
    std::unordered_map<std::string, std::shared_ptr<VariableRetriever>> variables_;
    std::unordered_map<std::string, std::unique_ptr<Function>> functions_;
};

/**
 * @brief Make a root build context
 *
 * @param opts The parser options
 */
std::shared_ptr<BuildContext> make_build_context(const ParseOpts opts);

/**
 * @brief Make a scoped build context
 *
 * @param parent The parent build context
 */
std::shared_ptr<BuildContext> make_build_context(std::shared_ptr<BuildContext> parent);
     
} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_SIPLUS_BUILD_CONTEXT_H_
