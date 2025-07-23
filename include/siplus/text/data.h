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

    std::type_index type = typeid(void);
    const void *ptr;
    deleter deleter_;

    template<typename T>
    bool is() { return type == typeid(std::remove_cvref_t<T>); }

    template<typename T>
    bool as() { return *(T*)ptr; }

    friend void swap(UnknownDataTypeContainer& self, UnknownDataTypeContainer& other) {
        using std::swap;

        swap(self.type, other.type);
        swap(self.ptr, other.ptr);
        swap(self.deleter_, other.deleter_);
        swap(self._ref, other._ref);
    }

    ~UnknownDataTypeContainer();

private:
    size_t *_ref;
};


template<typename T>
UnknownDataTypeContainer make_data(const T& value) {
    return UnknownDataTypeContainer(typeid(std::remove_cvref_t<T>), &value);
}

template<typename T>
UnknownDataTypeContainer make_data(const T *value, bool acquire = true) {
    return UnknownDataTypeContainer(typeid(T), value, [acquire](const void *ptr){ 
        if(acquire) 
            delete (T*)ptr; 
    } );
}

template<typename T>
UnknownDataTypeContainer make_data(const T&& value) {
    return make_data(new std::remove_cvref_t<T>(value), true);
}


}
}

#endif
