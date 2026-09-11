#include "stl.hxx"
#include "siplus/stl/functions/comparison.hxx"
#include "siplus/stl/functions/control.hxx"
#include "siplus/stl/functions/rand.hxx"
#include "siplus/stl/functions/arithmetic.hxx"
#include "siplus/stl/functions/iterable.hxx"
#include "siplus/stl/functions/set.hxx"
#include "siplus/stl/functions/text.hxx"
#include "siplus/stl/functions/type.hxx"
#include "siplus/stl/functions/typed_operator.hxx"

#include <functional>

using namespace SIPLUS_NAMESPACE;
using namespace SIPLUS_NAMESPACE::stl;

//----------------------------
// Free Functions
//----------------------------

void attach_stl(SIPlusParserContext& context) {
    //Misc
    context.emplace_function<str_func>("str");
    context.emplace_function<if_func>("if");
    context.emplace_function<while_func>("while");
    context.emplace_function<type_function>("type");

    //Set functions
    context.emplace_function<set_new_func>("set_new");
    context.emplace_function<set_add_func>("set_add");
    context.emplace_function<set_has_func>("set_has");

    //Iterator-related
    context.emplace_function<map_func>("map");
    context.emplace_function<length_func>("length");
    context.emplace_function<join_func>("join");
    context.emplace_function<contains_func>("contains");
    context.emplace_function<each_func>("each");
    context.emplace_function<all_func>("all");
    context.emplace_function<any_func>("any");
    context.emplace_function<sort_func>("sort");

    //Boolean logic
    using binary_bool_func = typed_binary_operator_function<types::BoolType, types::BoolType>;
    using unary_bool_func = typed_unary_operator_function<types::BoolType, types::BoolType>;
    context.emplace_function<binary_bool_func>("and", std::logical_and<bool>());
    context.emplace_function<binary_bool_func>("or", std::logical_or<bool>());
    context.emplace_function<binary_bool_func>("xor", std::not_equal_to<bool>());
    context.emplace_function<unary_bool_func>("not", std::logical_not<bool>());

    context.emplace_function<rand_func>("rand");
    context.emplace_function<rand_str_func>("randstr");

    context.emplace_function<AddFunction>("add");
    context.emplace_function<SubtractFunction>("sub");
    context.emplace_function<MultiplyFunction>("mul");
    context.emplace_function<DivideFunction>("div");

    //Comparison
    context.emplace_function<CompareFunction>("cmp");
    context.emplace_function<EqualsFunction>("eq");
    context.emplace_function<LessThanFunction>("lt");
    context.emplace_function<GreaterThanFunction>("gt");
    context.emplace_function<LessThanEqualFunction>("lte");
    context.emplace_function<GreaterThanEqualFunction>("gte");

    //Text Editing
    context.emplace_function<replace_function>("replace");
    context.emplace_function<pad_end_function>("padEnd");
    context.emplace_function<pad_start_function>("padStart");
    context.emplace_function<trim_function>("trim");
    context.emplace_function<upper_function>("upper");
    context.emplace_function<lower_function>("lower");
    context.emplace_function<split_function>("split");
    context.emplace_function<substr_function>("substr");
}
