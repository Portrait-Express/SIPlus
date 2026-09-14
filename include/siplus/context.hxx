#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_
#define INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_

#include <concepts>
#include <functional>
#include <list>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>

#include "siplus/config.h"
#include "siplus/util.hxx"

#define SIPLUS_DEFINE_TYPE_INFO(type_, type_info) \
    template<> struct type_info_for<type_> { using type = type_info; };

namespace SIPLUS_NAMESPACE {

class SIPLUS_EXPORT TypeInfo; 
struct SIPLUS_EXPORT UnknownDataTypeContainer; 
struct SIPLUS_EXPORT InvocationContext; 
class SIPLUS_EXPORT SIPlusParserContext;



/**
 * @brief Iterator is used to provide functionality for lists of objects.
 *
 * The standard loop used to interact with an Iterator goes more()->next()->current():
 * 
 * More is called to check if the first item is available, next() is called to move 
 * to that first item, and current is called to access it(). The loop continues for 
 * the second item and so on... Calling next() if more() is false is UB.
 *
 * @code
 * while(iterator.more()) {
 *     iterator.next();
 *     auto value = iterator.current();
 *     // Use value...
 * }
 * @endcode
 */
class SIPLUS_EXPORT Iterator {
public:
    /**
     * @brief Check if the next item is available
     *
     * @return True if next() can be called
     */
    virtual bool more() = 0;

    /**
     * @brief Move to the next item. Do not call this if more() is false.
     */
    virtual void next() = 0;

    /**
     * @brief Get the item at the current iterator position
     *
     * @return The data
     */
    virtual UnknownDataTypeContainer current() = 0;

    virtual ~Iterator() = default;
};


class TypeInfoDescriptor {
public:
    TypeInfoDescriptor(std::string name) : name(name) {}

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const TypeInfoDescriptor *descriptor) {
        return operator<<(out, *descriptor);
    }

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const TypeInfoDescriptor& descriptor) {
        out << descriptor.name;
        return out;
    }

    const std::string name;
};

template<typename T>
struct type_info_for { };

template<typename T>
using type_info_for_t = type_info_for<std::remove_cvref_t<std::decay_t<T>>>::type;

template<typename _>
concept True = true;

template<typename Type>
concept type_descriptor = std::same_as<Type, const TypeInfoDescriptor*>;

template<typename Type>
concept simple_value_retrievable_type = requires(const Type a) {
    Type::descriptor;
    requires std::same_as<decltype(Type::descriptor), const TypeInfoDescriptor *const>;

    { Type{} } -> std::same_as<Type>;
    { std::declval<typename Type::data_type>() } -> True;
} && std::is_base_of_v<TypeInfo, Type>;


/**
 * struct BaseTypeExtension - A type which represents an extension to a TypeInfo.
 * Each Extension type will generally be constructed once and a pointer will be 
 * stored in a static location, and used to refer to implementations for this 
 * extension. This pointer is referred to as the "descriptor". For examples, 
 * look at the arithmetic functions in the STL, or the comparison functions (
 * e.g. 'cmp', 'add', etc).
 */
struct BaseTypeExtension {
    BaseTypeExtension(std::string name) : name_(name) {}

    std::string name() const {
        return name_;
    }

    virtual ~BaseTypeExtension() = default;

private:
    const std::string name_;
};

struct BaseTypeExtensionImpl { 
    BaseTypeExtensionImpl(const BaseTypeExtension *descriptor) : descriptor_(descriptor) {}

    const BaseTypeExtension *descriptor() const { 
        return descriptor_; 
    }

    virtual ~BaseTypeExtensionImpl() = default;

private:
    const BaseTypeExtension *const descriptor_;
};

template<typename Ret, typename ...Args> 
struct TypeExtension : BaseTypeExtension {
    using return_type = Ret;
    using args_type = std::tuple<Args...>;

    TypeExtension(std::string name) : BaseTypeExtension(name) {}
};

/**
 * struct TypeExtensionImpl - Type that will implement a TypeExtension's functionality
 *
 * @tparam Ret The returned value of the extension
 * @tparam Args The arguments to the TypeExtension
 */
template<typename Ret, typename ...Args>
struct TypeExtensionImpl : BaseTypeExtensionImpl {
    TypeExtensionImpl(const TypeExtension<Ret, Args...> *descriptor) : BaseTypeExtensionImpl(descriptor) {}

    virtual Ret invoke(Args... args) const = 0;
};


template<typename T, typename Ret, typename ...Args>
concept is_type_extension = requires() {
    std::is_base_of_v<T, TypeExtension<Ret, Args...>>;
};

template<typename T, typename Ret, typename ...Args>
concept is_simple_type_extension = requires(std::string name) {
    requires is_type_extension<T, Ret, Args...>;
    { new T{name} } -> std::same_as<T>;
};


struct UnaryOperatorTypeExtensionImpl;

/**
 * struct UnaryOperatorTypeExtension - Base Type Extension Type for a unary
 * operator, such as `not` or conversion operators
 */
struct UnaryOperatorTypeExtension : TypeExtension<
    UnknownDataTypeContainer, 
    const UnknownDataTypeContainer&
> {
    using impl_type = UnaryOperatorTypeExtensionImpl;
    UnaryOperatorTypeExtension(std::string name) : TypeExtension(name) {}
};

struct UnaryOperatorTypeExtensionImpl : TypeExtensionImpl<
    UnknownDataTypeContainer, 
    const UnknownDataTypeContainer&
