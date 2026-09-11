#include "siplus/stl/functions/arithmetic.hxx"
#include "siplus/context.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct BinaryOperatorRetriever : ValueRetriever {
    using impl_type = UnknownDataTypeContainer (UnknownDataTypeContainer lhs, UnknownDataTypeContainer rhs);

    BinaryOperatorRetriever(
        std::shared_ptr<ValueRetriever> lhs,
        std::shared_ptr<ValueRetriever> rhs,
        std::function<impl_type> impl
    ) : lhs_(lhs), rhs_(rhs), impl_(impl) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<ValueRetriever> lhs_;
    std::shared_ptr<ValueRetriever> rhs_;
    std::function<impl_type> impl_;
};

UnknownDataTypeContainer BinaryOperatorRetriever::retrieve(InvocationContext &value) const {
    auto lhs = lhs_->retrieve(value);
    auto rhs = rhs_->retrieve(value);

    return impl_(lhs, rhs);
}

}

std::shared_ptr<ValueRetriever> AddFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, params);
    return std::make_shared<BinaryOperatorRetriever>(lhs, rhs, [](auto lhs, auto rhs) static {
        return lhs + rhs;
    });
}

std::shared_ptr<ValueRetriever> SubtractFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, params);
    return std::make_shared<BinaryOperatorRetriever>(lhs, rhs, [](auto lhs, auto rhs) static {
        return lhs - rhs;
    });
}

std::shared_ptr<ValueRetriever> MultiplyFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, params);
    return std::make_shared<BinaryOperatorRetriever>(lhs, rhs, [](auto lhs, auto rhs) static {
        return lhs * rhs;
    });
}

std::shared_ptr<ValueRetriever> DivideFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [lhs, rhs] = util::get_parameters_first_parent<2>(parent, params);
    return std::make_shared<BinaryOperatorRetriever>(lhs, rhs, [](auto lhs, auto rhs) static {
        return lhs / rhs;
    });
}


} /* stl */
} /* SIPLUS_NAMESPACE */
