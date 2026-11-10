#include "siplus/context.hxx"
#include "siplus/stl/functions/dictionary.hxx"
#include "siplus/range_iterator.hxx"
#include "siplus/util.hxx"

// Do not remove otherwise make_data in range_iterator cannot find type_info_for
// for the pair result from the unordered_map::const_iterator.
#include "siplus/stl/functions/pair.hxx" 

#include "../util.hxx"

using namespace SIPLUS_NAMESPACE;

namespace SIPLUS_NAMESPACE {
namespace stl {

namespace {

struct DictionaryStringConverter : UnaryOperatorTypeExtensionImpl {
    DictionaryStringConverter() : UnaryOperatorTypeExtensionImpl(
        make_conversion_descriptor<types::StringType>()
    ) {}

    UnknownDataTypeContainer invoke(
        const UnknownDataTypeContainer &thisValue
    ) const override {
        std::stringstream ss;
        auto iterator = thisValue.iterate();

        ss << "{ ";

        while(iterator->more()) {
            iterator->next();

            ss << iterator->current();

            if(iterator->more()) {
                ss << ", ";
            }
        }

        ss << " }";

        return make_data<types::StringType>(ss.str());
    }
};

struct DictionaryNewFunctionImpl : ValueRetriever {
    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        return make_data<DictionaryType>(new DictionaryType::data_type());
    }
};

struct DictionaryHasFuncImpl : ValueRetriever {
    DictionaryHasFuncImpl(
        std::shared_ptr<ValueRetriever> dict,
        std::shared_ptr<ValueRetriever> key
    ) : dict_(dict), key_(key) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto dict = dict_->retrieve(value);
        auto key = key_->retrieve(value);

        return make_data<types::BoolType>(dict.as<DictionaryType>().contains(key));
    }

private:
    std::shared_ptr<ValueRetriever> dict_;
    std::shared_ptr<ValueRetriever> key_;
};

struct DictionaryGetFuncImpl : ValueRetriever {
    DictionaryGetFuncImpl(
        std::shared_ptr<ValueRetriever> dict,
        std::shared_ptr<ValueRetriever> key
    ) : dict_(dict), key_(key) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto dict = dict_->retrieve(value);
        auto key = key_->retrieve(value);

        auto it = dict.as<DictionaryType>().find(key);
        if(it == dict.as<DictionaryType>().end()) {
            return UnknownDataTypeContainer{};
        }

        return it->second;
    }

private:
    std::shared_ptr<ValueRetriever> dict_;
    std::shared_ptr<ValueRetriever> key_;
};

struct DictionarySetFuncImpl : ValueRetriever {
    DictionarySetFuncImpl(
        std::shared_ptr<ValueRetriever> dict,
        std::shared_ptr<ValueRetriever> key,
        std::shared_ptr<ValueRetriever> value
    ) : dict_(dict), key_(key), value_(value) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto dict = dict_->retrieve(value);
        auto key = key_->retrieve(value);
        auto kValue = value_->retrieve(value);

        dict.as<DictionaryType>()[key] = kValue;

        return dict;
    }

private:
    std::shared_ptr<ValueRetriever> dict_;
    std::shared_ptr<ValueRetriever> key_;
    std::shared_ptr<ValueRetriever> value_;
};

struct DictionaryRemoveFuncImpl : ValueRetriever {
    DictionaryRemoveFuncImpl(
        std::shared_ptr<ValueRetriever> dict,
        std::shared_ptr<ValueRetriever> key
    ) : dict_(dict), key_(key) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto dict = dict_->retrieve(value);
        auto key = key_->retrieve(value);

        dict.as<DictionaryType>().erase(key);

        return dict;
    }

private:
    std::shared_ptr<ValueRetriever> dict_;
    std::shared_ptr<ValueRetriever> key_;
};

