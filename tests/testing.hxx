#pragma once
#include "siplus/util.hxx"
#include <utility>
#ifndef INCLUDE_TESTS_TESTING_HXX_
#define INCLUDE_TESTS_TESTING_HXX_

#include "siplus/context.hxx"
#include "common.hxx"

#include <exception>
#include <stacktrace>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>

#define _MAKE_CATEGORY(name, parent) namespace test_detail { \
TestCategory *Category##name = nullptr; \
TestCategory *make_category_##name() {  \
    if(Category##name == nullptr) Category##name = new TestCategory(parent, #name); \
    return Category##name; \
} \
} /* namespace test_detail */


#define CATEGORY(name) _MAKE_CATEGORY(name, nullptr)
#define CATEGORY_SUB(name, parent) _MAKE_CATEGORY(name, make_category_##parent())

#define TEST(name, category) void Test##name##Impl(TestingContext *t); \
TestDescriptor *Test##name = new TestDescriptor(test_detail::make_category_##category(), #name, TestDescriptor::impl_type{Test##name##Impl}); \
void Test##name##Impl(TestingContext *t)

#define RUN_CATEGORY(name) test_detail::make_category_##name()->run_all()

#define STR(x) #x
#define EXPECT_TRUE_S(expr, msg) ::expect::expect(expr, msg);
#define EXPECT_TRUE(expr) ::expect::expect(expr, "Expected '" #expr "' to be true. Was false.");
#define EXPECT_EQUAL(expected, actual) auto result = actual; \
::expect::expect(expr, "Expected '" STR(actual) "' to be == to '" STR(expected) ". Got: '" + ::SIPLUS_NAMESPACE::util::to_string(result) + "'");

class TestDescriptor;
class TestCategory;

class TestLogEntryBuilder;
class TestLoggerChannel;

class TestingContext;
class TestResult;
class CategoryResult;
class TestFailure;





class IndentStreambuf : public std::streambuf {
public:
    IndentStreambuf(std::ostream& os, int idx) 
        : dest_buf(os.rdbuf()), is_at_start_of_line(true), indent_index(idx), stream(os) {
        os.rdbuf(this); 
    }

    ~IndentStreambuf() override {
        stream.rdbuf(dest_buf); 
    }

protected:
    int overflow(int ch) override {
        if (ch == traits_type::eof()) {
            return traits_type::not_eof(ch);
        }

        int current_indent = stream.iword(indent_index);

        if (is_at_start_of_line && ch != '\n' && current_indent > 0) {
            for (int i = 0; i < current_indent; ++i) {
                if (dest_buf->sputc(' ') == traits_type::eof()) {
                    return traits_type::eof();
                }
            }
        }

        is_at_start_of_line = (ch == '\n');

        return dest_buf->sputc(ch);
    }

private:
    std::streambuf* dest_buf;
    bool is_at_start_of_line;
    int indent_index;
    std::ostream& stream;
};

struct streambuf_indent {
    int spaces;
    explicit streambuf_indent(int s) : spaces(s) {}

    static int slot() {
        static const int index = std::ios_base::xalloc();
        return index;
    }

    friend inline std::ostream& operator<<(std::ostream& os, const streambuf_indent& si) {
        static thread_local IndentStreambuf indent_buffer(os, streambuf_indent::slot());
        
        os.iword(streambuf_indent::slot()) = si.spaces;

        return os;
    }
};

inline size_t indent(std::ostream& os) { return os.iword(streambuf_indent::slot()); }
inline streambuf_indent indent(int s) { return streambuf_indent{s}; }





using TestTimestamp = std::chrono::time_point<std::chrono::system_clock>;
using TestDuration = std::chrono::microseconds;

class TestFailure : public std::runtime_error {
public:
    TestFailure(std::string error) : std::runtime_error(error), stacktrace(std::stacktrace::current()) { }

    const std::stacktrace stacktrace;
};

enum class TestLoggerSeverity {
    INFO,
    WARN,
    ERROR
};

struct TestLogEntry {
    const TestLoggerSeverity severity;
    const TestTimestamp timestamp = std::chrono::system_clock::now();
    const std::string message = "";
    const std::optional<std::string> exception = std::nullopt;
};

class TestLogEntryBuilder {
public:
    TestLogEntryBuilder(TestLogEntryBuilder&& other);
    TestLogEntryBuilder& operator=(TestLogEntryBuilder&& other);

    TestLogEntryBuilder(const TestLogEntryBuilder& other) = delete;
    TestLogEntryBuilder& operator=(const TestLogEntryBuilder& other) = delete;

    friend class TestLoggerChannel;

