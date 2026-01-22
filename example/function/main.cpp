#include <iostream>
#include <ostream>

#include "../common.hxx"

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

        text::UnknownDataTypeContainer retrieve(InvocationContext& value) const override {
            auto input = input_->retrieve(value);
            auto fieldName = context_->convert<std::string>(fieldName_->retrieve(value));

            return context_->accessor(input)->access(input, fieldName.as<std::string>());
        }

    private:
        std::shared_ptr<SIPlusParserContext> context_;
        std::shared_ptr<text::ValueRetriever> input_;
        std::shared_ptr<text::ValueRetriever> fieldName_;
    };
};

int main(int, char**) {
    Person person;
    person.first_name = "John";

    //Create parser
    Parser p;
    ParseOpts opts;

    //Set up parser.
    p.context().use_stl();
    p.context().emplace_accessor<PersonAccessor>(); 
    //Emplace our custom function
    p.context().emplace_function<access_func>("access", p.context().shared_from_this());

    auto constructor = p.get_interpolation("Hello, { . | access \"first_name\" }", opts);

    auto data = p.context()
        .builder()
        .use_default(text::make_data(person))
        .build();

    auto constructed = constructor.construct_with(data);
    std::cout << constructed << std::endl;
}
