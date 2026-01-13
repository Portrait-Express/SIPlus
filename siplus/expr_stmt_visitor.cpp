#include "expr_stmt_visitor.h"
#include "expr_visitor.h"
#include "generated/StringInterpolatorParser.h"
#include "siplus/context.h"
#include "siplus/invocation_context.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include <iterator>
#include <memory>
#include <vector>

namespace SIPLUS_NAMESPACE {

namespace {

//I hate this solution for storing the scope, but its the best I can come up with
void store_function_context(const std::string function, std::shared_ptr<InvocationContext> ctx) {
    ctx->set_variable("*@" + function, text::make_data(std::weak_ptr{ctx}));
}

std::shared_ptr<InvocationContext> get_function_context(const std::string function, InvocationContext& ctx) {
    return ctx.variable("*@" + function).as<std::weak_ptr<InvocationContext>>().lock();
}

struct FuncDefStmt : Statement {
    std::string name;

    FuncDefStmt(std::string name) : name(name) {}

    void invoke(InvocationContext& context) override {
        //Store function definition location's InvocationContext for later 
        //use on function execution
        store_function_context(name, context.shared_from_this());
    }
};

struct AssignStmt : Statement {
    AssignStmt(
        std::shared_ptr<VariableRetriever> variable,
        std::shared_ptr<text::ValueRetriever> expression
    ) : variable_(variable), expression_(expression) { }

    void invoke(InvocationContext& ctx) override {
        if(variable_->is_persist()) {
            if(persistInitialized_) return;
            persistInitialized_ = true;
        }

        variable_->set_value(ctx, expression_->retrieve(ctx));
    }

private:
    std::shared_ptr<VariableRetriever> variable_;
    std::shared_ptr<text::ValueRetriever> expression_;
    bool persistInitialized_:1 = false;
};

struct ExprStmt : Statement {
    ExprStmt(
        std::shared_ptr<text::ValueRetriever> expression
    ) : expression_(expression) { }

    void invoke(InvocationContext& ctx) override {
        expression_->retrieve(ctx);
    }

private:
    std::shared_ptr<text::ValueRetriever> expression_;
};

struct ParameterInfo {
    std::string name;
    bool required;
};

struct CustomFunction : Function {
    CustomFunction(
        std::string name,
        std::vector<ParameterInfo> parameters,
        std::shared_ptr<text::ValueRetriever> expr
    ) : name_(name), parameters_(parameters), expr_(expr) {}

    virtual std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const;
    
private:
    std::string name_;
    std::vector<ParameterInfo> parameters_;
    std::shared_ptr<text::ValueRetriever> expr_;
};

struct CustomFuncImpl : text::ValueRetriever {
    using parameter_info = std::pair<std::string, std::shared_ptr<text::ValueRetriever>>;

    CustomFuncImpl(
        std::string name,
        std::vector<parameter_info> parameters,
        std::shared_ptr<text::ValueRetriever> expr
    ) : name_(name), parameters_(parameters), expr_(expr) {}

    text::UnknownDataTypeContainer retrieve(InvocationContext &value) const override;

private:
    std::string name_;
    std::shared_ptr<text::ValueRetriever> expr_;
    std::vector<parameter_info> parameters_;
};

std::shared_ptr<text::ValueRetriever> CustomFunction::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    if(parent) {
        parameters.insert(parameters.begin(), parent);
    }

    if(parameters.size() > parameters_.size()) {
        throw std::runtime_error{util::to_string(
            "Too many parameters specified for '@", name_, "'. Expected at most ", 
            parameters_.size(), " recieved, ", parameters_.size(), "."
        )};
    }

    std::vector<CustomFuncImpl::parameter_info> params{parameters.size()};
    for(int i = 0; i < parameters_.size(); i++) {
        auto& param = parameters_[i];

        if(i >= parameters.size())  {
            if(param.required) {
                auto minRequired = std::ranges::find_if(parameters_, 
                    [](const ParameterInfo& i) { return i.required; });

                throw std::runtime_error{util::to_string(
                    "Not enough parameters specified for '@", name_, "'. Expected at least ", 
                    std::distance(parameters_.begin(), minRequired) + 1, " recieved, ", 
                    parameters_.size(), "."
                )};
            } else {
                break;
            }
        }

        params.emplace_back(param.name, parameters[i]);
    }

