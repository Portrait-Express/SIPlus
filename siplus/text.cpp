#include <sstream>

#include "siplus/context.h"
#include "siplus/text/constructor.h"
#include "siplus/text/constructor_steps/literal_step.h"
#include "siplus/text/constructor_steps/nested_constructor_step.h"
#include "siplus/text/constructor_steps/retriever_step.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/literal_retriever.h"
#include "siplus/text/value_retrievers/accessor_retriever.h"

namespace SIPLUS_NAMESPACE {
namespace text {

void TextConstructor::addStep(std::shared_ptr<TextConstructorStep> step) {
    steps_.push_back(step);
}

std::string TextConstructor::construct_with(UnknownDataTypeContainer data) {
    std::stringstream ss;

    for(auto& step : steps_) {
        ss << (*step).getPart(data);
    }

    return ss.str();
}
LiteralConstructorStep::LiteralConstructorStep(std::string val) : part_(val) {}

std::string LiteralConstructorStep::getPart(const UnknownDataTypeContainer&) {
    return part_;
}

NestedConstructorConstructorStep::NestedConstructorConstructorStep(TextConstructor sub) : sub_(sub) { }

std::string NestedConstructorConstructorStep::getPart(const UnknownDataTypeContainer& val) {
    return sub_.construct_with(val);
}

ValueRetrieverConstructorStep::ValueRetrieverConstructorStep(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<ValueRetriever> retriever
) : context_(context), retriever_(retriever) {}

std::string ValueRetrieverConstructorStep::getPart(const UnknownDataTypeContainer& part) {
    auto& function = context_->function("[internal::str]");
    auto retriever = function.value(retriever_, std::vector<std::shared_ptr<text::ValueRetriever>>{});
    auto value = retriever->retrieve(part);

    if(value.type != typeid(std::string)) {
        throw std::runtime_error{"[internal::str] did not return a string"};
    }

    return *(std::string*)value.ptr;
}

LiteralValueRetriever::LiteralValueRetriever(UnknownDataTypeContainer value) : value_(value) {}

UnknownDataTypeContainer LiteralValueRetriever::retrieve(UnknownDataTypeContainer value) {
    return value_;
}

AccessorValueRetriever::AccessorValueRetriever(
    std::shared_ptr<SIPlusParserContext> context, 
    std::string name
) : context_(context), name_(name) {}

AccessorValueRetriever::AccessorValueRetriever(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<ValueRetriever> parent,  
    std::string name
) : context_(context), parent_(parent), name_(name) {}

UnknownDataTypeContainer AccessorValueRetriever::retrieve(UnknownDataTypeContainer value) {
    auto accessor = context_->accessor(value);

    if(parent_) {
        return accessor->access(parent_->retrieve(value), name_);
    } else {
        return accessor->access(value, name_);
    }
}


}
}
