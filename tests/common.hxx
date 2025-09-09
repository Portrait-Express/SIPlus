#include "siplus/parser.h"

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
