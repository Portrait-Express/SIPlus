#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

namespace  {

struct NullEquatableImpl : BinaryOperatorTypeExtensionImpl {
    NullEquatableImpl() : BinaryOperatorTypeExtensionImpl(TypeInfo::Equatable) {}

    bool can_handle(const UnknownDataTypeContainer &other) const override {
        return true;
    }

    UnknownDataTypeContainer invoke(bool isLhs, const UnknownDataTypeContainer &thisValue, const UnknownDataTypeContainer &other) const override {
        return make_data(other.is<NullType>());
    }
};

struct NullStringConverter : UnaryOperatorTypeExtensionImpl {
    NullStringConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<StringType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data("(null)");
    }
};

struct NullBoolConverter : UnaryOperatorTypeExtensionImpl {
    NullBoolConverter () : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<BoolType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data(false);
    }
};

struct NullHashable : UnaryOperatorTypeExtensionImpl {
    NullHashable() : UnaryOperatorTypeExtensionImpl(TypeInfo::Hashable) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data<types::IntegerType>(0x42069420);
    }
};

} /* anonymous */


const TypeInfoDescriptor *const NullType::descriptor = new TypeInfoDescriptor("null");

NullType::NullType() : TypeInfo(descriptor) {
    add_extension(new NullStringConverter());
    add_extension(new NullBoolConverter());

    add_extension(new NullEquatableImpl());
    add_extension(new NullHashable());
}

UnknownDataTypeContainer NullType::access(const UnknownDataTypeContainer& data, const std::string& name) const {
    throw std::runtime_error{"Cannot access properties on null"};
}

bool NullType::is_iterable(const UnknownDataTypeContainer& data) const { 
    return false; 
}


} /* types */
} /* SIPLUS_NAMESPACE */