> {
    UnaryOperatorTypeExtensionImpl(const UnaryOperatorTypeExtension *descriptor) : TypeExtensionImpl(descriptor) {}

    /**
     * @brief Perform the operation.
     *
     * @param[in] thisValue "This" value, this will always be the value with 
     * the TypeInfo that this extension is registered on.
     *
     * @return Result of the operation
     */
    virtual UnknownDataTypeContainer invoke(
        const UnknownDataTypeContainer& thisValue
    ) const override = 0;
};



struct BinaryOperatorTypeExtensionImpl;

/**
 * struct BinaryOperatorTypeExtension - Base Type Extension Type for a binary 
 * operator, such as `add` or `and`
 */
struct BinaryOperatorTypeExtension : TypeExtension<
    UnknownDataTypeContainer, 
    bool, const UnknownDataTypeContainer&, const UnknownDataTypeContainer&
> {
    using impl_type = BinaryOperatorTypeExtensionImpl;
    BinaryOperatorTypeExtension(std::string name) : TypeExtension(name) {}
};

/**
 * struct BinaryOperatorTypeExtensionImpl - Implementation base class for a 
 * BinaryOperatorTypeExtension. All extensions for a BinaryOperatorTypeExtension
 * must derive from this class, and implement it's members.
 */
struct BinaryOperatorTypeExtensionImpl
        : TypeExtensionImpl<UnknownDataTypeContainer, bool, const UnknownDataTypeContainer&, const UnknownDataTypeContainer&> {
    BinaryOperatorTypeExtensionImpl(const BinaryOperatorTypeExtension *descriptor) : TypeExtensionImpl(descriptor) {}

    /**
     * @brief This will be called prior to invoke() with the other value to 
     * determine if this extension impelmentation is usable with the other 
     * binary operation value. If your implementation can implicitly convert 
     * from the other type, or use it directly, return true.
     *
     * @param[in] other The other value in the operation
     * @return true if this implementation can handle the operation. `invoke` 
     * may be called immediately after this if true.
     */
    virtual bool can_handle(const UnknownDataTypeContainer& other) const = 0;

    /**
     * @brief Perform the operation on the two values.
     *
     * @param[in] isLhs `true` if `thisValue` was the lhs of the 
     * operation, `false` if `other` is the lhs.
     * @param[in] thisValue "This" value, this will always be the value with 
     * the TypeInfo that this extension is registered on.
     * @param[in] other The other value in the operation. Same value as was 
     * passed to can_handle.
     *
     * @return Result of the operation
     */
    virtual UnknownDataTypeContainer invoke(
        bool isLhs, 
        const UnknownDataTypeContainer& thisValue, 
        const UnknownDataTypeContainer& other
    ) const override = 0;
};

/**
 * @brief Try to execute a binary operation on two values.
 *
 * @param[in] descriptor The binary operation to execute.
 * @param[in] lhs The left-hand side of the operation
 * @param[in] rhs The right-hand side of the operation
 * @returns Will be std::nullopt if no valid implementation for the descriptor 
 * was found, otherwise will contain the result of the operation.
 */
std::optional<UnknownDataTypeContainer> do_binary(
    const BinaryOperatorTypeExtension *descriptor,
    const UnknownDataTypeContainer& lhs, 
    const UnknownDataTypeContainer& rhs
);

/**
 * @brief Get a conversion descriptor for converting to a specified type.
 * Subsequent calls with the same type will (obviously) return the same pointer.
 *
 * @param[in] typeInfo The type to convert to
 * @return An extension descriptor
 */
const UnaryOperatorTypeExtension* make_conversion_descriptor(const TypeInfoDescriptor *type);

template<simple_value_retrievable_type T>
const UnaryOperatorTypeExtension* make_conversion_descriptor() {
    return make_conversion_descriptor(T::descriptor);
}





/**
 * @brief Type information in order to properly handle dynamically typed input data.
 */
class SIPLUS_EXPORT TypeInfo : public std::enable_shared_from_this<TypeInfo> {
public:
    TypeInfo(const TypeInfoDescriptor* descriptor) : descriptor_(descriptor) { }

    /** Descriptor for 'Addable' */
    static BinaryOperatorTypeExtension const *const Addable;

    /** Descriptor for 'Subtractable' */
    static BinaryOperatorTypeExtension const *const Subtractable;

    /** Descriptor for 'Multiplicable' */
    static BinaryOperatorTypeExtension const *const Multiplicable;

    /** Descriptor for 'Divisible' */
    static BinaryOperatorTypeExtension const *const Divisible;

    /** 
     * Descriptor for 'Comparable'. Implementations for Comparable should 
     * always return IntegerType.
     *
     * Implementing this also implements Equatable.
     */
    static BinaryOperatorTypeExtension const *const Comparable;

    /** Descriptor for 'Equatable' */
    static BinaryOperatorTypeExtension const *const Equatable;

    /** 
     * Descriptor for 'Hashable' 
     *
     * If not implemented, the data pointer will be used as the hash value.
     */
    static UnaryOperatorTypeExtension const *const Hashable;

    /**
     * @brief Returns the name of this type. Type equality is determined by 
     * comparing names, so please ensure that your TypeInfo uses a name unique 
     * to any other. Type names are also cached globally in some instances, so 
     * it should never change.
     *
     * @return The name of this type.
     */
    virtual std::string name() const {
        return descriptor_->name;
    }

    virtual const TypeInfoDescriptor* descriptor() const {
        return descriptor_;
    }

    /**
     * @brief Returns whether or not this type is iterable.
     *
     * @return True if the type is iterable
     */
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const {
        return false;
    }

