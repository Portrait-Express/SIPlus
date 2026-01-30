#include "siplus/invocation_context.hxx"
#include "siplus/types/array.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"
#include "siplus/util.hxx"

#include <algorithm>
#include <cctype>
#include <cstring>

#include "siplus/config.h"
#include "siplus/data.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"
#include "siplus/stl/functions/text.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct str_impl : public text::ValueRetriever {
    str_impl(
        std::shared_ptr<text::ValueRetriever> param,
        std::weak_ptr<SIPlusParserContext> context
    ) : param_(param), context_(context) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> param_;
};

struct replace_function_impl : text::ValueRetriever {
    replace_function_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> target,
        std::shared_ptr<text::ValueRetriever> value
    ) : ctx_(ctx), input_(input), target_(target), value_(value) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

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

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

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

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

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

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
};

struct upper_impl : text::ValueRetriever {
    upper_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input
    ) : ctx_(ctx), input_(input) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
};

struct lower_impl : text::ValueRetriever {
    lower_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input
    ) : ctx_(ctx), input_(input) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
};

struct split_impl : text::ValueRetriever {
    split_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> delim
    ) : ctx_(ctx), input_(input), delimiter_(delim) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> delimiter_;
};

struct substr_impl : text::ValueRetriever {
    substr_impl(
        std::weak_ptr<SIPlusParserContext> ctx,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> begin,
        std::shared_ptr<text::ValueRetriever> end
    ) : ctx_(ctx), input_(input), begin_(begin), end_(end) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> ctx_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> begin_;
    std::shared_ptr<text::ValueRetriever> end_;
};

} /* anonymous */

std::shared_ptr<text::ValueRetriever> 
str_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<str_impl>(input, context_);
}

UnknownDataTypeContainer 
str_impl::retrieve(InvocationContext& value) const {
    auto ctx = context_.lock();
    auto val = param_->retrieve(value);
    return ctx->convert<types::StringType>(val);
}

std::shared_ptr<text::ValueRetriever> replace_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, target, value] = util::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<replace_function_impl>(ctx_, input, target, value);
}

UnknownDataTypeContainer
replace_function_impl::retrieve(InvocationContext& value) const {
    std::shared_ptr<SIPlusParserContext> ctx = ctx_.lock();
    auto input = ctx->convert<types::StringType>(input_->retrieve(value)).as<types::StringType>();
    auto target = ctx->convert<types::StringType>(target_->retrieve(value)).as<types::StringType>();
    auto with = ctx->convert<types::StringType>(value_->retrieve(value)).as<types::StringType>();

    if(input.empty() || target.empty()) return make_data<types::StringType>(input);

    size_t start_pos = 0;
    while((start_pos = input.find(target, start_pos)) != std::string::npos) {
        input.replace(start_pos, target.length(), with);
        start_pos += with.length();
    }

    return make_data<types::StringType>(input);
}

std::shared_ptr<text::ValueRetriever> pad_end_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, length, padding] = util::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<pad_end_impl>(ctx_, input, length, padding);
}

UnknownDataTypeContainer 
pad_end_impl::retrieve(InvocationContext& value) const {
    std::shared_ptr<SIPlusParserContext> ctx = ctx_.lock();
    auto val = ctx->convert<types::StringType>(input_->retrieve(value)).as<types::StringType>();
    auto length = ctx->convert<types::IntegerType>(length_->retrieve(value)).as<types::IntegerType>();
    auto padding = ctx->convert<types::StringType>(padding_->retrieve(value)).as<types::StringType>();

    if(padding.size() != 1) {
        throw std::runtime_error{"Expected padding size to be one character."};
    }

    if(val.size() > length) {
        return make_data<types::StringType>(val);
    } else {
        val.resize(length, padding[0]);
    }

    return make_data<types::StringType>(val);
}

std::shared_ptr<text::ValueRetriever> pad_start_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, length, padding] = util::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<pad_start_impl>(ctx_, input, length, padding);
}

UnknownDataTypeContainer 
pad_start_impl::retrieve(InvocationContext& value) const {
    std::shared_ptr<SIPlusParserContext> ctx = ctx_.lock();
    auto val = ctx->convert<types::StringType>(input_->retrieve(value)).as<types::StringType>();
    auto length = ctx->convert<types::IntegerType>(length_->retrieve(value)).as<types::IntegerType>();
    auto padding = ctx->convert<types::StringType>(padding_->retrieve(value)).as<types::StringType>();

    if(padding.size() != 1) {
        throw std::runtime_error{"Expected padding size to be one character."};
    }

    if(val.size() > length) {
        return make_data<types::StringType>(val);
    }

    std::string out;
    out.resize(length, padding[0]);

    size_t offset = length - val.size();
    std::memcpy(out.data() + offset, val.c_str(), val.size());

    return make_data<types::StringType>(out);
}

std::shared_ptr<text::ValueRetriever> trim_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<trim_impl>(ctx_, input);
}

