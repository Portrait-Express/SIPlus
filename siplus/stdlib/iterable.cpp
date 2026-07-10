#include "siplus/context.hxx"
#include "siplus/invocation_context.hxx"
#include "siplus/data.hxx"
#include "siplus/text/value_retrievers/literal_retriever.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"
#include "siplus/stl/functions/iterable.hxx"
#include "siplus/types/array.hxx"
#include "siplus/types/bool.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"
#include "siplus/util.hxx"
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct map_impl : public text::ValueRetriever {
    map_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> expr
    ) : context_(context), input_(input), map_expr_(expr) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> map_expr_;
};

struct length_impl : public text::ValueRetriever {
    length_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input
    ) : context_(context), input_(input) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
};

struct join_impl : public text::ValueRetriever {
    join_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> delim
    ) : context_(context), input_(input), delimiter_(delim) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> delimiter_;
};

struct contains_impl : public text::ValueRetriever {
    contains_impl (
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> value
    ) : context_(context), input_(input), value_(value) {
    }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> value_;
};

/**
 * struct each_impl - ValueRetriever for each_func
 */
struct each_impl : public text::ValueRetriever {
    each_impl (
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> expr
    ) : input_(input), expr_(expr) { }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override {
        UnknownDataTypeContainer iterable = input_->retrieve(value);
        if(!iterable.is_iterable()) {
            throw std::runtime_error{util::to_string(
                "Type '", iterable.type->name(), "' used in 'each' is not iterable."
            )};
        }

        auto iterator = iterable.iterate();

        UnknownDataTypeContainer last;
        while(iterator->more()) {
            iterator->next();

            auto current = iterator->current();

            auto scope = wrap_scope(value.shared_from_this())
                .use_default(current)
                .build();

            last = expr_->retrieve(*scope);
        }

        return last;
    }

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> expr_;
};

struct all_impl : public text::ValueRetriever {
    all_impl (
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> predicate
    ) : context_(context), input_(input), predicate_(predicate) {
    }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override {
        auto context = context_.lock();
        UnknownDataTypeContainer iterable = input_->retrieve(value);
        if(!iterable.is_iterable()) {
            throw std::runtime_error{util::to_string(
                "Type '", iterable.type->name(), "' used in 'all' is not iterable."
            )};
        }

        auto iterator = iterable.iterate();

        while(iterator->more()) {
            iterator->next();

            auto current = iterator->current();

            auto scope = wrap_scope(value.shared_from_this())
                .use_default(current)
                .build();

            if(!context->convert<types::BoolType>(predicate_->retrieve(*scope)).as<types::BoolType>()) {
                return make_data(false);
            }
        }

        return make_data(true);
    }

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> predicate_;
};

struct any_impl : public text::ValueRetriever {
    any_impl (
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> input,
        std::shared_ptr<text::ValueRetriever> predicate
    ) : context_(context), input_(input), predicate_(predicate) {
    }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override {
        auto context = context_.lock();
        UnknownDataTypeContainer iterable = input_->retrieve(value);
        if(!iterable.is_iterable()) {
            throw std::runtime_error{util::to_string(
                "Type '", iterable.type->name(), "' used in 'any' is not iterable."
            )};
        }

        auto iterator = iterable.iterate();

        while(iterator->more()) {
            iterator->next();

            auto current = iterator->current();

            auto scope = wrap_scope(value.shared_from_this())
                .use_default(current)
                .build();

            if(context->convert<types::BoolType>(predicate_->retrieve(*scope)).as<types::BoolType>()) {
                return make_data(true);
            }
        }

        return make_data(false);
    }

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> input_;
    std::shared_ptr<text::ValueRetriever> predicate_;
};


