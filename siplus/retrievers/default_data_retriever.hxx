#pragma once
#ifndef INCLUDE_RETRIEVERS_DEFAULT_DATA_RETRIEVER_HXX_
#define INCLUDE_RETRIEVERS_DEFAULT_DATA_RETRIEVER_HXX_

#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.hxx"

namespace SIPLUS_NAMESPACE {

struct default_data_retriever : public text::ValueRetriever {
    default_data_retriever() {}
    
    UnknownDataTypeContainer retrieve(InvocationContext& value) const override;
};

}

#endif  // INCLUDE_RETRIEVERS_DEFAULT_DATA_RETRIEVER_HXX_
