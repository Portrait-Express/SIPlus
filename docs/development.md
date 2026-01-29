## Writing a custom function 
You can add a new custom function in code by implementing a `Function`, and providing it to `context.emplace_function`.
Below is an example of a simple function that just returns the value of the first parameter.
```cpp
#include <siplus/function.h>
#include <siplus/util.h>

using namespace SIPlus;

struct test_impl : public text::ValueRetriever {
    test_impl(std::shared_ptr<text::ValueRetriever> nested) : nested_(nested) {}

    text::UnknownDataTypeContainer retrieve(InvocationContext& ctx) const override {
        return nested_->retrieve(ctx);
    }

private:
    std::shared_ptr<text::ValueRetriever> nested_;
};

struct test_func : public Function {
    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, // "parent" is the piped value if it was provided
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
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
        std::shared_ptr<text::ValueRetriever> input;
        if(parent) {
            input = parent;
        } else {
            if(parameters.size() != 1) {
                throw std::runtime_error{"not enough parameters for 'test'"};
            }
            input = parameters[1];
        }
        //**************************************

        return std::make_shared<test_impl>(input);
    }
};

int main() {
    Parser p;
    p.context().emplace_function<test_func>();
}
```

We break functions into two steps so that we can do parameter validation at time of parsing the expression. This allows
execution to be (slightly) faster since we dont have to do redundant parameter count checks at invocation. 

This does mean adding variadic arguments later if wanted will be non-trivial.

