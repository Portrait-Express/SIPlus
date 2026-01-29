#pragma once
#ifndef INCLUDE_TYPES_STRING_H_
#define INCLUDE_TYPES_STRING_H_

#include "siplus/config.h"
#include "siplus/data.h"

namespace SIPLUS_NAMESPACE {
namespace types {

struct StringType : public TypeInfo {
    using data_type = std::string;

    virtual std::string name() const override;
    virtual bool is_iterable() const override;

    virtual std::unique_ptr<text::Iterator> iterate(void *data) const override;
};

} /* types */

SIPLUS_DEFINE_TYPE_INFO(char*, types::StringType);
SIPLUS_DEFINE_TYPE_INFO(types::StringType::data_type, types::StringType);

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TYPES_STRING_H_
