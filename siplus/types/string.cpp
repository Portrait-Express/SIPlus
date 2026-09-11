#include "siplus/context.hxx"
#include "common.hxx"

namespace SIPLUS_NAMESPACE {
namespace types {

namespace {

struct string_iterator_impl : Iterator {
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

struct StringAddableExtensionImpl : BinaryOperatorTypeExtensionImpl {
    StringAddableExtensionImpl() : BinaryOperatorTypeExtensionImpl(TypeInfo::Addable) {}

    bool can_handle(const UnknownDataTypeContainer &other) const override {
        return other.can_convert<StringType>();
    }

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer& thisValue, 
        const UnknownDataTypeContainer& other
    ) const override {
        auto strOther = other.convert<StringType>().as<StringType>();

        if(isLhs) {
            return make_data(thisValue.as<StringType>() + strOther);
        } else {
            return make_data(strOther + thisValue.as<StringType>());
        }
    }
};

struct StringComparableExtensionImpl : BinaryOperatorTypeExtensionImpl {
    StringComparableExtensionImpl() : BinaryOperatorTypeExtensionImpl(TypeInfo::Comparable) {}

    bool can_handle(const UnknownDataTypeContainer &other) const override {
        return other.is<StringType>();
    }

    UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer &thisValue, 
        const UnknownDataTypeContainer &other
    ) const override {
        return make_data<IntegerType>(thisValue.as<StringType>().compare(other.as<StringType>()));
    }
};

struct StringBoolConverter : UnaryOperatorTypeExtensionImpl {
    StringBoolConverter() : UnaryOperatorTypeExtensionImpl(make_conversion_descriptor<BoolType>()) {}

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override {
        return make_data<BoolType>(!thisValue.as<StringType>().empty());
    }
};

} /* anonymous */



const TypeInfoDescriptor *const StringType::descriptor = new TypeInfoDescriptor("string");

StringType::StringType() : TypeInfo(descriptor) {
    add_extension(new StringBoolConverter());

    add_extension(new StringAddableExtensionImpl());
    add_extension(new StringComparableExtensionImpl());
    add_extension(new NativeHashable<StringType>());
}

bool StringType::is_iterable(const UnknownDataTypeContainer& data) const { 
    return true; 
}

std::unique_ptr<Iterator> StringType::iterate(const UnknownDataTypeContainer& data) const {
    return std::make_unique<string_iterator_impl>(data.as<StringType>());
}


} /* types */
} /* SIPLUS_NAMESPACE */
