#include "siplus/context.h"

struct test_data {
    int x = 2;

    struct y {
        short b = 1;
    } y;
};

std::shared_ptr<SIPlus::SIPlusParserContext> test_context();
