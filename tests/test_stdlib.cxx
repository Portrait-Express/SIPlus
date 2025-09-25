#include "common.hxx"
#include "siplus/stl/converters/numeric.h"
#include "siplus/text/data.h"
#include "siplus/util.h"
#include <algorithm>
#include <bits/types/cookie_io_functions_t.h>
#include <cassert>
#include <cfloat>
#include <chrono>
#include <iostream>

int test_add() {
    return test("add", [](const SIPlus::Parser& parser) {
        auto expr = parser.get_expression("add .x .y.b");
        auto val = expr->retrieve(SIPlus::text::make_data(test_data{}));
        return (val.is<long>() && val.as<long>() == 3) ? 0 : 1;
    });
}

int test_str() {
    return test("str", [](const SIPlus::Parser& parser) {
        auto expr = parser.get_expression(".x | str");
        auto val = expr->retrieve(SIPlus::text::make_data(test_data{}));
        return (val.is<std::string>() && val.as<std::string>() == "2") ? 0 : 1;
    });
}

int test_map() {
    return test("map", [](const SIPlus::Parser& parser) {
        auto data = test_data{};

        auto expr = parser.get_expression(".users | map .id");
        auto val = expr->retrieve(SIPlus::text::make_data(test_data{}));

        if(!val.is<std::vector<SIPlus::text::UnknownDataTypeContainer>>()) {
            return 1;
        }

        const std::vector<SIPlus::text::UnknownDataTypeContainer>& vec = 
            val.as<std::vector<SIPlus::text::UnknownDataTypeContainer>>();

        if(!std::all_of(vec.begin(), vec.end(), [](SIPlus::text::UnknownDataTypeContainer val) {
            return val.is<int>();
        })) {
            return 1;
        }

        std::vector<int> result{};
        result.reserve(vec.size());

        std::transform(vec.begin(), vec.end(), std::back_inserter(result), 
                       [](SIPlus::text::UnknownDataTypeContainer val) {
            return val.as<int>();
        });

        return result == std::vector<int>{1, 2} ? 0 : 1;
    });
}



//https://stackoverflow.com/a/32334103/10844545
bool nearly_equal(
  float a, float b,
  float epsilon = 128 * FLT_EPSILON, float abs_th = FLT_MIN)
  // those defaults are arbitrary and could be removed
{
  assert(std::numeric_limits<float>::epsilon() <= epsilon);
  assert(epsilon < 1.f);

  if (a == b) return true;

  auto diff = std::abs(a-b);
  auto norm = std::min((std::abs(a) + std::abs(b)), std::numeric_limits<float>::max());
  // or even faster: std::min(std::abs(a + b), std::numeric_limits<float>::max());
  // keeping this commented out until I update figures below
  return diff < std::max(abs_th, epsilon * norm);
}

bool nearly_equal(
  double a, double b,
  double epsilon = 128 * DBL_EPSILON, double abs_th = DBL_MIN)
  // those defaults are arbitrary and could be removed
{
  assert(std::numeric_limits<double>::epsilon() <= epsilon);
  assert(epsilon < 1.f);

  if (a == b) return true;

  auto diff = std::abs(a-b);
  auto norm = std::min((std::abs(a) + std::abs(b)), std::numeric_limits<double>::max());
  // or even faster: std::min(std::abs(a + b), std::numeric_limits<float>::max());
  // keeping this commented out until I update figures below
  return diff < std::max(abs_th, epsilon * norm);
}

template<typename T>
bool conversion_equal(T first, T second) {
    return first == second;
}

template<>
bool conversion_equal<double>(double first, double second) {
    //Use float epsilon since float_converter casts from a float to a double, 
    //and should be within 1 FLT_EPSILON of accuracy
    return nearly_equal(first, second, (double)FLT_EPSILON, (double)FLT_MIN);
}

template<typename T, typename V, typename To> requires std::is_base_of_v<SIPlus::text::Converter, T>
int test_conversion(V&& val, To&& result) {
    T converter;
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

int test_int_converter() {
    return test("int_converter", [](const SIPlus::Parser& parser) {
        SIPlus::stl::int_converter converter;

        return tests(
            test_conversion<SIPlus::stl::int_converter, short, long>(12, 12),
            test_conversion<SIPlus::stl::int_converter, int, long>(42, 42),
            test_conversion<SIPlus::stl::int_converter, long, long>(1337, 1337)
        );
    });
}

int test_float_converter() {
    return test("float_converter", [](const SIPlus::Parser& parser) {
        SIPlus::text::UnknownDataTypeContainer data = SIPlus::text::make_data<double>(2);
        SIPlus::stl::float_converter con;
        std::cout << data.as<double>() << con.convert(data, typeid(double)).as<double>() << std::endl;
        
        return tests(
            test_conversion<SIPlus::stl::float_converter, float, double>(1.124f, 1.124),
            test_conversion<SIPlus::stl::float_converter, double, double>(3.141f, 3.141)
        );
    });
}

int test_numeric_string_converter() {
    return test("numeric_string_converter", [](const SIPlus::Parser& parser) {
        SIPlus::stl::numeric_string_converter converter;

        return tests(
            test_conversion<SIPlus::stl::numeric_string_converter, short, std::string>(1, "1"),
            test_conversion<SIPlus::stl::numeric_string_converter, int, std::string>(1, "1"),
            test_conversion<SIPlus::stl::numeric_string_converter, long, std::string>(1, "1"),
            test_conversion<SIPlus::stl::numeric_string_converter, float, std::string>(1, "1"),
            test_conversion<SIPlus::stl::numeric_string_converter, double, std::string>(1, "1")
        );
    });
}
int test_functions() {
    return group("functions", []() {
        return tests(
            test_add(),
            test_str(),
            test_map()
        );
    });
}


int test_converters() {
    return group("converters", []() {
        return tests(
            test_int_converter(),
            test_float_converter(),
            test_numeric_string_converter()
        );
    });
}

int test_stdlib(int, char**) {
    return group("stdlib", []() {
        return tests(
            test_functions(),
            test_converters()
        );
    });
}