struct sort_impl : text::ValueRetriever {
    sort_impl(
        std::weak_ptr<SIPlusParserContext> context,
        std::shared_ptr<text::ValueRetriever> list,
        std::shared_ptr<text::ValueRetriever> comparator
    ) : context_(context), list_(list), comparator_(comparator) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override {
        auto ctx = context_.lock();
        auto list = list_->retrieve(value);
        auto& input = list.as<types::ArrayType>();
        
        types::ArrayType::data_type arr = input;

        std::sort(arr.begin(), arr.end(), [this, &value, &ctx](UnknownDataTypeContainer& a, UnknownDataTypeContainer& b) {
            auto wrapped = wrap_scope(value.shared_from_this())
                .use_default(make_data(types::ArrayType::data_type{a, b}))
                .build();
            auto result = comparator_->retrieve(*wrapped);
            return ctx->convert<types::IntegerType>(result).as<types::IntegerType>() < 0;
        });

        return make_data(arr);
    }

private:
    std::weak_ptr<SIPlusParserContext> context_;
    std::shared_ptr<text::ValueRetriever> list_;
    std::shared_ptr<text::ValueRetriever> comparator_;
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

UnknownDataTypeContainer
map_impl::retrieve(InvocationContext& val) const {
    using vec_type = std::vector<UnknownDataTypeContainer>;

    std::unique_ptr<vec_type> ret = std::make_unique<vec_type>();
    UnknownDataTypeContainer iterable = val.default_data();
    auto context = context_.lock();

    if(input_) {
        iterable = input_->retrieve(val);
    }

    auto iterator = iterable.iterate();

    bool more = iterator->more();
    while(more) {
        iterator->next();

        auto current = iterator->current();

        auto scope = wrap_scope(val.shared_from_this()).use_default(current).build();
        auto mapped_val = map_expr_->retrieve(*scope);

        ret->push_back(mapped_val);

        more = iterator->more();
    }

    return make_data<types::ArrayType>(ret.release());
}

std::shared_ptr<text::ValueRetriever>
length_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<length_impl>(context_, input);
}

UnknownDataTypeContainer
length_impl::retrieve(InvocationContext& value) const {
    std::stringstream ss;
    auto context = context_.lock();
    auto iterable = input_->retrieve(value);

    auto iterator = iterable.iterate();

    long size = 0;
    bool more = iterator->more();
    while(more) {
        iterator->next();
        auto current = iterator->current();

        size++;

        more = iterator->more();
    }

    return make_data<types::IntegerType>(size);
}

std::shared_ptr<text::ValueRetriever>
join_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, delim] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<join_impl>(context_, input, delim);
}

UnknownDataTypeContainer
join_impl::retrieve(InvocationContext& value) const {
    std::stringstream ss;
    auto context = context_.lock();
    auto iterable = input_->retrieve(value);
    auto delimiter_val = delimiter_->retrieve(value);
    auto delimiter = context->convert<types::StringType>(delimiter_val).as<types::StringType>();

    auto iterator = iterable.iterate();

    bool more = iterator->more();
    while(more) {
        iterator->next();
        auto current = iterator->current();

        ss << context->convert<types::StringType>(current).as<types::StringType>();

        more = iterator->more();
        if(more) {
            ss << delimiter;
        }
    }

    return make_data<types::StringType>(ss.str());
}

std::shared_ptr<text::ValueRetriever>
contains_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [input, delim] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<contains_impl>(context_, input, delim);
}

UnknownDataTypeContainer
contains_impl::retrieve(InvocationContext& value) const {
    auto context = context_.lock();
    auto iterable = input_->retrieve(value);

    auto iterator = iterable.iterate();

    bool more = iterator->more();
    while(more) {
        iterator->next();
        auto current = iterator->current();

        auto retriever = std::make_shared<text::LiteralValueRetriever>(current);
        auto fn = context->function("eq").value(retriever, {value_});
        auto val = fn->retrieve(value);

        if(val.is<types::BoolType>() && val.as<types::BoolType>()) return val;

        more = iterator->more();
    }

    return make_data<types::BoolType>(false);
}

std::shared_ptr<text::ValueRetriever>
each_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [list, expr] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<each_impl>(list, expr);
}

std::shared_ptr<text::ValueRetriever>
all_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [list, pred] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<all_impl>(context_, list, pred);
}

std::shared_ptr<text::ValueRetriever>
any_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [list, pred] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<any_impl>(context_, list, pred);
}

std::shared_ptr<text::ValueRetriever>
sort_func::value(
    std::shared_ptr<text::ValueRetriever> parent, 
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto [list, comparator] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<sort_impl>(context_, list, comparator);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
