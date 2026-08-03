#pragma once
#ifndef INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_
#define INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_

#include <functional>
#include <list>
#include <memory>
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

    bool operator==(const TypeInfo& other) const {
        return name() == other.name();
    }

    virtual ~TypeInfo() = default;
};



namespace internal {

/**
 * struct BinaryTypeCache - Used to store a pair of types to a value. This is used 
 * for caching converter can_convet, or similar results.
 *
 * @tparam T The value type
 * @tparam T::*Handle the member to call on the value to determine if it can handle 
 * a pair of types
 */
template<typename T, bool (T::*Handle)(const TypeInfo&, const TypeInfo&) const = T::can_handle>
struct BinaryTypeCache {
    using iterator = std::list<std::shared_ptr<T>>::iterator;
    using const_iterator = std::list<std::shared_ptr<T>>::const_iterator;

    iterator begin() { return items_.begin(); }
    iterator end() { return items_.end(); }

    const_iterator begin() const { return items_.begin(); }
    const_iterator end() const { return items_.end(); }

    template<std::derived_from<T> U, typename... Ts>
    std::shared_ptr<U> emplace_item(Ts&&... args) {
        //put at front to prioritized newest entries.
        auto value = std::make_shared<U>(std::forward<Ts>(args)...);
        emplace_item(std::static_pointer_cast<T>(value));
        return value;
    }

    void emplace_item(std::shared_ptr<T> val) {
        items_.push_front(val);
    }

    iterator find(const TypeInfo& first, const TypeInfo& second) {
        auto firstIt = cache_.find(first.name());

        if(firstIt != cache_.end()) {
            auto secondIt = firstIt->second.find(second.name());

            if(secondIt != firstIt->second.end()) {
                return convert_constness(secondIt->second);
            }
        }

        for(auto it = items_.begin(); it != items_.end(); it++) {
            auto& item = *it;

            if(((*item).*Handle)(first, second)) {
                if(firstIt != cache_.end()) {
                    (firstIt->second)[second.name()] = it;
                } else {
                    cache_[first.name()][second.name()] = it;
                }

                return it;
            }
        }

        return items_.end();
    }

    const_iterator find(const TypeInfo& first, const TypeInfo& second) const {
        auto firstIt = cache_.find(first.name());

        if(firstIt != cache_.end()) {
            auto secondIt = firstIt->second.find(second.name());

            if(secondIt != firstIt->second.end()) {
                return secondIt->second;
            }
        }

        for(auto it = items_.begin(); it != items_.end(); it++) {
            auto& item = *it;

            if(((*item).*Handle)(first, second)) {
                if(firstIt != cache_.end()) {
                    (firstIt->second)[second.name()] = it;
                } else {
                    cache_[first.name()][second.name()] = it;
                }

                return it;
            }
        }

        return items_.end();
    }

private:
    std::list<std::shared_ptr<T>> items_;
    mutable std::unordered_map<std::string, std::unordered_map<std::string, const_iterator>> cache_;

    iterator convert_constness(const_iterator it) {
        //dont think about it too much... It cant hurt you any more
        //
        //I keep getting mentally flashbanged whenever I look at this - 05/08/2026
        
        return items_.erase(it, it);
    }
};

} /* internal */



template<typename T>
struct type_info_for { };

template<typename T>
using type_info_for_t = type_info_for<std::remove_cvref_t<std::decay_t<T>>>::type;

template<typename _>
concept True = true;

template<typename T>
concept is_pointer = std::is_pointer_v<T>;

template<typename Type>
concept simple_value_retrievable_type = requires(const Type a) {
    { Type{} } -> std::same_as<Type>;
    { std::declval<typename Type::data_type>() } -> True;
} && std::is_base_of_v<TypeInfo, Type>;




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
    std::shared_ptr<const TypeInfo> type;
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
     * @brief Index this object.
     *
     * @param[in] name The name of the property to access.
     * @return The data at that property. Throws if property does not exist.
     */
    UnknownDataTypeContainer 
    index(std::shared_ptr<SIPlusParserContext> context, 
          UnknownDataTypeContainer& index);

    /**
     * @brief Create an iterator for this object. This will throw if 
     * is_iterable() is false.
     *
     * @return A new iterator
     */
    std::unique_ptr<Iterator> iterate();

    /**
     * @brief See TypeInfo::is_iterable
     *
     * @return True if this object is iterable.
     */
    bool is_iterable() const;

    ~UnknownDataTypeContainer();

