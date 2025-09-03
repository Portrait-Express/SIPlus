#include <format>
#include <functional>
#include <stdexcept>
#include <string>

#include "siplus/stl.h"
#include "siplus/context.h"
#include "siplus/function.h"
#include "siplus/stl/functions/add.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"

#include "util.h"

namespace SIPLUS_NAMESPACE {

namespace {

using cbtype = std::function<text::UnknownDataTypeContainer (const text::UnknownDataTypeContainer&)>;

template<typename T>
constexpr std::optional<text::UnknownDataTypeContainer> ift(
    const text::UnknownDataTypeContainer& value, 
    cbtype cb)  {

    if(value.type == typeid(T)) {
        return cb(value);
    }

    return std::nullopt;
}

class internal_tostring : public Function {
public:
    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters) override {

        if(parent) {
            return std::make_shared<retriever>(parent);
        }

        if(parameters.size() == 1) {
            return std::make_shared<retriever>(parameters[0]);
        } else {
            throw std::runtime_error{"One parameter expected for [internal::str]"};
        }
    }

private:
    struct retriever : public text::ValueRetriever {
        retriever(std::shared_ptr<text::ValueRetriever> parent) : parent(parent) {};

        std::shared_ptr<text::ValueRetriever> parent;

        text::UnknownDataTypeContainer retrieve(text::UnknownDataTypeContainer value) override {
            auto retrieved = parent->retrieve(value);

            if(retrieved.is<std::string>()) {
                return retrieved;
            }

            if(retrieved.is<int>()) {
                return text::make_data(std::to_string(retrieved.as<int>()));
            }

            auto name = get_type_name(retrieved.type);

            throw std::runtime_error{"No known method to convert type " + name + " to a string"};
        }
    };
};

} /* anonymous */


SIPlusParserContext::SIPlusParserContext() {
    emplace_function<internal_tostring>("[internal::str]");
}

Function& SIPlusParserContext::function(const std::string& name) {
    auto it = functions_.find(name);

    if(it == functions_.end()) {
        throw std::runtime_error{std::format("Function '{}' not found.", name)};
    }

    return *it->second;
}

std::shared_ptr<text::Accessor> 
SIPlusParserContext::accessor(const text::UnknownDataTypeContainer& value) {
    auto it = accessors_cache_.find(value.type);
    if(it != accessors_cache_.end()) {
        return it->second;
    }

    for(auto& accessor : accessors_) {
        if(accessor->can_access(value)) {
            accessors_cache_[value.type] = accessor;
            return accessor;
        }
    }

    throw std::runtime_error{std::format("No accessor available able to handle {}", value.type.name())};
}


std::shared_ptr<text::IteratorProvider> 
SIPlusParserContext::iterator(const text::UnknownDataTypeContainer& value) {
    auto it = iterators_cache_.find(value.type);
    if(it != iterators_cache_.end()) {
        return it->second;
    }

    for(auto& iterator : iterators_) {
        if(iterator->can_iterate(value)) {
            iterators_cache_[value.type] = iterator;
            return iterator;
        }
    }

    throw std::runtime_error{std::format(
        "No iterator provider available able to iterate {}", 
        get_type_name(value.type))};
}


std::shared_ptr<text::Converter> 
SIPlusParserContext::converter(std::type_index from, std::type_index to) {
    auto fromIt = converters_cache_.find(from);

    if(fromIt != converters_cache_.end()) {
        auto toIt = fromIt->second.find(to);

        if(toIt != fromIt->second.end()) {
            return toIt->second;
        }
    }

    for(auto& converter : converters_) {
        if(converter->can_convert(from, to)) {
            converters_cache_[from][to] = converter;
            return converter;
        }
    }

    throw std::runtime_error{std::format(
        "No converter available to convert from {} to {}",
        get_type_name(from), get_type_name(to))};
}

void
SIPlusParserContext::use_stl() {
    stl::attach_stl(*this);
}

}
