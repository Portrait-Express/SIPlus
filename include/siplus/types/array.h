#pragma once
#include <vector>
#ifndef INCLUDE_TYPES_ARRAY_H_
#define INCLUDE_TYPES_ARRAY_H_

#include "siplus/config.h"
#include "siplus/data.h"

namespace SIPLUS_NAMESPACE {
namespace types {

struct ArrayType : public TypeInfo {
    using data_type = std::vector<UnknownDataTypeContainer>;

    virtual std::string name() const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;

    virtual std::unique_ptr<text::Iterator> iterate(const UnknownDataTypeContainer& data) const override;
};

} /* types */

SIPLUS_DEFINE_TYPE_INFO(types::ArrayType::data_type, types::ArrayType);

template<typename T>
UnknownDataTypeContainer make_data(const std::vector<T>& vec) {
    std::vector<UnknownDataTypeContainer> array;
    array.reserve(vec.size());

    for(auto it = vec.begin(); it != vec.end(); it++) {
        array.push_back(make_data(*it));
    }

    return make_data<types::ArrayType>(array);
}

} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_TYPES_ARRAY_H_
