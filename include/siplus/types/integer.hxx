#pragma once
#ifndef INCLUDE_TYPES_INTEGER_HXX_
#define INCLUDE_TYPES_INTEGER_HXX_

#include "siplus/config.h"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

struct IntegerType : public TypeInfo {
    using data_type = long;

    virtual std::string name() const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};

} /* types */

SIPLUS_DEFINE_TYPE_INFO(char, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(short, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(types::IntegerType::data_type, types::IntegerType);

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TYPES_INTEGER_HXX_