    /**
     * @brief Access a property on this object.
     *
     * @param[in] ptr A void* to the object.
     * @param[in] name The name of the property to access
     * @return The data held at that property. Throw if the property does not 
     * exist.
     */
    virtual UnknownDataTypeContainer access(const UnknownDataTypeContainer& data, const std::string& name) const;

    /**
     * @brief Function used to access a property through indexer.
     * @note Default implementation tries to get index as an array, or tries 
     * to get the property name.
     * @example
     * .["id"]
     * .[1]
     *
     * @param[in] index The value passed to the braces.
     * @return The data at that index. Throws if property does not exist.
     */
    UnknownDataTypeContainer 
    virtual index(std::shared_ptr<SIPlusParserContext> context, 
          UnknownDataTypeContainer& value,
          UnknownDataTypeContainer& index) const;

    /**
     * @brief Create an iterator to iterate over the object.
     *
     * @param[in] data A void* to the object
     * @return A new iterator for this object. Throws if `is_iterable()` 
     * is false.
     */
    virtual std::unique_ptr<Iterator> iterate(const UnknownDataTypeContainer& data) const;

    const BaseTypeExtensionImpl* get_extension(const BaseTypeExtension *descriptor) const;

    template<typename T, typename Impl = T::impl_type>
    const Impl* get_extension(const T *descriptor) const {
        auto impl = get_extension(static_cast<const BaseTypeExtension*>(descriptor));
        if(impl == nullptr) return nullptr;

        const Impl* ptr;
        if((ptr = dynamic_cast<const Impl*>(impl)) == nullptr) {
            throw std::runtime_error{"Invalid base class for found for extension " + descriptor->name()};
        } else {
            return ptr;
        }
    }

    template<typename Ret, typename ...Args>
    const TypeExtensionImpl<Ret, Args...>* get_extension(const TypeExtension<Ret, Args...> *descriptor) const {
        return get_extension<TypeExtension<Ret, Args...>, TypeExtensionImpl<Ret, Args...>>(descriptor);
    }

    bool operator==(const TypeInfo& other) const {
        return descriptor() == other.descriptor();
    }

    template<simple_value_retrievable_type T>
    bool is() const noexcept {
        return T::descriptor == descriptor_;
    }

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const TypeInfo& info) {
        out << info.name();
        return out;
    }

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const std::shared_ptr<TypeInfo> info) {
        out << info->name();
        return out;
    }

    virtual ~TypeInfo() = default;

protected:
    void add_extension(const BaseTypeExtensionImpl *impl);

private:
    const TypeInfoDescriptor *const descriptor_;
    std::unordered_map<const BaseTypeExtension*, std::unique_ptr<const BaseTypeExtensionImpl>> extensions_;
};


/** 
 * @brief namespace types contains the default types available in SIPlus
 */
namespace types {

/**
 * struct NullType - This is the default type of an UnknownDataTypeContainer. Used to 
 * represent an empty container.
 *
 * Extensions:
 * - Converter[string]
 * - Equatable
 */
struct SIPLUS_EXPORT NullType : public TypeInfo {
    using data_type = void;
    static const TypeInfoDescriptor *const descriptor;

    NullType();

    virtual UnknownDataTypeContainer access(const UnknownDataTypeContainer& data, const std::string& name) const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};




/**
 * struct BoolType - This is the tyoe for boolean values.
 *
 * Extensions: 
 * - Converter[string]
 * - Converter[long]
 * - Equatable
 */
struct SIPLUS_EXPORT BoolType : public TypeInfo {
    using data_type = bool;
    static const TypeInfoDescriptor *const descriptor;

    BoolType();

    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};



/**
 * struct FloatType - Type for floating point numbers
 *
 * Extensions:
 * - Converter[string]
 * - Converter[bool]
 * - Converter[long]
 * - Addable - with self, or IntegerType
 * - Subtractable - with self, or IntegerType
 * - Muiltiplicable - with self, or IntegerType
 * - Divisible - with self, or IntegerType
 * - Comparable - with self, or IntegerType
 */
struct SIPLUS_EXPORT FloatType : public TypeInfo {
    using data_type = double;
    static const TypeInfoDescriptor *const descriptor;

    FloatType();

    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};




/**
 * struct IntegerType - Type for floating point numbers
 *
 * Extensions:
 * - Converter[string]
 * - Converter[bool]
 * - Converter[double]
 * - Addable - with self, or FloatType
 * - Subtractable - with self, or FloatType
 * - Muiltiplicable - with self, or FloatType
 * - Divisible - with self, or FloatType
 * - Comparable - with self, or FloatType
 */
struct SIPLUS_EXPORT IntegerType : public TypeInfo {
    using data_type = int64_t;
    static const TypeInfoDescriptor *const descriptor;

    IntegerType();

    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};




/**
 * struct StringType - TypeInfo for strings.
 *
 * Extensions:
 * - Converter[bool]
 * - Addable
 * - Comparable
 */
struct SIPLUS_EXPORT StringType : public TypeInfo {
    using data_type = std::string;
    static const TypeInfoDescriptor *const descriptor;

    StringType();

    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;

    virtual std::unique_ptr<Iterator> iterate(const UnknownDataTypeContainer& data) const override;
};




/**
 * struct ArrayType - TypeInfo for arrays.
 *
 * Extensions:
 * - Converter[string]
 * - Addable
 * - Equatable - Checks Equatable on each element with another iterable type.
 */
struct SIPLUS_EXPORT ArrayType : public TypeInfo {
    using data_type = std::vector<UnknownDataTypeContainer>;
    static const TypeInfoDescriptor *const descriptor;

