#include "siplus/context.h"
#include "siplus/text/data.h"
#include "siplus/text/iterator.h"
#include "siplus/text/value_retrievers/dummy_retriever.h"
#include "siplus/text/value_retrievers/literal_retriever.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/stl/iterators/string_iterator_provider.h"
#include "siplus/stl/functions/iterable.h"
#include "siplus/util.h"
#include <sstream>

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct map_impl : public SIPlus::text::ValueRetriever {
    map_impl(
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

struct length_impl : public SIPlus::text::ValueRetriever {
    length_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input
    ) : context_(context), input_(input) {}

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer &value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
};

struct join_impl : public SIPlus::text::ValueRetriever {
    join_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> delim
    ) : context_(context), input_(input), delimiter_(delim) {}

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer &value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> delimiter_;
};

struct contains_impl : public SIPlus::text::ValueRetriever {
    contains_impl (
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> value
    ) : context_(context), input_(input), value_(value) {
    }

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer &value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> value_;
};

struct string_iterator_impl : text::Iterator {
    string_iterator_impl(std::string value) : value_(value) { }

    virtual bool more();
    virtual void next();
    virtual text::UnknownDataTypeContainer current();

private:
    std::string value_;
    long index_ = -1;
};

}

std::shared_ptr<text::ValueRetriever>
map_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, expr] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<map_impl>(context_, input, expr);
}

text::UnknownDataTypeContainer
map_impl::retrieve(const text::UnknownDataTypeContainer& val) const {
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
length_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<length_impl>(context_, input);
}

text::UnknownDataTypeContainer
length_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    std::stringstream ss;
    auto context = context_.lock();
    auto iterable = input_->retrieve(value);

    auto iterator = context->iterator(iterable)->iterator(iterable);

    long size = 0;
    bool more = iterator->more();
    while(more) {
        iterator->next();
        auto current = iterator->current();

        size++;

        more = iterator->more();
    }

    return text::make_data<long>(size);
}

std::shared_ptr<text::ValueRetriever>
join_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, delim] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<join_impl>(context_, input, delim);
}

text::UnknownDataTypeContainer
join_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    std::stringstream ss;
    auto context = context_.lock();
    auto iterable = input_->retrieve(value);
    auto delimiter_val = delimiter_->retrieve(value);
    auto delimiter = context->convert<std::string>(delimiter_val).as<std::string>();

    auto iterator = context->iterator(iterable)->iterator(iterable);

    bool more = iterator->more();
    while(more) {
        iterator->next();
        auto current = iterator->current();

        ss << context->convert<std::string>(current).as<std::string>();

        more = iterator->more();
        if(more) {
            ss << delimiter;
        }
    }

    return text::make_data(ss.str());
}

std::shared_ptr<text::ValueRetriever>
contains_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, delim] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<contains_impl>(context_, input, delim);
}

text::UnknownDataTypeContainer
contains_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    auto context = context_.lock();
    auto iterable = input_->retrieve(value);

    auto iterator = context->iterator(iterable)->iterator(iterable);

    bool more = iterator->more();
    while(more) {
        iterator->next();
        auto current = iterator->current();

        auto retriever = std::make_shared<text::LiteralValueRetriever>(current);
        auto fn = context->function("eq").value(retriever, {value_});
        auto val = fn->retrieve(value);

        if(val.is<bool>() && val.as<bool>()) return val;

        more = iterator->more();
    }

    return text::make_data(false);
}

bool string_iterator::can_iterate(const text::UnknownDataTypeContainer& value) {
    return value.is<std::string>();
}

std::unique_ptr<text::Iterator> string_iterator::iterator(const text::UnknownDataTypeContainer& value) {
    return std::make_unique<string_iterator_impl>(value.as<std::string>());
}

bool string_iterator_impl::more() {
    return index_ < (static_cast<long>(value_.size()) - 1);
}

void string_iterator_impl::next() {
    index_++;
}

text::UnknownDataTypeContainer string_iterator_impl::current() {
    return text::make_data(std::string{value_[index_]});
}


} /* stl */
} /* SIPLUS_NAMESPACE */
