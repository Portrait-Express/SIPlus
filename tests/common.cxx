#include <cpptrace/from_current.hpp>
#include <iostream> 
#include <format>
#include <memory>
#include <stdexcept>
#include <vector>

#include "siplus/context.h"
#include "siplus/parser.h"
#include "siplus/text/data.h"
#include "siplus/text/iterator.h"

#include "common.hxx"
#include "../siplus/util.h"

using namespace SIPLUS_NAMESPACE;

int common(int, char**) { return 0; } //dummy for ctest

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

struct vector_iterator : public SIPlus::text::IteratorProvider {
    std::unique_ptr<text::Iterator> iterator(const text::UnknownDataTypeContainer &value) override {
        const auto& ref = value.as<std::vector<User>>();

        auto ptr = new iterator_impl<User>{ref.begin(), ref.end()};
        return std::unique_ptr<text::Iterator>{ptr};
    }

    bool can_iterate(const text::UnknownDataTypeContainer &value) override {
        return value.type == typeid(std::vector<User>);
    }


private:
    template<typename T>
    struct iterator_impl : text::Iterator {
    public:
        explicit iterator_impl(
            std::vector<T>::const_iterator begin,
            std::vector<T>::const_iterator end
        ) : begin(begin), cur(begin), end(end) { }

        bool more() override {
            return cur < end - 1;
        }

        void next() override {
            //cur is valid at iterator creation, but we need to eat a next() 
            //to start the iterator as iterators should not have a valid current()
            //if next() has not been called
            if(!begun_) {
                begun_ = true;
                return;
            }

            cur++;

            if(cur >= end) {
                throw std::runtime_error{"next() called on completed iterator"};
            }
        }

        text::UnknownDataTypeContainer current() override {
            if(!begun_) {
                throw std::runtime_error{"next() has not been called. call more()&&next()"};
            }

            return text::make_data(*cur);
        }

        ~iterator_impl() override { };

    private:
        bool begun_ = false;

        const std::vector<T>::const_iterator begin;
        const std::vector<T>::const_iterator end;

        std::vector<T>::const_iterator cur;
    };
};

struct data_accessor : public SIPlus::text::Accessor {
    text::UnknownDataTypeContainer access(
        const text::UnknownDataTypeContainer &value, 
        const std::string &name) override {
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
        return value.type == typeid(test_data);
    }
};

Parser get_test_context() {
    Parser parser;

    parser.context().use_stl();
    parser.context().emplace_accessor<data_accessor>();
    parser.context().emplace_accessor<user_accessor>();
    parser.context().emplace_iterator<vector_iterator>();

    return parser;
}

int test(std::function<int(const Parser&)> test_impl) {
    Parser parser = get_test_context();

    CPPTRACE_TRY {
        return test_impl(parser);
    } CPPTRACE_CATCH(std::exception& e) {
        std::cout << e.what() << std::endl;
        cpptrace::from_current_exception().print();

        return 1;
    }

    return 1;
}
