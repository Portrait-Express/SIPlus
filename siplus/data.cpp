#include "siplus/data.h"
#include "siplus/text/iterator.h"
#include "siplus/util.h"

namespace SIPLUS_NAMESPACE {

UnknownDataTypeContainer TypeInfo::access(const UnknownDataTypeContainer&, const std::string&) const {
    throw std::runtime_error{util::to_string(name(), " has no accessible properties")};
}

std::unique_ptr<text::Iterator> TypeInfo::iterate(const UnknownDataTypeContainer&) const {
    throw std::runtime_error{util::to_string(name(), " is not iterable")};
}

UnknownDataTypeContainer::UnknownDataTypeContainer() {
    _ref = new size_t(1);
}

UnknownDataTypeContainer::UnknownDataTypeContainer(std::shared_ptr<TypeInfo> type, void *ptr) : UnknownDataTypeContainer() {
    this->type = type;
    this->ptr = ptr;
}

UnknownDataTypeContainer::UnknownDataTypeContainer(std::shared_ptr<TypeInfo> type, void *ptr, deleter deleter) : UnknownDataTypeContainer(type, ptr) {
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

UnknownDataTypeContainer UnknownDataTypeContainer::access(const std::string& name) {
    return type->access(*this, name);
}

std::unique_ptr<text::Iterator> UnknownDataTypeContainer::iterate() {
    return type->iterate(*this);
}

bool UnknownDataTypeContainer::is_iterable() {
    return type->is_iterable();
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
