#include "siplus/stl/functions/set.h"
#include "siplus/context.h"
#include "siplus/text/data.h"
#include "siplus/text/text.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/text/value_retrievers/lambda_value_retriever.h"
#include "siplus/util.h"
#include <unordered_set>

using namespace SIPLUS_NAMESPACE;

namespace std {

hash<text::UnknownDataTypeContainer>::hash(
    shared_ptr<SIPlusParserContext> context
) : context_(context) { }

std::uint64_t hash<text::UnknownDataTypeContainer>::operator()(
    const text::UnknownDataTypeContainer& container
) const {
    if(text::is_numeric(container.type)) {
        auto base = text::as_base(context_, container);

        if(base.is<long>()) {
            return long_(base.as<long>());
        } else if(base.is<double>()) {
            return double_(base.as<double>());
        } else {
            throw runtime_error{util::to_string(
                "Unknown hash numeric ", base.type.name()
            )};
        }
    } else if(container.is<string>()) {
        return string_(container.as<string>());
    } else {
        throw runtime_error{"Unsure how to hash " + 
            text::get_type_name(container.type)};
    }
}

equal_to<text::UnknownDataTypeContainer>::equal_to(
    shared_ptr<SIPlusParserContext> context,
    shared_ptr<text::ValueRetriever> comparator
) : context_(context), comparator_(comparator) { }

bool equal_to<text::UnknownDataTypeContainer>::operator()(
    const text::UnknownDataTypeContainer& lhs,
    const text::UnknownDataTypeContainer& rhs
) const {
    auto ctx = context_->builder()
        .with("*lhs", lhs)
        .with("*rhs", rhs)
        .build();

    auto result = comparator_->retrieve(*ctx);

    if(!result.is<bool>()) {
        throw runtime_error{"eq didnt return bool"};
    }

    return result.as<bool>();
}

} /* std */

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct set_new_impl : text::ValueRetriever {
    set_new_impl(
        std::shared_ptr<SIPlusParserContext> context
    ) : context_(context) {}

    text::UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<text::ValueRetriever> hasher_;
    std::shared_ptr<text::ValueRetriever> equality_;
    std::shared_ptr<SIPlusParserContext> context_;
};

text::UnknownDataTypeContainer
set_new_impl::retrieve(InvocationContext& value) const {
    std::shared_ptr<text::ValueRetriever> lhs = 
        std::make_shared<text::LambdaValueRetriever>([](InvocationContext& ctx) {
            return ctx.variable("*lhs");
        });

    std::shared_ptr<text::ValueRetriever> rhs = 
        std::make_shared<text::LambdaValueRetriever>([](InvocationContext& ctx) {
            return ctx.variable("*rhs");
        });

    auto eq = context_->function("eq").value(
        std::shared_ptr<text::ValueRetriever>{}, 
        std::vector<std::shared_ptr<text::ValueRetriever>>{ lhs, rhs }
    );

    set_t *set = new set_t{
        1, 
        std::hash<text::UnknownDataTypeContainer>{context_},
        std::equal_to<text::UnknownDataTypeContainer>{ context_, eq }
    };

    return text::make_data(set);
}

struct set_add_impl : text::ValueRetriever {
    set_add_impl(
        std::shared_ptr<text::ValueRetriever> set,
        std::shared_ptr<text::ValueRetriever> value
    ) : set_(set), value_(value) {}

    text::UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<text::ValueRetriever> set_;
    std::shared_ptr<text::ValueRetriever> value_;
};

text::UnknownDataTypeContainer
set_add_impl::retrieve(InvocationContext& context) const {
    text::UnknownDataTypeContainer set = set_->retrieve(context);
    text::UnknownDataTypeContainer value = value_->retrieve(context);

    if(!set.is<set_t>()) {
        throw std::runtime_error{"Expected first argument to be an instance of a set"};
    }

    set.as<set_t>().insert(value);

    return set;
}

struct set_has_impl : text::ValueRetriever {
    set_has_impl(
        std::shared_ptr<text::ValueRetriever> set,
        std::shared_ptr<text::ValueRetriever> value
    ) : set_(set), value_(value) {}

    text::UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<text::ValueRetriever> set_;
    std::shared_ptr<text::ValueRetriever> value_;
};

text::UnknownDataTypeContainer
set_has_impl::retrieve(InvocationContext& context) const {
    auto set = set_->retrieve(context);
    auto value = value_->retrieve(context);

    if(!set.is<set_t>()) {
        throw std::runtime_error{"Expected first argument to be an instance of a set"};
    }

    return text::make_data(set.as<set_t>().contains(value));
}
 
} /* anonymous */

std::shared_ptr<text::ValueRetriever> set_new_func::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> arguments
) const {
    if(parent || arguments.size() > 0) {
        throw std::runtime_error{"set_new does not expect any arguments"};
    }
    return std::make_shared<set_new_impl>(context_.lock());
}

std::shared_ptr<text::ValueRetriever> set_add_func::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> arguments
) const {
    auto [set, val] = util::get_parameters_first_parent<2>(parent, arguments);
    return std::make_shared<set_add_impl>(set, val);
}

std::shared_ptr<text::ValueRetriever> set_has_func::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> arguments
) const {
    auto [set, val] = util::get_parameters_first_parent<2>(parent, arguments);
    return std::make_shared<set_has_impl>(set, val);
}



bool set_iterator::more() {
    return begin_ != end_;
}
void set_iterator::next() {
    if(!next_called_) {
        next_called_ = true;
        return;
    }

    begin_++;
}
text::UnknownDataTypeContainer set_iterator::current() {
    return *begin_;
}

std::unique_ptr<text::Iterator> set_iterator_provider::iterator(
    const text::UnknownDataTypeContainer& value
) {
    auto& set = value.as<std::unordered_set<text::UnknownDataTypeContainer>>();

    return std::make_unique<set_iterator>(set.begin(), set.end());
}

bool set_iterator_provider::can_iterate(const text::UnknownDataTypeContainer& value) {
    return value.is<std::unordered_set<text::UnknownDataTypeContainer>>();
}

} /* stl */
} /* SIPLUS_NAMESPACE */
