#pragma once
#ifndef INCLUDE_FUNCTIONS_DICTIONARY_HXX_
#define INCLUDE_FUNCTIONS_DICTIONARY_HXX_

#include "siplus/config.h"
#include "siplus/context.hxx"

#include <unordered_map>

namespace SIPLUS_NAMESPACE {
namespace stl {

struct SIPLUS_EXPORT DictionaryType : public TypeInfo {
    using data_type = std::unordered_map<UnknownDataTypeContainer, UnknownDataTypeContainer>;
    static const TypeInfoDescriptor *const descriptor;

    DictionaryType();

    virtual UnknownDataTypeContainer index(
        std::shared_ptr<SIPlusParserContext> context, 
        UnknownDataTypeContainer &value, 
        UnknownDataTypeContainer &index
    ) const override;

    virtual bool is_iterable(const UnknownDataTypeContainer &data) const override;

    virtual std::unique_ptr<Iterator> iterate(const UnknownDataTypeContainer& data) const override;
};

struct SIPLUS_EXPORT DictionaryNewFunction : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT DictionaryHasFunc : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT DictionarySetFunc : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT DictionaryGetFunc : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT DictionaryRemoveFunc : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT DictionaryValuesFunc : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT DictionaryKeysFunc : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT ToDictFunc : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

struct SIPLUS_EXPORT GroupFunc : Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

} /* stl */

SIPLUS_DEFINE_TYPE_INFO(stl::DictionaryType::data_type, stl::DictionaryType);

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_FUNCTIONS_DICTIONARY_HXX_