    template<typename T>
    friend TestLogEntryBuilder& operator<<(TestLogEntryBuilder& builder, const T& result) {
        builder.ss_ << result;
        return builder;
    }

    friend void swap(TestLogEntryBuilder& first, TestLogEntryBuilder& other);

    ~TestLogEntryBuilder() noexcept;

private:
    TestLogEntryBuilder(TestLoggerChannel* channel, TestLoggerSeverity severity);
    TestLogEntry build() const noexcept;

    TestLoggerSeverity severity_;
    std::stringstream ss_;
    TestLoggerChannel* channel_;
    TestTimestamp timestamp_ = std::chrono::system_clock::now();
};

class TestLoggerChannel {
public:
    TestLoggerChannel() noexcept;

    TestLogEntryBuilder log(TestLoggerSeverity severity) noexcept;
    TestLoggerChannel& add(TestLogEntry entry) noexcept;

    std::list<TestLogEntry> entries() const noexcept;
    
private:
    TestingContext *context_;
    std::list<TestLogEntry> entries_;
};

class TestingContext {
public:
    TestingContext(const TestDescriptor *descriptor) noexcept;

    TestDescriptor *current() noexcept;

    TestLogEntryBuilder err() noexcept;
    TestLogEntryBuilder warn() noexcept;
    TestLogEntryBuilder out() noexcept;

    std::list<TestLogEntry> log() const;

private:
    TestDescriptor const * const test_;
    TestLoggerChannel log_;
};

class TestDescriptor {
public:
    using impl_type = std::function<void (TestingContext *)>;

    TestDescriptor(TestCategory *category, std::string name, impl_type implementation) noexcept;

    const TestCategory *category() const;
    std::string name() const;

    TestResult invoke() const noexcept;

private:
    const TestCategory *const category_;
    std::string name_;
    impl_type impl_;
};

class TestCategory {
public:
    friend class TestDescriptor;

    TestCategory(std::string name) : TestCategory(nullptr, name) {}
    TestCategory(TestCategory *parent, std::string name) : name_(name), parent_(parent) {
        if(parent != nullptr) {
            parent->categories_.emplace_back(this);
        }
    }

    std::string name() const;
    std::list<TestDescriptor*> tests();
    const TestCategory *parent() { return parent_; }

    CategoryResult run_all() const;

private:
    void register_test(TestDescriptor *test) noexcept;

    const std::string name_;
    const TestCategory *const parent_;
    std::list<TestCategory*> categories_;
    std::list<TestDescriptor*> tests_;
};

std::string stringify_exception(std::exception_ptr ex);

struct TestResult {
    const TestDescriptor *test;
    bool passed;
    std::list<TestLogEntry> log;
    std::optional<std::exception_ptr> exception = std::nullopt;
    std::chrono::microseconds runtime;

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const TestResult& result) {
        if(result.passed) {
            out << "✔  PASSED";
        } else {
            out << "❌ FAILED";
        }

        out << ' ' << result.test->name() << ' ' << result.runtime;

        if(result.exception) {
            auto oldIndent = indent(out);
            out << indent(oldIndent + 4) << '\n' << stringify_exception(*result.exception) 
                << indent(oldIndent);
        }

        return out;
    }
};

struct CategoryResult {
    const TestCategory *category;
    std::list<TestResult> results;
    std::chrono::milliseconds duration;

    bool passed() {
        bool passed = true;

        for(auto test : results) {
            passed = passed && test.passed;
        }

        return passed;
    }

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const CategoryResult& result) {
        out << "Category " << result.category->name();

        auto oldIndent = indent(out);
        auto count = 0;
        auto passed = 0;

        out << indent(oldIndent + 4);
        for(auto testResult : result.results) {
            count++;
            if(testResult.passed) passed++;

            out << "\n" << count << ". " << testResult;
        }

        out << "\n\n" << passed << '/' << count << " passed in " << result.duration
            << indent(oldIndent);

        return out;
    }
};

