#include "siplus/context.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"
#include "siplus/util.hxx"

namespace SIPLUS_NAMESPACE {

UnknownDataTypeContainer TypeInfo::access(const UnknownDataTypeContainer&, const std::string&) const {
    throw std::runtime_error{util::to_string(name(), " has no accessible properties")};
}

UnknownDataTypeContainer 
TypeInfo::index(
    std::shared_ptr<SIPlusParserContext> context, 
    UnknownDataTypeContainer& value, 
    UnknownDataTypeContainer& index
) const {
    if(index.is<types::IntegerType>() || context->can_convert<types::IntegerType>(*index.type)) {
        auto index_ = context->convert<types::IntegerType>(index).as<types::IntegerType>();

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
    } else if(index.is<types::StringType>() || context->can_convert<types::StringType>(*index.type)) {
        auto property = context->convert<types::StringType>(index).as<types::StringType>();

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

UnknownDataTypeContainer::UnknownDataTypeContainer() {
    _ref = new size_t(1);
    type = std::make_shared<types::NullType>();
}

UnknownDataTypeContainer::UnknownDataTypeContainer(std::shared_ptr<const TypeInfo> type, void *ptr) : UnknownDataTypeContainer() {
    this->type = type;
    this->ptr = ptr;
}

UnknownDataTypeContainer::UnknownDataTypeContainer(std::shared_ptr<const TypeInfo> type, void *ptr, deleter deleter) : UnknownDataTypeContainer(type, ptr) {
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

UnknownDataTypeContainer UnknownDataTypeContainer::index(
    std::shared_ptr<SIPlusParserContext> context, 
    UnknownDataTypeContainer& index
) {
    return type->index(context, *this, index);
}

std::unique_ptr<Iterator> UnknownDataTypeContainer::iterate() {
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
