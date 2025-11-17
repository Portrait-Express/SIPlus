#include "siplus/stl/converters.h"
#include "siplus/util.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

bool
int_converter::can_convert(std::type_index from, std::type_index to) {
    return (
            from == typeid(short) ||
            from == typeid(int) || 
            from == typeid(long)
        ) &&
        to == typeid(long);
}

text::UnknownDataTypeContainer 
int_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    if(from.is<long>()) return from; 

    long val;

    if(from.is<int>()) {
        val = from.as<int>();
    } else if(from.is<short>()) {
        val = from.as<short>();
    } else {
        throw std::runtime_error{"Int converter cannot handle source type " + 
            get_type_name(from.type)};
    }

    return text::make_data(val);
}

bool float_converter::can_convert(std::type_index from, std::type_index to) {
    return (
        from == typeid(float) ||
        from == typeid(double)
    ) && to == typeid(double);
}

text::UnknownDataTypeContainer
float_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    if(from.is<double>()) return from;

    double d;

    if(from.is<float>()) {
        d = from.as<float>();
    }

    return text::make_data(d);
}

bool
numeric_string_converter::can_convert(std::type_index from, std::type_index to) {
    return (
        int_converter_.can_convert(from, typeid(long)) ||
        float_converter_.can_convert(from, typeid(double))
    ) && to == typeid(std::string);
}

text::UnknownDataTypeContainer
numeric_string_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    if(int_converter_.can_convert(from.type, typeid(long))) {
        long val = int_converter_.convert(from, typeid(long)).as<long>();
        return text::make_data(to_string(val));
    } else if(float_converter_.can_convert(from.type, typeid(double))) {
        double val = float_converter_.convert(from, typeid(double)).as<double>();
        return text::make_data(to_string(val));
    } else {
        throw std::runtime_error{"Cannot convert from " + get_type_name(from.type) 
            + " to " + get_type_name(to)};
    }
}

bool
numeric_bool_converter::can_convert(std::type_index from, std::type_index to) {
    return (
        float_converter_.can_convert(from, typeid(double)) ||
        int_converter_.can_convert(from, typeid(long))
    ) && to == typeid(bool);
}

text::UnknownDataTypeContainer
numeric_bool_converter::convert(text::UnknownDataTypeContainer from, std::type_index to) {
    if(float_converter_.can_convert(from.type, typeid(double))) {
        return text::make_data(static_cast<bool>(float_converter_.convert(from, typeid(double)).as<double>()));
    } else if(int_converter_.can_convert(from.type, typeid(long))) {
        return text::make_data(static_cast<bool>(int_converter_.convert(from, typeid(long)).as<long>()));
    } else {
        throw std::runtime_error{"Cannot convert from " + get_type_name(from.type) + " to bool."};
    }
}

} /* stl */
} /* SIPLUS_NAMESPACE */
