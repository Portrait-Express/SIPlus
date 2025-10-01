#include "siplus/internal/vector_iterator_provider.h"
#include "siplus/stl.h"
#include "siplus/stl/converters/numeric.h"
#include "siplus/stl/functions.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/util.h"
#include <functional>
#include <memory>
#include <vector>

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct add_func_retriever : public text::ValueRetriever {
    add_func_retriever(
        const internal::BinaryTypeCache<AdditionImpl, &AdditionImpl::can_add> &adders,
        std::vector<std::shared_ptr<text::ValueRetriever>> params,
        std::weak_ptr<SIPlusParserContext> context
    ) : adders_(adders), params(params), context_(context) {}

    text::UnknownDataTypeContainer retrieve(const text::UnknownDataTypeContainer& value) const override;

    std::vector<std::shared_ptr<text::ValueRetriever>> params;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    const internal::BinaryTypeCache<AdditionImpl, &AdditionImpl::can_add> &adders_;
};

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

    text::UnknownDataTypeContainer retrieve(const text::UnknownDataTypeContainer& value) const override;

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

struct xor_func_retriever : public text::ValueRetriever {
    xor_func_retriever(
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

struct or_func_retriever : public text::ValueRetriever {
    or_func_retriever(
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

struct and_func_retriever : public text::ValueRetriever {
    and_func_retriever(
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

struct not_func_retriever : public text::ValueRetriever {
    not_func_retriever(
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

template<typename T>
struct operator_function : Function {
    operator_function(
        std::weak_ptr<SIPlusParserContext> context,
        std::function<T(T,T)> comparator
    ) : context_(context), comparator_(comparator) {}

    std::shared_ptr<text::ValueRetriever> 
    value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override {
        std::shared_ptr<text::ValueRetriever> a;
        std::shared_ptr<text::ValueRetriever> b;

        if(parent) {
            if(parameters.size() != 1) {
                throw std::runtime_error{"Expected one parameter"};
            }

            a = parent;
            b = parameters[0];
        } else {
            if(parameters.size() != 2) {
                throw std::runtime_error{"Expected two parameters"};
            }

            a = parameters[0];
            b = parameters[1];
        }

        return std::make_shared<impl>(context_, comparator_, a, b);
    }

    struct impl : text::ValueRetriever {
        impl(
            std::weak_ptr<SIPlusParserContext> context,
            std::function<T(T,T)> comparator,
            std::shared_ptr<text::ValueRetriever> a,
            std::shared_ptr<text::ValueRetriever> b
        ) : context_(context), comparator_(comparator), a_(a), b_(b) {}

        text::UnknownDataTypeContainer
        retrieve(const text::UnknownDataTypeContainer &value) const override {
            auto ctx = context_.lock();

            T a = ctx->convert<T>(a_->retrieve(value)).template as<T>();
            T b = ctx->convert<T>(b_->retrieve(value)).template as<T>();

            return text::make_data(comparator_(a, b));
        }

    private:
        std::weak_ptr<SIPlusParserContext> context_;
        std::shared_ptr<text::ValueRetriever> a_;
        std::shared_ptr<text::ValueRetriever> b_;
        std::function<T(T,T)> comparator_;
    };

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::function<T(T,T)> comparator_;
};

text::UnknownDataTypeContainer 
DefaultAdder::add(std::shared_ptr<SIPlusParserContext> context, 
                  text::UnknownDataTypeContainer sum, 
                  text::UnknownDataTypeContainer val) {
    if(sum.is<std::string>()) {
        sum = text::make_data(sum.as<std::string>() + 
                              context->convert<std::string>(val).as<std::string>());
    } else if(sum.is<int>()) {
        long lval = context->convert<long>(sum).as<long>();

        if(val.is<long>()) {
            sum = text::make_data(lval + val.as<long>());
        } else if(val.is<double>()) {
            sum = text::make_data(lval + val.as<double>());
        } else if(val.is<std::string>()) {
            sum = text::make_data(context->convert<std::string>(sum).as<std::string>() + 
                                  val.as<std::string>());
        } else {
            sum = text::make_data(lval + context->convert<long>(val).as<long>());
        }
    } else if(sum.is<double>()) {
        if(val.is<long>()) {
            sum = text::make_data(sum.as<double>() + val.as<long>());
        } else if(val.is<double>()) {
            sum = text::make_data(sum.as<double>() + val.as<double>());
        } else {
            sum = text::make_data(sum.as<double>() + 
                                  context->convert<double>(val).as<double>());
        }
    } else if(sum.is<long>()) {
        if(val.is<long>()) {
            sum = text::make_data(sum.as<long>() + val.as<long>());
        } else if(val.is<double>()) {
            sum = text::make_data(sum.as<long>() + val.as<double>());
        } else if(val.is<std::string>()) {
            sum = text::make_data(context->convert<std::string>(sum).as<std::string>() + 
                                  val.as<std::string>());
        } else {
            sum = text::make_data(sum.as<long>() + 
                                  context->convert<long>(val).as<long>());
        }
    } else if(sum.is<double>()) {
        if(val.is<long>()) {
            sum = text::make_data(sum.as<double>() + val.as<long>());
        } else if(val.is<double>()) {
            sum = text::make_data(sum.as<double>() + val.as<double>());
        } else {
            sum = text::make_data(sum.as<double>() + 
                                  context->convert<double>(val).as<double>());
        }
    } else {
        throw std::runtime_error{"Not sure how to add " 
            + get_type_name(sum.type) + " and " + get_type_name(val.type)};
    }

    return sum;
}

bool DefaultAdder::can_add(std::type_index sum, std::type_index add) {
    return sum == typeid(std::string) || 
        sum == typeid(int) || sum == typeid(long) ||
        sum == typeid(float) || sum == typeid(double);
}

std::shared_ptr<text::ValueRetriever> 
add_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    if(parameters.size() <= 0) {
        throw std::runtime_error{"Expected at least one parameter for function `add`"};
    }

    std::vector<std::shared_ptr<text::ValueRetriever>> sum;

    if(parent) {
        sum.push_back(parent);
    } else {
        if(parameters.size() <= 1) {
            throw std::runtime_error{"If no input is piped in, `add` must take at least 2 parameters"};
        }
    }

    for(auto& ptr : parameters) {
        sum.push_back(ptr);
    }

    return std::make_shared<add_func_retriever>(cache_, sum, context_);
}

text::UnknownDataTypeContainer 
add_func_retriever::retrieve(const text::UnknownDataTypeContainer& value) const {
    auto context = context_.lock();
    text::UnknownDataTypeContainer sum;

    for(auto& ptr : params) {
        if(!sum) {
            sum = ptr->retrieve(value);
            continue;
        }

        auto val = ptr->retrieve(value);
        auto adder = adders_.find(sum.type, val.type);
        if(adder == adders_.end()) {
            throw std::runtime_error{"Unsure how to add " 
                + get_type_name(sum.type) + " and " + get_type_name(val.type)};
        }

        sum = (*adder)->add(context, sum, val);
    }

    return sum;
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

bool
int_converter::can_convert(std::type_index from, std::type_index to) {
    return (
            from == typeid(short) ||
            from == typeid(int) || 
            from == typeid(long)
        ) &&
        to == typeid(long);
}

text::UnknownDataTypeContainer 
int_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    if(from.is<long>()) return from; 

    long val;

    if(from.is<int>()) {
        val = from.as<int>();
    } else if(from.is<short>()) {
        val = from.as<short>();
    } else {
        throw std::runtime_error{"Int converter cannot handle source type " + 
            get_type_name(from.type)};
    }

    return text::make_data(val);
}

bool float_converter::can_convert(std::type_index from, std::type_index to) {
    return (
        from == typeid(float) ||
        from == typeid(double)
    ) && to == typeid(double);
}

text::UnknownDataTypeContainer
float_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    if(from.is<double>()) return from;

    double d;

    if(from.is<float>()) {
        d = from.as<float>();
    }

    return text::make_data(d);
}

bool
numeric_string_converter::can_convert(std::type_index from, std::type_index to) {
    return (
        int_converter_.can_convert(from, typeid(long)) ||
        float_converter_.can_convert(from, typeid(double))
    ) && to == typeid(std::string);
}

text::UnknownDataTypeContainer
numeric_string_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    if(int_converter_.can_convert(from.type, typeid(long))) {
        long val = int_converter_.convert(from, typeid(long)).as<long>();
        return text::make_data(to_string(val));
    } else if(float_converter_.can_convert(from.type, typeid(double))) {
        double val = float_converter_.convert(from, typeid(double)).as<double>();
        return text::make_data(to_string(val));
    } else {
        throw std::runtime_error{"Cannot convert from " + get_type_name(from.type) 
            + " to " + get_type_name(to)};
    }
}

bool
numeric_bool_converter::can_convert(std::type_index from, std::type_index to) {
    return (
        float_converter_.can_convert(from, typeid(double)) ||
        int_converter_.can_convert(from, typeid(long))
    ) && to == typeid(bool);
}

text::UnknownDataTypeContainer
numeric_bool_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    if(float_converter_.can_convert(from.type, typeid(double))) {
        return text::make_data(static_cast<bool>(float_converter_.convert(from, typeid(double)).as<double>()));
    } else if(int_converter_.can_convert(from.type, typeid(long))) {
        return text::make_data(static_cast<bool>(int_converter_.convert(from, typeid(long)).as<long>()));
    } else {
        throw std::runtime_error{"Cannot convert from " + get_type_name(from.type) + " to bool."};
    }
}

void attach_stl(SIPlusParserContext& context) {
    attach_stl_functions(context);
    attach_stl_converters(context);
}

void attach_stl_functions(SIPlusParserContext& context) {
    context.emplace_function<add_func>("add", context.shared_from_this());
    context.emplace_function<str_func>("str", context.shared_from_this());
    context.emplace_function<map_func>("map", context.shared_from_this());
    context.emplace_function<if_func>("if", context.shared_from_this());

    context.emplace_function<operator_function<bool>>("and", context.shared_from_this(), std::logical_and<bool>());
    context.emplace_function<operator_function<bool>>("or", context.shared_from_this(), std::logical_or<bool>());
    context.emplace_function<operator_function<bool>>("xor", context.shared_from_this(), std::not_equal_to<bool>());

    context.emplace_iterator<internal::vector_iterator<text::UnknownDataTypeContainer>>();
}

void attach_stl_converters(SIPlusParserContext& context) {
    context.emplace_converter<int_converter>();
    context.emplace_converter<float_converter>();
    context.emplace_converter<numeric_string_converter>();
    context.emplace_converter<numeric_bool_converter>();
}

} /* stl */
} /* SIPLUS_NAESPACE */