    return make_shared<CustomFuncImpl>(name_, params, expr_);
}

text::UnknownDataTypeContainer CustomFuncImpl::retrieve(InvocationContext& context) const {
    auto function_scope = get_function_context(name_, context);
    auto builder = wrap_scope(function_scope);

    for(auto [k, v] : parameters_) {
        builder.with(k, v->retrieve(context));
    }

    auto scope = builder.build(); 
    return expr_->retrieve(*scope);
}

} /* anonymous */

ExprStmtVisitor::ExprStmtVisitor(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<BuildContext> buildContext, 
    const antlr4::BufferedTokenStream& tokens
) : context_(context), buildContext_(buildContext), tokens_(tokens) { }

bool ExprStmtVisitor::shouldVisitNextChild(antlr4::tree::ParseTree *node, const std::any& current) {
    return dynamic_cast<StringInterpolatorParser::Function_def_stmtContext*>(node) == nullptr 
        && dynamic_cast<StringInterpolatorParser::Assign_stmtContext*>(node) == nullptr 
        && dynamic_cast<StringInterpolatorParser::ExprContext*>(node) == nullptr;
}

std::any ExprStmtVisitor::visitFunction_def_stmt(StringInterpolatorParser::Function_def_stmtContext *ctx) {
    std::string name = ctx->ID()->getText();

    auto paramContext = ctx->function_parameters();
    std::vector<ParameterInfo> params;
    if(paramContext) {
        bool optionalFound = false;
        for(auto param : paramContext->function_parameter()) {
            ParameterInfo& info = params.emplace_back();
            info.name = param->ID()->getText();
            info.required = !static_cast<bool>(param->QUESTION());

            if(optionalFound && info.required) {
                throw std::runtime_error{"Non-optional parameters cannot appear after an optional parameter."};
            }

            optionalFound = optionalFound || !info.required;
        }
    }

    ExpressionVisitor visitor{context_, buildContext_, tokens_};
    auto expr = std::any_cast<std::shared_ptr<text::ValueRetriever>>(ctx->expr_block()->accept(&visitor));

    buildContext_->emplace_function<CustomFunction>(name, name, params, expr);

    return std::static_pointer_cast<Statement>(std::make_shared<FuncDefStmt>(name)); 
}

std::any ExprStmtVisitor::visitAssign_stmt(StringInterpolatorParser::Assign_stmtContext *ctx) {
    std::string varName = ctx->ID()->getText();

    ExpressionVisitor visitor{context_, buildContext_, tokens_};
    auto expression = visitor.visit(ctx->expr());

    VariableOpts opts;
    opts.is_const = static_cast<bool>(ctx->CONST());
    opts.is_persist = static_cast<bool>(ctx->PERSIST());

    std::shared_ptr<VariableRetriever> variable;
    if(ctx->VAR()) {
        variable = buildContext_->declare_variable(varName, opts);
    } else {
        variable = buildContext_->get_variable(varName);

        if(variable->is_mutable()) {
            throw std::runtime_error{util::to_string(
                "Attempted to mutate a const variable '$", varName, "'.")};
        }
    }

    return std::static_pointer_cast<Statement>(std::make_shared<AssignStmt>(variable, expression));
}

std::any ExprStmtVisitor::visitSimple_expr_stmt(StringInterpolatorParser::Simple_expr_stmtContext *ctx) {
    ExpressionVisitor visitor{context_, buildContext_, tokens_};
    auto retriever = visitor.visit(ctx->expr());
    return std::static_pointer_cast<Statement>(std::make_shared<ExprStmt>(retriever));
}

} /* SIPLUS_NAMESPACE */
