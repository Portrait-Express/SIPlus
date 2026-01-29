#pragma once
#ifndef INCLUDE_TYPES_BOOL_H_
#define INCLUDE_TYPES_BOOL_H_

#include "siplus/config.h"
#include "siplus/data.h"

namespace SIPLUS_NAMESPACE {
namespace types {

struct BoolType : public TypeInfo {
    using data_type = bool;

    virtual std::string name() const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};

} /* types */

SIPLUS_DEFINE_TYPE_INFO(types::BoolType::data_type, types::BoolType);

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TYPES_BOOL_H_
