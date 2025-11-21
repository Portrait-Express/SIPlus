#include "siplus/stl/converters.h"
#include "siplus/text/data.h"
#include "siplus/util.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

bool
int_converter::can_convert(std::type_index from, std::type_index to) const {
    return (
            from == typeid(short) ||
            from == typeid(int) || 
            from == typeid(long)
        ) &&
        to == typeid(long);
}

text::UnknownDataTypeContainer 
int_converter::convert(const text::UnknownDataTypeContainer& from, std::type_index to) const {
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

bool float_converter::can_convert(std::type_index from, std::type_index to) const {
    return (
        from == typeid(float) ||
        from == typeid(double)
    ) && to == typeid(double);
}

text::UnknownDataTypeContainer
float_converter::convert(const text::UnknownDataTypeContainer& from, std::type_index to) const {
    if(from.is<double>()) return from;

    double d;

    if(from.is<float>()) {
        d = from.as<float>();
    }

    return text::make_data(d);
}

bool
numeric_string_converter::can_convert(std::type_index from, std::type_index to) const {
    return util::is_numeric(from) && to == typeid(std::string);
}

text::UnknownDataTypeContainer
numeric_string_converter::convert(const text::UnknownDataTypeContainer& from, std::type_index to) const {
    auto ctx = ctx_.lock();
    auto base = util::as_base(ctx, from);
    if(base.is<double>()) {
        long val = base.as<double>();
        return text::make_data(to_string(val));
    } else if(base.is<long>()) {
        double val = base.as<long>();
        return text::make_data(to_string(val));
    } else {
        throw std::runtime_error{"Cannot convert from " + get_type_name(from.type) 
            + " to " + get_type_name(to)};
    }
}

bool
numeric_bool_converter::can_convert(std::type_index from, std::type_index to) const {
    return util::is_numeric(from) && to == typeid(bool);
}

text::UnknownDataTypeContainer
numeric_bool_converter::convert(const text::UnknownDataTypeContainer& from, std::type_index to) const {
    auto ctx = ctx_.lock();
    auto base = util::as_base(ctx, from);

    if(base.is<double>()) {
        return text::make_data(static_cast<bool>(base.as<double>()));
    } else if(base.is<long>()) {
        return text::make_data(static_cast<bool>(base.as<long>()));
    } else {
        throw std::runtime_error{"Cannot convert from " + get_type_name(from.type) + " to bool."};
    }
}

bool bool_string_converter::can_convert(std::type_index from, std::type_index to) const {
    return from == typeid(bool) && to == typeid(std::string);
}

text::UnknownDataTypeContainer bool_string_converter::convert(
    const text::UnknownDataTypeContainer& from,
    std::type_index to
) const {
    if(from.as<bool>()) {
        return text::make_data<std::string>("true");
    } else {
        return text::make_data<std::string>("false");
    }
}

bool string_bool_converter::can_convert(std::type_index from, std::type_index to) const {
    return from == typeid(std::string) && to == typeid(bool);
}

text::UnknownDataTypeContainer string_bool_converter::convert(
    const text::UnknownDataTypeContainer& from,
    std::type_index to
) const {
    bool value = !from.as<std::string>().empty();
    return text::make_data(value);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
