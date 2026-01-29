#include <algorithm>
#include <cassert>
#include <cfloat>
#include <iostream>
#include <string>
#include <vector>

#include "siplus/siplus.h"

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

struct test_data_type : SIPLUS_NAMESPACE::TypeInfo {
    using data_type = test_data;
    std::string name() const override { return "test_data"; }
    bool is_iterable(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& data) const override { return false; }

    SIPLUS_NAMESPACE::UnknownDataTypeContainer 
    access(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& ptr, const std::string& name) const override;
};

struct test_data_y_type : SIPLUS_NAMESPACE::TypeInfo {
    using data_type = struct test_data::y;
    std::string name() const override { return "test_data::y"; }
    bool is_iterable(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& data) const override { return false; }

    SIPLUS_NAMESPACE::UnknownDataTypeContainer 
    access(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& ptr, const std::string& name) const override;
};

struct user_type : SIPLUS_NAMESPACE::TypeInfo {
    using data_type = User;
    std::string name() const override { return "user"; }
    bool is_iterable(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& data) const override { return false; }

    SIPLUS_NAMESPACE::UnknownDataTypeContainer 
    access(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& ptr, const std::string& name) const override;
};

namespace SIPLUS_NAMESPACE {
SIPLUS_DEFINE_TYPE_INFO(test_data, test_data_type);
SIPLUS_DEFINE_TYPE_INFO(struct test_data::y, test_data_y_type);
SIPLUS_DEFINE_TYPE_INFO(User, user_type);
}

SIPLUS_NAMESPACE::Parser& get_test_context();
int test(std::string name, std::function<int(const SIPLUS_NAMESPACE::Parser&)> test_impl);
int group(std::string name, std::function<int(const SIPLUS_NAMESPACE::Parser&)> test_impl);
int group(std::string name, std::function<int()> test_impl);

template<typename... TestResults>
int tests(TestResults... results) {
    return (results || ...);
}

//https://stackoverflow.com/a/32334103/10844545
bool nearly_equal(float a, float b, float epsilon = 128 * FLT_EPSILON, float abs_th = FLT_MIN);
bool nearly_equal(double a, double b, double epsilon = 128 * DBL_EPSILON, double abs_th = DBL_MIN);

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

template<typename T, typename Inner>
concept callable_1 = requires(T f, const Inner& v) {
    { f(v) } -> std::same_as<bool>;
};

template<typename T, callable_1<T> F>
struct test_expression_compare<T, F> {
    static bool compare(const T& val, const F& test) {
        return test(val);
    }
};

template<>
struct test_expression_compare<std::vector<SIPLUS_NAMESPACE::UnknownDataTypeContainer>, std::vector<std::string>> {
    static bool compare(
        const std::vector<SIPLUS_NAMESPACE::UnknownDataTypeContainer>& val, 
        const std::vector<std::string>& other
    ) {
        std::vector<std::string> strVal{};
        strVal.reserve(val.size());

        for(auto& v : val) {
            if(!v.is<SIPlus::types::StringType>()) return false;
            strVal.push_back(v.as<SIPlus::types::StringType>());
        }

        return strVal == other;
    }
};