    ArrayType();

    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;

    virtual UnknownDataTypeContainer index(
        std::shared_ptr<SIPlusParserContext> context, 
        UnknownDataTypeContainer &value, 
        UnknownDataTypeContainer &index
    ) const override;

    virtual std::unique_ptr<Iterator> iterate(const UnknownDataTypeContainer& data) const override;
};


} /* types */





/**
 * struct UnknownDataTypeContainer - Container to hold data that will be used by a template.
 * The data should be heap-allocated, so that its lifetime does not end while still in use 
 * by a container. 
 *
 * Internally it stores the data as a void*, alongside a TypeInfo object for information on 
 * how to use said pointer. 
 *
 * If your TypeInfo provides MyType::data_type, then you may use
 * as<type> on this object to cast the void* to MyType::data_type. Remember, as() does no 
 * type-checking, so double check before using as().
 *
 * The container may be copied and moved at will, but only one copy of the data exists.
 * The container has a reference counter to invoke the deleter.
 */
struct SIPLUS_EXPORT UnknownDataTypeContainer {
    using deleter = std::function<void (void*)>; 

    /**
     * Get the type of this data container. DO NOT ASSIGN TO THIS UNLESS YOU KNOW WHAT YOU ARE DOING.
     */
    std::shared_ptr<const TypeInfo> type;
    //This probably should not be an exposed property, but it is. Maybe we should change it to type()
    

    /**
     * The void* to the data.
     */
    void *ptr = 0;


    /**
     * @brief Construct an empty UnknownDataTypeContainer. Use this to create null.
     */
    UnknownDataTypeContainer() noexcept;

    /**
     * @brief Create a container with a type, and data, but no deleter. If you don't 
     * delete the void* yourself, it WILL leak.
     *
     * @param[in] type The type of the object
     * @param[in] ptr The void* to the data
     */
    UnknownDataTypeContainer(std::shared_ptr<const TypeInfo> type, void *ptr) noexcept;

    /**
     * @brief Create a container with a type, data, and a deleter. The deleter 
     * will be invoked once the reference count reaches 0
     *
     * @param[in] type The type of the object
     * @param[in] ptr The void* to the data
     * @param[in] deleter The deleter callback to invoke on deletion
     */
    UnknownDataTypeContainer(std::shared_ptr<const TypeInfo> type, void *ptr, deleter deleter) noexcept;

    /** @brief Copy constructor. Increments reference counter by one */
    UnknownDataTypeContainer(const UnknownDataTypeContainer& other) noexcept;

    /** @brief Move constructor. Swaps the data in this with `other` */
    UnknownDataTypeContainer(UnknownDataTypeContainer&& other) noexcept;

    /** @brief Assignment operator. */
    UnknownDataTypeContainer& operator=(UnknownDataTypeContainer other) noexcept;

    /** 
     * @brief Convert this container to a boolean value. If no conversion extension
     * is registered for this type, simply return if the value is not null.
     */
    explicit operator bool() const { 
        if(can_convert<types::BoolType>()) {
            return convert<types::BoolType>().as<types::BoolType>();
        } else {
            return !is<types::NullType>();
        }
    }

    /**
     * @brief Check if two DataContainers are equal. This will use Comparable, 
     * or Equatable if implemented, or will fall back to comparing type and ptr 
     * if neither is implemented.
     *
     * @param[in] other The other value
     * @return `true` if the values in the containers are equal.
     */
    bool operator==(const UnknownDataTypeContainer& other) const;

    /**
     * @brief Compare the values in two data containers. This will throw if neither
     * of these is 'Comparable' with the other.
     *
     * @param[in] other The other value
     * @return If this is less than other, via Comparable.
     */
    bool operator<(const UnknownDataTypeContainer& other) const {
        return compare(other) < 0;
    }

    /**
     * @brief Compare the values in two data containers. This will throw if neither
     * of these is 'Comparable' with the other.
     *
     * @param[in] other The other value
     * @return If this is less than or equal to other, via Comparable.
     */
    bool operator<=(const UnknownDataTypeContainer& other) const {
        return compare(other) <= 0;
    }

    /**
     * @brief Compare the values in two data containers. This will throw if neither
     * of these is 'Comparable' with the other.
     *
     * @param[in] other The other value
     * @return If this is greater than other, via Comparable.
     */
    bool operator>(const UnknownDataTypeContainer& other) const {
        return compare(other) > 0;
    }

    /**
     * @brief Compare the values in two data containers. This will throw if neither
     * of these is 'Comparable' with the other.
     *
     * @param[in] other The other value
     * @return If this is greater than or equal to other, via Comparable.
     */
    bool operator>=(const UnknownDataTypeContainer& other) const {
        return compare(other) >= 0;
    }

    /**
     * @brief Sum the values in two data containers. This will throw if neither
     * of these is 'Addable' with the other.
     *
     * @param[in] other The other value
     * @return The sum of the values.
     */
    UnknownDataTypeContainer operator+(const UnknownDataTypeContainer& other) const;

    /**
     * @brief Subtract the values in two data containers. This will throw if neither
     * of these is 'Subtractable' with the other.
     *
     * @param[in] other The other value
     * @return The difference of the values.
     */
    UnknownDataTypeContainer operator-(const UnknownDataTypeContainer& other) const;

    /**
     * @brief Mutliply the values in two data containers. This will throw if neither
     * of these is 'Multiplicable' with the other.
     *
     * @param[in] other The other value
     * @return The product of the values.
     */
    UnknownDataTypeContainer operator*(const UnknownDataTypeContainer& other) const;

