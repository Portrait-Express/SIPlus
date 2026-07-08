#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_HXX_
#define INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_HXX_

#include <memory>
#include <string>

#include "siplus/config.h"
#include "siplus/invocation_context.hxx"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {
namespace text {

/**
 * @brief A ValueRetriever that accesses a property on a container.
 */
class SIPLUS_EXPORT AccessorValueRetriever : public ValueRetriever {
public:
    /**
     * @brief Make a new AccessorValueRetriever. Uses default_data() as the parent object.
     *
     * @param[in] accessor The ParserContext
     * @param[in] name The name of the property
     */
    AccessorValueRetriever(std::string name);

    /**
     * @brief Make a new AccessorValueRetriever with a dedicated parent.
     *
     * @param[in] accessor The ParserContext
     * @param[in] parent The Value retriever to read the property from.
     * @param[in] name The name of the property
     */
    AccessorValueRetriever(std::shared_ptr<ValueRetriever> parent, std::string name);

    UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<ValueRetriever> parent_;
    std::string name_;
};

    
} /* text */
}

#endif  // INCLUDE_SIPLUS_TEXT_ACCESSOR_RETRIEVER_HXX_