UnknownDataTypeContainer
trim_impl::retrieve(InvocationContext& value) const {
    auto ctx = ctx_.lock();
    auto str = ctx->convert<types::StringType>(input_->retrieve(value)).as<types::StringType>();
    
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
    
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c) {
        return !std::isspace(c);
    }).base(), str.end());

    return make_data<types::StringType>(str);
}

std::shared_ptr<text::ValueRetriever> upper_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters); 
    return std::make_shared<upper_impl>(ctx_, input);
}

UnknownDataTypeContainer
upper_impl::retrieve(InvocationContext& value) const {
    auto ctx = ctx_.lock();
    auto str = ctx->convert<types::StringType>(input_->retrieve(value)).as<types::StringType>();
    
    std::transform(str.begin(), str.end(), str.begin(), [](char c) {
        return std::toupper(c);
    });

    return make_data<types::StringType>(str);
}

std::shared_ptr<text::ValueRetriever> lower_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<lower_impl>(ctx_, input);
}

UnknownDataTypeContainer
lower_impl::retrieve(InvocationContext& value) const {
    auto ctx = ctx_.lock();
    auto str = ctx->convert<types::StringType>(input_->retrieve(value)).as<types::StringType>();
    
    std::transform(str.begin(), str.end(), str.begin(), [](char c) {
        return std::tolower(c);
    });

    return make_data<types::StringType>(str);
}

std::shared_ptr<text::ValueRetriever>
split_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, delim] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<split_impl>(ctx_, input, delim);
}

UnknownDataTypeContainer
split_impl::retrieve(InvocationContext& value) const {
    auto ctx = ctx_.lock();
    auto input_val = input_->retrieve(value);
    auto delimiter_val = delimiter_->retrieve(value);
    auto delimiter = ctx->convert<types::StringType>(delimiter_val).as<types::StringType>();
    auto text = ctx->convert<types::StringType>(input_val).as<types::StringType>();

    std::vector<UnknownDataTypeContainer> ret;
    auto last = 0;
    auto idx = text.find(delimiter);
    while(idx != std::string::npos) {
        if(idx != last)  {
            std::string substr = text.substr(last, idx-last);
            ret.push_back(make_data<types::StringType>(substr));
        }

        last = idx + delimiter.size();
        idx = text.find(delimiter, idx + std::max<size_t>(delimiter.size(), 1));
    }

    if(text.empty() || (idx != last && text.size() - last != 0)) {
        std::string substr = text.substr(last, text.size() - last);
        ret.push_back(make_data<types::StringType>(substr));
    }

    return make_data<types::ArrayType>(ret);
}

std::shared_ptr<text::ValueRetriever>
substr_function::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, begin, end] = util::get_parameters_first_parent<2, 1>(parent, parameters);
    return std::make_shared<substr_impl>(ctx_, input, begin, end);
}

UnknownDataTypeContainer
substr_impl::retrieve(InvocationContext& value) const {
    auto ctx = ctx_.lock();
    UnknownDataTypeContainer input_val = input_->retrieve(value);
    UnknownDataTypeContainer begin_val = begin_->retrieve(value);
    std::string input = ctx->convert<types::StringType>(input_val).as<types::StringType>();
    long begin = ctx->convert<types::IntegerType>(begin_val).as<types::IntegerType>();
    long end = input.size();

    if(end_) {
        UnknownDataTypeContainer end_val = end_->retrieve(value);
        end = ctx->convert<types::IntegerType>(end_val).as<types::IntegerType>();
    }

    return make_data<types::StringType>(input.substr(begin, end));
}

UnknownDataTypeContainer string_concatenator::invoke(
    std::shared_ptr<SIPlusParserContext> ctx,
    UnknownDataTypeContainer       lhs,
    UnknownDataTypeContainer       rhs
) {
    if(!lhs.is<types::StringType>() || !rhs.is<types::StringType>()) {
        throw std::runtime_error{"String concatenator can only handle std::string"};
    }
    return make_data<types::StringType>(lhs.as<types::StringType>() + rhs.as<types::StringType>());
}

bool string_concatenator::can_handle(const TypeInfo& lhs, const TypeInfo& rhs) const {
    return lhs.is<types::StringType>() && rhs.is<types::StringType>();
}

UnknownDataTypeContainer 
string_comparator::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    UnknownDataTypeContainer lhs, 
    UnknownDataTypeContainer rhs
) {
    auto strl = lhs.as<types::StringType>();
    auto strr = rhs.as<types::StringType>();

    if(strl < strr) {
        return make_data<types::IntegerType>(-1L);
    } else if(strl > strr) {
        return make_data<types::IntegerType>(1L);
    } else {
        return make_data<types::IntegerType>(0L);
    }
}

bool string_comparator::can_handle(const TypeInfo& lhs, const TypeInfo& rhs) const {
    return lhs.is<types::StringType>() && rhs.is<types::StringType>();
}

} /* stl */
} /* SIPLUS_NAMESPACE */
