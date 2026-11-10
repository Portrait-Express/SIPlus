#include "siplus/context.hxx"
#include "siplus/stl/functions/pair.hxx"
#include "siplus/util.hxx"

#include "../util.hxx"

#include <sstream>

using namespace SIPLUS_NAMESPACE;

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct PairStringConverter : public UnaryOperatorTypeExtensionImpl {
    PairStringConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<types::StringType>()) {}

    virtual UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        auto pair = thisValue.as<PairType>();
        std::stringstream ss;
        
        ss << "{ " << pair.first << ", " << pair.second << " }";

        return make_data<types::StringType>(ss.str());
    }
};

struct PairEquatableImpl : BinaryOperatorTypeExtensionImpl {
    PairEquatableImpl() : BinaryOperatorTypeExtensionImpl(TypeInfo::Equatable) {}

    bool can_handle(const UnknownDataTypeContainer &other) const override {
        return other.is<PairType>();
    }

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer &thisValue, 
        const UnknownDataTypeContainer &other
    ) const override {
        auto &thisPair = thisValue.as<PairType>();
        auto &otherPair = other.as<PairType>();

        return make_data<types::BoolType>(
            thisPair.first == otherPair.first && 
                thisPair.second == otherPair.second
        );
    }
};

struct PairFunctionImpl : ValueRetriever {
    PairFunctionImpl(
        std::shared_ptr<ValueRetriever> first,
        std::shared_ptr<ValueRetriever> second
    ) : first_(first), second_(second) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto first = first_->retrieve(value);
        auto second = second_->retrieve(value);

        return make_data<PairType>({ first, second });
    }

private:
    std::shared_ptr<ValueRetriever> first_;
    std::shared_ptr<ValueRetriever> second_;
};

} /* namespace anonymous */

const TypeInfoDescriptor *const PairType::descriptor = new TypeInfoDescriptor("pair");
PairType::PairType() : TypeInfo(descriptor) {
    add_extension(new PairStringConverter());
    add_extension(new PairEquatableImpl());
}

UnknownDataTypeContainer
PairType::access(
    const UnknownDataTypeContainer& data, 
    const std::string& name
) const {
    if(name == "first") {
        return data.as<PairType>().first;
    } else if(name == "second") {
        return data.as<PairType>().second;
    }

    throw new std::runtime_error{"No property named " + name};
}

std::shared_ptr<ValueRetriever>
PairFunction::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [first, second] = util::get_parameters_first_parent<2>(parent, parameters);
    return detail::make_retriever<PairFunctionImpl>(first, second);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
