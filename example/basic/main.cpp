#include "siplus/text/data.h"
#include <iostream>
#include <ostream>

#include "../common.hxx"

using namespace SIPlus;

int main(int, char**) {
    Person person;
    person.first_name = "John";

    //Create parser
    Parser p;
    ParseOpts opts;

    //Set up parser.
    p.context().use_stl(); // This call is necessary to include the STL functions and converters
                           // use_stl() will not be present if SIPLUS_INCLUDE_STDLIB is not defined
    p.context().emplace_accessor<PersonAccessor>(/* constructor arguments */); 

    auto constructor = p.get_interpolation("Hello, { .first_name }", opts);
    auto retriever = p.get_expression(".first_name", opts);

    //Build the data to invoke templates with
    auto data = p.context()
        .builder()
        .use_default(text::make_data(person))
        .build();

    //get_interpolation
    auto constructed = constructor.construct_with(data);
    std::cout << "TextConstructor: " << constructed << std::endl;

    //get_expression
    auto retrieved = retriever->retrieve(*data);
    if(retrieved.is<std::string>()) {
        std::cout << "ValueRetriever: " << retrieved.as<std::string>() << std::endl;
    } else {
        std::cerr << "This shouldnt happen for this example, but outputs can be anything." << std::endl;
    }
}
