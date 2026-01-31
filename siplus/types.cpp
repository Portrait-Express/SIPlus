#include "siplus/data.hxx"
#include "siplus/text/iterator.hxx"
#include "siplus/text/range_iterator.hxx"
#include "siplus/types/bool.hxx"
#include "siplus/types/string.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/float.hxx"
#include "siplus/types/array.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

namespace {

struct string_iterator_impl : text::Iterator {
    string_iterator_impl(std::string value) : value_(value) { }

    virtual bool more();
    virtual void next();
    virtual UnknownDataTypeContainer current();

private:
    std::string value_;
    long index_ = -1;
};

bool string_iterator_impl::more() {
    return index_ < (static_cast<long>(value_.size()) - 1);
}

void string_iterator_impl::next() {
    index_++;
}

UnknownDataTypeContainer string_iterator_impl::current() {
    return make_data<StringType>(std::string{value_[index_]});
}

} /* anonymous */

std::string IntegerType::name() const { return "long"; }
bool IntegerType::is_iterable(const UnknownDataTypeContainer& data) const { return false; }

std::string BoolType::name() const { return "boolean"; }
bool BoolType::is_iterable(const UnknownDataTypeContainer& data) const { return false; }

std::string FloatType::name() const { return "double"; }
bool FloatType::is_iterable(const UnknownDataTypeContainer& data) const { return false; }

std::string StringType::name() const { return "string"; }
bool StringType::is_iterable(const UnknownDataTypeContainer& data) const { return true; }
std::unique_ptr<text::Iterator> StringType::iterate(const UnknownDataTypeContainer& data) const {
    return std::make_unique<string_iterator_impl>(data.as<StringType>());
}

UnknownDataTypeContainer make_data(std::string str) {
    return SIPLUS_NAMESPACE::make_data<StringType>(str);
}

std::string ArrayType::name() const { return "array"; }
bool ArrayType::is_iterable(const UnknownDataTypeContainer& data) const { return true; }
std::unique_ptr<text::Iterator> ArrayType::iterate(const UnknownDataTypeContainer& data) const {
    using it_t = ArrayType::data_type::const_iterator;
    return std::make_unique<value_range_iterator<it_t, it_t>>(
        data.as<ArrayType>().begin(), data.as<ArrayType>().end()
    );
}


} /* types */
} /* SIPLUS_NAMESPACE */
