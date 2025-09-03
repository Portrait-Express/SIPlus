#include <sstream>

#include "siplus/context.h"
#include "siplus/text/constructor.h"
#include "siplus/text/constructor_steps/literal_step.h"
#include "siplus/text/constructor_steps/repeated_constructor_step.h"
#include "siplus/text/constructor_steps/retriever_step.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/literal_retriever.h"
#include "siplus/text/value_retrievers/accessor_retriever.h"

#include "util.h"

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

RepeatedConstructorConstructorStep::RepeatedConstructorConstructorStep(
        std::shared_ptr<SIPlusParserContext> context,
        std::shared_ptr<ValueRetriever> retriever,
        text::TextConstructor sub
) : context_(context), retriever_(retriever), sub_(sub) { }

std::string RepeatedConstructorConstructorStep::getPart(const UnknownDataTypeContainer& val) {
    UnknownDataTypeContainer iterable = retriever_->retrieve(val);

    auto provider = context_->iterator(iterable);
    auto iterator = provider->iterator(iterable);

    bool more = iterator->more();
    std::stringstream ss;

    while(more) {
        iterator->next();

        more = iterator->more();

        if(more) {
            // "Last" handling will go here later
            // For now this will get optimized out
        }

        ss << sub_.construct_with(iterator->current());
    }

    return ss.str();
}

ValueRetrieverConstructorStep::ValueRetrieverConstructorStep(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<ValueRetriever> retriever
) : context_(context), retriever_(retriever) {}

std::string ValueRetrieverConstructorStep::getPart(const UnknownDataTypeContainer& part) {
    auto value = retriever_->retrieve(part);

    if(!value.is<std::string>()) {
        value = context_->convert<std::string>(value);
    }

    return value.as<std::string>();
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
