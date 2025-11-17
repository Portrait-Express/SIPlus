#include "siplus/stl/functions/converting_operator.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/util.h"
#include <memory>
#include <stdexcept>
#include <vector>

namespace SIPLUS_NAMESPACE {
namespace stl {

bool operator_impl::btcache_can_handle(std::type_index lhs, std::type_index rhs) {
    return can_handle(lhs, rhs);
}

text::UnknownDataTypeContainer 
numeric_adder::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer       lhs, 
    text::UnknownDataTypeContainer       rhs
) {
    lhs = as_base(context, lhs);
    rhs = as_base(context, rhs);

    if(lhs.is<long>()) {
        long val = lhs.as<long>();

        if(rhs.is<long>()) { 
            return text::make_data(val + rhs.as<long>());
        } else if(rhs.is<double>()) {
            return text::make_data(val + rhs.as<double>());
        } else {
            throw std::runtime_error{"Cannot add types long and " + get_type_name(rhs.type)};
        }
    } else if(lhs.is<double>()) {
        double val = lhs.as<double>();

        if(rhs.is<long>()) { 
            return text::make_data(val + rhs.as<long>());
        } else if(rhs.is<double>()) {
            return text::make_data(val + rhs.as<double>());
        } else {
            throw std::runtime_error{"Cannot add types double and " + get_type_name(rhs.type)};
        }
    } else {
        throw std::runtime_error{"Cannot add types " + get_type_name(lhs.type) 
            + " and " + get_type_name(rhs.type)};
    }
}

bool numeric_adder::is_numeric(std::type_index type) const {
    return type == typeid(long) || type == typeid(int) || type == typeid(short)
        || type == typeid(float) || type == typeid(double);
}

text::UnknownDataTypeContainer 
numeric_adder::as_base(
    std::shared_ptr<SIPlusParserContext> ctx,
    text::UnknownDataTypeContainer       value
) const {
    if(value.is<long>() || value.is<double>()) {
        return value;
    } else if(value.is<int>() || value.is<short>()) {
        return ctx->convert<long>(value);
    } else if(value.is<float>()) {
        return ctx->convert<float>(value);
    } else {
        throw std::runtime_error{"numeric_adder cannot add type " + get_type_name(value.type)};
    }
}

bool
numeric_adder::can_handle(std::type_index lhs, std::type_index rhs) const {
    return is_numeric(lhs) && is_numeric(rhs);
}

text::UnknownDataTypeContainer string_concatenator::invoke(
    std::shared_ptr<SIPlusParserContext> ctx,
    text::UnknownDataTypeContainer       lhs,
    text::UnknownDataTypeContainer       rhs
) {
    if(!lhs.is<std::string>() || !rhs.is<std::string>()) {
        throw std::runtime_error{"String concatenator can only handle std::string"};
    }
    return text::make_data(lhs.as<std::string>() + rhs.as<std::string>());
}

bool string_concatenator::can_handle(std::type_index lhs, std::type_index rhs) const {
    return lhs == typeid(std::string) && rhs == typeid(std::string);
}

namespace {

struct converting_operator_impl : text::ValueRetriever {
    converting_operator_impl(
        const converting_operator_function& parent,
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> lhs,
        std::shared_ptr<text::ValueRetriever> rhs
    ) : parent_(parent), ctx_(ctx), lhs_(lhs), rhs_(rhs) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    const converting_operator_function& parent_;
    std::shared_ptr<text::ValueRetriever> lhs_;
    std::shared_ptr<text::ValueRetriever> rhs_;
    std::weak_ptr<SIPlusParserContext> ctx_;
};

} /* anonymous */

bool 
converting_operator_function::has_impl(std::type_index lhs, std::type_index rhs) const {
    return cache_.find(lhs, rhs) != cache_.end();;
}

std::shared_ptr<operator_impl> 
converting_operator_function::find_impl(std::type_index lhs, std::type_index rhs) const {
    return *cache_.find(lhs, rhs);
}

std::shared_ptr<text::ValueRetriever>
converting_operator_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    std::shared_ptr<text::ValueRetriever> lhs;
    std::shared_ptr<text::ValueRetriever> rhs;

    if(parent) {
        lhs = parent;

        if(parameters.size() != 1) {
            throw std::runtime_error{""};
        }

        rhs = parameters[0];
    } else {
        if(parameters.size() != 2) {
            throw std::runtime_error{""};
        }

        lhs = parameters[0];
        rhs = parameters[1];
    }

    return std::make_shared<converting_operator_impl>(*this, context_, lhs, rhs);
}

text::UnknownDataTypeContainer
converting_operator_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    std::shared_ptr<SIPlusParserContext> ctx = ctx_.lock();
    text::UnknownDataTypeContainer lhs = lhs_->retrieve(value);
    text::UnknownDataTypeContainer rhs = rhs_->retrieve(value);

    if(parent_.has_impl(lhs.type, rhs.type)) {
        auto adder = parent_.find_impl(lhs.type, rhs.type);
        return adder->invoke(ctx, lhs, rhs);

    } else if(ctx->try_converter(rhs.type, lhs.type) && parent_.has_impl(lhs.type, lhs.type)) { // Can convert rhs to lhs type
        auto adder = parent_.find_impl(lhs.type, lhs.type);
        return adder->invoke(ctx, lhs, ctx->convert(rhs, lhs.type));

    } else if(ctx->try_converter(lhs.type, rhs.type) && parent_.has_impl(rhs.type, rhs.type)) { // Can convert lhs to rhs type
        auto adder = parent_.find_impl(rhs.type, rhs.type);
        return adder->invoke(ctx, ctx->convert(lhs, rhs.type), rhs);

    } else {
        throw std::runtime_error{"Unsure how to operate on " + 
            get_type_name(lhs.type) + " and " + get_type_name(rhs.type)};
    }
}

} /* stl */
} /* SIPLUS_NAMESPACE */