private:
    size_t *_ref = nullptr;
    deleter deleter_;
};



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
 * @brief Provide converter functionality between types.
 */
class SIPLUS_EXPORT Converter {
public:
    /**
     * @brief This will return true if this converter can convert from `from` to `to`.
     * The result of this is cached internally for future lookups
     *
     * @param[in] from From type
     * @param[in] to To type
     * @return True if this converter can handle the conversion.
     */
    virtual bool can_convert(const TypeInfo& from, const TypeInfo& to) const = 0;

    /**
     * @brief Convert from one type to another
     *
     * @param[in] from The data to convert from
     * @param[in] to The type to convert to
     * @return The converted object. This MUST be an instance of `to`.
     */
    virtual UnknownDataTypeContainer convert(
        const UnknownDataTypeContainer& from,
        const TypeInfo& to
    ) const = 0;

    virtual ~Converter() = default;
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

#ifdef SIPLUS_INCLUDE_STDLIB
    /**
     * @brief Attaches the STL library of functions and converters, and iterators to this context.
     */
    void use_stl();
#endif

    /**
     * @brief Finds a function instance with the specified name.
     *
     * @param[int] name The name of the function to find.
     */
    Function& function(const std::string& name) const;

    /**
     * @brief Tries to find a converter aboe to convert from `from` to `to`. If no usable
     * converter is found, this throws an error.
     * 
     * @param[in] from The type to convert from
     * @param[in] to The type to convert to
     */
    std::shared_ptr<Converter> converter(const TypeInfo& from, const TypeInfo& to) const;

    template<typename T>
    bool can_convert(const TypeInfo& from) const {
        auto type = std::make_shared<T>();
        return static_cast<bool>(try_converter(from, *type));
    }

    /**
     * @brief Tries to find a converter aboe to convert from `from` to `to`. Returned 
     * `shared_ptr` will be nullptr if none is found. Use `std::shared_ptr::operator bool()` 
     * to check validity.
     *
     * Use this as a way to check if a conversion is legal.
     *
     * @code
     * if(ctx->try_converter(container.type, typeid(long))) {
     *     ctx->convert<long>(container);
     *     //...
     * }
     * @endcode
     *
     * @param[in] from The type to convert from
     * @param[in] to The type to convert to
     */
    std::shared_ptr<Converter> try_converter(const TypeInfo& from, const TypeInfo& to) const;

    UnknownDataTypeContainer convert(const UnknownDataTypeContainer& data, const TypeInfo& to) const;

    void emplace_function(std::string name, std::shared_ptr<Function> function);
    void emplace_converter(std::shared_ptr<Converter> converter);

    template<typename T> requires std::is_base_of_v<TypeInfo, T>
    UnknownDataTypeContainer convert(const UnknownDataTypeContainer& data) const {
        if(data.is<T>()) return data;
        return convert(data, *std::make_shared<T>());
    }

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

    template<typename T, typename ...Ts, typename = std::enable_if_t<std::is_base_of_v<Converter, T>>>
    std::shared_ptr<T> emplace_converter(Ts&&... args) {
        auto converter = std::make_shared<T>(std::forward<Ts>(args)...);
        emplace_converter(converter);
        return converter;
    }

private:
    //accessing caches
    internal::BinaryTypeCache<Converter, &Converter::can_convert> converters_;

    //storage
    std::unordered_map<std::string, std::shared_ptr<Function>> functions_;
};



namespace types {

/**
 * struct NullType - This is the default type of an UnknownDataTypeContainer. Used to 
 * represent an empty container.
 */
struct SIPLUS_EXPORT NullType : public TypeInfo {
    using data_type = void;
    virtual std::string name() const override;
    virtual UnknownDataTypeContainer access(const UnknownDataTypeContainer& data, const std::string& name) const override;
    virtual bool is_iterable(const UnknownDataTypeContainer& data) const override;
};

} /* types */



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

constexpr inline UnknownDataTypeContainer make_data(const UnknownDataTypeContainer& data) {
    return data;
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
} /* namespace std */


#endif  // INCLUDE_SIPLUS_TEXT_CONTEXT_HXX_
