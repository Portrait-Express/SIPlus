#include <cassert>
#include <cfloat>
#include <iostream>
#include <string>
#include <tuple>

#include "siplus/context.h"
#include "siplus/parser.h"
#include "siplus/siplus.h"
#include "siplus/text/data.h"
#include "siplus/text/text.h"

template<typename _OStream, typename T>
_OStream& operator<<(_OStream& stream, std::function<T> func) {
    stream << "(function)";
    return stream;
}

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
            << SIPLUS_NAMESPACE::text::get_type_name(typeid(T)) << " cannot convert from " 
            << SIPLUS_NAMESPACE::text::get_type_name(typeid(To)) << " to " 
            << SIPLUS_NAMESPACE::text::get_type_name(container.type) << std::endl;
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
        std::cout << "Expected type " << SIPLUS_NAMESPACE::text::get_type_name(typeid(To)) 
            << ". Recieved " << SIPLUS_NAMESPACE::text::get_type_name(container.type) << std::endl;
        return 1;
    }
}

template<typename T, typename V, typename To> requires std::is_base_of_v<SIPlus::text::Converter, T>
int test_conversion(const V& val, const To& result) {
    T converter;
    return test_conversion<T, V, To>(converter, val, result);
}

template<typename T1, typename T2>
struct test_expression_compare {
    static bool compare(const T1& val, const T2& other) {
        return val == other;
    }
};

template<>
struct test_expression_compare<float, float> {
    static bool compare(const float& val, const float& other) {
        return nearly_equal(val, other);
    }
};

template<>
struct test_expression_compare<double, double> {
    static bool compare(const double& val, const double& other) {
        return nearly_equal(val, other);
    }
};

template<typename T>
struct test_expression_compare<T, std::function<bool (const T&)>> {
    static bool compare(const T& val, const std::function<bool (const T&)> test) {
        return test(val);
    }
};

template<>
struct test_expression_compare<std::vector<SIPlus::text::UnknownDataTypeContainer>, std::vector<std::string>> {
    static bool compare(
        const std::vector<SIPlus::text::UnknownDataTypeContainer>& val, 
        const std::vector<std::string>& other
    ) {
        std::vector<std::string> strVal{};
        strVal.reserve(val.size());

        for(auto& v : val) {
            if(!v.is<std::string>()) return false;
            strVal.push_back(v.as<std::string>());
        }

        return strVal == other;
    }
};

template<typename T>
struct test_expression_compare<std::vector<SIPlus::text::UnknownDataTypeContainer>, std::vector<T>> {
    static bool compare(
        const std::vector<SIPlus::text::UnknownDataTypeContainer>& val, 
        const std::vector<T>& other
    ) {
        if(val.size() != other.size()) return false;

        for(int i = 0; i < val.size(); i++) {
            if(!val[i].is<T>()) return false;
            if(val[i].as<T>() != other[i]) {
                return false;
            }
        }

        return true;
    }
};

template<typename T1, typename T2> 
bool compare(const T1& v1, const T2& v2) {
    return test_expression_compare<T1, T2>::compare(v1, v2);
}

template<typename T>
bool compare(const T& v1, const T& v2) {
    return compare<T, T>(v1, v2);
}

template<typename T, typename V, typename _ExpectedType = T>
int test_expression(
    const std::string& expression, 
    const SIPLUS_NAMESPACE::ParseOpts& opts,
    const V& data, 
    const T& expected
) {
    auto retriever = get_test_context().get_expression(expression, opts);

    std::shared_ptr<SIPLUS_NAMESPACE::InvocationContext> ctx;
    if constexpr (std::is_same_v<V, std::shared_ptr<SIPLUS_NAMESPACE::InvocationContext>>) {
        ctx = data;
    } else {
        ctx = get_test_context().context().builder()
            .use_default(SIPlus::text::make_data(data))
            .build();
    }

    auto result = retriever->retrieve(*ctx);

    if(!result.template is<_ExpectedType>()) {
        std::cout << "Expression \"" << expression << "\" failed: Expected type " 
            << SIPLUS_NAMESPACE::text::get_type_name(typeid(_ExpectedType)) << " recieved value of type " 
            << SIPLUS_NAMESPACE::text::get_type_name(result.type) << "." << std::endl;
        return 1;
    }

    if(!compare(result.template as<_ExpectedType>(), expected)) {
        std::cout 
            << "Expression \"" << expression << "\" failed: Expected " 
             << expected << " recieved value " 
            << result.template as<_ExpectedType>() << "." << std::endl;
        return 1;
    }

    return 0;
}

template<typename T, typename _ExpectedType = T>
int test_expression(const std::string& expression, const T& expected) {
    return test_expression<T, test_data, _ExpectedType>(expression, SIPLUS_NAMESPACE::ParseOpts{}, test_data{}, expected);
}

template<typename T, typename V, typename _ExpectedType = T>
int test_expression(
    const std::string& expression, 
    const V& data, 
    const T& expected
) {
    return test_expression<T, V, _ExpectedType>(expression, SIPLUS_NAMESPACE::ParseOpts{}, data, expected);
}

template<typename V>
int test_interpolation(
    const std::string& expression, 
    const SIPLUS_NAMESPACE::ParseOpts& opts,
    const V& data, 
    const std::string& expected
) {
    auto retriever = get_test_context().get_interpolation(expression, opts);

    std::shared_ptr<SIPlus::InvocationContext> invoCtx;
    if constexpr (std::is_same_v<V, std::shared_ptr<SIPlus::InvocationContext>>) {
        invoCtx = data;
    } else {
        invoCtx = get_test_context()
            .context()
            .builder()
            .use_default(SIPlus::text::make_data(data))
            .build();
    }

    auto result = retriever.construct_with(invoCtx);

    if(result != expected) {
        std::cout 
            << "Expression \"" << expression << "\" failed: Expected \"" 
            << expected << "\" " << " recieved value \"" << result << "\"." << std::endl;
        return 1;
    }

    return 0;
}

inline int test_interpolation(const std::string& expression, const std::string& expected) {
    return test_interpolation<test_data>(expression, SIPLUS_NAMESPACE::ParseOpts{}, test_data{}, expected);
}

inline int expect_throw(std::function<void ()> func) {
    try {
        func();
        std::cout << "Expected a test to throw. It did not." << std::endl;
        return 1;
    } catch(std::runtime_error e) {
        return 0;
    }
}
