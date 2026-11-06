#include "siplus/context.hxx"
#include "siplus/util.hxx"

#include <mutex>
#include <shared_mutex>

namespace SIPLUS_NAMESPACE {

std::optional<UnknownDataTypeContainer> do_binary(
    const BinaryOperatorTypeExtension *descriptor,
    const UnknownDataTypeContainer& lhs, 
    const UnknownDataTypeContainer& rhs
) {
    const BinaryOperatorTypeExtensionImpl *lhsExtensionImpl;
    const BinaryOperatorTypeExtensionImpl *rhsExtensionImpl;

    lhsExtensionImpl = lhs.type->get_extension(descriptor);
    if(lhsExtensionImpl && lhsExtensionImpl->can_handle(rhs)) {
        return lhsExtensionImpl->invoke(true, lhs, rhs);
    }

    rhsExtensionImpl = rhs.type->get_extension(descriptor);
    if(rhsExtensionImpl && rhsExtensionImpl->can_handle(lhs)) {
        return rhsExtensionImpl->invoke(false, rhs, lhs);
    }

    return std::nullopt;
}

BinaryOperatorTypeExtension const *const TypeInfo::Addable = new BinaryOperatorTypeExtension("Addable");
BinaryOperatorTypeExtension const *const TypeInfo::Subtractable = new BinaryOperatorTypeExtension("Subtractable");
BinaryOperatorTypeExtension const *const TypeInfo::Multiplicable = new BinaryOperatorTypeExtension("Multiplicable");
BinaryOperatorTypeExtension const *const TypeInfo::Divisible = new BinaryOperatorTypeExtension("Divisible");
BinaryOperatorTypeExtension const *const TypeInfo::Comparable = new BinaryOperatorTypeExtension("Comparable");
BinaryOperatorTypeExtension const *const TypeInfo::Equatable = new BinaryOperatorTypeExtension("Equatable");
UnaryOperatorTypeExtension const *const TypeInfo::Hashable = new UnaryOperatorTypeExtension("Hashable");


std::shared_mutex conversionCacheLock_;
std::unordered_map<const TypeInfoDescriptor*, const UnaryOperatorTypeExtension*> conversionDescriptors_;

/**
 * @brief Get an existing conversion descriptor from conversionDescriptors_.
 *
 * @param[in] type The typeInfo to get a descriptor for.
 * @return The descriptor, or nullptr if it does not exist yet.
 */
const UnaryOperatorTypeExtension *get_conversion_descriptor(const TypeInfoDescriptor *descriptor) {
    auto it = conversionDescriptors_.find(descriptor);
    if(it != conversionDescriptors_.end()) {
        return it->second;
    }

    return nullptr;
}

__attribute__((no_sanitize_address))
const UnaryOperatorTypeExtension* make_conversion_descriptor(const TypeInfoDescriptor *descriptor) {
    const UnaryOperatorTypeExtension *ptr;
    std::string name = descriptor->name;

    {
        std::shared_lock<std::shared_mutex> shared_guard{conversionCacheLock_};

        ptr = get_conversion_descriptor(descriptor);
        if(ptr != nullptr) return ptr;
    }

    std::lock_guard<std::shared_mutex> guard{conversionCacheLock_};

    ptr = get_conversion_descriptor(descriptor);
    if(ptr != nullptr) return ptr;

    ptr = new UnaryOperatorTypeExtension{"Conversion[" + name + "]"};
    conversionDescriptors_[descriptor] = ptr;

    return ptr;
}

const BaseTypeExtensionImpl* TypeInfo::get_extension(const BaseTypeExtension *descriptor) const {
    auto it = extensions_.find(descriptor);

    if(it == extensions_.end()) {
        return nullptr;
    } else {
        return it->second.get();
    }
}

void TypeInfo::add_extension(const BaseTypeExtensionImpl *impl) {
    auto it = extensions_.find(impl->descriptor());

    if(it != extensions_.end()) {
        throw std::runtime_error{util::to_string(
            "Implementation for extension '", impl->descriptor()->name(), "' on type '",
            name(), "' already registered.")};
    }

    extensions_.emplace(impl->descriptor(), impl);
}

UnknownDataTypeContainer TypeInfo::access(const UnknownDataTypeContainer&, const std::string&) const {
    throw std::runtime_error{util::to_string(name(), " has no accessible properties")};
}

UnknownDataTypeContainer 
TypeInfo::index(
    std::shared_ptr<SIPlusParserContext> context, 
    UnknownDataTypeContainer& value, 
    UnknownDataTypeContainer& index
) const {
    if(index.can_convert<types::IntegerType>()) {
        auto index_ = index.convert<types::IntegerType>().as<types::IntegerType>();

        if(!value.is_iterable()) {
            throw std::runtime_error{util::to_string(
                "Tried to index position ", index_, " of a non-iterable type ", value.type->name()
            )};
        }

        auto i = 0;
        auto iterator = value.iterate();
        while(iterator->more()) {
            iterator->next();

            if(i == index_) return iterator->current();

            i++;
        }

        throw std::runtime_error{util::to_string(
            "Index out of bounds: index ", index_, " is out of range of list of size ", i
        )};
    } else if(index.can_convert<types::StringType>()) {
        auto property = index.convert<types::StringType>().as<types::StringType>();
        return value.access(property);
    } else {
        throw std::runtime_error{util::to_string(
            "Cannot use value of type '", index.type->name(), "' to index value of type '", value.type->name(), "'"
        )};
    }
}

std::unique_ptr<Iterator> TypeInfo::iterate(const UnknownDataTypeContainer&) const {
    throw std::runtime_error{util::to_string(name(), " is not iterable")};
}


inline void throw_cant_operate(
    const UnknownDataTypeContainer& lhs,
    const UnknownDataTypeContainer& rhs,
    std::string_view verb, 
    std::string_view adjective
) {
    throw std::runtime_error{util::to_string(
        "Cannot ", verb, " '", lhs.type->name(), "' and '", rhs.type->name(), 
        "'. Neither type is ", adjective, " with the other."
    )};
}

UnknownDataTypeContainer::UnknownDataTypeContainer() noexcept {
    _ref = new size_t(1);
    type = std::make_shared<types::NullType>();
}

UnknownDataTypeContainer::UnknownDataTypeContainer(std::shared_ptr<const TypeInfo> type, void *ptr) noexcept : UnknownDataTypeContainer() {
    this->type = type;
    this->ptr = ptr;
}

UnknownDataTypeContainer::UnknownDataTypeContainer(std::shared_ptr<const TypeInfo> type, void *ptr, deleter deleter) noexcept : UnknownDataTypeContainer(type, ptr) {
    deleter_ = deleter;
}

UnknownDataTypeContainer::UnknownDataTypeContainer(const UnknownDataTypeContainer& other) noexcept {
    type = other.type;
    ptr = other.ptr;
    deleter_ = other.deleter_;
    _ref = other._ref;
    
    *_ref = *_ref+1;
}
UnknownDataTypeContainer::UnknownDataTypeContainer(UnknownDataTypeContainer&& other) noexcept { 
    swap(*this, other); 
}

UnknownDataTypeContainer& UnknownDataTypeContainer::operator=(UnknownDataTypeContainer other) noexcept { 
    swap(*this, other); 
    return *this;
}

bool UnknownDataTypeContainer::operator==(const UnknownDataTypeContainer& other) const {
    auto result = do_binary(TypeInfo::Equatable, *this, other);
    if(result != std::nullopt) {
        if(!result->is<types::BoolType>()) {
            throw std::runtime_error{"Equatable did not return a boolean as expected."};
        }

        return result->as<types::BoolType>();
    }

    result = do_binary(TypeInfo::Comparable, *this, other);
    if(result != std::nullopt) {
        if(!result->is<types::IntegerType>()) {
            throw std::runtime_error{"Comparable did not return a number as expected."};
        }

        return result->as<types::IntegerType>() == 0;
    }

    throw_cant_operate(*this, other, "compare", "comparable");
    return false; // Above never returns, this will never be hit
}

UnknownDataTypeContainer UnknownDataTypeContainer::operator+(const UnknownDataTypeContainer& other) const {
    auto result = do_binary(TypeInfo::Addable, *this, other);

    if(result == std::nullopt) {
        throw_cant_operate(*this, other, "add", "addable");
    }

    return *result;
}

UnknownDataTypeContainer UnknownDataTypeContainer::operator-(const UnknownDataTypeContainer& other) const {
    auto result = do_binary(TypeInfo::Subtractable, *this, other);

    if(result == std::nullopt) {
        throw_cant_operate(*this, other, "subtract", "subtractable");
    }

    return *result;
}

UnknownDataTypeContainer UnknownDataTypeContainer::operator*(const UnknownDataTypeContainer& other) const {
    auto result = do_binary(TypeInfo::Multiplicable, *this, other);

    if(result == std::nullopt) {
        throw_cant_operate(*this, other, "multiply", "multiplicable");
    }

    return *result;
}

UnknownDataTypeContainer UnknownDataTypeContainer::operator/(const UnknownDataTypeContainer& other) const {
    auto result = do_binary(TypeInfo::Divisible, *this, other);

    if(result == std::nullopt) {
        throw_cant_operate(*this, other, "divide", "divisible");
    }

    return *result;
}

UnknownDataTypeContainer UnknownDataTypeContainer::operator||(const UnknownDataTypeContainer& other) const {
    return make_data((bool)*this || (bool)other);
}

UnknownDataTypeContainer UnknownDataTypeContainer::operator&&(const UnknownDataTypeContainer& other) const {
    return make_data((bool)*this && (bool)other);
}

int64_t UnknownDataTypeContainer::compare(const UnknownDataTypeContainer& other) const {
    auto result = do_binary(TypeInfo::Comparable, *this, other);

    if(result == std::nullopt) {
        throw_cant_operate(*this, other, "compare", "comparable");
    }

    if(!result->is<types::IntegerType>()) {
        throw std::runtime_error{"Comparable implementation did not return IntegerType."};
    }

    return result->as<types::IntegerType>();
}

UnknownDataTypeContainer UnknownDataTypeContainer::access(const std::string& name) {
    return type->access(*this, name);
}

UnknownDataTypeContainer UnknownDataTypeContainer::index(
    std::shared_ptr<SIPlusParserContext> context, 
    UnknownDataTypeContainer& index
) {
    return type->index(context, *this, index);
}

std::unique_ptr<Iterator> UnknownDataTypeContainer::iterate() const {
    return type->iterate(*this);
}

bool UnknownDataTypeContainer::is_iterable() const {
    return type->is_iterable(*this);
}

UnknownDataTypeContainer::~UnknownDataTypeContainer() {
    //_ref can be nullptr if this object is moved from
    if(_ref != nullptr) {
        if(*_ref == 1) {
            delete _ref;

            if(deleter_) {
                deleter_(ptr);
            }
        } else {
            *_ref = *_ref - 1;
        }
    }
}


}
