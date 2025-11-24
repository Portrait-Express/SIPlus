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
int test_conversion(const T& converter, const V& val, const To& result) {
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

template<typename T, typename V, typename To> requires std::is_base_of_v<SIPlus::text::Converter, T>
int test_conversion(const V& val, const To& result) {
    T converter;
    return test_conversion<T, V, To>(converter, val, result);
}

template<typename T>
struct test_expression_compare {
    static bool compare(const T& val, const T& other) {
        return val == other;
    }
};

template<>
struct test_expression_compare<float> {
    static bool compare(const float& val, const float& other) {
        return nearly_equal(val, other);
    }
};

template<>
struct test_expression_compare<double> {
    static bool compare(const double& val, const double& other) {
        return nearly_equal(val, other);
    }
};

inline std::string get_value_str(SIPLUS_NAMESPACE::text::UnknownDataTypeContainer val) {
    if(val.is<double>()) {
        return to_string(val.as<double>());
    } else if(val.is<float>()) {
        return to_string(val.as<float>());
    } else if(val.is<std::string>()) {
        return val.as<std::string>();
    } else {
        return "<unknown>";
    }
}

template<typename T>
int test_expression(const std::string& expression, const T& expected) {
    return test_expression(expression, test_data{}, expected);
}

template<typename T, typename V>
int test_expression(const std::string& expression, const V& data, const T& expected) {
    auto retriever = get_test_context().get_expression(expression);
    auto result = retriever->retrieve(SIPLUS_NAMESPACE::text::make_data(data));

    if(!result.template is<T>()) {
        std::cout << "Expression \"" << expression << "\" failed: Expected type " 
            << get_type_name(typeid(T)) << " recieved value of type " 
            << get_type_name(result.type) << "." << std::endl;
        return 1;
    }

    if(!test_expression_compare<T>::compare(result.template as<T>(), expected)) {
        std::cout 
            << "Expression \"" << expression << "\" failed: Expected " 
            << get_type_name(typeid(T)) << " " << to_string(expected) 
            << " recieved value " 
            << get_type_name(result.type) << " " << get_value_str(result)
            << "." << std::endl;
        return 1;
    }

    return 0;
}

template<typename V>
int test_interpolation(const std::string& expression, const V& data, const std::string& expected) {
    auto retriever = get_test_context().get_interpolation(expression);
    auto result = retriever.construct_with(SIPLUS_NAMESPACE::text::make_data(data));

    if(result != expected) {
        std::cout 
            << "Expression \"" << expression << "\" failed: Expected \"" 
            << expected << "\" " << " recieved value \"" << result << "\"." << std::endl;
        return 1;
    }

    return 0;
}

inline int test_interpolation(const std::string& expression, const std::string& expected) {
    return test_interpolation<test_data>(expression, test_data{}, expected);
}
