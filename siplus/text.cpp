#include <sstream>

#include "siplus/context.h"
#include "siplus/invocation_context.h"
#include "siplus/text/constructor.h"
#include "siplus/text/constructor_steps/literal_step.h"
#include "siplus/text/constructor_steps/repeated_constructor_step.h"
#include "siplus/text/constructor_steps/retriever_step.h"
#include "siplus/data.h"
#include "siplus/text/value_retrievers/literal_retriever.h"
#include "siplus/text/value_retrievers/accessor_retriever.h"
#include "siplus/types/string.h"

namespace SIPLUS_NAMESPACE {
namespace text {

void TextConstructor::addStep(std::shared_ptr<TextConstructorStep> step) {
    steps_.push_back(step);
}

std::string TextConstructor::construct_with(std::shared_ptr<InvocationContext> data) {
    data = wrap_scope(data).build(); //Wrap as to not alter passed data

    std::stringstream ss;

    for(auto& step : steps_) {
        ss << (*step).getPart(*data);
    }

    return ss.str();
}

LiteralConstructorStep::LiteralConstructorStep(std::string val) : part_(val) {}

std::string LiteralConstructorStep::getPart(InvocationContext&) {
    return part_;
}

RepeatedConstructorConstructorStep::RepeatedConstructorConstructorStep(
        std::shared_ptr<SIPlusParserContext> context,
        std::shared_ptr<ValueRetriever> retriever,
        text::TextConstructor sub
) : context_(context), retriever_(retriever), sub_(sub) { }

std::string RepeatedConstructorConstructorStep::getPart(InvocationContext& val) {
    UnknownDataTypeContainer iterable = retriever_->retrieve(val);

    auto iterator = iterable.iterate();

    bool more = iterator->more();
    std::stringstream ss;

    while(more) {
        iterator->next();

        more = iterator->more();

        if(!more) {
            // "Last" handling will go here later
            // For now this will get optimized out
        }
        
        auto scope = wrap_scope(val.shared_from_this()).use_default(iterator->current()).build();
        ss << sub_.construct_with(scope);
    }

    return ss.str();
}

ValueRetrieverConstructorStep::ValueRetrieverConstructorStep(
    std::shared_ptr<SIPlusParserContext> context, 
    std::shared_ptr<ValueRetriever> retriever
) : context_(context), retriever_(retriever) {}

std::string ValueRetrieverConstructorStep::getPart(InvocationContext& part) {
    auto value = retriever_->retrieve(part);

    if(!value.is<types::StringType>()) {
        value = context_->convert<types::StringType>(value);
    }

    return value.as<types::StringType>();
}

LiteralValueRetriever::LiteralValueRetriever(UnknownDataTypeContainer value) : value_(value) {}

UnknownDataTypeContainer LiteralValueRetriever::retrieve(InvocationContext& value) const {
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

UnknownDataTypeContainer AccessorValueRetriever::retrieve(InvocationContext& value) const {
    if(parent_) {
        return parent_->retrieve(value).access(name_);
    } else {
        return value.default_data().access(name_);
    }
}

}
}