struct DictionaryValuesFuncImpl : ValueRetriever {
    DictionaryValuesFuncImpl(
        std::shared_ptr<ValueRetriever> dict
    ) : dict_(dict) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto dict = dict_->retrieve(value);
        auto list = new types::ArrayType::data_type{};
        list->reserve(dict.as<DictionaryType>().size());

        for(auto [_, v] : dict.as<DictionaryType>()) {
            list->emplace_back(v);
        }

        return make_data<types::ArrayType>(list);
    }

private:
    std::shared_ptr<ValueRetriever> dict_;
};

struct DictionaryKeysFuncImpl : ValueRetriever {
    DictionaryKeysFuncImpl(
        std::shared_ptr<ValueRetriever> dict
    ) : dict_(dict) {}

    UnknownDataTypeContainer retrieve(InvocationContext &value) const override {
        auto dict = dict_->retrieve(value);
        auto list = new types::ArrayType::data_type{};
        list->reserve(dict.as<DictionaryType>().size());

        for(auto [k, _] : dict.as<DictionaryType>()) {
            list->emplace_back(k);
        }

        return make_data<types::ArrayType>(list);
    }

private:
    std::shared_ptr<ValueRetriever> dict_;
};

} /* namespace anonymous */

const TypeInfoDescriptor *const DictionaryType::descriptor = new TypeInfoDescriptor("dict");

DictionaryType::DictionaryType() : TypeInfo(descriptor) {
    add_extension(new DictionaryStringConverter());
}

UnknownDataTypeContainer
DictionaryType::index(
    std::shared_ptr<SIPlusParserContext> context, 
    UnknownDataTypeContainer& thisValue,
    UnknownDataTypeContainer& key
) const {
    return thisValue.as<DictionaryType>()[key];
}

bool DictionaryType::is_iterable(const UnknownDataTypeContainer&) const {
    return true;
}

std::unique_ptr<Iterator> DictionaryType::iterate(const UnknownDataTypeContainer& data) const {
    return std::make_unique<range_iterator<DictionaryType::data_type::const_iterator>>(
        data.as<DictionaryType>().begin(), data.as<DictionaryType>().end()
    );
}

std::shared_ptr<ValueRetriever>
DictionaryNewFunction::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    return detail::make_retriever<DictionaryNewFunctionImpl>();
}

std::shared_ptr<ValueRetriever>
DictionaryHasFunc::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [dict, key] = util::get_parameters_first_parent<2>(parent, params);
    return detail::make_retriever<DictionaryHasFuncImpl>(dict, key);
}

std::shared_ptr<ValueRetriever>
DictionaryGetFunc::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [dict, key] = util::get_parameters_first_parent<2>(parent, params);
    return detail::make_retriever<DictionaryGetFuncImpl>(dict, key);
}

std::shared_ptr<ValueRetriever>
DictionarySetFunc::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [dict, key, value] = util::get_parameters_first_parent<3>(parent, params);
    return detail::make_retriever<DictionarySetFuncImpl>(dict, key, value);
}

std::shared_ptr<ValueRetriever>
DictionaryRemoveFunc::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [dict, key] = util::get_parameters_first_parent<2>(parent, params);
    return detail::make_retriever<DictionaryRemoveFuncImpl>(dict, key);
}

std::shared_ptr<ValueRetriever>
DictionaryKeysFunc::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [dict] = util::get_parameters_first_parent<1>(parent, params);
    return detail::make_retriever<DictionaryKeysFuncImpl>(dict);
}

std::shared_ptr<ValueRetriever>
DictionaryValuesFunc::value(
    std::shared_ptr<ValueRetriever> parent, 
    std::vector<std::shared_ptr<ValueRetriever>> params
) const {
    auto [dict] = util::get_parameters_first_parent<1>(parent, params);
    return detail::make_retriever<DictionaryValuesFuncImpl>(dict);
}

} /* namespace stl */
} /* namespace SIPLUS_NAMESPACE */
