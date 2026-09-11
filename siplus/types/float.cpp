#include "siplus/context.hxx"

#include "common.hxx"
#include "integral.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

namespace {

struct StringConverter : UnaryOperatorTypeExtensionImpl {
    StringConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<StringType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data(util::to_string(thisValue.as<FloatType>()));
    }
};

struct IntegerConverter : UnaryOperatorTypeExtensionImpl {
    IntegerConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<FloatType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data(static_cast<double>(thisValue.as<FloatType>()));
    }
};

struct BoolConverter : UnaryOperatorTypeExtensionImpl {
    BoolConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<BoolType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data(static_cast<bool>(thisValue.as<FloatType>()));
    }
};

} /* anonymous */

const TypeInfoDescriptor *const FloatType::descriptor = new TypeInfoDescriptor("double");

FloatType::FloatType() : TypeInfo(descriptor) {
    add_extension(new StringConverter());
    add_extension(new IntegerConverter());
    add_extension(new BoolConverter());

    add_extension(new IntegralAddable());
    add_extension(new IntegralSubtractable());
    add_extension(new IntegralMultiplicable());
    add_extension(new IntegralDivisible());
    add_extension(new IntegralComparable());
    add_extension(new NativeHashable<FloatType>());
}

bool FloatType::is_iterable(const UnknownDataTypeContainer& data) const { 
    return false; 
}


} /* types */
} /* SIPLUS_NAMESPACE */
