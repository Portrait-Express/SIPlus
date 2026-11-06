#pragma once
#ifndef INCLUDE_FUNCTIONS_PAIR_HXX_
#define INCLUDE_FUNCTIONS_PAIR_HXX_

#include "siplus/context.hxx"

namespace SIPLUS_NAMESPACE {
namespace stl {

/**
 * @brief This is the type returned by dict_entries.
 *
 * Extensions:
 * - Converter[string]
 * - Equatable
 */
struct SIPLUS_EXPORT PairType : public TypeInfo {
    using mc_pair_type = std::pair<UnknownDataTypeContainer, const UnknownDataTypeContainer>;
    using cm_pair_type = std::pair<const UnknownDataTypeContainer, UnknownDataTypeContainer>;
    using mm_pair_type = std::pair<UnknownDataTypeContainer, UnknownDataTypeContainer>;

    using data_type = std::pair<const UnknownDataTypeContainer, const UnknownDataTypeContainer>;
    static const TypeInfoDescriptor *const descriptor;

    PairType();

    UnknownDataTypeContainer access(
        const UnknownDataTypeContainer &data, 
        const std::string &name
    ) const override;
};

struct PairFunction : Function {
    virtual std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, 
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;
};

} /* stl */

SIPLUS_DEFINE_TYPE_INFO(stl::PairType::data_type, stl::PairType);
SIPLUS_DEFINE_TYPE_INFO(stl::PairType::mc_pair_type, stl::PairType);
SIPLUS_DEFINE_TYPE_INFO(stl::PairType::cm_pair_type, stl::PairType);
SIPLUS_DEFINE_TYPE_INFO(stl::PairType::mm_pair_type, stl::PairType);

/**
 * @brief Special overload for creating PairType data.
 *
 * @param[in] pair pair value
 * @return PairType data container
 */
template<typename P1, typename P2>
UnknownDataTypeContainer make_data(const std::pair<P1, P2>& pair) {
    return make_data<stl::PairType>(new stl::PairType::data_type{
        make_data(pair.first),
        make_data(pair.second)
    });
}


} /* SIPLUS_NAMESPACE */

#endif  // INCLUDE_FUNCTIONS_PAIR_HXX_

