#include "siplus/context.hxx"
#include "siplus/range_iterator.hxx"
#include "siplus/stl/functions/set.hxx"
#include "siplus/util.hxx"

#include <unordered_set>

using namespace SIPLUS_NAMESPACE;

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct set_new_impl : ValueRetriever {
    UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<ValueRetriever> hasher_;
    std::shared_ptr<ValueRetriever> equality_;
};

UnknownDataTypeContainer
set_new_impl::retrieve(InvocationContext& value) const {
    SetType::data_type *set = new SetType::data_type{};
    return make_data<SetType>(set);
}

struct set_add_impl : ValueRetriever {
    set_add_impl(
        std::shared_ptr<ValueRetriever> set,
        std::shared_ptr<ValueRetriever> value
    ) : set_(set), value_(value) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<ValueRetriever> set_;
    std::shared_ptr<ValueRetriever> value_;
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

struct set_has_impl : ValueRetriever {
    set_has_impl(
        std::shared_ptr<ValueRetriever> set,
        std::shared_ptr<ValueRetriever> value
    ) : set_(set), value_(value) {}

    UnknownDataTypeContainer 
    retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<ValueRetriever> set_;
    std::shared_ptr<ValueRetriever> value_;
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

std::shared_ptr<ValueRetriever> set_new_func::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> arguments
) const {
    if(parent || arguments.size() > 0) {
        throw std::runtime_error{"set_new does not expect any arguments"};
    }
    return std::make_shared<set_new_impl>();
}

std::shared_ptr<ValueRetriever> set_add_func::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> arguments
) const {
    auto [set, val] = util::get_parameters_first_parent<2>(parent, arguments);
    return std::make_shared<set_add_impl>(set, val);
}

std::shared_ptr<ValueRetriever> set_has_func::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> arguments
) const {
    auto [set, val] = util::get_parameters_first_parent<2>(parent, arguments);
    return std::make_shared<set_has_impl>(set, val);
}


const TypeInfoDescriptor *const SetType::descriptor = new TypeInfoDescriptor("set");

SetType::SetType() : TypeInfo(descriptor) {}

bool SetType::is_iterable(const UnknownDataTypeContainer& data) const {
    return true;
}

std::unique_ptr<Iterator> SetType::iterate(const UnknownDataTypeContainer& data) const {
    return std::make_unique<range_iterator<SetType::data_type::iterator>>(
        data.as<SetType>().begin(), data.as<SetType>().end()
    );
}

} /* stl */
} /* SIPLUS_NAMESPACE */
