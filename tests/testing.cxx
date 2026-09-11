#include "testing.hxx"
#include <exception>
#include <iostream>

TestLogEntryBuilder::TestLogEntryBuilder(TestLoggerChannel* channel, TestLoggerSeverity severity) 
    : channel_(channel), severity_() { }

TestLogEntryBuilder::~TestLogEntryBuilder() noexcept {
    channel_->add(TestLogEntry{
        .severity = severity_,
        .timestamp = timestamp_,
        .message = ss_.str(),
    });
}

TestLoggerChannel::TestLoggerChannel() noexcept {}

TestLoggerChannel& TestLoggerChannel::add(TestLogEntry entry) noexcept {
    entries_.emplace_back(entry);

    return *this;
}

TestLogEntryBuilder TestLoggerChannel::log(TestLoggerSeverity severity) noexcept {
    return TestLogEntryBuilder(this, severity);
}

std::list<TestLogEntry> TestLoggerChannel::entries() const noexcept {
    return std::list<TestLogEntry>{entries_};
}


void swap(TestLogEntryBuilder& first, TestLogEntryBuilder& other) {
    using namespace std;

    swap(first.ss_, other.ss_);
    swap(first.channel_, other.channel_);
    swap(first.timestamp_, other.timestamp_);
}

TestingContext::TestingContext(const TestDescriptor *test) noexcept 
    : test_(test) { }


std::list<TestLogEntry> TestingContext::log() const {
    return log_.entries();
}

TestLogEntryBuilder TestingContext::err() noexcept {
    return log_.log(TestLoggerSeverity::ERROR);
}

TestLogEntryBuilder TestingContext::warn() noexcept {
    return log_.log(TestLoggerSeverity::WARN);
}

TestLogEntryBuilder TestingContext::out() noexcept {
    return log_.log(TestLoggerSeverity::INFO);
}


TestDescriptor::TestDescriptor(
    TestCategory *category, 
    std::string name, 
    impl_type implementation
) noexcept : category_(category), name_(name), impl_(implementation) { 
    category->register_test(this);
}

const TestCategory* TestDescriptor::category() const {
    return category_;
}

std::string TestDescriptor::name() const {
    return category_->name + "/" + name_;
}

TestResult TestDescriptor::invoke() const noexcept {
    auto context = TestingContext{this};

    try {
        bool success = impl_(&context);
        return TestResult{
            .test = this,
            .passed = success,
            .log = context.log()
        };
    } catch(...) {
        return TestResult{
            .test = this,
            .passed = false,
            .log = context.log(),
            .exception = std::current_exception(),
        };
    }
}



void TestCategory::register_test(TestDescriptor *test) noexcept {
    tests_.emplace_back(test);
}

CategoryResult TestCategory::run_all() {
    std::list<TestResult> results;

    for(auto test : tests_) {
        auto result = test->invoke();
        results.emplace_back(result);
    }

    return CategoryResult{
        .category = this,
        .results = results
    };
}

std::string stringify_exception(std::exception_ptr ex) {
    try {
        std::rethrow_exception(ex);
    } catch(const TestFailure& e) {
        std::stringstream ss;
        ss << e.what() << '\n' << e.stacktrace;
        return ss.str();
    } catch(const std::exception& e) {
        return e.what();
    } catch(...) {
        return "Unknown exception type. (Caught with catch(...))";
    }
}

//==================
// expect
//==================

inline void throw_expect_failed(std::string message) {
    throw TestFailure{message};
}

inline void throw_expect_failed(std::optional<std::string> message, std::string defaultMessage) {
    throw TestFailure{message.value_or(defaultMessage)};
}

void expect::assert(bool condition, std::string message) {
    if(!condition) {
        throw_expect_failed(message);
    }
}
