#pragma once
#ifndef INCLUDE_TESTS_TESTING_HXX_
#define INCLUDE_TESTS_TESTING_HXX_


#include <exception>
#include <numeric>
#include <stacktrace>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <sstream>
#include <stdexcept>
#include <streambuf>
#include <string>

#define CATEGORY(name) namespace test_detail { \
TestCategory *Category##name = nullptr; \
TestCategory *make_category_##name() {  \
    if(Category##name == nullptr) Category##name = new TestCategory(#name); \
    return Category##name; \
} \
} /* namespace test_detail */ \

#define TEST(name, category) bool Test##name##Impl(TestingContext *ctx); \
TestDescriptor *Test##name = new TestDescriptor(test_detail::make_category_##category(), #name, TestDescriptor::impl_type{Test##name##Impl}); \
bool Test##name##Impl(TestingContext *ctx)

class TestDescriptor;
class TestCategory;

class TestLogEntryBuilder;
class TestLoggerChannel;

class TestingContext;
class TestResult;
class CategoryResult;
class TestFailure;





class IndentStreambuf : public std::streambuf {
private:
    std::streambuf* dest_buf;
    bool is_at_start_of_line;
    int indent_index;
    std::ostream& stream;

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

public:
    IndentStreambuf(std::ostream& os, int idx) 
        : dest_buf(os.rdbuf()), is_at_start_of_line(true), indent_index(idx), stream(os) {
        os.rdbuf(this); 
    }

    ~IndentStreambuf() override {
        stream.rdbuf(dest_buf); 
    }
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
    using impl_type = std::function<bool (TestingContext *)>;

    TestDescriptor(TestCategory *category, std::string name, impl_type implementation) noexcept;

    const TestCategory* category() const;
    std::string name() const;

    TestResult invoke() const noexcept;

private:
    TestCategory *category_;
    std::string name_;
    impl_type impl_;
};

class TestCategory {
public:
    friend class TestDescriptor;

    TestCategory(std::string name) : name(name) {}
    std::list<TestDescriptor*> tests();

    CategoryResult run_all();

    const std::string name;

private:
    void register_test(TestDescriptor *test) noexcept;

    std::list<TestDescriptor*> tests_;
};

std::string stringify_exception(std::exception_ptr ex);

struct TestResult {
    const TestDescriptor *test;
    bool passed;
    std::list<TestLogEntry> log;
    std::optional<std::exception_ptr> exception = std::nullopt;

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const TestResult& result) {
        if(result.passed) {
            out << "✔  PASSED";
        } else {
            out << "❌ FAILED";
        }

        out << ' ' << result.test->name();

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

    bool passed() {
        bool passed = true;

        for(auto test : results) {
            passed = passed && test.passed;
        }

        return passed;
    }

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const CategoryResult& result) {
        out << "Category " << result.category->name;

        auto oldIndent = indent(out);
        auto count = 0;
        auto passed = 0;

        out << indent(oldIndent + 4);
        for(auto testResult : result.results) {
            count++;
            if(testResult.passed) passed++;

            out << "\n" << count << ". " << testResult;
        }

        out << "\n\n" << passed << '/' << count << " passed" 
            << indent(oldIndent);

        return out;
    }
};

namespace expect {

void assert(bool condition, std::string message);

} /* namespace expect */

#define STR(x) #x
#define EXPECT_TRUE_S(expr, msg) ::expect::assert(expr, msg);
#define EXPECT_TRUE(expr) ::expect::assert(expr, "Expected '" #expr "' to be true. Was false.");
#define EXPECT_EQUAL(expected, actual) auto result = actual; \
::expect::assert(expr, "Expected '" STR(actual) "' to be == to '" STR(expected) ". Got: '" + ::SIPLUS_NAMESPACE::util::to_string(result) + "'");

#endif  // INCLUDE_TESTS_TESTING_HXX_   
