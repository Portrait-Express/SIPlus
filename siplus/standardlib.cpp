#include <format>
#include <iostream>

#include "siplus/stl.h"

#include "siplus/stl/converters/int_string.h"
#include "siplus/stl/functions.h"
#include "siplus/stl/functions/str.h"
#include "siplus/text/data.h"
#include "util.h"

namespace SIPLUS_NAMESPACE {
namespace stl {


std::shared_ptr<text::ValueRetriever> 
add_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) {
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

    return std::make_shared<retriever>(sum, context_);
}

text::UnknownDataTypeContainer 
add_func::retriever::retrieve(const text::UnknownDataTypeContainer& value) {
    auto context = context_.lock();
    text::UnknownDataTypeContainer sum;

    for(auto& ptr : params) {
        if(!sum) {
            sum = ptr->retrieve(value);
            continue;
        }

        auto val = ptr->retrieve(value);
        if(sum.is<std::string>()) {
            sum = text::make_data(sum.as<std::string>() + 
                                  context->convert<std::string>(val).as<std::string>());

        } else if(sum.is<int>()) {
            if(val.is<int>()) {
                sum = text::make_data(sum.as<int>() + val.as<int>());
            } else if(val.is<float>()) {
                sum = text::make_data(sum.as<int>() + val.as<float>());
            } else if(val.is<std::string>()) {
                sum = text::make_data(context->convert<std::string>(sum).as<std::string>() + 
                                      val.as<std::string>());
            } else {
                sum = text::make_data(sum.as<int>() + 
                                      context->convert<int>(val).as<int>());
            }
        } else if(sum.is<float>()) {
            if(val.is<int>()) {
                sum = text::make_data(sum.as<float>() + val.as<int>());
            } else if(val.is<float>()) {
                sum = text::make_data(sum.as<float>() + val.as<float>());
            } else {
                sum = text::make_data(sum.as<float>() + 
                                      context->convert<float>(val).as<float>());
            }
        } else {
            throw std::runtime_error{std::format("Not sure how to add {} and {}",
                                                 get_type_name(sum.type), 
                                                 get_type_name(val.type))};
        }
    }

    return sum;
}

std::shared_ptr<text::ValueRetriever> 
str_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) {
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

    return std::make_shared<str_func::retriever>(param, context_);
}

text::UnknownDataTypeContainer 
str_func::retriever::retrieve(const text::UnknownDataTypeContainer& value) {
    auto ctx = context_.lock();
    auto val = param->retrieve(value);
    return ctx->convert<std::string>(val);
}


bool
int_converter::can_convert(std::type_index from, std::type_index to) {
    if(from != typeid(int)) {
        return false;
    }

    return to == typeid(std::string) ||
           to == typeid(float);
}

text::UnknownDataTypeContainer 
int_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    int val = from.as<int>();

    if(to == typeid(std::string)) {
        return text::make_data(std::to_string(val));
    } else if(to == typeid(float)) {
        return text::make_data(val);
    } else {
        throw std::runtime_error{"Cant convert int to " + get_type_name(to)};
    }
}

void attach_stl(SIPlusParserContext& context) {
    attach_stl_functions(context);
    attach_stl_converters(context);
}

void attach_stl_functions(SIPlusParserContext& context) {
    context.emplace_function<add_func>("add", context.shared_from_this());
    context.emplace_function<str_func>("str", context.shared_from_this());
}

void attach_stl_converters(SIPlusParserContext& context) {
    context.emplace_converter<int_converter>();
}

} /* stl */
} /* SIPLUS_NAMESPACE */
