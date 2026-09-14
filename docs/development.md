## Writing a custom function 
You can add a new custom function in code by implementing a `Function`, and providing it to `context.emplace_function`.
Below is an example of a simple function that just returns the value of the first parameter.
```cpp
#include <siplus/siplus.hxx>

using namespace SIPlus;

struct TestImpl : public ValueRetriever {
    TestImpl(std::shared_ptr<ValueRetriever> nested) : nested_(nested) {}

    UnknownDataTypeContainer retrieve(InvocationContext& ctx) const override {
        return nested_->retrieve(ctx);
    }

private:
    std::shared_ptr<text::ValueRetriever> nested_;
};

struct TestFunc : public Function {
    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent, // "parent" is the piped value if it was provided
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override {
        /**
         * get_parameters_first_parent() is a utility function provided, that returns a 
         * number of parameters, using the parent as the first parameter if it was specififed.
         * It returns a tuple of the size the template parameter specifies, of parameters.
         * You can provide a second template argument to provide a maximum number of additional 
         * optional parameters
         */
        auto [ input ] = util::get_parameters_first_parent<1>(parent, parameters);

        //Instead of above you could do ********
        std::shared_ptr<ValueRetriever> input;
        if(parent) {
            input = parent;
        } else {
            if(parameters.size() != 1) {
                throw std::runtime_error{"not enough parameters for 'test'"};
            }
            input = parameters[1];
        }
        //**************************************

        return std::make_shared<TestImpl>(input);
    }
};

int main() {
    Parser p;
    p.context().emplace_function<TestFunc>();
}
```

We break functions into two steps so that we can do parameter validation at time of parsing the expression. This allows
execution to be (slightly) faster since we dont have to do redundant parameter count checks at invocation. 


## Making a new TypeInfo
```cpp
// MyType.hxx
#include <siplus/context.hxx>

struct MyType {
    std::string foo;
};

struct MyTypeInfo : public SIPlus::TypeInfo {
    using data_type = MyType;
    static const SIPlus::TypeInfoDescriptor *const descriptor;

    MyTypeInfo();

    virtual SIPlus::UnknownDataTypeContainer access(const SIPlus::UnknownDataTypeContainer& data, const std::string& name) const;
};

namespace ::SIPlus {
SIPLUS_DEFINE_TYPE_INFO(MyType, MyTypeInfo);
}

// MyType.cpp
#include "MyType.hxx"

using namespace SIPlus;

namespace {

// Implementation to convert to a string.
struct MyTypeStringConverter : UnaryOperatorTypeExtensionImpl {
    MyTypeStringConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<types::StringType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer& thisValue) {
        return make_data(thisValue.as<MyTypeInfo>().foo);
    }
};

}

//The descriptor is your type's identifier. This is used globally, so do not delete
// the descriptor. Let it leak, because it should only be allocated once.
const TypeInfoDescriptor *const MyTypeInfo::descriptor = new TypeInfoDescriptor("MyType");

MyTypeInfo::MyTypeInfo() : TypeInfo(descriptor) {
    // Add the extension.
    add_extension(new MyTypeStringConverter()); // This object will be deleted along with the TypeInfo
}

UnknownDataTypeContainer MyTypeInfo::access(const UnknownDataTypeContainer& data, const std::string& name) const {
    auto& value = data.as<MyTypeInfo>();

    if(name == "foo") {
        return make_data(value.foo);
    }

    throw std::runtime_error{"Cannot access '" + name "' on MyType"};
}
```
