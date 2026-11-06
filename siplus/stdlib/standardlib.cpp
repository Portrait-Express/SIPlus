#include "siplus/context.hxx"
#include "siplus/stl/functions/dictionary.hxx"
#include "siplus/stl/functions/pair.hxx"
#include "siplus/util.hxx"
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

struct FindFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct FilterFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};


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

    //Dictionary functions
    context.emplace_function<DictionaryNewFunction>("dict_new");
    context.emplace_function<DictionaryHasFunc>    ("dict_has");
    context.emplace_function<DictionaryGetFunc>    ("dict_get");
    context.emplace_function<DictionarySetFunc>    ("dict_set");
    context.emplace_function<DictionaryRemoveFunc> ("dict_remove");
    context.emplace_function<DictionaryKeysFunc>   ("dict_keys");
    context.emplace_function<DictionaryValuesFunc> ("dict_values");

    //Pair functions
    context.emplace_function<PairFunction>("pair");

    //Iterator-related
    context.emplace_function<map_func>("map");
    context.emplace_function<length_func>("length");
    context.emplace_function<join_func>("join");
    context.emplace_function<contains_func>("contains");
    context.emplace_function<each_func>("each");
    context.emplace_function<all_func>("all");
    context.emplace_function<any_func>("any");
    context.emplace_function<sort_func>("sort");
    context.emplace_function<FindFunction>("find");
    context.emplace_function<FilterFunction>("filter");

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

struct FindFunctionImpl : ValueRetriever {
    FindFunctionImpl(
        std::shared_ptr<ValueRetriever> list,
        std::shared_ptr<ValueRetriever> test
    ) : list_(list), test_(test) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<ValueRetriever> list_;
    std::shared_ptr<ValueRetriever> test_;
};

UnknownDataTypeContainer FindFunctionImpl::retrieve(InvocationContext& value) const {
    auto list = list_->retrieve(value);
    auto iterator = list.iterate();

    while(iterator->more()) {
        iterator->next();

        auto val = iterator->current();
        auto scope = wrap_scope(value.shared_from_this())
            .use_default(val)
            .build();

        auto result = test_->retrieve(*scope);

        if(result.convert<types::BoolType>().as<types::BoolType>()) {
            return val;
        }
    }

    return UnknownDataTypeContainer{};
}

std::shared_ptr<ValueRetriever> 
FindFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [list, test] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<FindFunctionImpl>(list, test);
}



struct FilterFunctionImpl : ValueRetriever {
    FilterFunctionImpl(
        std::shared_ptr<ValueRetriever> list,
        std::shared_ptr<ValueRetriever> test
    ) : list_(list), test_(test) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override;

private:
    std::shared_ptr<ValueRetriever> list_;
    std::shared_ptr<ValueRetriever> test_;
};

UnknownDataTypeContainer FilterFunctionImpl::retrieve(InvocationContext& value) const {
    auto ret = make_data<types::ArrayType>(std::vector<UnknownDataTypeContainer>{});
    auto list = list_->retrieve(value);
    auto iterator = list.iterate();

    while(iterator->more()) {
        iterator->next();

        auto val = iterator->current();
        auto scope = wrap_scope(value.shared_from_this())
            .use_default(val)
            .build();

        auto result = test_->retrieve(*scope);

        if(result.convert<types::BoolType>().as<types::BoolType>()) {
            ret.as<types::ArrayType>().emplace_back(val);
        }
    }

    return ret;
}

std::shared_ptr<ValueRetriever> FilterFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    auto [list, test] = util::get_parameters_first_parent<2>(parent, parameters);
    return std::make_shared<FilterFunctionImpl>(list, test);
}
