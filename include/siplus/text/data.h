#ifndef INCLUDE_SIPLUS_TEXT_DATA_H_
#define INCLUDE_SIPLUS_TEXT_DATA_H_

#include <functional>
#include <typeindex>

#include "siplus/_config.h"

namespace SIPLUS_NAMESPACE {
namespace text {

struct UnknownDataTypeContainer {
    using deleter = std::function<void (const void*)>; 

    UnknownDataTypeContainer();
    UnknownDataTypeContainer(std::type_index type, const void *ptr);
    UnknownDataTypeContainer(std::type_index type, const void *ptr, deleter deleter);

    UnknownDataTypeContainer(const UnknownDataTypeContainer& other);
    UnknownDataTypeContainer(UnknownDataTypeContainer&& other);

    UnknownDataTypeContainer& operator=(UnknownDataTypeContainer other);

    operator bool() { return ptr; }

    std::type_index type = typeid(void);
    const void *ptr = 0;

    template<typename T>
    bool is() { return type == typeid(std::remove_cvref_t<T>); }

    /**
     * @brief Returns a reference to the stored data as a specified type. If 
     * this is called with the incorrect type, the returned data is undefined.
     * Always use `is` before calling this.
     *
     * @tparam T The type to return
     * @return Const reference to stored data
     */
    template<typename T>
    const T& as() const { return *(const T*)ptr; }

    friend void swap(UnknownDataTypeContainer& self, UnknownDataTypeContainer& other) {
        using std::swap;

        swap(self.type, other.type);
        swap(self.ptr, other.ptr);
        swap(self.deleter_, other.deleter_);
        swap(self._ref, other._ref);
    }

    ~UnknownDataTypeContainer();

private:
    size_t *_ref = nullptr;
    deleter deleter_;
};


/**
 * @brief Make a UnknownDataTypeContainer. Does not take ownership. Valid for 
 * the lifetime of the referenced object.
 */
template<typename T>
UnknownDataTypeContainer make_data(const T& value) {
    return UnknownDataTypeContainer(typeid(std::remove_cvref_t<T>), &value);
}

/** @brief Make a UnknownDataTypeContainer. Takes ownership of the pointer if 
 * acquire is `true`. Defaults to `true`. Frees pointer with a `delete`. If 
 * you need other freeing, construct a UnknownDataTypeContainer yourself, and
 * pass a custom deleter.
 */
template<typename T>
UnknownDataTypeContainer make_data(const T *value, bool acquire = true) {
    return UnknownDataTypeContainer(typeid(T), value, [acquire](const void *ptr){ 
        if(acquire) 
            delete (T*)ptr; 
    } );
}

/**
 * @brief Make a UnknownDataTypeContainer. Copies the object to the heap, and 
 * deletes the pointer when all references die. 
 */
template<typename T>
UnknownDataTypeContainer make_data(const T&& value) {
    return make_data(new std::remove_cvref_t<T>(value), true);
}


}
}

#endif
