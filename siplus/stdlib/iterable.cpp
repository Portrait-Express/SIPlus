#include <algorithm>
#include <functional>
#include <memory>
#include <sstream>

#include "siplus/context.hxx"
#include "siplus/stl/functions/iterable.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct map_impl : public ValueRetriever {
    map_impl(
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> expr
    ) : input_(input), map_expr_(expr) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> map_expr_;
};

struct length_impl : public ValueRetriever {
    length_impl(
        std::shared_ptr<ValueRetriever> input
    ) : input_(input) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
};

struct join_impl : public ValueRetriever {
    join_impl(
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> delim
    ) : input_(input), delimiter_(delim) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> delimiter_;
};

struct contains_impl : public ValueRetriever {
    contains_impl (
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> value
    ) : input_(input), value_(value) {
    }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> value_;
};

/**
 * struct each_impl - ValueRetriever for each_func
 */
struct each_impl : public ValueRetriever {
    each_impl (
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> expr
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
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> expr_;
};

struct all_impl : public ValueRetriever {
    all_impl (
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> predicate
    ) : input_(input), predicate_(predicate) {
    }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override {
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

            auto predicateResult = predicate_->retrieve(*scope);

            if(!predicateResult.convert<types::BoolType>().as<types::BoolType>()) {
                return make_data(false);
            }
        }

        return make_data(true);
    }

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> predicate_;
};

struct any_impl : public ValueRetriever {
    any_impl (
        std::shared_ptr<ValueRetriever> input,
        std::shared_ptr<ValueRetriever> predicate
    ) : input_(input), predicate_(predicate) {
    }

    UnknownDataTypeContainer 
    retrieve(InvocationContext& value) const override {
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

            auto predicateResult = predicate_->retrieve(*scope);

            if(predicateResult.convert<types::BoolType>().as<types::BoolType>()) {
                return make_data(true);
            }
        }

        return make_data(false);
    }

private:
    std::shared_ptr<ValueRetriever> input_;
    std::shared_ptr<ValueRetriever> predicate_;
};

struct sort_impl;

bool do_comparator(const sort_impl& retriever, std::shared_ptr<InvocationContext> context,
    UnknownDataTypeContainer& lhs, UnknownDataTypeContainer& rhs);

bool do_default(const sort_impl& retriever, std::shared_ptr<InvocationContext> context,
    UnknownDataTypeContainer& lhs, UnknownDataTypeContainer& rhs);

struct sort_impl : ValueRetriever {
    sort_impl(
        std::shared_ptr<ValueRetriever> list,
        std::shared_ptr<ValueRetriever> comparator
    ) : list_(list), comparator_(comparator) {}

    friend bool do_comparator(
        const sort_impl& retriever, 
        std::shared_ptr<InvocationContext> context,
        UnknownDataTypeContainer& lhs, 
        UnknownDataTypeContainer& rhs
    ) {
        auto wrapped = wrap_scope(context)
            .use_default(make_data(types::ArrayType::data_type{lhs, rhs}))
            .build();

        auto result = retriever.comparator_->retrieve(*wrapped);

        return result < make_data(0);
    }

    friend bool do_default(
        const sort_impl& retriever, 
        std::shared_ptr<InvocationContext> context,
        UnknownDataTypeContainer& lhs, 
        UnknownDataTypeContainer& rhs
    ) {
        return lhs.compare(rhs) < 0;
    }

    UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override {
        auto list = list_->retrieve(value);
        auto& input = list.as<types::ArrayType>();
        
        types::ArrayType::data_type arr = input;

        std::sort(arr.begin(), arr.end(), 
                  comparator_ ? bind(do_default, value) : bind(do_comparator, value)
        );

        return make_data(arr);
    }

private:
    std::function<bool (UnknownDataTypeContainer&, UnknownDataTypeContainer&)> 
        
    bind(
        std::function<bool (const sort_impl&, std::shared_ptr<InvocationContext>, UnknownDataTypeContainer&, UnknownDataTypeContainer&)> comparator,
        InvocationContext& context
    ) const {
        return std::bind(comparator, *this, context.shared_from_this(), std::placeholders::_1, std::placeholders::_2);
    }

    std::shared_ptr<ValueRetriever> list_;
    std::shared_ptr<ValueRetriever> comparator_;
};

}

std::shared_ptr<ValueRetriever>
map_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input, expr] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<map_impl>(input, expr);
}

UnknownDataTypeContainer
map_impl::retrieve(InvocationContext& val) const {
    using vec_type = std::vector<UnknownDataTypeContainer>;

    std::unique_ptr<vec_type> ret = std::make_unique<vec_type>();
    UnknownDataTypeContainer iterable = input_->retrieve(val);;

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

std::shared_ptr<ValueRetriever>
length_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input] = util::get_parameters_first_parent<1>(parent, parameters);
    return std::make_shared<length_impl>(input);
}

UnknownDataTypeContainer
length_impl::retrieve(InvocationContext& value) const {
    std::stringstream ss;
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

std::shared_ptr<ValueRetriever>
join_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input, delim] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<join_impl>(input, delim);
}

UnknownDataTypeContainer
join_impl::retrieve(InvocationContext& value) const {
    std::stringstream ss;
    auto iterable = input_->retrieve(value);
    auto delimiter_val = delimiter_->retrieve(value);
    
    delimiter_val.assert_type<types::StringType>("delimiter");

    auto iterator = iterable.iterate();

    bool more = iterator->more();
    while(more) {
        iterator->next();
        auto current = iterator->current();

        ss << current.convert<types::StringType>().as<types::StringType>();

        more = iterator->more();
        if(more) {
            ss << delimiter_val.as<types::StringType>();
        }
    }

    return make_data<types::StringType>(ss.str());
}

std::shared_ptr<ValueRetriever>
contains_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [input, delim] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<contains_impl>(input, delim);
}

UnknownDataTypeContainer
contains_impl::retrieve(InvocationContext& value) const {
    auto testValue = value_->retrieve(value);
    auto iterable = input_->retrieve(value);

    auto iterator = iterable.iterate();


    bool more = iterator->more();
    while(more) {
        iterator->next();
        auto current = iterator->current();

        if(iterator->current() == testValue) {
            return make_data(true);
        }

        more = iterator->more();
    }

    return make_data<types::BoolType>(false);
}

std::shared_ptr<ValueRetriever>
each_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [list, expr] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<each_impl>(list, expr);
}

std::shared_ptr<ValueRetriever>
all_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [list, pred] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<all_impl>(list, pred);
}

std::shared_ptr<ValueRetriever>
any_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [list, pred] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<any_impl>(list, pred);
}

std::shared_ptr<ValueRetriever>
sort_func::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [list, comparator] = util::get_parameters_first_parent<1, 1>(parent, parameters);
    return std::make_shared<sort_impl>(list, comparator);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
