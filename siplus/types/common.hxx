#include "siplus/config.h"
#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {

template<simple_value_retrievable_type T>
struct NativeHashable : UnaryOperatorTypeExtensionImpl {
    NativeHashable() : UnaryOperatorTypeExtensionImpl(TypeInfo::Hashable) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data<types::IntegerType>(native_(thisValue.as<T>()));
    }
    
private:
    std::hash<typename T::data_type> native_;
};

} /* SIPLUS_NAMESPACE */
