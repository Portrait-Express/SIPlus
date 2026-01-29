#pragma once
#ifndef INCLUDE_TYPES_STRING_HXX_
#define INCLUDE_TYPES_STRING_HXX_

#include "siplus/config.hxx"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

struct StringType : public TypeInfo {
    using data_type = std::string;

    virtual std::string name() const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;

    virtual std::unique_ptr<text::Iterator> iterate(const UnknownDataTypeContainer& data) const override;
};

} /* types */

SIPLUS_DEFINE_TYPE_INFO(char*, types::StringType);
SIPLUS_DEFINE_TYPE_INFO(types::StringType::data_type, types::StringType);

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TYPES_STRING_HXX_
