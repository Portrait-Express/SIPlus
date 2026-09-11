#include "siplus/context.hxx"
#include "siplus/range_iterator.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

namespace {
 
struct ArrayEqualsImpl : BinaryOperatorTypeExtensionImpl {
    ArrayEqualsImpl() : BinaryOperatorTypeExtensionImpl(TypeInfo::Equatable) {}

    bool can_handle(const UnknownDataTypeContainer &other) const override {
        return other.is_iterable();
    }

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer &thisValue, 
        const UnknownDataTypeContainer &other
    ) const override {
        
    }
};

} /* namespace anonymous */

const TypeInfoDescriptor *const ArrayType::descriptor = new TypeInfoDescriptor("array");

ArrayType::ArrayType() : TypeInfo(descriptor) {
    add_extension(new ArrayEqualsImpl());
}

bool ArrayType::is_iterable(const UnknownDataTypeContainer& data) const { 
    return true; 
}

std::unique_ptr<Iterator> ArrayType::iterate(const UnknownDataTypeContainer& data) const {
    using it_t = ArrayType::data_type::const_iterator;
    return std::make_unique<value_range_iterator<it_t, it_t>>(
        data.as<ArrayType>().begin(), data.as<ArrayType>().end()
    );
}

UnknownDataTypeContainer ArrayType::index(
    std::shared_ptr<SIPlusParserContext> context, 
    UnknownDataTypeContainer &value, 
    UnknownDataTypeContainer &indexValue
) const {
    auto& arr = value.as<ArrayType>();
    auto index = indexValue.convert<IntegerType>().as<IntegerType>();

    if(index < 0 || index >= arr.size()) {
        throw std::runtime_error{util::to_string(
            "Index ", index, " out of range for array (size: ", arr.size(), ")"
        )};
    }

    return value.as<ArrayType>()[index];
}


} /* types */
} /* SIPLUS_NAMESPACE */
