#include "siplus/util.h"
#include "siplus/context.h"
#include "siplus/text/text.h"
#include <memory>
#include <typeindex>

namespace SIPLUS_NAMESPACE {
namespace text {

bool is_numeric(std::type_index type) {
    return type == typeid(long) || type == typeid(int) || type == typeid(short)
        || type == typeid(float) || type == typeid(double);
}

text::UnknownDataTypeContainer as_base(
    std::shared_ptr<const SIPlusParserContext> ctx,
    text::UnknownDataTypeContainer       value
) {
    if(value.is<long>() || value.is<double>()) {
        return value;
    } else if(value.is<int>() || value.is<short>()) {
        return ctx->convert<long>(value);
    } else if(value.is<float>()) {
        return ctx->convert<double>(value);
    } else {
        throw std::runtime_error{"numeric_adder cannot add type " + text::get_type_name(value.type)};
    }
}

} /* text */
} /* SIPLUS_NAMESPACE */
