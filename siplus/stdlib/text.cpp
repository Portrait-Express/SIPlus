#include "util.h"

#include <algorithm>
#include <cctype>
#include <cstring>

#include "siplus/config.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/stl/functions/text.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct replace_function_impl : text::ValueRetriever {
    replace_function_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> target,
        std::shared_ptr<text::ValueRetriever> value
    ) : ctx_(ctx), input_(input), target_(target), value_(value) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> target_;
    std::shared_ptr<text::ValueRetriever> value_;
};

struct pad_end_impl : text::ValueRetriever {
    pad_end_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> length,
        std::shared_ptr<text::ValueRetriever> padding
    ) : ctx_(ctx), input_(input), length_(length), padding_(padding) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> length_;
    std::shared_ptr<text::ValueRetriever> padding_;
};

struct pad_start_impl : text::ValueRetriever {
    pad_start_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> length,
        std::shared_ptr<text::ValueRetriever> padding
    ) : ctx_(ctx), input_(input), length_(length), padding_(padding) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> length_;
    std::shared_ptr<text::ValueRetriever> padding_;
};

struct trim_impl : text::ValueRetriever {
    trim_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input
    ) : ctx_(ctx), input_(input) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
};

struct upper_impl : text::ValueRetriever {
    upper_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input
    ) : ctx_(ctx), input_(input) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
};

struct lower_impl : text::ValueRetriever {
    lower_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input
    ) : ctx_(ctx), input_(input) { }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
};

} /* anonymous */

std::shared_ptr<text::ValueRetriever> replace_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, target, value] = detail::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<replace_function_impl>(ctx_, input, target, value);
}

text::UnknownDataTypeContainer
replace_function_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    std::shared_ptr<SIPlusParserContext> ctx = ctx_.lock();
    auto input = ctx->convert<std::string>(input_->retrieve(value)).as<std::string>();
    auto target = ctx->convert<std::string>(target_->retrieve(value)).as<std::string>();
    auto with = ctx->convert<std::string>(value_->retrieve(value)).as<std::string>();

    if(input.empty() || target.empty()) return text::make_data(input);

    size_t start_pos = 0;
    while((start_pos = input.find(target, start_pos)) != std::string::npos) {
        input.replace(start_pos, target.length(), with);
        start_pos += with.length();
    }

    return text::make_data(input);
}

std::shared_ptr<text::ValueRetriever> pad_end_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, length, padding] = detail::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<pad_end_impl>(ctx_, input, length, padding);
}

text::UnknownDataTypeContainer 
pad_end_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    std::shared_ptr<SIPlusParserContext> ctx = ctx_.lock();
    auto val = ctx->convert<std::string>(input_->retrieve(value)).as<std::string>();
    auto length = ctx->convert<long>(length_->retrieve(value)).as<long>();
    auto padding = ctx->convert<std::string>(padding_->retrieve(value)).as<std::string>();

    if(padding.size() != 1) {
        throw std::runtime_error{"Expected padding size to be one character."};
    }

    if(val.size() > length) {
        return text::make_data(val);
    } else {
        val.resize(length, padding[0]);
    }

    return text::make_data(val);
}

std::shared_ptr<text::ValueRetriever> pad_start_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, length, padding] = detail::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<pad_start_impl>(ctx_, input, length, padding);
}

text::UnknownDataTypeContainer 
pad_start_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    std::shared_ptr<SIPlusParserContext> ctx = ctx_.lock();
    auto val = ctx->convert<std::string>(input_->retrieve(value)).as<std::string>();
    auto length = ctx->convert<long>(length_->retrieve(value)).as<long>();
    auto padding = ctx->convert<std::string>(padding_->retrieve(value)).as<std::string>();

    if(padding.size() != 1) {
        throw std::runtime_error{"Expected padding size to be one character."};
    }

    if(val.size() > length) {
        return text::make_data(val);
    }

    std::string out;
    out.resize(length, padding[0]);

    size_t offset = length - val.size();
    std::memcpy(out.data() + offset, val.c_str(), val.size());

    return text::make_data(out);
}

std::shared_ptr<text::ValueRetriever> trim_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = detail::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<trim_impl>(ctx_, input);
}

text::UnknownDataTypeContainer
trim_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    auto ctx = ctx_.lock();
    auto str = ctx->convert<std::string>(input_->retrieve(value)).as<std::string>();
    
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
    
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c) {
        return !std::isspace(c);
    }).base(), str.end());

    return text::make_data(str);
}

std::shared_ptr<text::ValueRetriever> upper_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = detail::get_parameters_first_parent<1>(parent, parameters); 
    return std::make_shared<upper_impl>(ctx_, input);
}

text::UnknownDataTypeContainer
upper_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    auto ctx = ctx_.lock();
    auto str = ctx->convert<std::string>(input_->retrieve(value)).as<std::string>();
    
    std::transform(str.begin(), str.end(), str.begin(), [](char c) {
        return std::toupper(c);
    });

    return text::make_data(str);
}

std::shared_ptr<text::ValueRetriever> lower_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = detail::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<lower_impl>(ctx_, input);
}

text::UnknownDataTypeContainer
lower_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    auto ctx = ctx_.lock();
    auto str = ctx->convert<std::string>(input_->retrieve(value)).as<std::string>();
    
    std::transform(str.begin(), str.end(), str.begin(), [](char c) {
        return std::tolower(c);
    });

    return text::make_data(str);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
