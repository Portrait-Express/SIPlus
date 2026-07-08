#pragma once
#ifndef INCLUDE_RETRIEVERS_VARIABLE_ASSIGNMENT_RETRIEVER_HXX_
#define INCLUDE_RETRIEVERS_VARIABLE_ASSIGNMENT_RETRIEVER_HXX_

#include "siplus/build_context.hxx"
#include "siplus/config.h"
#include "siplus/text/value_retrievers/retriever.hxx"

#include <memory>

namespace SIPLUS_NAMESPACE {

struct variable_assignment_retriever : public text::ValueRetriever {
    variable_assignment_retriever (
        std::shared_ptr<VariableRetriever> variable,
        std::shared_ptr<text::ValueRetriever> value
    ) : variable_(variable), value_(value) {}
    
    UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

private:
    std::shared_ptr<VariableRetriever> variable_;
    std::shared_ptr<text::ValueRetriever> value_;
};

}

#endif  // INCLUDE_RETRIEVERS_VARIABLE_ASSIGNMENT_RETRIEVER_HXX_
