#include "common.hxx"
#include "integral.hxx"
#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

namespace {

struct StringConverter : UnaryOperatorTypeExtensionImpl {
    StringConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<StringType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data(util::to_string(thisValue.as<IntegerType>()));
    }
};

struct FloatConverter : UnaryOperatorTypeExtensionImpl {
    FloatConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<FloatType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data(static_cast<double>(thisValue.as<IntegerType>()));
    }
};

struct BoolConverter : UnaryOperatorTypeExtensionImpl {
    BoolConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<BoolType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data(static_cast<bool>(thisValue.as<IntegerType>()));
    }
};


} /* anonymous */

const TypeInfoDescriptor *const IntegerType::descriptor = new TypeInfoDescriptor("long");

IntegerType::IntegerType() : TypeInfo(descriptor) {
    add_extension(new StringConverter());
    add_extension(new FloatConverter());
    add_extension(new BoolConverter());

    add_extension(new IntegralAddable());
    add_extension(new IntegralSubtractable());
    add_extension(new IntegralMultiplicable());
    add_extension(new IntegralDivisible());
    add_extension(new IntegralComparable());
    add_extension(new NativeHashable<IntegerType>());
}

bool IntegerType::is_iterable(const UnknownDataTypeContainer& data) const { 
    return false; 
}


} /* types */
} /* SIPLUS_NAMESPACE */