    /**
     * @brief Divide the values in two data containers. This will throw if neither
     * of these is 'Divisible' with the other.
     *
     * @param[in] other The other value
     * @return The quotient of the values.
     */
    UnknownDataTypeContainer operator/(const UnknownDataTypeContainer& other) const;

    /**
     * @brief Divide the values in two data containers. This will throw if neither
     * of these is 'Divisible' with the other.
     *
     * @param[in] other The other value
     * @return The quotient of the values.
     */
    UnknownDataTypeContainer operator||(const UnknownDataTypeContainer& other) const;

    /**
     * @brief AND the value with the other. 
     *
     * @param[in] other The other value
     * @return The quotient of the values.
     */
    UnknownDataTypeContainer operator&&(const UnknownDataTypeContainer& other) const;

/** These are useful if we can make it work, but make_data is not available here.
 * We can use these later if we are able 

#define _TEMPLATE_OPERATOR_FOR(operator) template<typename T> \
bool operator(T&& value) { \
    return this->operator(make_data(std::forward<T>(value))); \
}

    _TEMPLATE_OPERATOR_FOR(operator<);
    _TEMPLATE_OPERATOR_FOR(operator<=);
    _TEMPLATE_OPERATOR_FOR(operator>);
    _TEMPLATE_OPERATOR_FOR(operator>=);
    _TEMPLATE_OPERATOR_FOR(operator==);
    _TEMPLATE_OPERATOR_FOR(operator+);
    _TEMPLATE_OPERATOR_FOR(operator-);
    _TEMPLATE_OPERATOR_FOR(operator*);
    _TEMPLATE_OPERATOR_FOR(operator/);
#undef _TEMPLATE_OPERATOR_FOR

*/

    /**
     * @brief Compare this data container with another. Will throw if neither 
     * type is 'Comparable' with the other.
     *
     * @param[in] other The other value
     * @return Returns <0 if this is less than other, 0 if equal, or >0 if 
     * greater than other.
     */
    int64_t compare(const UnknownDataTypeContainer& other) const;

    /**
     * @brief Checks if this object is an instance of the type.
     *
     * @tparam T The type to check if this object is an instance of.
     * @return True if this object is an instance of T.
     */
    template<simple_value_retrievable_type T>
    bool is() const {
        return is(T::descriptor);
    }

    /**
     * @brief Checks if this object is an instance of the type.
     *
     * @tparam T The type to check if this object is an instance of.
     * @return True if this object is an instance of T.
     */
    bool is(const TypeInfoDescriptor *type) const {
        return this->type->descriptor() == type;
    }

    /**
     * @brief Casts this object to a T::data_type&. This does NO type checking. Check is<> first.
     *
     * @tparam simple_value_retrievable_type The type to cast to
     */
    template<simple_value_retrievable_type T>
    T::data_type& as() const {
        return *reinterpret_cast<T::data_type*>(ptr);
    }

    /**
     * @brief Swap the values in this container, and another container.
     *
     * @param[in] self This container.
     * @param[in] other The container to swap into this
     * @return [TODO:description]
     */
    friend void swap(UnknownDataTypeContainer& self, UnknownDataTypeContainer& other) {
        using std::swap;

        swap(self.type, other.type);
        swap(self.ptr, other.ptr);
        swap(self.deleter_, other.deleter_);
        swap(self._ref, other._ref);
    }

    /**
     * @brief Access a property on this object. Delegates to TypeInfo.
     *
     * @param[in] name The name of the property to access.
     * @return The data at that property. Throws if property does not exist.
     */
    UnknownDataTypeContainer access(const std::string& name);

    /**
     * @brief Index this object. Delegates to TypeInfo.
     *
     * @param[in] name The name of the property to access.
     * @return The data at that property. Throws if property does not exist.
     */
    UnknownDataTypeContainer 
    index(std::shared_ptr<SIPlusParserContext> context, 
          UnknownDataTypeContainer& index);

    /**
     * @brief Create an iterator for this object. This will throw if 
     * is_iterable() is false. Delegates to TypeInfo.
     *
     * @return A new iterator
     */
    std::unique_ptr<Iterator> iterate() const;

    /**
     * @brief See TypeInfo::is_iterable
     *
     * @return True if this object is iterable.
     */
    bool is_iterable() const;

    /**
     * @brief Check if there is a converter implementation to convert to a specific type.
     * Also returns true if `this->is<T>()`.
     *
     * @tparam T The destination TypeInfo.
     * @return `true` if this type can be converted.
     */
    bool can_convert(const TypeInfoDescriptor *to) const {
        if(type->descriptor() == to) {
            return true;
        }

        auto descriptor = make_conversion_descriptor(to);
        return type->get_extension(descriptor) != nullptr;
    }

    /**
     * @brief Check if there is a converter implementation to convert to a specific type.
     * Also returns true if `this->is<T>()`.
     *
     * @tparam T The destination TypeInfo.
     * @return `true` if this type can be converted.
     */
    template<simple_value_retrievable_type T>
    bool can_convert() const {
        if(is<T>()) return true;

        auto descriptor = make_conversion_descriptor<T>();
        return type->get_extension(descriptor) != nullptr;
    }

    /**
     * @brief Convert this object to another data type.
     *
     * @tparam T The desired TypeInfo
     * @return A value of type T
     */
    UnknownDataTypeContainer convert(const TypeInfoDescriptor *type) const {
        if(is(type)) return *this;

        auto descriptor = make_conversion_descriptor(type);
        auto converterImpl = this->type->get_extension(descriptor);

        if(converterImpl == nullptr) {
            throw std::runtime_error{util::to_string(
                "No converter available to convert from '", this->type, 
                "' to '", type, "'."
            )};
        }

        return converterImpl->invoke(*this);
    }

