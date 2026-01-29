#include "siplus/data.h"
#include "siplus/text/iterator.h"
#include "siplus/types/bool.h"
#include "siplus/types/string.h"
#include "siplus/types/integer.h"
#include "siplus/types/float.h"
#include "siplus/types/array.h"
#include "siplus/vector_iterator.h"

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
bool IntegerType::is_iterable() const { return false; }

std::string BoolType::name() const { return "boolean"; }
bool BoolType::is_iterable() const { return false; }

std::string FloatType::name() const { return "double"; }
bool FloatType::is_iterable() const { return false; }

std::string StringType::name() const { return "string"; }
bool StringType::is_iterable() const { return true; }
std::unique_ptr<text::Iterator> StringType::iterate(void *data) const {
    return std::make_unique<string_iterator_impl>(*reinterpret_cast<std::string*>(data));
}

UnknownDataTypeContainer make_data(std::string str) {
    return SIPLUS_NAMESPACE::make_data<StringType>(str);
}

std::string ArrayType::name() const { return "array"; }
bool ArrayType::is_iterable() const { return true; }
std::unique_ptr<text::Iterator> ArrayType::iterate(void *data) const {
    return std::make_unique<vector_iterator<UnknownDataTypeContainer>>(
        reinterpret_cast<ArrayType::data_type*>(data)->begin(),
        reinterpret_cast<ArrayType::data_type*>(data)->end()
    );
}


} /* types */
} /* SIPLUS_NAMESPACE */
