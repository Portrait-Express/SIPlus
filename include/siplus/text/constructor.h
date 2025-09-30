#ifndef INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_H_
#define INCLUDE_SIPLUS_TEXT_CONSTRUCTOR_H_

#include <memory>
#include <string>
#include <vector>

#include "siplus/config.h"
#include "siplus/text/constructor_steps/constructor_step.h"
#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {
namespace text {

class TextConstructor {
public:
    void addStep(std::shared_ptr<TextConstructorStep>);

    template<typename T>
    std::string construct(const T&& value) {
        return construct_with(make_data<const T&&>(value));
    }

    std::string construct_with(UnknownDataTypeContainer data);
private:

    std::vector<std::shared_ptr<TextConstructorStep>> steps_;
};

}
}

#endif  // INCLUDE_TEXT_CONSTRUCTOR_H_
