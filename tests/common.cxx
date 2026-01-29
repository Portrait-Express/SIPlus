#include <chrono>
#include <iostream> 
#include <format>
#include <stdexcept>

#ifdef SIPLUS_HAS_CPPTRACE

#include <cpptrace/from_current.hpp>
#define SIPLUS_TRY CPPTRACE_TRY
#define SIPLUS_CATCH(args) CPPTRACE_CATCH(args)

#else 

#define SIPLUS_TRY try
#define SIPLUS_CATCH catch

#endif

#include "siplus/context.h"
#include "siplus/parser.h"
#include "siplus/data.h"

#include "common.hxx"

using namespace SIPLUS_NAMESPACE;

int common(int, char**) { return 0; } //dummy for ctest

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

UnknownDataTypeContainer test_data_y_type::access(void *ptr, const std::string& name) const  {
    struct test_data::y *data = reinterpret_cast<struct test_data::y*>(ptr);

    if(name == "b") {
        return make_data(data->b);
    } else {
        throw std::runtime_error(std::format("No viable property for '{}'", name));
    }
}

UnknownDataTypeContainer test_data_type::access(void *ptr, const std::string& name) const  {
    test_data *data = reinterpret_cast<test_data*>(ptr);

    if(name == "x") {
        return make_data(data->x);
    } else if(name == "y") {
        return make_data(data->y);
    } else if(name == "users") {
        return make_data(data->users);
    } else {
        throw std::runtime_error(std::format("No viable property for '{}'", name));
    }
}

UnknownDataTypeContainer user_type::access(void *ptr, const std::string& name) const {
    User *user = reinterpret_cast<User*>(ptr);

    if(name == "id") {
        return make_data(user->id);
    } else if(name == "email") {
        return make_data(user->email);
    } else if(name == "username") {
        return make_data(user->username);
    } else if(name == "can_login") {
        return make_data(user->can_login);
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

#ifdef SIPLUS_HAS_CPPTRACE
        cpptrace::from_current_exception().print();
#endif
        
        result = 1;
    }

    return result;
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