template<typename T>
struct test_expression_compare<std::vector<SIPLUS_NAMESPACE::UnknownDataTypeContainer>, std::vector<T>> {
    static bool compare(
        const std::vector<SIPLUS_NAMESPACE::UnknownDataTypeContainer>& val, 
        const std::vector<T>& other
    ) {
        if(val.size() != other.size()) return false;

        using type_info = SIPLUS_NAMESPACE::type_info_for_t<T>;

        for(int i = 0; i < val.size(); i++) {
            if(!val[i].is<type_info>()) return false;
            if(val[i].as<type_info>() != other[i]) {
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

template<
    SIPLUS_NAMESPACE::simple_value_retrievable_type _ExpectedType, 
    typename _ExpectedVal = _ExpectedType::data_type
>
bool expect_equal(
    const SIPLUS_NAMESPACE::UnknownDataTypeContainer container, const _ExpectedVal& expected
) {
    if(!container.template is<_ExpectedType>()) {
        throw std::runtime_error{SIPLUS_NAMESPACE::util::to_string(
            "Expected type ", 
            _ExpectedType{}.name(),
            " recieved value of type ",
            container.type->name(), "."
        )};
    }

    if(!compare(container.template as<_ExpectedType>(), expected)) {
        throw std::runtime_error{SIPLUS_NAMESPACE::util::to_string(
            "Expected ", expected, " recieved value ", 
            container.template as<_ExpectedType>(), "."
        )};
    }

    return true;
}

template<
    SIPLUS_NAMESPACE::simple_value_retrievable_type _ExpectedType,
    typename T = _ExpectedType::data_type
>
int test_expression(
    const std::string& expression, 
    SIPLUS_NAMESPACE::ParseOpts opts,
    const SIPlus::UnknownDataTypeContainer& data, 
    const T& expected,
    const std::vector<std::pair<std::string, SIPLUS_NAMESPACE::UnknownDataTypeContainer>>& extra
) {
    auto builder = get_test_context().context().builder().use_default(data);

    for(auto [k, v] : extra) {
        auto it = std::find(opts.globals.begin(), opts.globals.end(), k);
        if(it == opts.globals.end()) {
            opts.globals.emplace_back(k);
        }

        builder.with(k, v);
    }

    auto retriever = get_test_context().get_expression(expression, opts);

    auto result = retriever->retrieve(*builder.build());
                                      
    try {
        return expect_equal<_ExpectedType, T>(result, expected) ? 0 : 1;
    } catch(std::runtime_error& e) {
        throw std::runtime_error{SIPLUS_NAMESPACE::util::to_string(
            "Expression '", expression, "' failed: ", e.what()
        )};

        return 1;
    }
}

template<SIPLUS_NAMESPACE::simple_value_retrievable_type Expected, typename T = Expected::data_type> 
int test_expression(
    const std::string& expr,
    const T& expected,
    const std::vector<std::pair<std::string, SIPLUS_NAMESPACE::UnknownDataTypeContainer>>& extra
) {
    auto container = SIPLUS_NAMESPACE::make_data(test_data{});
    return test_expression<Expected, T>(
        expr, SIPLUS_NAMESPACE::ParseOpts{}, container, expected, extra
    );
}
template<SIPLUS_NAMESPACE::simple_value_retrievable_type Expected, typename Data, typename T = Expected::data_type> 
int test_expression(
    const std::string& expr,
    const Data& data,
    const T& expected
) {
    auto container = SIPLUS_NAMESPACE::make_data(data);
    return test_expression<Expected, T>(
        expr, SIPLUS_NAMESPACE::ParseOpts{}, container, expected, {}
    );
}

template<SIPLUS_NAMESPACE::simple_value_retrievable_type Expected, typename T = Expected::data_type> 
int test_expression(
    const std::string& expr,
    const T& expected
) {
    auto container = SIPLUS_NAMESPACE::make_data(test_data{});
    return test_expression<Expected, T>(
        expr, SIPLUS_NAMESPACE::ParseOpts{}, container, expected, {}
    );
}

template<typename Expected, typename Data> 
int test_expression(
    const std::string& expr,
    const Data& data,
    const Expected& expected
) {
    auto container = SIPLUS_NAMESPACE::make_data(data);
    return test_expression<SIPLUS_NAMESPACE::type_info_for_t<Expected>>(
        expr, SIPLUS_NAMESPACE::ParseOpts{}, container, expected, {}
    );
}

template<typename Expected> 
int test_expression(
    const std::string& expr,
    const Expected& expected
) {
    return test_expression(expr, test_data{}, expected);
}



template<SIPlus::simple_value_retrievable_type V >
int test_interpolation(
    const std::string& expression, 
    SIPLUS_NAMESPACE::ParseOpts opts,
    const typename V::data_type& data, 
    const std::string& expected,
    const std::vector<std::pair<std::string, SIPLUS_NAMESPACE::UnknownDataTypeContainer>>& extra
) {
    auto builder = get_test_context().context().builder()
        .use_default(SIPLUS_NAMESPACE::make_data(data));

    for(auto [k, v] : extra) {
        auto it = std::find(opts.globals.begin(), opts.globals.end(), k);
        if(it == opts.globals.end()) {
            opts.globals.emplace_back(k);
        }

        builder.with(k, v);
    }

    auto retriever = get_test_context().get_interpolation(expression, opts);

    auto result = retriever.construct_with(builder.build());

    if(result != expected) {
        std::cout 
            << "Expression \"" << expression << "\" failed: Expected \"" 
            << expected << "\" " << " recieved value \"" << result << "\"." << std::endl;
        return 1;
    }

    return 0;
}

inline int test_interpolation(
    const std::string& expression, 
    const std::string& expected,
    const std::vector<std::pair<std::string, SIPLUS_NAMESPACE::UnknownDataTypeContainer>>& extra
) {
    return test_interpolation<test_data_type>(expression, SIPLUS_NAMESPACE::ParseOpts{}, test_data{}, expected, extra);
}

inline int test_interpolation(const std::string& expression, const std::string& expected) {
    return test_interpolation<test_data_type>(expression, SIPLUS_NAMESPACE::ParseOpts{}, test_data{}, expected, {});
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

template<
    typename T, 
    SIPLUS_NAMESPACE::simple_value_retrievable_type To
> requires std::is_base_of_v<SIPLUS_NAMESPACE::text::Converter, T>
int test_conversion(
    const T& converter, 
    const SIPLUS_NAMESPACE::UnknownDataTypeContainer& from,
    const typename To::data_type& result
) {
    auto to_type = To{};

    if(!converter.can_convert(*from.type, to_type)) {
        std::cout 
            << typeid(T).name() << " cannot convert from " 
            << from.type->name() << " to " << to_type.name() << std::endl;
        return 1;
    }

    auto container = converter.convert(from, to_type);

    if(!container.template is<To>()) {
        std::cout << "Expected type " << to_type.name()
            << ". Recieved " << container.type->name() << std::endl;
        return 1;
    }

    try {
        return expect_equal<To>(container, result) ? 0 : 1;
    } catch(std::runtime_error& e) {
        throw std::runtime_error{SIPLUS_NAMESPACE::util::to_string(
            "Conversion failed: ", e.what()
        )};

        return 1;
    }
}

template<typename T, typename V, typename To> requires std::is_base_of_v<SIPLUS_NAMESPACE::text::Converter, T>
int test_conversion(const T& converter, const V& val, const To& result) {
    auto container = SIPLUS_NAMESPACE::make_data(val);
    return test_conversion<T, SIPLUS_NAMESPACE::type_info_for_t<To>>(converter, container, result);
}

template<typename T, typename V, typename To> requires std::is_base_of_v<SIPLUS_NAMESPACE::text::Converter, T>
int test_conversion(const V& val, const To& result) {
    T converter;
    return test_conversion<T, V, To>(converter, val, result);
}