    /**
     * @brief Convert this object to another data type.
     *
     * @tparam T The desired TypeInfo
     * @return A value of type T
     */
    template<simple_value_retrievable_type T>
    UnknownDataTypeContainer convert() const {
        if(is<T>()) return *this;

        auto descriptor = make_conversion_descriptor<T>();
        auto converterImpl = type->get_extension(descriptor);

        if(converterImpl == nullptr) {
            auto toType = std::make_shared<T>();
            throw std::runtime_error{util::to_string(
                "No converter available to convert from '", type->name(), 
                "' to '", toType->name(), "'."
            )};
        }

        return converterImpl->invoke(*this);
    }

    template<typename T>
    void assert_type(std::string name) {
        if(!is<T>()) {
            T type;
            throw std::runtime_error{util::to_string(
                "Expected '", name, "' to be instance of '", type.name(), "'. ",
                "Received value of type '", this->type->name(), "' instead."
            )};
        }
    }

    template<typename OStream>
    friend OStream& operator<<(OStream& out, const UnknownDataTypeContainer& data) {
        if(!data.can_convert<types::StringType>()) {
            out << "{data " << data.type->name() << '}';
        } else {
            out << data.convert<types::StringType>().as<types::StringType>();
        }

        return out;
    }

    ~UnknownDataTypeContainer();

private:
    size_t *_ref = nullptr;
    deleter deleter_;
};



