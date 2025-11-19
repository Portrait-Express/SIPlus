#include "siplus/stl/functions/arithmetic.h"
#include "siplus/text/data.h"
#include "siplus/util.h"

namespace SIPLUS_NAMESPACE {
namespace stl {

text::UnknownDataTypeContainer 
SIPLUS_NAMESPACE::stl::numeric_adder::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer       lhs, 
    text::UnknownDataTypeContainer       rhs
) {
    lhs = util::as_base(context, lhs);
    rhs = util::as_base(context, rhs);

    if(lhs.is<long>()) {
        long val = lhs.as<long>();

        if(rhs.is<long>()) { 
            return text::make_data(val + rhs.as<long>());
        } else if(rhs.is<double>()) {
            return text::make_data(val + rhs.as<double>());
        } else {
            throw std::runtime_error{"Cannot add types long and " + get_type_name(rhs.type)};
        }
    } else if(lhs.is<double>()) {
        double val = lhs.as<double>();

        if(rhs.is<long>()) { 
            return text::make_data(val + rhs.as<long>());
        } else if(rhs.is<double>()) {
            return text::make_data(val + rhs.as<double>());
        } else {
            throw std::runtime_error{"Cannot add types double and " + get_type_name(rhs.type)};
        }
    } else {
        throw std::runtime_error{"Cannot add types " + get_type_name(lhs.type) 
            + " and " + get_type_name(rhs.type)};
    }
}

bool
numeric_adder::can_handle(std::type_index lhs, std::type_index rhs) const {
    return util::is_numeric(lhs) && util::is_numeric(rhs);
}

text::UnknownDataTypeContainer 
numeric_comparator::invoke(
    std::shared_ptr<SIPlusParserContext> context,
    text::UnknownDataTypeContainer lhs, 
    text::UnknownDataTypeContainer rhs
) {
    auto b_lhs = util::as_base(context, lhs);
    auto b_rhs = util::as_base(context, rhs);
    
    if(b_lhs.is<long>()) {
        if(b_rhs.is<long>()) {
            return text::make_data(compare(b_lhs.as<long>(), b_rhs.as<long>()));
        } else if(b_rhs.is<double>()) {
            return text::make_data(compare(b_lhs.as<long>(), b_rhs.as<double>()));
        } 
    } else if(b_lhs.is<double>()) {
        if(b_rhs.is<long>()) {
            return text::make_data(compare(b_lhs.as<double>(), b_rhs.as<long>()));
        } else if(b_rhs.is<double>()) {
            return text::make_data(compare(b_lhs.as<double>(), b_rhs.as<double>()));
        } 
    }

    throw std::runtime_error{"Uncomparable types " + get_type_name(b_lhs.type) 
        + " and " + get_type_name(b_rhs.type)};
}

bool numeric_comparator::can_handle(std::type_index lhs, std::type_index rhs) const {
    return util::is_numeric(lhs) && util::is_numeric(rhs);
}

} /* stl */
} /* SIPLUS_NAMESPACE */
