#include "siplus/parser.h"

struct test_data {
    int x = 2;

    struct y {
        short b = 1;
    } y;
};

SIPlus::Parser test_context();
