#include "siplus/util.hxx"

#include <algorithm>
#include <cctype>
#include <cstring>

#include "siplus/context.hxx"
#include "siplus/stl/functions/text.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct str_impl : public ValueRetriever {
    str_impl(std::shared_ptr<ValueRetriever> param) : param_(param) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> param_;
};

struct replace_function_impl : ValueRetriever {
    replace_function_impl(
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> target,
        std::shared_ptr<ValueRetriever> value
    ) : input_(input), target_(target), value_(value) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> target_;
    std::shared_ptr<ValueRetriever> value_;
};

struct pad_end_impl : ValueRetriever {
    pad_end_impl(
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> length,
        std::shared_ptr<ValueRetriever> padding
    ) : input_(input), length_(length), padding_(padding) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> length_;
    std::shared_ptr<ValueRetriever> padding_;
};

struct pad_start_impl : ValueRetriever {
    pad_start_impl(
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> length,
        std::shared_ptr<ValueRetriever> padding
    ) : input_(input), length_(length), padding_(padding) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> length_;
    std::shared_ptr<ValueRetriever> padding_;
};

struct trim_impl : ValueRetriever {
    trim_impl(
        std::shared_ptr<ValueRetriever> input
    ) : input_(input) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
};

struct upper_impl : ValueRetriever {
    upper_impl(
        std::shared_ptr<ValueRetriever> input
    ) : input_(input) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
};

struct lower_impl : ValueRetriever {
    lower_impl(
        std::shared_ptr<ValueRetriever> input
    ) : input_(input) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
};

struct split_impl : ValueRetriever {
    split_impl(
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> delim
    ) : input_(input), delimiter_(delim) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> delimiter_;
};

struct substr_impl : ValueRetriever {
    substr_impl(
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> begin,
        std::shared_ptr<ValueRetriever> end
    ) : input_(input), begin_(begin), end_(end) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> begin_;
    std::shared_ptr<ValueRetriever> end_;
};

} /* anonymous */

std::shared_ptr<ValueRetriever> 
str_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<str_impl>(input);
}

UnknownDataTypeContainer 
str_impl::retrieve(InvocationContext& value) const {
    auto val = param_->retrieve(value);

    return val.convert<types::StringType>();
}

std::shared_ptr<ValueRetriever> replace_function::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input, target, value] = util::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<replace_function_impl>(input, target, value);
}

UnknownDataTypeContainer
replace_function_impl::retrieve(InvocationContext& value) const {
    auto input = input_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    auto target = target_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    auto with = value_->retrieve(value).convert<types::StringType>().as<types::StringType>();

    if(input.empty() || target.empty()) return make_data<types::StringType>(input);

    size_t start_pos = 0;
    while((start_pos = input.find(target, start_pos)) != std::string::npos) {
        input.replace(start_pos, target.length(), with);
        start_pos += with.length();
    }

    return make_data<types::StringType>(input);
}

std::shared_ptr<ValueRetriever> pad_end_function::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input, length, padding] = util::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<pad_end_impl>(input, length, padding);
}

UnknownDataTypeContainer 
pad_end_impl::retrieve(InvocationContext& value) const {
    auto val = input_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    auto length = length_->retrieve(value).convert<types::IntegerType>().as<types::IntegerType>();
    auto padding = padding_->retrieve(value).convert<types::StringType>().as<types::StringType>();

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

std::shared_ptr<ValueRetriever> pad_start_function::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input, length, padding] = util::get_parameters_first_parent<3>(parent, parameters);
    return std::make_shared<pad_start_impl>(input, length, padding);
}

UnknownDataTypeContainer 
pad_start_impl::retrieve(InvocationContext& value) const {
    auto val = input_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    auto length = length_->retrieve(value).convert<types::IntegerType>().as<types::IntegerType>();
    auto padding = padding_->retrieve(value).convert<types::StringType>().as<types::StringType>();

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

std::shared_ptr<ValueRetriever> trim_function::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<trim_impl>(input);
}

UnknownDataTypeContainer
trim_impl::retrieve(InvocationContext& value) const {
    auto str = input_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
    
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char c) {
        return !std::isspace(c);
    }).base(), str.end());

    return make_data<types::StringType>(str);
}

std::shared_ptr<ValueRetriever> upper_function::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters); 
    return std::make_shared<upper_impl>(input);
}

UnknownDataTypeContainer
upper_impl::retrieve(InvocationContext& value) const {
    auto str = input_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    
    std::transform(str.begin(), str.end(), str.begin(), [](char c) {
        return std::toupper(c);
    });

    return make_data<types::StringType>(str);
}

std::shared_ptr<ValueRetriever> lower_function::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<lower_impl>(input);
}

UnknownDataTypeContainer
lower_impl::retrieve(InvocationContext& value) const {
    auto str = input_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    
    std::transform(str.begin(), str.end(), str.begin(), [](char c) {
        return std::tolower(c);
    });

    return make_data<types::StringType>(str);
}

std::shared_ptr<ValueRetriever>
split_function::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input, delim] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<split_impl>(input, delim);
}

UnknownDataTypeContainer
split_impl::retrieve(InvocationContext& value) const {
    auto delimiter = delimiter_->retrieve(value).convert<types::StringType>().as<types::StringType>();
    auto text = input_->retrieve(value).convert<types::StringType>().as<types::StringType>();

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

std::shared_ptr<ValueRetriever>
substr_function::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input, begin, end] = util::get_parameters_first_parent<2, 1>(parent, parameters);
    return std::make_shared<substr_impl>(input, begin, end);
}

UnknownDataTypeContainer
substr_impl::retrieve(InvocationContext& value) const {
    std::string input = input_->retrieve(value)
        .convert<types::StringType>()
        .as<types::StringType>();
    long begin = begin_->retrieve(value).convert<types::IntegerType>().as<types::IntegerType>();
    long end = input.size();

    if(end_) {
        end = end_->retrieve(value).convert<types::IntegerType>().as<types::IntegerType>();
    }

    return make_data<types::StringType>(input.substr(begin, end));
}

} /* stl */
} /* SIPLUS_NAMESPACE */
