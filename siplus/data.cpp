#include "siplus/text/data.h"

namespace SIPLUS_NAMESPACE {

namespace text {

UnknownDataTypeContainer::UnknownDataTypeContainer() {
    _ref = new size_t(1);
}

UnknownDataTypeContainer::UnknownDataTypeContainer(std::type_index type, const void *ptr) : UnknownDataTypeContainer() {
    this->type = type;
    this->ptr = ptr;
}

UnknownDataTypeContainer::UnknownDataTypeContainer(std::type_index type, const void *ptr, deleter deleter) : UnknownDataTypeContainer(type, ptr) {
    deleter_ = deleter;
}

UnknownDataTypeContainer::UnknownDataTypeContainer(const UnknownDataTypeContainer& other) {
    type = other.type;
    ptr = other.ptr;
    deleter_ = other.deleter_;
    _ref = other._ref;
    
    *_ref = *_ref+1;
}
UnknownDataTypeContainer::UnknownDataTypeContainer(UnknownDataTypeContainer&& other) { 
    swap(*this, other); 
}

UnknownDataTypeContainer& UnknownDataTypeContainer::operator=(UnknownDataTypeContainer other) { 
    swap(*this, other); 
    return *this;
}

UnknownDataTypeContainer::~UnknownDataTypeContainer() {
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
