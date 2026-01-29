#include "siplus/stl/converters.hxx"
#include "siplus/data.hxx"
#include "siplus/types/bool.hxx"
#include "siplus/types/float.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"
#include "siplus/util.hxx"
#include <iomanip>

namespace SIPLUS_NAMESPACE {
namespace stl {


bool int_float_converter::can_convert(const TypeInfo& from, const TypeInfo& to) const {
    return from.is<types::IntegerType>() && to.is<types::FloatType>();
}

UnknownDataTypeContainer
int_float_converter::convert(const UnknownDataTypeContainer& from, const TypeInfo& to) const {
    return make_data<types::FloatType>(from.as<types::IntegerType>());
}

bool
numeric_string_converter::can_convert(const TypeInfo& from, const TypeInfo& to) const {
    return (
        from.is<types::IntegerType>() || 
        from.is<types::FloatType>()
    ) && to.is<types::StringType>();
}

UnknownDataTypeContainer
numeric_string_converter::convert(const UnknownDataTypeContainer& from, const TypeInfo& to) const {
    if(from.is<types::IntegerType>()) {
        return make_data<types::StringType>(std::to_string(from.as<types::IntegerType>()));
    } else if(from.is<types::FloatType>()) {
        return make_data<types::StringType>(util::to_string(
            std::setprecision(8), from.as<types::FloatType>()
        ));
    } else {
        throw std::runtime_error{"Cannot convert from " + from.type->name() + " to " + to.name()}; 
    }
}

bool
numeric_bool_converter::can_convert(const TypeInfo& from, const TypeInfo& to) const {
    return (
        from.is<types::IntegerType>() || 
        from.is<types::FloatType>()
    ) && to.is<types::BoolType>();
}

UnknownDataTypeContainer
numeric_bool_converter::convert(const UnknownDataTypeContainer& from, const TypeInfo& to) const {
    if(from.is<types::IntegerType>()) {
        return make_data<types::BoolType>(from.as<types::IntegerType>());
    } else if(from.is<types::FloatType>()) {
        return make_data<types::BoolType>(from.as<types::FloatType>());
    } else {
        throw std::runtime_error{"Cannot convert from " + from.type->name() + " to " + to.name()}; 
    }
}

bool bool_string_converter::can_convert(const TypeInfo& from, const TypeInfo& to) const {
    return from.is<types::BoolType>() && to.is<types::StringType>();
}

UnknownDataTypeContainer bool_string_converter::convert(
    const UnknownDataTypeContainer& from,
    const TypeInfo& to
) const {
    return make_data<types::StringType>(
        from.as<types::BoolType>() ? "true" : "false"
    );
}

bool string_bool_converter::can_convert(const TypeInfo& from, const TypeInfo& to) const {
    return from.is<types::StringType>() && to.is<types::BoolType>();
}

UnknownDataTypeContainer string_bool_converter::convert(
    const UnknownDataTypeContainer& from,
    const TypeInfo& to
) const {
    bool value = !from.as<types::StringType>().empty();
    return make_data<types::BoolType>(value);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
