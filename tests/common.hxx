#include <cassert>
#include <cfloat>
#include <iostream>

#include "siplus/parser.h"
#include "siplus/util.h"

struct User {
    int id;
    std::string username;
    std::string email;
    bool can_login;
};

struct test_data {
    std::vector<User> users = {
        User{1, "root", "root@example.com", false},
        User{2, "Admin", "admin@example.com", true}
    };

    int x = 2;

    struct y {
        short b = 1;
    } y;
};

SIPlus::Parser& get_test_context();
int test(std::string name, std::function<int(const SIPlus::Parser&)> test_impl);
int group(std::string name, std::function<int(const SIPlus::Parser&)> test_impl);
int group(std::string name, std::function<int()> test_impl);

template<typename... TestResults>
int tests(TestResults... results) {
    return (results || ...);
}

//https://stackoverflow.com/a/32334103/10844545
bool nearly_equal(float a, float b, float epsilon = 128 * FLT_EPSILON, float abs_th = FLT_MIN);
bool nearly_equal(double a, double b, double epsilon = 128 * DBL_EPSILON, double abs_th = DBL_MIN);

template<typename T>
bool conversion_equal(T first, T second) {
    return first == second;
}

template<>
bool conversion_equal<double>(double first, double second);

template<typename T, typename V, typename To> requires std::is_base_of_v<SIPlus::text::Converter, T>
int test_conversion(V&& val, To&& result) {
    T converter;
    SIPlus::text::UnknownDataTypeContainer container;

    if(converter.can_convert(typeid(V), typeid(To))) {
        container = converter.convert(SIPlus::text::make_data(val), typeid(To));
    } else {
        std::cout 
            << get_type_name(typeid(T)) << " cannot convert from " 
            << get_type_name(typeid(To)) << " to " 
            << get_type_name(container.type) << std::endl;
        return 1;
    }

    if(container.is<To>()) {
        if(conversion_equal<To>(container.as<To>(), result)) {
            return 0;
        } else {
            std::cout << "Expected value " << result
                << ". Recieved value " << container.as<To>() << std::endl;
            return 1;
        }
    } else {
        std::cout << "Expected type " << get_type_name(typeid(To)) 
            << ". Recieved " << get_type_name(container.type) << std::endl;
        return 1;
    }
}

template<typename T>
int test_expression(std::string expression, T value) {
    auto retriever = get_test_context().get_expression(expression);
    auto result = retriever->retrieve(SIPlus::text::make_data(test_data()));

    if(!result.template is<T>()) return 1;
    if(result.template as<T>() != value) return 1;

    return 0;
}
