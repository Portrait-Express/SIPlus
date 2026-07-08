#include <algorithm>
#include <any>
#include <iterator>
#include <vector>

#include "siplus/build_context.hxx"
#include "siplus/data.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"

#include "../util.hxx"
#include "block_contents_visitor.hxx"
#include "siplus_visitor.hxx"

namespace SIPLUS_NAMESPACE {

namespace {

struct DummyScopeType : public TypeInfo { 
    using data_type = std::weak_ptr<InvocationContext>;

    virtual std::string name() const { return "<internal-scope>"; }
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const { return false; }
};

//I hate this solution for storing the scope, but its the best I can come up with
void store_function_context(const std::string function, std::shared_ptr<InvocationContext> ctx) {
    ctx->set_variable("*@" + function, make_data<DummyScopeType>(std::weak_ptr{ctx}));
}

std::shared_ptr<InvocationContext> get_function_context(const std::string function, InvocationContext& ctx) {
    return ctx.variable("*@" + function).as<DummyScopeType>().lock();
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

struct VariableDeclarationStmt : Statement {
    VariableDeclarationStmt(
        std::shared_ptr<VariableRetriever> variable,
        std::shared_ptr<text::ValueRetriever> value
    ) : variable_(variable), value_(value) {
        if(variable->is_const() && !value) 
            throw std::runtime_error{"Const variable '" + variable->name() + "' not initialized"};
    }

    void invoke(InvocationContext& ctx) override {
        if(variable_->is_persist()) {
            if(!persistInitialized_) {
                auto value = value_->retrieve(ctx);
                variable_->set_value(ctx, value);
                persistInitialized_ = true;
            }
        } else {
            auto value = value_->retrieve(ctx);
            variable_->set_value(ctx, value);
        }
    }

private:
    std::shared_ptr<VariableRetriever> variable_;
    std::shared_ptr<text::ValueRetriever> value_;
    bool persistInitialized_ = false;
};

struct ParameterInfo {
    std::string name;
    bool required;
    std::shared_ptr<VariableRetriever> variable;
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
    using parameter_info = std::pair<std::shared_ptr<VariableRetriever>, std::shared_ptr<text::ValueRetriever>>;

    CustomFuncImpl(
        std::string name,
        std::vector<parameter_info> parameters,
        std::shared_ptr<text::ValueRetriever> expr
    ) : name_(name), parameters_(parameters), expr_(expr) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override;

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

    std::vector<CustomFuncImpl::parameter_info> params{};
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

        params.emplace_back(param.variable, parameters[i]);
    }

    return make_shared<CustomFuncImpl>(name_, params, expr_);
}

UnknownDataTypeContainer CustomFuncImpl::retrieve(InvocationContext& context) const {
    auto function_scope = get_function_context(name_, context);
    auto scope = wrap_scope(function_scope).build();

    for(auto [k, v] : parameters_) {
        k->set_value(*scope, v->retrieve(context));
    }

    return expr_->retrieve(*scope);
}

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


struct StatementExecutingValueRetriever : public text::ValueRetriever {
    StatementExecutingValueRetriever(
        std::vector<std::shared_ptr<Statement>> stmts,
        std::shared_ptr<text::ValueRetriever> expr
    ) : statements_(stmts), expr_(expr) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override {
        for(auto stmt : statements_) {
            stmt->invoke(value);
        }

        return expr_->retrieve(value);
    }

private:
    std::vector<std::shared_ptr<Statement>> statements_;
    std::shared_ptr<text::ValueRetriever> expr_;
};

}

block_contents_visitor::block_contents_visitor(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<BuildContext> buildContext, 
    const antlr4::BufferedTokenStream& tokens
) : context_(context), buildContext_(buildContext), tokens_(tokens) {}

std::any block_contents_visitor::visitFunction_definition(StringInterpolatorParser::Function_definitionContext *ctx) {
    std::string name = ctx->ID()->getText();

    auto paramContext = ctx->function_parameters();
    std::vector<ParameterInfo> params;

    auto buildCtx = std::make_shared<BuildContext>(buildContext_);
    VariableOpts paramDeclareOpts;

    if(paramContext) {
        bool optionalFound = false;
        auto parameterDefinitions = paramContext->function_parameter();
        params.reserve(parameterDefinitions.size());

        for(auto param : parameterDefinitions) {
            const auto name = param->ID()->getText();
            ParameterInfo& info = params.emplace_back(ParameterInfo{
                .name = name,
                .required = !static_cast<bool>(param->QUESTION()),
                .variable = buildCtx->declare_variable(name, paramDeclareOpts)
            });

            if(optionalFound && info.required) {
                throw std::runtime_error{"Non-optional parameters cannot appear after an optional parameter."};
            }

            optionalFound = optionalFound || !info.required;
        }
    }

    auto expr = siplus_visitor{context_, buildCtx, tokens_}.visit(ctx->expr());
    buildContext_->emplace_function<CustomFunction>(name, name, params, expr);
    return std::static_pointer_cast<Statement>(std::make_shared<FuncDefStmt>(name)); 
}

std::any block_contents_visitor::visitVariable_declaration(StringInterpolatorParser::Variable_declarationContext *ctx) {
    VariableOpts opts;
    std::shared_ptr<VariableRetriever> variable;
    std::shared_ptr<text::ValueRetriever> value;

    opts.is_const = static_cast<bool>(ctx->CONST());
    opts.is_persist = static_cast<bool>(ctx->PERSIST());

    variable = buildContext_->declare_variable(ctx->ID()->getText(), opts);

    if(auto expr = ctx->expr()) {
        value = siplus_visitor{context_, buildContext_, tokens_}.visit(expr);
    }

    return std::static_pointer_cast<Statement>(
        std::make_shared<VariableDeclarationStmt>(variable, value)
    );
}

std::any block_contents_visitor::visitBlock_expr(StringInterpolatorParser::Block_exprContext *ctx) {
    siplus_visitor visitor{context_, buildContext_, tokens_};
    return ctx->accept(&visitor);
}

std::any block_contents_visitor::visitBlock_stmt(StringInterpolatorParser::Block_stmtContext *ctx) {
    if(auto funcCtx = ctx->function_definition()) {
        return visitFunction_definition(funcCtx);
    } else if(auto declCtx = ctx->variable_declaration()) {
        return visitVariable_declaration(declCtx);
    } else if(auto exprCtx = ctx->expr()) {
        siplus_visitor visitor{context_, buildContext_, tokens_};
        auto expr = visitor.visit(exprCtx);

        return std::static_pointer_cast<Statement>(std::make_shared<ExprStmt>(expr));
    } else {
        throw std::runtime_error{"Unknown block_stmt syntax"};
    }
}

std::any block_contents_visitor::visitBlock_contents(StringInterpolatorParser::Block_contentsContext *ctx) {
    auto stmtCtxs = ctx->block_stmt();
    std::vector<std::shared_ptr<Statement>> stmts;
    stmts.reserve(stmtCtxs.size());

    //Visit statements first, otherwise dependent variables may not be initialized
    std::transform(stmtCtxs.begin(), stmtCtxs.end(), std::back_inserter(stmts), [this](auto *ctx) { return visit(ctx); });

    auto expr = visit(ctx->block_expr());

    return detail::make_retriever<StatementExecutingValueRetriever>(stmts, expr);
}

} /* SIPLUS_NAMESPACE */
