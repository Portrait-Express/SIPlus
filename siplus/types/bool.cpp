#include "siplus/context.hxx"
#include "common.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

namespace {

struct BoolEqualsImpl : BinaryOperatorTypeExtensionImpl {
    BoolEqualsImpl() : BinaryOperatorTypeExtensionImpl(TypeInfo::Equatable) {}

    bool can_handle(const UnknownDataTypeContainer &other) const override {
        return other.is<BoolType>();
    }

    UnknownDataTypeContainer invoke(bool isLhs, const UnknownDataTypeContainer &thisValue, const UnknownDataTypeContainer &other) const override {
        return make_data(other.as<BoolType>() == thisValue.as<BoolType>());
    }
};

struct BoolStringConverterImpl : UnaryOperatorTypeExtensionImpl {
    BoolStringConverterImpl() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<StringType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &value) const override {
        return make_data(value.as<BoolType>() ? "true" : "false");
    }
};

struct BoolIntegerConverterImpl : UnaryOperatorTypeExtensionImpl {
    BoolIntegerConverterImpl() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<IntegerType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &value) const override {
        return make_data(value.as<BoolType>() ? 1 : 0);
    }
};

} /* namespace anonymous */

const TypeInfoDescriptor *const BoolType::descriptor = new TypeInfoDescriptor("boolean");

BoolType::BoolType() : TypeInfo(BoolType::descriptor) {
    add_extension(new BoolIntegerConverterImpl());
    add_extension(new BoolStringConverterImpl());

    add_extension(new NativeHashable<BoolType>());
    add_extension(new BoolEqualsImpl());
}

bool BoolType::is_iterable(const UnknownDataTypeContainer& data) const { 
    return false; 
}


} /* types */
} /* SIPLUS_NAMESPACE */
