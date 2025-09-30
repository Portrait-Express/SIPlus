#include "siplus/text/converter.h"
#include <chrono>
#include <iostream> 
#include <format>
#include <sstream>
#include <stdexcept>
#include <typeindex>

#ifdef SIPLUS_HAS_CPPTRACE

#include <cpptrace/from_current.hpp>
#define SIPLUS_TRY CPPTRACE_TRY
#define SIPLUS_CATCH(args) CPPTRACE_CATCH(args)

#else 

#define SIPLUS_TRY try
#define SIPLUS_CATCH catch

#endif

#include "siplus/context.h"
#include "siplus/internal/vector_iterator_provider.h"
#include "siplus/parser.h"
#include "siplus/text/data.h"
#include "siplus/util.h"

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

struct user_accessor : public SIPlus::text::Accessor {
    text::UnknownDataTypeContainer access(
        const text::UnknownDataTypeContainer &value, 
        const std::string &name
    ) override {

        const User& data = value.as<User>();

        if(name == "id") {
            return text::make_data(data.id);
        } else if(name == "email") {
            return text::make_data(data.email);
        } else if(name == "username") {
            return text::make_data(data.username);
        } else if(name == "can_login") {
            return text::make_data(data.can_login);
        }

        throw std::runtime_error(std::format("No viable property for '{}'", name));
    }

    bool can_access(const text::UnknownDataTypeContainer& value) override {
        return value.type == typeid(User);
    }
};

struct data_accessor : public SIPlus::text::Accessor {
    text::UnknownDataTypeContainer access(
        const text::UnknownDataTypeContainer &value, 
        const std::string &name) override {
        if(value.is<struct test_data::y>()) {
            return text::make_data(value.as<struct test_data::y>().b);
        }

        const test_data& data = value.as<test_data>();

        if(name == "x") {
            return text::make_data(data.x);
        }

        if(name == "y") {
            return text::make_data(data.y);
        }

        if(name == "users") {
            return text::make_data(data.users);
        }


        throw std::runtime_error(std::format("No viable property for '{}'", name));
    }

    bool can_access(const text::UnknownDataTypeContainer& value) override {
        return value.type == typeid(test_data) || 
            value.type == typeid(struct test_data::y);
    }
};

Parser& get_test_context() {
    static Parser parser;

#ifdef SIPLUS_INCLUDE_STDLIB
    parser.context().use_stl();
#else
    parser.context().emplace_converter<int_string_converter>();
#endif

    parser.context().emplace_accessor<data_accessor>();
    parser.context().emplace_accessor<user_accessor>();
    parser.context().emplace_iterator<internal::vector_iterator<User>>();

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

int group(std::string name, std::function<int(const SIPlus::Parser&)> test_impl) {
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
