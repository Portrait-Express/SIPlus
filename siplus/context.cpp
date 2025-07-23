#include <format>
#include <functional>
#include <stdexcept>
#include <string>

#include "siplus/context.h"
#include "siplus/function.h"
#include "siplus/text/data.h"
#include "siplus/text/value_retrievers/retriever.h"

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


#ifdef __GNUG__
#include <cstdlib>
#include <cxxabi.h>
#endif

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

            std::string name{retrieved.type.name()};

#ifdef __GNUG__
            int status = -2;
            char *buf = __cxxabiv1::__cxa_demangle(name.c_str(), NULL, NULL, &status);
            if(status == 0) {
                name = buf;
            }
            std::free(buf);
#endif

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

std::shared_ptr<text::Accessor> SIPlusParserContext::accessor(const text::UnknownDataTypeContainer& value) {
    for(auto& accessor : accessors_) {
        if(accessor->can_access(value)) {
            return accessor;
        }
    }

    throw std::runtime_error{std::format("No accessor available able to handle {}", value.type.name())};
}

}
