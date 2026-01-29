#include "siplus/stl/functions/set.h"
#include "siplus/context.h"
#include "siplus/data.h"
#include "siplus/parser.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/text/value_retrievers/lambda_value_retriever.h"
#include "siplus/types/bool.h"
#include "siplus/types/float.h"
#include "siplus/types/string.h"
#include "siplus/util.h"
#include <unordered_set>

using namespace SIPLUS_NAMESPACE;

namespace std {

std::uint64_t hash<UnknownDataTypeContainer>::operator()(
    const UnknownDataTypeContainer& container
) const {
    if(container.is<types::IntegerType>()) {
        return long_(container.as<types::IntegerType>());
    } else if(container.is<types::FloatType>()) {
        return double_(container.as<types::FloatType>());
    } else if(container.is<types::StringType>()) {
        return string_(container.as<types::StringType>());
    } else {
        throw runtime_error{"Unsure how to hash " + container.type->name()}; 
    }
}

equal_to<UnknownDataTypeContainer>::equal_to(
    shared_ptr<SIPlusParserContext> context,
    shared_ptr<text::ValueRetriever> comparator
) : context_(context), comparator_(comparator) { }

bool equal_to<UnknownDataTypeContainer>::operator()(
    const UnknownDataTypeContainer& lhs,
    const UnknownDataTypeContainer& rhs
) const {
    auto ctx = context_->builder()
        .with("*lhs", lhs)
        .with("*rhs", rhs)
        .build();

    auto result = comparator_->retrieve(*ctx);

    if(!result.is<types::BoolType>()) {
        throw runtime_error{"eq didnt return bool"};
    }

    return result.as<types::BoolType>();
}

} /* std */

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct set_new_impl : text::ValueRetriever {
    set_new_impl(
        std::shared_ptr<SIPlusParserContext> context
    ) : context_(context) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<text::ValueRetriever> hasher_;
    std::shared_ptr<text::ValueRetriever> equality_;
    std::shared_ptr<SIPlusParserContext> context_;
};

UnknownDataTypeContainer
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

    SetType::data_type *set = new SetType::data_type{
        1, 
        std::hash<UnknownDataTypeContainer>{},
        std::equal_to<UnknownDataTypeContainer>{ context_, eq }
    };

    return make_data<SetType>(set);
}

struct set_add_impl : text::ValueRetriever {
    set_add_impl(
        std::shared_ptr<text::ValueRetriever> set,
        std::shared_ptr<text::ValueRetriever> value
    ) : set_(set), value_(value) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<text::ValueRetriever> set_;
    std::shared_ptr<text::ValueRetriever> value_;
};

UnknownDataTypeContainer
set_add_impl::retrieve(InvocationContext& context) const {
    UnknownDataTypeContainer set = set_->retrieve(context);
    UnknownDataTypeContainer value = value_->retrieve(context);

    if(!set.is<SetType>()) {
        throw std::runtime_error{"Expected first argument to be an instance of a set"};
    }

    set.as<SetType>().insert(value);

    return set;
}

struct set_has_impl : text::ValueRetriever {
    set_has_impl(
        std::shared_ptr<text::ValueRetriever> set,
        std::shared_ptr<text::ValueRetriever> value
    ) : set_(set), value_(value) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<text::ValueRetriever> set_;
    std::shared_ptr<text::ValueRetriever> value_;
};

UnknownDataTypeContainer
set_has_impl::retrieve(InvocationContext& context) const {
    auto set = set_->retrieve(context);
    auto value = value_->retrieve(context);

    if(!set.is<SetType>()) {
        throw std::runtime_error{"Expected first argument to be an instance of a set"};
    }

    return make_data<types::BoolType>(set.as<SetType>().contains(value));
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


std::string SetType::name() const {
    return "set";
}

bool SetType::is_iterable() const {
    return true;
}

std::unique_ptr<text::Iterator> SetType::iterate(const UnknownDataTypeContainer& data) const {
    return std::make_unique<set_iterator>(
        data.as<SetType>().begin(), data.as<SetType>().end()
    );
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
UnknownDataTypeContainer set_iterator::current() {
    return *begin_;
}

} /* stl */
} /* SIPLUS_NAMESPACE */
