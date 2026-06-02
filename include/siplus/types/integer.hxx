#pragma once
#include <cstdint>
#ifndef INCLUDE_TYPES_INTEGER_HXX_
#define INCLUDE_TYPES_INTEGER_HXX_

#include "siplus/config.h"
#include "siplus/data.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

struct SIPLUS_EXPORT IntegerType : public TypeInfo {
    using data_type = int64_t;

    virtual std::string name() const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};

} /* types */

SIPLUS_DEFINE_TYPE_INFO(char, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(short int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(long int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(long long int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned char, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned short int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned long int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned long long int, types::IntegerType);

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TYPES_INTEGER_HXX_