SIPLUS_DEFINE_TYPE_INFO(types::ArrayType::data_type, types::ArrayType);
SIPLUS_DEFINE_TYPE_INFO(types::BoolType::data_type, types::BoolType);
SIPLUS_DEFINE_TYPE_INFO(float, types::FloatType);
SIPLUS_DEFINE_TYPE_INFO(types::FloatType::data_type, types::FloatType);
SIPLUS_DEFINE_TYPE_INFO(char, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(short int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(long int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(long long int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned char, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned short int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned long int, types::IntegerType);
SIPLUS_DEFINE_TYPE_INFO(unsigned long long int, types::IntegerType); //This one can lead to data loss...
//Need to add both since const in const char* is not a top level const
SIPLUS_DEFINE_TYPE_INFO(const char*, types::StringType);
SIPLUS_DEFINE_TYPE_INFO(char*, types::StringType);
SIPLUS_DEFINE_TYPE_INFO(types::StringType::data_type, types::StringType);


/**
 * @brief Create an UnknownDataTypeContainer from a pointer to an object. By 
 * default this "acquires" the pointer passed in, meaning the container will 
 * `delete` the pointer when its lifetime is over.
 *
 * @tparam simple_value_retrievable_type The type of the container
 * @param[in] data The pointer to the data
 * @param[in] acquire If true, this will `delete` the pointer 
 * after the container's lifetime is over. Default: true
 * @return A new data container
 */
template<simple_value_retrievable_type T>
UnknownDataTypeContainer make_data(typename T::data_type *data, bool acquire = true) {
    if(acquire) {
        return UnknownDataTypeContainer{
            std::make_shared<T>(),
            reinterpret_cast<void*>(data),
            [data](void*){ delete data; }
        };
    } else {
        return UnknownDataTypeContainer{
            std::make_shared<T>(),
            reinterpret_cast<void*>(data)
        };
    }
}

/**
 * @brief Create an UnknownDataTypeContainer from an object. This will 
 * copy-construct the object to new storage, and manage that storage.
 *
 * @tparam simple_value_retrievable_type The type of the container
 * @param[in] data The data object
 * @return A new data container
 */
template<simple_value_retrievable_type T>
UnknownDataTypeContainer make_data(const typename T::data_type& data) {
    auto ptr = new typename T::data_type{data};
    return UnknownDataTypeContainer{
        std::make_shared<T>(),
        reinterpret_cast<void*>(ptr),
        [ptr](void*){ delete ptr; }
    };
}

/**
 * @brief Create an UnknownDataTypeContainer from an object. This will 
 * copy-construct the object to new storage, and manage that storage.
 *
 * @tparam simple_value_retrievable_type The type of the container
 * @param[in] data The data object
 * @return A new data container
 */
template<typename T>
UnknownDataTypeContainer make_data(const T& data) {
    return make_data<type_info_for_t<T>>(data);
}

/** @brief Identity overload. Returns parameter. */
inline UnknownDataTypeContainer make_data(const UnknownDataTypeContainer& data) {
    return data;
}

inline UnknownDataTypeContainer make_data(std::string str) {
    return SIPLUS_NAMESPACE::make_data<types::StringType>(str);
}


/**
 * @brief Special overload for creating ArrayType data.
 *
 * @param[in] vec Data array
 * @return ArrayType data container
 */
template<typename T>
UnknownDataTypeContainer make_data(const std::vector<T>& vec) {
    std::vector<UnknownDataTypeContainer> array;
    array.reserve(vec.size());

    for(auto it = vec.begin(); it != vec.end(); it++) {
        array.push_back(make_data(*it));
    }

    return make_data<types::ArrayType>(array);
}



/**
 * @brief A ValueRetriever is an object that supplies a value on invocation. This is used
 * to represent Expression templates.
 */
class SIPLUS_EXPORT ValueRetriever {
public:
    /**
     * @brief Override this to provide a value on invocation.
     *
     * @param[in] value The InvocationContext
     * @return The result of your retriever
     */
    virtual UnknownDataTypeContainer retrieve(InvocationContext& value) const = 0;

    virtual ~ValueRetriever() = default;
};



/**
 * @brief Base class for a function's implementation. Override this to implement your own function.
 */
class SIPLUS_EXPORT Function {
public:
    /**
     * @brief Get the ValueRetriever for an invocation of a function.
     *
     * This is called when a function is called in a template.
     * Your returned ValueRetriever should call your parameters' .retrieve() methods to 
     * get the actual *values* passed into these parameters.
     *
     * @param[in] parent This is the parameter passed in through '|'. This will be falsy 
     * if there is no such parameter.
     * @param[in] parameters Any values passed in the parameter list.
     */
    virtual std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const = 0;

    virtual ~Function() = default;
};



/**
 * struct InvocationContext - Represents a context for a single invocation of a template.
 *
 * InvocationContexts must not be reused, but you may call build() multiple times on the 
 * builder to get mutliple instances of the same context.
 */
struct SIPLUS_EXPORT InvocationContext : public std::enable_shared_from_this<InvocationContext> {
    /**
     * @brief Get the default data (The data at '.')
     *
     * @return Data container
     */
    virtual UnknownDataTypeContainer default_data() const;

    /**
     * @brief Checks if a variable is defined.
     *
     * @param[in] key The name of the variable
     * @return true if the variable is defined.
     */
    virtual bool variable_defined(std::string key) const = 0;

    /**
     * @brief Get the value of a variable.
     *
     * @param[in] key The variable name
     * @return The data in the variable
     */
    virtual const UnknownDataTypeContainer variable(std::string key) const = 0;

    /**
     * @brief Set a variable's value. Using this as a side-effect is highly 
     * discouraged.
     *
     * @param[in] key The variable name
     * @param[in] val The value
     */
    virtual void set_variable(std::string key, const UnknownDataTypeContainer& val) = 0;

    virtual ~InvocationContext() = default;
};



/**
 * struct InvocationContextWrapperBuilder - Builder class for `InvocationContextWrapper`
 */
struct SIPLUS_EXPORT InvocationContextWrapperBuilder {
    InvocationContextWrapperBuilder(std::shared_ptr<InvocationContext> context) : parent_(context) { }

    InvocationContextWrapperBuilder& use_default(UnknownDataTypeContainer val);
    InvocationContextWrapperBuilder& with(std::string name, UnknownDataTypeContainer val);
    std::shared_ptr<InvocationContext> build();

private:
    std::shared_ptr<InvocationContext> parent_;
    std::unordered_map<std::string, UnknownDataTypeContainer> variables_;
};



SIPLUS_EXPORT InvocationContextWrapperBuilder wrap_scope(std::shared_ptr<InvocationContext> context);



/**
 * struct InvocationContextWrapper - Wraps another InvocationContext to hold new data, 
 * while still accessing prior data.
 *
 * Implementation for scopes. Wrapping an InvocationContext effectively creates a new scope.
 */
struct SIPLUS_EXPORT InvocationContextWrapper : InvocationContext {
    friend struct InvocationContextWrapperBuilder;

    InvocationContextWrapper(std::shared_ptr<InvocationContext> parent) : parent_(parent) {}
    virtual bool variable_defined(std::string key) const override;
    virtual const UnknownDataTypeContainer variable(std::string key) const override;
    virtual void set_variable(std::string key, const UnknownDataTypeContainer& value) override;
private:
    std::shared_ptr<InvocationContext> parent_;
    std::unordered_map<std::string, UnknownDataTypeContainer> variables_;
};



/**
 * struct ContextInvocationContextBuilder - Builder class for a root `InvocationContext`
 */
struct SIPLUS_EXPORT ContextInvocationContextBuilder {
    friend class SIPlusParserContext;

    /**
     * @brief Set the default data for this invocation. The data accessible at `$0` or `.`.
     * Calling `with("0", data)`, is an equivalent call, but prefer this.
     *
     * @param data The data to use
     */
    ContextInvocationContextBuilder& use_default(UnknownDataTypeContainer data);

    /**
     * @brief Add an additional variable accessible at `$name`
     *
     * @param name The name of the variable to add
     * @param data The data to use at the variable
     */
    ContextInvocationContextBuilder& with(std::string name, UnknownDataTypeContainer data);

    /**
     * @brief Return the build `InvocationContext`
     */
    std::shared_ptr<InvocationContext> build() const;

private:
    ContextInvocationContextBuilder(std::shared_ptr<const SIPlusParserContext> context) : context_(context) {}

    std::shared_ptr<const SIPlusParserContext> context_;
    std::unordered_map<std::string, UnknownDataTypeContainer> variables_;
};



struct SIPLUS_EXPORT VariableOpts {
    bool is_persist:1 = false;
    bool is_const:1 = false;
};

struct SIPLUS_EXPORT VariableRetriever : public ValueRetriever {
    virtual bool is_persist() const = 0;
    virtual bool is_const() const = 0;
    virtual std::string name() const = 0;

    virtual void set_value(InvocationContext& context, UnknownDataTypeContainer value) = 0;
};



/**
 * struct BuildContext - This is used internally only, it likely should not be in the public headers.
 */
struct SIPLUS_EXPORT BuildContext : public std::enable_shared_from_this<BuildContext> {
    BuildContext() = default;
    BuildContext(const BuildContext& other) = delete;
    BuildContext(BuildContext&& other) = default;
    explicit BuildContext(std::shared_ptr<BuildContext> parent) : parent_(parent) {}
    ~BuildContext() = default;

    BuildContext& operator=(const BuildContext& other) = delete;
    BuildContext& operator=(BuildContext&& other) = default;

    /**
     * @brief Returns true if the specified variable is declared in the current scope 
     * (including parent scopes)
     *
     * @param name the name of the variable
     * @return `true` if declared, `false` otherwise
     */
    bool has_variable(std::string name);

    /**
     * @brief Get a `VariableRetriever` by name.
     *
     * @param name The name of the variable.
     * @param declare If set to `true` this will declare the variable in the 
     * current scope, if not defined.
     */
    std::shared_ptr<VariableRetriever> get_variable(std::string name);

    /**
     * @brief Declare a variable in the current scope
     *
     * @param name The name of the variable.
     * @param opts The options of the variable.
     * @return The created variable
     */
    std::shared_ptr<VariableRetriever> declare_variable(
        std::string name, 
        const VariableOpts& opts
    );

    bool has_function(const std::string& name);
    Function& function(const std::string& name);

    template<typename T, typename... Ts>
    void emplace_function(const std::string& name, Ts&&... args) {
        if(has_function(name)) {
            throw std::runtime_error{util::to_string("Function '@", name, "' already defined")};
        }

        functions_[name] = std::make_unique<T>(std::forward<Ts>(args)...);
    }

private:
    std::shared_ptr<BuildContext> parent_;
    std::unordered_map<std::string, std::shared_ptr<VariableRetriever>> variables_;
    std::unordered_map<std::string, std::unique_ptr<Function>> functions_;
};



/**
 * @brief Make a root build context
 *
 * @param opts The parser options
 */
std::shared_ptr<BuildContext> SIPLUS_EXPORT make_build_context(const std::vector<std::string>& opts);

/**
 * @brief Make a scoped build context
 *
 * @param parent The parent build context
 */
std::shared_ptr<BuildContext> SIPLUS_EXPORT make_build_context(std::shared_ptr<BuildContext> parent);



/**
 * @brief The context object passed around between SIPlus objects to communicate converters,
 * accesors, iterators, and other data related information.
 */
class SIPLUS_EXPORT SIPlusParserContext : public std::enable_shared_from_this<SIPlusParserContext> {
public:
    SIPlusParserContext();

    /**
     * @brief Finds a function instance with the specified name.
     *
     * @param[int] name The name of the function to find.
     */
    Function& function(const std::string& name) const;

    void emplace_function(std::string name, std::shared_ptr<Function> function);

    /**
     * @brief Create a builder to make an `InvocationContext`
     *
     * @return A builder object
     */
    ContextInvocationContextBuilder builder() const;

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<Function, T>>>
    std::shared_ptr<T> emplace_function(std::string name, Ts&&... args) {
        auto function = std::make_shared<T>(std::forward<Ts>(args)...);
        emplace_function(name, function);
        return function;
    }

private:
    //storage
    std::unordered_map<std::string, std::shared_ptr<Function>> functions_;
};



/**
 * @brief Utility function for classes implementing BinaryOperatorTypeExtensionImpl.
 * Accepts isLhs, thisValue, and other, and returns a tuple containing [lhs, rhs].
 *
 * @param[in] isLhs value passed to BinaryOperatorTypeExtensionImpl::invoke
 * @param[in] thisValue value passed to BinaryOperatorTypeExtensionImpl::invoke
 * @param[in] other value passed to BinaryOperatorTypeExtensionImpl::invoke
 */
inline std::tuple<UnknownDataTypeContainer, UnknownDataTypeContainer> resolve_lhs(
    bool isLhs, 
    const UnknownDataTypeContainer &thisValue, 
    const UnknownDataTypeContainer &other
) {
    return {
        isLhs ? thisValue : other,
        isLhs ? other : thisValue
    };
}

} /* SIPLUS_NAMESPACE */


namespace std {

template<>
struct equal_to<SIPLUS_NAMESPACE::TypeInfo> {
    bool operator()(const SIPLUS_NAMESPACE::TypeInfo& lhs, const SIPLUS_NAMESPACE::TypeInfo& rhs) const noexcept {
        return lhs == rhs;
    }
};

template<>
struct hash<SIPLUS_NAMESPACE::TypeInfo> {
    size_t operator()(const SIPLUS_NAMESPACE::TypeInfo& info) const noexcept {
        return reinterpret_cast<uint64_t>(info.descriptor());
    }
};

template<>
struct hash<SIPLUS_NAMESPACE::UnknownDataTypeContainer> {
    std::uint64_t operator()(const SIPLUS_NAMESPACE::UnknownDataTypeContainer& container) const {
        auto hashImpl = container.type->get_extension(SIPLUS_NAMESPACE::TypeInfo::Hashable);

        if(hashImpl == nullptr) {
            return reinterpret_cast<uint64_t>(container.ptr);
        }

        auto hash = hashImpl->invoke(container);
        hash.assert_type<SIPlus::types::IntegerType>("<Hashable result>");

        return longHash_(hash.as<SIPlus::types::IntegerType>());
    }

private:
    std::hash<SIPLUS_NAMESPACE::types::IntegerType::data_type> longHash_;
};

template<>
struct equal_to<SIPLUS_NAMESPACE::UnknownDataTypeContainer> {
    bool operator()(
        const SIPLUS_NAMESPACE::UnknownDataTypeContainer& lhs,
        const SIPLUS_NAMESPACE::UnknownDataTypeContainer& rhs
    ) const { 
        return lhs == rhs; 
    }
};

} /* namespace std */


#endif  // INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_
