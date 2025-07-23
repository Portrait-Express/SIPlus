#ifndef INCLUDE_SIPLUS_TEXT_CONTEXT_H_
#define INCLUDE_SIPLUS_TEXT_CONTEXT_H_

#include <memory>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "siplus/text/accessor.h"
#include "siplus/function.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {

class SIPlusParserContext : public std::enable_shared_from_this<SIPlusParserContext> {
public:
    SIPlusParserContext();

    void getAccessor();
    Function& function(const std::string& name);
    std::shared_ptr<text::Accessor> accessor(const text::UnknownDataTypeContainer& value);

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<Function, T>>>
    void emplace_function(std::string name, Ts&&... args) {
        T *ptr = new T{args...};
        std::unique_ptr<Function> unique{ptr};
        functions_[name] = std::move(unique);
    }

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<text::Accessor, T>>>
    void emplace_accessor(Ts&&... args) {
        accessors_.emplace_back(std::make_shared<T>(std::forward<Ts>(args)...));
    }


private:
    std::unordered_map<std::string, std::unique_ptr<Function>> functions_;
    std::vector<std::shared_ptr<text::Accessor>> accessors_;
};

}

#endif  // INCLUDE_SIPLUS_TEXT_CONTEXT_H_
