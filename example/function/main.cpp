#include <iostream>
#include <ostream>

#include "../common.hxx"
#include "siplus/types/string.hxx"

using namespace SIPLUS_NAMESPACE;

struct access_func : Function {
    access_func(std::shared_ptr<SIPlusParserContext> context) : context_(context) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent, 
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override {
        auto [ input, fieldName ] = util::get_parameters_first_parent<2>(parent ,parameters);
        return std::make_shared<impl>(context_.lock(), input, fieldName);
    }

private:
    /**
     * If your function need to store the context, use a weak_ptr. If you use 
     * a normal shared_ptr, the context ends up storing a shared_ptr to itself 
     * through this function object causing a reference loop and it will never 
     * be destroyed.
     */
    std::weak_ptr<SIPlusParserContext> context_;

    struct impl : text::ValueRetriever {
        impl(
            std::shared_ptr<SIPlusParserContext> context,
            std::shared_ptr<text::ValueRetriever> input,
            std::shared_ptr<text::ValueRetriever> fieldName
        ) : context_(context), input_(input), fieldName_(fieldName) {}

        UnknownDataTypeContainer retrieve(InvocationContext& value) const override {
            //Get input value
            auto input = input_->retrieve(value);

            //Get the field name parameter
            auto fieldName = context_->convert<types::StringType>(fieldName_->retrieve(value));

            //Access the field on the object.
            return input.access(fieldName.as<types::StringType>());
        }

    private:
        std::shared_ptr<SIPlusParserContext> context_;
        std::shared_ptr<text::ValueRetriever> input_;
        std::shared_ptr<text::ValueRetriever> fieldName_;
    };
};

int main(int, char**) {
    std::string templateText = "Hello, { . | access \"first_name\" }";
    User person{2, "John"};

    //Create parser
    Parser p;
    ParseOpts opts;

    //Set up parser.
    p.context().use_stl();
    
    //Emplace our custom function
    p.context().emplace_function<access_func>("access", p.context().shared_from_this());

    auto constructor = p.get_interpolation(templateText);

    auto data = p.context()
        .builder()
        .use_default(make_data(person))
        .build();

    auto constructed = constructor.construct_with(data);
    std::cout 
        << "Template: " << templateText << '\n'
        << "Result:   " << constructed << std::endl;

    return 0;
}
