#include <chrono>
#include <iostream> 
#include <format>
#include <stacktrace>
#include <stdexcept>

#define SIPLUS_TRY try
#define SIPLUS_CATCH catch

#include "siplus/context.hxx"
#include "siplus/parser.hxx"
#include "siplus/data.hxx"

#include "common.hxx"

using namespace SIPLUS_NAMESPACE;

int common(int, char** const) { return 0; } //dummy for ctest

#ifndef SIPLUS_INCLUDE_STDLIB

struct int_string_converter : text::Converter {
    bool can_convert(std::type_index from, std::type_index to) override {
        return from == typeid(int) && to == typeid(std::string);
    }

    text::UnknownDataTypeContainer 
    convert(text::UnknownDataTypeContainer from, std::type_index to) override {
        std::stringstream ss;
        ss << from.as<int>();
        return text::make_data(ss.str());
    }
};

#endif

UnknownDataTypeContainer test_data_y_type::access(const UnknownDataTypeContainer& ptr, const std::string& name) const  {
    struct test_data::y& data = ptr.as<test_data_y_type>();

    if(name == "b") {
        return make_data(data.b);
    } else {
        throw std::runtime_error(std::format("No viable property for '{}'", name));
    }
}

UnknownDataTypeContainer test_data_type::access(const UnknownDataTypeContainer& ptr, const std::string& name) const  {
    test_data& data = ptr.as<test_data_type>();

    if(name == "x") {
        return make_data(data.x);
    } else if(name == "y") {
        return make_data(data.y);
    } else if(name == "users") {
        return make_data(data.users);
    } else {
        throw std::runtime_error(std::format("No viable property for '{}'", name));
    }
}

UnknownDataTypeContainer user_type::access(const UnknownDataTypeContainer& ptr, const std::string& name) const {
    User& user = ptr.as<user_type>();

    if(name == "id") {
        return make_data(user.id);
    } else if(name == "email") {
        return make_data(user.email);
    } else if(name == "username") {
        return make_data(user.username);
    } else if(name == "can_login") {
        return make_data(user.can_login);
    }

    throw std::runtime_error(std::format("No viable property for '{}'", name));
}

bool g_parser_init = false;
Parser& get_test_context() {
    static Parser parser;

    if(!g_parser_init) {
#ifdef SIPLUS_INCLUDE_STDLIB
        parser.context().use_stl();
#else
        parser.context().emplace_converter<int_string_converter>();
#endif

        g_parser_init = true;
    }

    return parser;
}

std::string group_prefix;
int test(std::string name, std::function<int(const Parser&)> test_impl) {
    Parser& parser = get_test_context();

    std::cout << "Running test: " << group_prefix << name << " - ";
    int result;

    std::chrono::system_clock::time_point start;
    SIPLUS_TRY {
        start = std::chrono::system_clock::now();
        result = test_impl(parser);
        auto end = std::chrono::system_clock::now();

        if(result == 0) {
            std::cout << "Pass";
        } else {
            std::cout << "Failed";
        }

        std::cout << " " << std::chrono::duration_cast<std::chrono::microseconds>(end - start) << std::endl;
    } SIPLUS_CATCH(std::exception& e) {
        auto end = std::chrono::system_clock::now();
        std::cout << "Failed with exception " << std::chrono::duration_cast<std::chrono::microseconds>(end - start) << '\n';

        std::cout << e.what() << std::endl;
        print_stacktrace();
        
        result = 1;
    }

    return result;
}

int test(std::string name, std::function<int()> test_impl) {
    return test(name, [&](const Parser&) {
        return test_impl();
    });
}

int group(std::string name, std::function<int(const Parser&)> test_impl) {
    //Remove any slashes from name
    name.erase(std::remove(name.begin(), name.end(), '/'), name.end());
    group_prefix += name + "/";

    //run test fn
    int result = test_impl(get_test_context());

    //Remove last segment of prefix
    auto it = group_prefix.rfind('/', name.size()-1);
    if(it != std::string::npos)
        group_prefix.erase(group_prefix.begin() + it + 1, group_prefix.end());

    return result;
}

int group(std::string name, std::function<int()> test_impl) {
    return group(name, [&](const Parser&) {
        return test_impl();
    });
}

bool nearly_equal(float a, float b, float epsilon, float abs_th) {
  assert(std::numeric_limits<float>::epsilon() <= epsilon);
  assert(epsilon < 1.f);

  if (a == b) return true;

  auto diff = std::abs(a-b);
  auto norm = std::min((std::abs(a) + std::abs(b)), std::numeric_limits<float>::max());
  return diff < std::max(abs_th, epsilon * norm);
}

bool nearly_equal(double a, double b, double epsilon, double abs_th) {
  assert(std::numeric_limits<double>::epsilon() <= epsilon);
  assert(epsilon < 1.f);

  if (a == b) return true;

  auto diff = std::abs(a-b);
  auto norm = std::min((std::abs(a) + std::abs(b)), std::numeric_limits<double>::max());
  return diff < std::max(abs_th, epsilon * norm);
}

//BELOW: Credit to https://werwolv.net/posts/cpp_exception_stacktraces/
thread_local std::array<std::stacktrace, 5> s_stacktraces;

extern "C" void __real___cxa_throw(
    void *thrown_object,
    std::type_info *tinfo,
    void (*dest)(void *)
);

extern "C" void __wrap___cxa_throw(
    void *thrown_object,
    std::type_info *tinfo,
    void (*dest)(void *)
) {
    auto exception_count = std::uncaught_exceptions();

    if (exception_count < ssize_t(s_stacktraces.size())) {
        s_stacktraces[exception_count] = std::stacktrace::current(1);
    }

    __real___cxa_throw(thrown_object, tinfo, dest);
}

void print_stacktrace() {
    auto exception_count = std::uncaught_exceptions();

    if (exception_count < 0) {
        std::cout << "No active exception" << std::endl;
    } else if (exception_count >= s_stacktraces.size()) {
        std::cout << "Too many active exceptions" << std::endl;
    } else {
        std::cout << "Stacktrace:\n" << s_stacktraces[exception_count];
    }
};
