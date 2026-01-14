#include "siplus/stl/functions/rand.h"
#include "siplus/stl/functions/arithmetic.h"
#include "siplus/stl/functions/iterable.h"
#include "siplus/stl/functions/text.h"
#include "siplus/stl/functions/typed_operator.h"
#include "siplus/text/data.h"
#include "siplus/stl.h"

#include <functional>
#include <memory>

namespace SIPLUS_NAMESPACE {
namespace stl {


//----------------------------
// Free Functions
//----------------------------

void attach_stl(SIPlusParserContext& context) {
    //Base converters
    context.emplace_converter<int_converter>();
    context.emplace_converter<float_converter>();
    context.emplace_converter<string_bool_converter>();
    context.emplace_converter<bool_string_converter>();
    context.emplace_converter<numeric_string_converter>(context.shared_from_this());
    context.emplace_converter<numeric_bool_converter>(context.shared_from_this());

    //Misc
    context.emplace_function<str_func>("str", context.shared_from_this());
    context.emplace_function<if_func>("if", context.shared_from_this());
    context.emplace_function<while_func>("while", context.shared_from_this());

    //Iterator-related
    context.emplace_function<map_func>("map", context.shared_from_this());
    context.emplace_function<length_func>("length", context.shared_from_this());
    context.emplace_function<join_func>("join", context.shared_from_this());
    context.emplace_function<contains_func>("contains", context.shared_from_this());
    context.emplace_iterator<vector_iterator<text::UnknownDataTypeContainer>>();
    context.emplace_iterator<string_iterator>();

    //Boolean logic
    context.emplace_function<typed_binary_operator_function<bool, bool>>("and", context.shared_from_this(), std::logical_and<bool>());
    context.emplace_function<typed_binary_operator_function<bool, bool>>("or", context.shared_from_this(), std::logical_or<bool>());
    context.emplace_function<typed_binary_operator_function<bool, bool>>("xor", context.shared_from_this(), std::not_equal_to<bool>());
    context.emplace_function<typed_unary_operator_function<bool, bool>>("not", context.shared_from_this(), std::logical_not<bool>());

    context.emplace_function<rand_func>("rand", context.shared_from_this());
    context.emplace_function<rand_str_func>("randstr", context.shared_from_this());

    //Arithmetic
    auto add_func = converting_operator_function{context.shared_from_this()};
    add_func.emplace_impl<string_concatenator>().emplace_impl<numeric_adder>();

    auto sub_func = converting_operator_function{context.shared_from_this()};
    sub_func.emplace_impl<numeric_subtractor>();

    auto mul_func = converting_operator_function{context.shared_from_this()};
    mul_func.emplace_impl<numeric_multiplier>();

    auto div_func = converting_operator_function{context.shared_from_this()};
    div_func.emplace_impl<numeric_divider>();

    context.emplace_function<converting_operator_function>("add", add_func);
    context.emplace_function<converting_operator_function>("sub", sub_func);
    context.emplace_function<converting_operator_function>("mul", mul_func);
    context.emplace_function<converting_operator_function>("div", div_func);

    //Comparison
    auto cmp_func = converting_operator_function{context.shared_from_this()};
    auto cmp_ptr = context.emplace_function<converting_operator_function>("cmp", cmp_func);
    cmp_ptr->emplace_impl<string_comparator>();
    cmp_ptr->emplace_impl<numeric_comparator>();
    context.emplace_function<lt_func>("lt", context.shared_from_this(), cmp_ptr);
    context.emplace_function<gt_func>("gt", context.shared_from_this(), cmp_ptr);
    context.emplace_function<eq_func>("eq", context.shared_from_this(), cmp_ptr);

    //Text Editing
    context.emplace_function<replace_function>("replace", context.shared_from_this());
    context.emplace_function<pad_end_function>("padEnd", context.shared_from_this());
    context.emplace_function<pad_start_function>("padStart", context.shared_from_this());
    context.emplace_function<trim_function>("trim", context.shared_from_this());
    context.emplace_function<upper_function>("upper", context.shared_from_this());
    context.emplace_function<lower_function>("lower", context.shared_from_this());
    context.emplace_function<split_function>("split", context.shared_from_this());
    context.emplace_function<substr_function>("substr", context.shared_from_this());
}

} /* stl */
} /* SIPLUS_NAESPACE */