namespace expect {

namespace detail {

template<typename L, typename R>
struct equal_tester {
    static bool test(const L& lhs, const R& rhs) {
        return lhs == rhs;
    }
};

template<>
struct equal_tester<double, double> {
    static bool test(const double& val, const double& other) {
        return nearly_equal(val, other);
    }
};

template<typename T>
concept is_data_container = requires {
    requires std::is_same_v<std::remove_cvref_t<T>, SIPLUS_NAMESPACE::UnknownDataTypeContainer>;
};

} /* detail */

inline void throw_expect_failed(std::string message) {
    throw TestFailure{message};
}

inline void throw_expect_failed(std::optional<std::string> message, std::string defaultMessage) {
    throw TestFailure{message.value_or(defaultMessage)};
}

/**
 * @brief Test equality in C++ code, not in SIPlus code. This is useful to avoid
 * possible SIPlus type conversions when testing equality when you want to strictly 
 * make sure that a value is a certain exact value.
 *
 * (side note, are we basically making == vs === again? If so, someone stop me)
 *
 * @tparam L Left hand value
 * @tparam R Right hand value
 * @param[in] lhs Left hand value 
 * @param[in] rhs Right hand value
 * @return whether they are equal
 */
template<typename L, typename R>
bool equal(const L& lhs, const R& rhs) {
    return detail::equal_tester<L, R>::test(lhs, rhs);
}

void expect(bool condition, std::string message);

void expression(
    const std::string& expression, 
    const SIPLUS_NAMESPACE::UnknownDataTypeContainer& expected,
    const SIPLUS_NAMESPACE::UnknownDataTypeContainer& defaultData 
);

/**
 * @brief Compare two lists of values and ensure that they both contain the 
 * same set of items, but in any order.
 *
 * @tparam T The expected values
 * @param[in] expected The expected items.
 * @param[in] actual The actual items.
 */
template<typename T>
void unordered_elements(
    const std::vector<T>& expected,
    const std::vector<SIPLUS_NAMESPACE::UnknownDataTypeContainer>& actual
) {
    expect(
        expected.size() == actual.size(), 
        SIPLUS_NAMESPACE::util::to_string(
            "List sizes do not match. Expected: ", expected, 
            " Actual: ", actual
        )
    );

    std::unordered_map<SIPlus::UnknownDataTypeContainer, long> counts;
    for(const auto& element : expected) {
        auto container = SIPLUS_NAMESPACE::make_data(element);
        counts[container]++;
    }

    for(const auto& element : actual) {
        counts[element]--;
    }

    for(const auto& [k, v] : counts) {
        if(v > 0) {
            throw_expect_failed(SIPLUS_NAMESPACE::util::to_string(
                "Missing elements from expected result. Expected: ", expected, 
                " Actual: ", actual
            ));
        } else if(v < 0) {
            throw_expect_failed(SIPLUS_NAMESPACE::util::to_string(
                "Result contained more elements than expected. Expected: ", 
                expected, " Actual: ", actual
            ));
        }
    }
}

template<
    typename Expected,
    typename Default = SIPLUS_NAMESPACE::UnknownDataTypeContainer
> requires (!detail::is_data_container<Default> || !detail::is_data_container<Expected>)
void expression(
    const std::string& expression, 
    Expected&& expected,
    Default&& defaultData = SIPLUS_NAMESPACE::make_data(test_data{})
) {
    expect::expression(
        expression, 
        SIPLUS_NAMESPACE::make_data(std::forward<Expected>(expected)),
        SIPLUS_NAMESPACE::make_data(std::forward<Default>(defaultData)) 
    );
}

template<SIPLUS_NAMESPACE::simple_value_retrievable_type T>
void conversion(
    const SIPLUS_NAMESPACE::UnknownDataTypeContainer& from,
    const typename T::data_type& to
) {
    if(!from.can_convert(T::descriptor)) {
        throw TestFailure{SIPLUS_NAMESPACE::util::to_string(
            "No converter available to convert from '", from.type, "' to '", 
            T::descriptor->name, "'"
        )};
    }

    auto result = from.convert(T::descriptor);

    expect::expect(equal(result.template as<T>(), to), SIPLUS_NAMESPACE::util::to_string(
        "Value ", from, ", when converted to '", T::descriptor->name, 
        "', is not equal to ", to, ". Received ", result, "."
    ));
}

template<
    SIPLUS_NAMESPACE::simple_value_retrievable_type T,
    typename From
> requires (!detail::is_data_container<From> || !detail::is_data_container<From>)
void conversion(From&& from, const typename T::data_type& to) {
    expect::conversion<T>(SIPLUS_NAMESPACE::make_data(std::forward<From>(from)), to);
}

} /* namespace expect */

SIPLUS_NAMESPACE::UnknownDataTypeContainer do_expression(
    const std::string& expression, 
    const SIPLUS_NAMESPACE::UnknownDataTypeContainer& defaultData = SIPLUS_NAMESPACE::UnknownDataTypeContainer{}
);

template<typename T> requires (!expect::detail::is_data_container<T>)
SIPLUS_NAMESPACE::UnknownDataTypeContainer do_expression(
    const std::string& expression, 
    T&& defaultData
) {
    return do_expression(expression, SIPLUS_NAMESPACE::make_data(std::forward<T>(defaultData)));
}

#endif  // INCLUDE_TESTS_TESTING_HXX_   
