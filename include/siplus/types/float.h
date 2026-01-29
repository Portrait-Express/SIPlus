#pragma once
#include "siplus/data.h"
#ifndef INCLUDE_TYPES_FLOAT_H_
#define INCLUDE_TYPES_FLOAT_H_

#include "siplus/config.h"

namespace SIPLUS_NAMESPACE {
namespace types {

struct FloatType : public TypeInfo {
    using data_type = double;

    virtual std::string name() const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};

} /* types */

SIPLUS_DEFINE_TYPE_INFO(float, types::FloatType);
SIPLUS_DEFINE_TYPE_INFO(types::FloatType::data_type, types::FloatType);

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TYPES_FLOAT_H_
