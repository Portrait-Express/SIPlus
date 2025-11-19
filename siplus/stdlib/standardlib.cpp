#include "siplus/function.h"
#include "siplus/internal/vector_iterator_provider.h"
#include "siplus/stl.h"
#include "siplus/stl/converters/numeric.h"
#include "siplus/stl/functions.h"
#include "siplus/stl/functions/text.h"
#include "siplus/text/data.h"
#include "siplus/text/iterator.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "util.h"
#include <functional>
#include <memory>
#include <vector>

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct map_func_retriever : public text::ValueRetriever {
    map_func_retriever(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> expr
    ) : context_(context), input_(input), map_expr_(expr) {}

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer &value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> map_expr_;
};

struct str_func_retriever : public text::ValueRetriever {
    str_func_retriever(
        std::shared_ptr<text::ValueRetriever> param,
        std::weak_ptr<SIPlusParserContext> context
    ) : param(param), context_(context) {}

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

    std::shared_ptr<text::ValueRetriever> param;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

struct if_func_retriever : public text::ValueRetriever {
    if_func_retriever(
        std::shared_ptr<text::ValueRetriever> condition,
        std::shared_ptr<text::ValueRetriever> tVal,
        std::shared_ptr<text::ValueRetriever> fVal,
        std::weak_ptr<SIPlusParserContext> context
    ) : condition(condition), tVal(tVal), fVal(fVal), context_(context) {}

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

    std::shared_ptr<text::ValueRetriever> condition;
    std::shared_ptr<text::ValueRetriever> tVal;
    std::shared_ptr<text::ValueRetriever> fVal;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

}

std::shared_ptr<text::ValueRetriever>
map_func::value(std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> params) const {

    if(params.size() != 1) {
        throw std::runtime_error{"Expected 1 parameter for function `map`. Got " + 
            std::to_string(params.size())};
    }

    return std::make_shared<map_func_retriever>(context_, parent, params[0]);
}

text::UnknownDataTypeContainer
map_func_retriever::retrieve(const text::UnknownDataTypeContainer& val) const {
    using vec_type = std::vector<text::UnknownDataTypeContainer>;

    std::unique_ptr<vec_type> ret = std::make_unique<vec_type>();
    text::UnknownDataTypeContainer iterable = val;
    auto context = context_.lock();

    if(input_) {
        iterable = input_->retrieve(val);
    }

    auto iterator = context->iterator(iterable)->iterator(iterable);

    bool more = iterator->more();
    while(more) {
        iterator->next();

        auto current = iterator->current();
        auto mapped_val = map_expr_->retrieve(current);

        ret->push_back(mapped_val);

        more = iterator->more();
    }

    return text::make_data(ret.release());
}

std::shared_ptr<text::ValueRetriever> 
str_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    std::shared_ptr<text::ValueRetriever> param;

    if(parent) {
        param = parent;
    }

    if(parameters.size() > 0) {
        if(param || parameters.size() > 1) {
            throw std::runtime_error{"Can only specify one input to `str`, piped or argument"};
        }

        param = parameters[0];
    }

    return std::make_shared<str_func_retriever>(param, context_);
}

text::UnknownDataTypeContainer 
str_func_retriever::retrieve(const text::UnknownDataTypeContainer& value) const {
    auto ctx = context_.lock();
    auto val = param->retrieve(value);
    return ctx->convert<std::string>(val);
}

std::shared_ptr<text::ValueRetriever>
if_func::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    std::shared_ptr<text::ValueRetriever> condition;
    std::shared_ptr<text::ValueRetriever> tVal;
    std::shared_ptr<text::ValueRetriever> fVal;

    if(parent) {
        if(parameters.size() < 1) {
            throw std::runtime_error{"Too few parameters specified for 'if'"};
        }
        if(parameters.size() > 2) {
            throw std::runtime_error{"Too many parameters specified for 'if'"};
        }
        
        condition = parent;
        tVal = parameters[0];
        if(parameters.size() == 2) {
            fVal = parameters[1];
        }
    } else {
        if(parameters.size() < 2) {
            throw std::runtime_error{"Too few parameters specified for 'if'"};
        }
        if(parameters.size() > 3) {
            throw std::runtime_error{"Too many parameters specified for 'if'"};
        }

        condition = parameters[0];
        tVal = parameters[1];
        if(parameters.size() == 3) {
            fVal = parameters[2];
        }
    }

    return std::make_shared<if_func_retriever>(condition, tVal, fVal, context_);
}

text::UnknownDataTypeContainer
if_func_retriever::retrieve(const text::UnknownDataTypeContainer& value) const {
    auto ctx = context_.lock();
    auto cond = condition->retrieve(value);

    if(ctx->convert<bool>(cond).as<bool>()) {
        return tVal->retrieve(value);
    } else {
        return fVal->retrieve(value);
    }
}


//----------------------------
// Free Functions
//----------------------------

void attach_stl(SIPlusParserContext& context) {
    attach_stl_functions(context);
    attach_stl_converters(context);
}

void attach_stl_functions(SIPlusParserContext& context) {
    context.emplace_function<str_func>("str", context.shared_from_this());
    context.emplace_function<if_func>("if", context.shared_from_this());

    context.emplace_function<map_func>("map", context.shared_from_this());
    context.emplace_iterator<internal::vector_iterator<text::UnknownDataTypeContainer>>();

    context.emplace_function<typed_operator_function<bool>>("and", context.shared_from_this(), std::logical_and<bool>());
    context.emplace_function<typed_operator_function<bool>>("or", context.shared_from_this(), std::logical_or<bool>());
    context.emplace_function<typed_operator_function<bool>>("xor", context.shared_from_this(), std::not_equal_to<bool>());

    auto add_func = converting_operator_function{context.shared_from_this()};
    add_func.emplace_impl<string_concatenator>();
    add_func.emplace_impl<numeric_adder>();
    context.emplace_function<converting_operator_function>("add", add_func);

    auto cmp_func = converting_operator_function{context.shared_from_this()};
    auto cmp_ptr = context.emplace_function<converting_operator_function>("cmp", cmp_func);
    cmp_ptr->emplace_impl<string_comparator>();
    cmp_ptr->emplace_impl<numeric_comparator>();
    context.emplace_function<lt_func>("lt", context.shared_from_this(), cmp_ptr);
    context.emplace_function<gt_func>("gt", context.shared_from_this(), cmp_ptr);
    context.emplace_function<eq_func>("eq", context.shared_from_this(), cmp_ptr);

    context.emplace_function<replace_function>("replace", context.shared_from_this());
    context.emplace_function<pad_end_function>("padEnd", context.shared_from_this());
    context.emplace_function<pad_start_function>("padStart", context.shared_from_this());
    context.emplace_function<trim_function>("trim", context.shared_from_this());
    context.emplace_function<upper_function>("upper", context.shared_from_this());
    context.emplace_function<lower_function>("lower", context.shared_from_this());
}

void attach_stl_converters(SIPlusParserContext& context) {
    context.emplace_converter<int_converter>();
    context.emplace_converter<float_converter>();
    context.emplace_converter<numeric_string_converter>();
    context.emplace_converter<numeric_bool_converter>();
}

} /* stl */
} /* SIPLUS_NAESPACE */
