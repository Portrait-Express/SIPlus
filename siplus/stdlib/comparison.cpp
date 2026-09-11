#include "siplus/util.hxx"
#include "siplus/value_retrievers/binary_operator_value_retriever.hxx"
#include "siplus/stl/functions/comparison.hxx"
#include "siplus/context.hxx"

#include <iostream>
#include <memory>

namespace SIPLUS_NAMESPACE {
namespace stl {


namespace {

struct ComparableDerivedRetriever : BinaryOperatorFunctionRetriever {
    ComparableDerivedRetriever(
        std::function<bool (long i)> testInteger,
        std::shared_ptr<ValueRetriever> lhs,
        std::shared_ptr<ValueRetriever> rhs
    ) : testInteger_(testInteger),
        BinaryOperatorFunctionRetriever(TypeInfo::Comparable, lhs, rhs) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto result = BinaryOperatorFunctionRetriever::retrieve(value);

        if(result.is<types::IntegerType>()) {
            return make_data(testInteger_(result.as<types::IntegerType>()));
        } else {
            throw std::runtime_error{"Comparable did not return a number as expected."};
        }
    }

private:
    std::function<bool (long i)> testInteger_;
};

} /* anonymous */



std::shared_ptr<ValueRetriever> LessThanFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, parameters);

    return std::make_shared<ComparableDerivedRetriever>(
        [](long i){ return i < 0; }, lhs, rhs
    );
}

std::shared_ptr<ValueRetriever> GreaterThanFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, parameters);

    return std::make_shared<ComparableDerivedRetriever>(
        [](long i){ return i > 0; }, lhs, rhs
    );
}

std::shared_ptr<ValueRetriever> LessThanEqualFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, parameters);

    return std::make_shared<ComparableDerivedRetriever>(
        [](long i){ return i <= 0; }, lhs, rhs
    );
}

std::shared_ptr<ValueRetriever> GreaterThanEqualFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, parameters);

    return std::make_shared<ComparableDerivedRetriever>(
        [](long i){ return i >= 0; }, lhs, rhs
    );
}

std::shared_ptr<ValueRetriever> CompareFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, parameters);

    return std::make_shared<BinaryOperatorFunctionRetriever>(TypeInfo::Comparable, lhs, rhs);
}

struct EqualsRetriever : ValueRetriever {
    EqualsRetriever(
        std::shared_ptr<ValueRetriever> lhs,
        std::shared_ptr<ValueRetriever> rhs
    ) : lhs_(lhs), rhs_(rhs) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto lhs = lhs_->retrieve(value);
        auto rhs = rhs_->retrieve(value);

        auto optResult = do_binary(TypeInfo::Equatable, lhs, rhs);
        if(optResult != std::nullopt) {
            return *optResult;
        }

        optResult = do_binary(TypeInfo::Comparable, lhs, rhs);
        if(optResult == std::nullopt) {
            throw std::runtime_error{util::to_string(
                "Cannot compare '", lhs.type->name(), "' and '", lhs.type->name(), 
                "'. Neither type is 'Equatable' or 'Comparable' with the other."
            )};
        }

        auto& result = *optResult;
        if(result.is<types::IntegerType>()) {
            return make_data(result.as<types::IntegerType>() == 0);
        } else {
            throw std::runtime_error{"Comparable did not return a number as expected."};
        }
    }

private:
    std::shared_ptr<ValueRetriever> lhs_;
    std::shared_ptr<ValueRetriever> rhs_;
};

struct EqualsFunctionImpl : ValueRetriever { 
    EqualsFunctionImpl(
        std::shared_ptr<ValueRetriever> lhs,
        std::shared_ptr<ValueRetriever> rhs
    ) : lhs_(lhs), rhs_(rhs) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto lhs = lhs_->retrieve(value);
        auto rhs = rhs_->retrieve(value);

        return make_data(lhs == rhs);
    }

private:
    std::shared_ptr<ValueRetriever> lhs_;
    std::shared_ptr<ValueRetriever> rhs_;
};

std::shared_ptr<ValueRetriever> EqualsFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, parameters);

    return std::make_shared<EqualsFunctionImpl>(lhs, rhs);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
