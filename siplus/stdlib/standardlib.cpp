#include "siplus/stl/functions/typed_operator.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"
#include "siplus/stl.h"

#include <functional>
#include <memory>
#include <vector>

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct if_impl : public text::ValueRetriever {
    if_impl(
        std::shared_ptr<text::ValueRetriever> condition,
        std::shared_ptr<text::ValueRetriever> tVal,
        std::shared_ptr<text::ValueRetriever> fVal,
        std::weak_ptr<SIPlusParserContext> context
    ) : condition(condition), tVal(tVal), fVal(fVal), context_(context) {}

    text::UnknownDataTypeContainer 
    retrieve(const text::UnknownDataTypeContainer& value) const override;

    std::shared_ptr<text::ValueRetriever> condition;
    std::shared_ptr<text::ValueRetriever> tVal;
    std::shared_ptr<text::ValueRetriever> fVal;

private:
    std::weak_ptr<SIPlusParserContext> context_;
};

}

std::shared_ptr<text::ValueRetriever>
if_func::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    std::shared_ptr<text::ValueRetriever> condition;
    std::shared_ptr<text::ValueRetriever> tVal;
    std::shared_ptr<text::ValueRetriever> fVal;

    if(parent) {
        if(parameters.size() < 1) {
            throw std::runtime_error{"Too few parameters specified for 'if'"};
        }
        if(parameters.size() > 2) {
            throw std::runtime_error{"Too many parameters specified for 'if'"};
        }
        
        condition = parent;
        tVal = parameters[0];
        if(parameters.size() == 2) {
            fVal = parameters[1];
        }
    } else {
        if(parameters.size() < 2) {
            throw std::runtime_error{"Too few parameters specified for 'if'"};
        }
        if(parameters.size() > 3) {
            throw std::runtime_error{"Too many parameters specified for 'if'"};
        }

        condition = parameters[0];
        tVal = parameters[1];
        if(parameters.size() == 3) {
            fVal = parameters[2];
        }
    }

    return std::make_shared<if_impl>(condition, tVal, fVal, context_);
}

text::UnknownDataTypeContainer
if_impl::retrieve(const text::UnknownDataTypeContainer& value) const {
    auto ctx = context_.lock();
    auto cond = condition->retrieve(value);

    if(ctx->convert<bool>(cond).as<bool>()) {
        return tVal->retrieve(value);
    } else {
        return fVal->retrieve(value);
    }
}


//----------------------------
// Free Functions
//----------------------------

void attach_stl(SIPlusParserContext& context) {
    //Base converters
    context.emplace_converter<int_converter>();
    context.emplace_converter<float_converter>();
    context.emplace_converter<numeric_string_converter>(context.shared_from_this());
    context.emplace_converter<numeric_bool_converter>(context.shared_from_this());

    //Misc
    context.emplace_function<str_func>("str", context.shared_from_this());
    context.emplace_function<if_func>("if", context.shared_from_this());

    //Iterator-related
    context.emplace_function<map_func>("map", context.shared_from_this());
    context.emplace_function<length_func>("length", context.shared_from_this());
    context.emplace_function<join_func>("join", context.shared_from_this());
    context.emplace_iterator<vector_iterator<long>>(); //base type iterators
    context.emplace_iterator<vector_iterator<int>>();
    context.emplace_iterator<vector_iterator<short>>();
    context.emplace_iterator<vector_iterator<double>>();
    context.emplace_iterator<vector_iterator<float>>();
    context.emplace_iterator<vector_iterator<std::string>>();
    context.emplace_iterator<vector_iterator<text::UnknownDataTypeContainer>>();
    context.emplace_iterator<string_iterator>();

    //Boolean logic
    context.emplace_function<typed_binary_operator_function<bool, bool>>("and", context.shared_from_this(), std::logical_and<bool>());
    context.emplace_function<typed_binary_operator_function<bool, bool>>("or", context.shared_from_this(), std::logical_or<bool>());
    context.emplace_function<typed_binary_operator_function<bool, bool>>("xor", context.shared_from_this(), std::not_equal_to<bool>());
    context.emplace_function<typed_unary_operator_function<bool, bool>>("not", context.shared_from_this(), std::logical_not<bool>());

    //Arithmetic
    auto add_func = converting_operator_function{context.shared_from_this()};
    add_func.emplace_impl<string_concatenator>();
    add_func.emplace_impl<numeric_adder>();
    context.emplace_function<converting_operator_function>("add", add_func);

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
}

} /* stl */
} /* SIPLUS_NAESPACE */
