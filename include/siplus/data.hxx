#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_DATA_HXX_
#define INCLUDE_SIPLUS_TEXT_DATA_HXX_

#define SIPLUS_DEFINE_TYPE_INFO(type_, type_info) \
    template<> struct type_info_for<type_> { using type = type_info; };

#include <concepts>
#include <functional>
#include <memory>
#include <string>

#include "siplus/config.h"

namespace SIPLUS_NAMESPACE {

namespace text { struct Iterator; }
struct SIPLUS_EXPORT UnknownDataTypeContainer; 

/**
 * @brief Type information in order to properly handle dynamically typed input data.
 */
class SIPLUS_EXPORT TypeInfo : public std::enable_shared_from_this<TypeInfo> {
public:
    /**
     * @brief Returns the name of this type. Type equality is determined by 
     * comparing names, so please ensure that your TypeInfo uses a name unique 
     * to any other.
     *
     * @return The name of this type.
     */
    virtual std::string name() const = 0;

    /**
     * @brief Returns whether or not this type is iterable.
     *
     * @return True if the type is iterable
     */
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const = 0;

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
     * @brief Create an iterator to iterate over the object.
     *
     * @param[in] data A void* to the object
     * @return A new iterator for this object. Throws if `is_iterable()` 
     * is false.
     */
    virtual std::unique_ptr<text::Iterator> iterate(const UnknownDataTypeContainer& data) const;

#ifndef SWIG
    /**
     * @brief Check of this type is an instance of a specific subclass.
     * Simple wrapper for dynamic_cast<T*>(this) !== nullptr
     *
     * @tparam T The subclass to check
     * @return True if this type is an instance (or an instance of a subclass) 
     * of T
     */
    template<typename T> requires std::is_base_of_v<TypeInfo, T>
    bool is() const {
        return dynamic_cast<const T*>(this) != nullptr;
    }
#endif // SWIG

    bool operator==(const TypeInfo& other) const {
        return name() == other.name();
    }

    virtual ~TypeInfo() = default;
};

template<typename T>
struct type_info_for { };

template<typename T>
using type_info_for_t = type_info_for<std::remove_cvref_t<std::decay_t<T>>>::type;

template<typename _>
concept True = true;

template<typename T>
concept is_pointer = std::is_pointer_v<T>;

#ifndef SWIG
template<typename Type>
concept simple_value_retrievable_type = requires(const Type a) {
    { Type{} } -> std::same_as<Type>;
    { std::declval<typename Type::data_type>() } -> True;
} && std::is_base_of_v<TypeInfo, Type>;
#endif // SWIG

namespace types {

/**
 * struct NullType - This is the default type of an UnknownDataTypeContainer. Used to 
 * represent an empty container.
 */
struct SIPLUS_EXPORT NullType : public TypeInfo {
    virtual std::string name() const override;
    virtual UnknownDataTypeContainer access(const UnknownDataTypeContainer& data, const std::string& name) const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
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
     * @brief Construct an empty UnknownDataTypeContainer. Use this to create null.
     */
    UnknownDataTypeContainer();

    /**
     * @brief Create a container with a type, and data, but no deleter. If you don't 
     * delete the void* yourself, it WILL leak.
     *
     * @param[in] type The type of the object
     * @param[in] ptr The void* to the data
     */
    UnknownDataTypeContainer(std::shared_ptr<const TypeInfo> type, void *ptr);

    /**
     * @brief Create a container with a type, data, and a deleter. The deleter 
     * will be invoked once the reference count reaches 0
     *
     * @param[in] type The type of the object
     * @param[in] ptr The void* to the data
     * @param[in] deleter The deleter callback to invoke on deletion
     */
    UnknownDataTypeContainer(std::shared_ptr<const TypeInfo> type, void *ptr, deleter deleter);

    UnknownDataTypeContainer(const UnknownDataTypeContainer& other);
    UnknownDataTypeContainer(UnknownDataTypeContainer&& other);

    /**
     * @type Get the type of this data container. DO NOT ASSIGN TO THIS UNLESS YOU KNOW WHAT YOU ARE DOING.
     */
    std::shared_ptr<const TypeInfo> type = std::make_shared<types::NullType>();
    //This probably should not be an exposed property, but it is. Maybe we should change it to type()
    

    /**
     * The void* to the data.
     */
    void *ptr = 0;

    UnknownDataTypeContainer& operator=(UnknownDataTypeContainer other);

    /**
     * @brief Returns true if this container is not null
     */
    explicit operator bool() { return ptr; }

#ifndef SWIG
    /**
     * @brief Checks if this object is an instance of the type.
     *
     * @tparam T The type to check if this object is an instance of.
     * @return True if this object is an instance of T.
     */
    template<typename T> requires std::is_base_of_v<TypeInfo, T>
    bool is() const {
        return type->is<T>();
    }
#endif // SWIG

    /**
     * @brief Casts this object to a T::data_type&. This does NO type checking. Check is<> first.
     *
     * @tparam simple_value_retrievable_type The type to cast to
     */
    template<simple_value_retrievable_type T>
    T::data_type& as() const {
        return *reinterpret_cast<T::data_type*>(ptr);
    }

    friend void swap(UnknownDataTypeContainer& self, UnknownDataTypeContainer& other) {
        using std::swap;

        swap(self.type, other.type);
        swap(self.ptr, other.ptr);
        swap(self.deleter_, other.deleter_);
        swap(self._ref, other._ref);
    }

    /**
     * @brief Access a property on this object.
     *
     * @param[in] name The name of the property to access.
     * @return The data at that property. Throws if property does not exist.
     */
    UnknownDataTypeContainer access(const std::string& name);

    /**
     * @brief Create an iterator for this object. This will throw if 
     * is_iterable() is false.
     *
     * @return A new iterator
     */
    std::unique_ptr<text::Iterator> iterate();

    /**
     * @brief See TypeInfo::is_iterable
     *
     * @return True if this object is iterable.
     */
    bool is_iterable();

    ~UnknownDataTypeContainer();

private:
    size_t *_ref = nullptr;
    deleter deleter_;
};

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

} /* SIPLUS_NAMESPACE */

namespace std {
template<>
struct equal_to<SIPLUS_NAMESPACE::TypeInfo> {
    bool operator()(const SIPLUS_NAMESPACE::TypeInfo& lhs, const SIPLUS_NAMESPACE::TypeInfo& rhs) const noexcept {
        return lhs.name() == rhs.name();
    }
};

template<>
struct hash<SIPLUS_NAMESPACE::TypeInfo> {
    size_t operator()(const SIPLUS_NAMESPACE::TypeInfo& info) const noexcept {
        return hash<std::string>{}(info.name());
    }
};
}

#endif
