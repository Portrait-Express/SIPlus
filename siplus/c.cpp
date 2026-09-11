#include "siplus/csiplus.h"
#include "siplus/context.hxx"
#include "siplus/parser.hxx"
#include "siplus/util.hxx"
#include <cassert>
#include <cstring>
#include <exception>
#include <memory>
#include <type_traits>

#define __STR(x) #x
#define STR(x) __STR(x)

#define __COUNT(a1,a2,a3,a4,a5,a6,a7,a8,a9,a,...) a
#define COUNT(...) __COUNT(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)


#define __CONCAT_EX(a, b) a##b
#define CONCAT_EX(a, b) __CONCAT_EX(a, b)

#define __SIPLUS_NOT_NULL(var) assert(var != nullptr && STR(var) " cannot be NULL");

#define _SIPLUS_NOT_NULL_9(var,...) _SIPLUS_NOT_NULL_8(__VA_ARGS__) __SIPLUS_NOT_NULL(var)
#define _SIPLUS_NOT_NULL_8(var,...) _SIPLUS_NOT_NULL_7(__VA_ARGS__) __SIPLUS_NOT_NULL(var)
#define _SIPLUS_NOT_NULL_7(var,...) _SIPLUS_NOT_NULL_6(__VA_ARGS__) __SIPLUS_NOT_NULL(var)
#define _SIPLUS_NOT_NULL_6(var,...) _SIPLUS_NOT_NULL_5(__VA_ARGS__) __SIPLUS_NOT_NULL(var)
#define _SIPLUS_NOT_NULL_5(var,...) _SIPLUS_NOT_NULL_4(__VA_ARGS__) __SIPLUS_NOT_NULL(var)
#define _SIPLUS_NOT_NULL_4(var,...) _SIPLUS_NOT_NULL_3(__VA_ARGS__) __SIPLUS_NOT_NULL(var)
#define _SIPLUS_NOT_NULL_3(var,...) _SIPLUS_NOT_NULL_2(__VA_ARGS__) __SIPLUS_NOT_NULL(var)
#define _SIPLUS_NOT_NULL_2(var,...) _SIPLUS_NOT_NULL_1(__VA_ARGS__) __SIPLUS_NOT_NULL(var)
#define _SIPLUS_NOT_NULL_1(var) __SIPLUS_NOT_NULL(var)
#define SIPLUS_NOT_NULL(...) CONCAT_EX(_SIPLUS_NOT_NULL_, COUNT(__VA_ARGS__))(__VA_ARGS__)

#define SIPLUS_TRY(body) { try { body } catch(std::exception& e) { return siplus_error_set(SIPLUS_INVOKE_ERROR, e.what()); } }

using namespace SIPLUS_NAMESPACE;

static thread_local int last_error = SIPLUS_OK;
static thread_local std::optional<std::string> last_message;

int siplus_error_set(int err, std::optional<std::string> message = std::nullopt) {
    last_message = message;
    last_error = err;
    return err;
}

std::string error_name(int error) {
    switch(error) {
    case SIPLUS_OK:
        return "OK";

    case SIPLUS_ERR:
        return "ERR";

    case SIPLUS_INVALID_ARG:
        return "INVALID_ARG";

    case SIPLUS_PARSE_ERROR:
        return "PARSE_ERROR";

    case SIPLUS_INVOKE_ERROR:
        return "INVOKE_ERROR";

    default:
        return "UNKNOWN_ERROR";
    }
}

void throw_last_error(std::optional<std::string> default_message = std::nullopt) {
    if(last_error != SIPLUS_OK) {
        throw std::runtime_error{
            last_message.value_or(default_message.value_or(util::to_string("Received error ", error_name(last_error))))
        };
    }
}

#define TRY_C(expr) if(auto err = expr; err != SIPLUS_OK) { throw_last_error(); }

struct _SIPlusUnknownDataContainer {
    std::unique_ptr<UnknownDataTypeContainer> container;
};

struct _SIPlusParser {
    Parser parser;
};

struct _SIPlusParserContext {
    _SIPlusParserContext(std::shared_ptr<SIPlusParserContext> context) : context(context) { }

    std::shared_ptr<SIPlusParserContext> context;
};

struct _SIPlusTextConstructor {
    std::shared_ptr<text::TextConstructor> constructor;
};

struct _SIPlusValueRetriever {
    std::shared_ptr<ValueRetriever> retriever;
};

struct _SIPlusParseOpts {
    ParseOpts opts;
};

struct _SIPlusInvocationContextBuilder {
    ContextInvocationContextBuilder builder;
};

struct _SIPlusInvocationContext {
    std::shared_ptr<InvocationContext> context;
};

struct _SIPlusIterator {
    std::unique_ptr<Iterator> iterator;
};

struct _SIPlusFunction {
    std::shared_ptr<Function> function;
};

namespace {

struct CValueRetriever : ValueRetriever {
    CValueRetriever(
        void *data, 
        SIPlusRetrieverImpl impl,
        SIPlusDataDeleterCallback deleter
    ) : data(data), impl(impl), deleter(deleter) {}

    UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

    ~CValueRetriever() { if(deleter) deleter(data); }

    void *data;
    SIPlusRetrieverImpl impl;
    SIPlusDataDeleterCallback deleter;
};

UnknownDataTypeContainer CValueRetriever::retrieve(InvocationContext& value) const {
    SIPlusUnknownDataContainer *container;
    auto ptr = std::make_unique<_SIPlusInvocationContext>(value.shared_from_this());
    
    auto result = impl(&container, data, ptr.get());
    if(result != SIPLUS_OK) {
        throw std::runtime_error{
            last_message.value_or(
                util::to_string(
                    "SIPlusRetrieverImpl() failed with ", error_name(result)))
        };
    }

    UnknownDataTypeContainer ret = *container->container;

    siplus_data_delete(container);

    return ret;
}

struct CFunction : Function {
    CFunction(
        void *data,
        SIPlusFunctionValue impl,
        SIPlusDataDeleterCallback deleter
    ) : data(data), impl(impl), deleter(deleter) {}

    std::shared_ptr<ValueRetriever> value(
        std::shared_ptr<ValueRetriever> parent,
        std::vector<std::shared_ptr<ValueRetriever>> parameters
    ) const override;

    ~CFunction() { if(deleter) deleter(data); }

    void *data;
    SIPlusFunctionValue impl;
    SIPlusDataDeleterCallback deleter;
};

std::shared_ptr<ValueRetriever> CFunction::value(
    std::shared_ptr<ValueRetriever> parent,
    std::vector<std::shared_ptr<ValueRetriever>> parameters
) const {
    size_t argc = parameters.size();
    SIPlusValueRetriever *retrieverPtr = nullptr;
    SIPlusValueRetriever *parentPtr = nullptr;
    SIPlusValueRetriever **paramsPtr = new _SIPlusValueRetriever*[argc];

    if(parent) {
        parentPtr = new _SIPlusValueRetriever(parent);
    }

    for(int i = 0; i < argc; i++) {
        paramsPtr[i] = new _SIPlusValueRetriever(parameters[i]);
    }

    auto result = impl(&retrieverPtr, data, parentPtr, argc, paramsPtr);
    delete[] paramsPtr;

    if(result) {
        throw std::runtime_error{
            last_message.value_or(
                util::to_string(
                    "SIPlusFunction() on function failed with ", error_name(result)
                ))};
    }

    auto retriever = retrieverPtr->retriever;

    siplus_value_unref(retrieverPtr);

    return retriever;
}

struct CType : TypeInfo {
    CType(
        void *data,
        const TypeInfoDescriptor* descriptor,
        SIPlusTypeIsIterable is_iterable,
        SIPlusTypeAccess access,
        SIPlusTypeIndex index,
        SIPlusTypeIterate iterate,
        SIPlusDataDeleterCallback deleter
    ) : TypeInfo(descriptor),
        data(data), is_iterable_(is_iterable), iterate_(iterate), access_(access), index_(index), deleter_(deleter) { }

    bool is_iterable(const UnknownDataTypeContainer &data) const override;

    UnknownDataTypeContainer access(const UnknownDataTypeContainer &data, const std::string &name) const override;
    UnknownDataTypeContainer index(std::shared_ptr<SIPlusParserContext> context, 
          UnknownDataTypeContainer& value, UnknownDataTypeContainer& index) const override;
    std::unique_ptr<Iterator> iterate(const UnknownDataTypeContainer &data) const override;

    void add_extension_public(const BaseTypeExtensionImpl *impl) {
        this->add_extension(impl);
    }

    ~CType() { if(deleter_) deleter_(data); }

    void *data;

private:
    SIPlusTypeIsIterable is_iterable_;
    SIPlusTypeIterate iterate_;
    SIPlusTypeAccess access_;
    SIPlusTypeIndex index_;
    SIPlusDataDeleterCallback deleter_;
};

bool CType::is_iterable(const UnknownDataTypeContainer &value) const {
    return is_iterable_(data, value.ptr);
}

UnknownDataTypeContainer CType::access(const UnknownDataTypeContainer &value, const std::string &name) const {
    if(!access_) TypeInfo::access(value, name);

    SIPlusUnknownDataContainer *container;
    if(access_(&container, data, value.ptr, name.c_str())) {
        throw std::runtime_error{
            last_message.value_or(
                util::to_string(
                    "Accessing \"", name, "\" on object of type ", 
                    this->name(), " failed with ", error_name(last_error)
                ))};
    }

    UnknownDataTypeContainer ret = *container->container;
    siplus_data_delete(container);
    return ret;
}

UnknownDataTypeContainer CType::index(
    std::shared_ptr<SIPlusParserContext> context, 
    UnknownDataTypeContainer& value, 
    UnknownDataTypeContainer& index
) const {
    if(index_) {
        SIPlusContext cContext{context};
        SIPlusUnknownDataContainer *cIndex = new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(index)};

        SIPlusUnknownDataContainer *result;
        if(index_(&result, data, &cContext, value.ptr, cIndex)) {
            throw std::runtime_error{last_message.value_or(
                util::to_string(
                    "Indexing object of type '", value.type->name(), 
                    "' with value of type '", index.type->name(), 
                    "' failed with ", error_name(last_error)
                ))
            };
        }

        UnknownDataTypeContainer ret = *result->container;
        siplus_data_delete(result);
        return ret;
    } else {
        return TypeInfo::index(context, value, index);
    }
}

std::unique_ptr<Iterator> CType::iterate(const UnknownDataTypeContainer &value) const {
    if(!iterate_) TypeInfo::iterate(value);

    SIPlusIterator *iterator;
    if(iterate_(&iterator, data, value.ptr)) {
        throw std::runtime_error{
            last_message.value_or(
                util::to_string(
                    "Iterating on object of type ", this->name(), 
                    " failed with ", error_name(last_error)
                ))};
    }

    auto ret = std::move(iterator->iterator);
    siplus_iterator_delete(iterator);
    return ret;
}

struct CIterator : Iterator {
    CIterator(
        void *data,
        SIPlusIteratorMore more,
        SIPlusIteratorNext next,
        SIPlusIteratorCurrent current,
        SIPlusDataDeleterCallback deleter
    ) : data(data), more_(more), next_(next), current_(current), deleter_(deleter) {}

    bool more() override;
    void next() override;
    UnknownDataTypeContainer current() override;

    ~CIterator() { if(deleter_) deleter_(data); }

    void *data;

private:
    SIPlusIteratorMore more_;
    SIPlusIteratorNext next_;
    SIPlusIteratorCurrent current_;
    SIPlusDataDeleterCallback deleter_;
};


bool CIterator::more() {
    return more_(data);
}

void CIterator::next() {
    if(auto err = next_(data); err) {
        throw std::runtime_error{
            last_message.value_or(
                util::to_string(
                    "next() on iterator failed with ", error_name(err)
                ))};
    }
}

UnknownDataTypeContainer CIterator::current() {
    SIPlusUnknownDataContainer *container;
    if(auto err = current_(&container, data); err) {
        throw std::runtime_error{
            last_message.value_or(
                util::to_string(
                    "current() on iterator failed with ", error_name(err)
                ))};
    }

    auto ret = std::move(container->container);
    siplus_data_delete(container);
    return *ret;
}


template<simple_value_retrievable_type T, typename Out>
int siplus_data_as(Out *result, SIPlusUnknownDataContainer *value) {
    if(!result) return siplus_error_set(SIPLUS_INVALID_ARG, "result cannot be NULL");
    if(!value) return siplus_error_set(SIPLUS_INVALID_ARG, "value cannot be NULL");
    if(!value->container->is<T>()) {
        auto msg = util::to_string("value was not an instance of ", T::descriptor->name);
        return siplus_error_set(SIPLUS_INVALID_ARG, msg);
    }

    *result = value->container->as<T>();
    return SIPLUS_OK;
} 



struct CBinaryOperatorImpl : BinaryOperatorTypeExtensionImpl {
    CBinaryOperatorImpl(
        const BinaryOperatorTypeExtension *extension,
        void *data,
        SIPlusBinaryTypeExtensionImplCanHandleCallback can_handle,
        SIPlusBinaryTypeExtensionImplCallback impl,
        SIPlusDataDeleterCallback deleter
    ) : BinaryOperatorTypeExtensionImpl(extension),
        data_(data), can_handle_(can_handle), impl_(impl), deleter_(deleter) { }

    bool can_handle(const UnknownDataTypeContainer &other) const override;

    UnknownDataTypeContainer invoke(bool isLhs, const UnknownDataTypeContainer &thisValue, const UnknownDataTypeContainer &other) const override;

    ~CBinaryOperatorImpl() override {
        if(deleter_) {
            deleter_(data_);
        }
    }

private:
    void *data_;
    SIPlusBinaryTypeExtensionImplCallback impl_;
    SIPlusBinaryTypeExtensionImplCanHandleCallback can_handle_;
    SIPlusDataDeleterCallback deleter_;
};

bool CBinaryOperatorImpl::can_handle(const UnknownDataTypeContainer &other) const {
    int result;
    SIPlusUnknownDataContainer cOther{std::make_unique<UnknownDataTypeContainer>(other)};

    TRY_C(can_handle_(&result, data_, &cOther));

    return result;
}

UnknownDataTypeContainer CBinaryOperatorImpl::invoke(
    bool isLhs, 
    const UnknownDataTypeContainer &thisValue, 
    const UnknownDataTypeContainer &other
) const {
    SIPlusUnknownDataContainer *result = nullptr;
    SIPlusUnknownDataContainer cThisValue{std::make_unique<UnknownDataTypeContainer>(thisValue)};
    SIPlusUnknownDataContainer cOther{std::make_unique<UnknownDataTypeContainer>(other)};

    TRY_C(impl_(&result, data_, isLhs, &cThisValue, &cOther));
    if(result == nullptr) {
        throw std::runtime_error("SIPlusBinaryTypeExtensionImplCallback did not assign to result");
    }

    auto ret = *result->container;
    siplus_data_delete(result);

    return ret;
}

struct CUnaryOperatorImpl : UnaryOperatorTypeExtensionImpl {
    CUnaryOperatorImpl(
        const UnaryOperatorTypeExtension *extension,
        void *data,
        SIPlusUnaryTypeExtensionImplCallback impl,
        SIPlusDataDeleterCallback deleter
    ) : UnaryOperatorTypeExtensionImpl(extension),
        data_(data), impl_(impl), deleter_(deleter) { }

    UnknownDataTypeContainer invoke(const UnknownDataTypeContainer &thisValue) const override;

    ~CUnaryOperatorImpl() override {
        if(deleter_) {
            deleter_(data_);
        }
    }

private:
    void *data_;
    SIPlusUnaryTypeExtensionImplCallback impl_;
    SIPlusDataDeleterCallback deleter_;
};

UnknownDataTypeContainer CUnaryOperatorImpl::invoke(const UnknownDataTypeContainer &thisValue) const {
    SIPlusUnknownDataContainer *result = nullptr;
    SIPlusUnknownDataContainer cThisValue{std::make_unique<UnknownDataTypeContainer>(thisValue)};

    TRY_C(impl_(&result, data_, &cThisValue));
    if(result == nullptr) {
        throw std::runtime_error("SIPlusUnaryTypeExtensionImplCallback did not assign to result");
    }

    auto ret = *result->container;
    siplus_data_delete(result);

    return ret;
}

template<typename T, typename Base>
concept maybe_qualified = requires {
    requires std::same_as<Base, std::remove_cvref_t<T>>;
};

template<typename T> struct c_type_for {};
template<typename T> using c_type_for_t = c_type_for<T>::type;
template<typename T> struct cpp_type_for {};
template<typename T> using cpp_type_for_t = cpp_type_for<T>::type;

#define MAP_C_PTR_TYPE(cppType, cType) template<> struct c_type_for<cppType> { using type = cType; }; \
template<> struct cpp_type_for<cType> { using type = cppType; };

template<typename T, typename Out>
struct copy_const { using type = std::conditional_t<std::is_const_v<T>, const Out, Out>; };

template<typename T, typename Out>
struct copy_const<T*, Out> : copy_const<T, Out> {};

template<typename T, typename Out> using copy_const_t = copy_const<T, Out>::type;



MAP_C_PTR_TYPE(TypeInfoDescriptor, SIPlusTypeDescriptor);
MAP_C_PTR_TYPE(BinaryOperatorTypeExtension, SIPlusBinaryTypeExtensionDescriptor);
MAP_C_PTR_TYPE(UnaryOperatorTypeExtension, SIPlusUnaryTypeExtensionDescriptor);
MAP_C_PTR_TYPE(BinaryOperatorTypeExtensionImpl, SIPlusBinaryTypeExtensionImpl);
MAP_C_PTR_TYPE(UnaryOperatorTypeExtensionImpl, SIPlusUnaryTypeExtensionImpl);

using a = copy_const_t<const int*, float>;
using b = copy_const_t<int, float>;

template<typename T> concept is_c_type = requires() {
    typename cpp_type_for<std::remove_cvref_t<T>>::type;
};
template<typename T> concept is_cpp_type = requires() {
    typename c_type_for<std::remove_cvref_t<T>>::type;
};

template<is_cpp_type T>
auto cconvert(T *cdescriptor) {
    using ret_type = copy_const_t<T, c_type_for_t<std::remove_cvref_t<T>>>*;
    return reinterpret_cast<ret_type>(cdescriptor);
}

template<is_c_type T>
auto cconvert(T *descriptor) {
    using ret_type = copy_const_t<T, cpp_type_for_t<std::remove_cvref_t<T>>>*;
    return reinterpret_cast<ret_type>(descriptor);
}


//Theres some fuckery here with the consts and you probably could do some weird
//const casting-away somehow, but I don't think it really matters that much here.
//Idk, it just feels icky.
//
//Specifying SIPlusTypeInfo cconvert overloads manually because of needing  
//`shared_ptr<const T>` instead of just `const shared_ptr<T>`

/** */
std::shared_ptr<TypeInfo> *cconvert(SIPlusTypeInfo *info) {
    return reinterpret_cast<std::shared_ptr<TypeInfo>*>(info);
}

const std::shared_ptr<const TypeInfo> *cconvert(const SIPlusTypeInfo *info) {
    return reinterpret_cast<const std::shared_ptr<const TypeInfo>*>(info);
}

SIPlusTypeInfo *cconvert(std::shared_ptr<TypeInfo> *info) {
    return reinterpret_cast<SIPlusTypeInfo*>(info);
}

const SIPlusTypeInfo *cconvert(std::shared_ptr<const TypeInfo> *info) {
    return reinterpret_cast<const SIPlusTypeInfo*>(info);
}

/**
 * @brief Create a new SIPlusTypeInfo instance from a new TypeInfo instance.
 *
 * @tparam T The type to create
 * @return A new SIPlusTypeInfo pointer
 */
template<typename T>
const SIPlusTypeInfo *siplus_type_new_internal() {
    return cconvert(new std::shared_ptr<TypeInfo>(new T()));
}

} /* namespace anonymous */




extern "C" {



void siplus_string_delete(const char *ptr) {
    if(!ptr) { return; }
    delete[] ptr;
}



int siplus_error_get(char **message) {
    if(message) {
        if(last_message) {
            size_t size = last_message->size();

            *message = new char[size + 1];
            strncpy(*message, last_message->c_str(), size);
            (*message)[size] = 0;
        } else {
            *message = nullptr;
        }
    }

    return last_error;
}

int siplus_error_set(int err, const char *message) {
    last_error = err;
    if(message) {
        last_message = message;
    } else {
        last_message = std::nullopt;
    }
    return err;
}



SIPlusParser *siplus_parser_new() {
    return new _SIPlusParser();
}

int siplus_parser_context(SIPlusContext **context, SIPlusParser *parser) {
    SIPLUS_NOT_NULL(parser, context);

    *context =  new _SIPlusParserContext(parser->parser.context().shared_from_this());
    return siplus_error_set(SIPLUS_OK);
}

int siplus_parser_get_interpolation(
    SIPlusTextConstructor **constructor, SIPlusParser *parser, const char *text, SIPlusParseOpts *opts) {
    SIPLUS_NOT_NULL(constructor, parser, text);


    try {
        auto result = parser->parser.get_interpolation(text, opts ? opts->opts : ParseOpts{});
        *constructor = new _SIPlusTextConstructor{
            std::make_shared<text::TextConstructor>(result)
        };
        return siplus_error_set(SIPLUS_OK);
    } catch(std::exception& e) {
        return siplus_error_set(SIPLUS_PARSE_ERROR, e.what());
    }
}

int siplus_parser_get_expression(
    SIPlusValueRetriever **retriever, SIPlusParser *parser, const char *expr, SIPlusParseOpts *opts) {
    SIPLUS_NOT_NULL(retriever, parser, expr);

    *retriever = new _SIPlusValueRetriever();

    try {
        auto result = parser->parser.get_expression(expr, opts ? opts->opts : ParseOpts{});
        (*retriever)->retriever = result;
        return siplus_error_set(SIPLUS_OK);
    } catch(std::exception& e) {
        return siplus_error_set(SIPLUS_PARSE_ERROR, e.what());
    }
}

void siplus_parser_delete(SIPlusParser *parser) {
    if(!parser) return;
    delete parser;
}





int siplus_value_create(SIPlusValueRetriever **retriever, void* context, SIPlusRetrieverImpl impl, SIPlusDataDeleterCallback deleter) {
    SIPLUS_NOT_NULL(impl);

    *retriever = new _SIPlusValueRetriever();
    (*retriever)->retriever = std::make_shared<CValueRetriever>(context, impl, deleter);

    return siplus_error_set(SIPLUS_OK);
}

void *siplus_value_data_ptr(SIPlusValueRetriever *value) {
    if(!value) return nullptr;

    auto ptr = dynamic_cast<CValueRetriever*>(value->retriever.get());
    if(ptr != nullptr) {
        return ptr->data;
    } else {
        return nullptr;
    }
}

int siplus_value_retrieve(SIPlusUnknownDataContainer **data, SIPlusValueRetriever *value, SIPlusInvocationContext *context) {
    SIPLUS_NOT_NULL(value);

    try {
        auto result = value->retriever->retrieve(*context->context);
        *data = new _SIPlusUnknownDataContainer();
        (*data)->container = std::make_unique<UnknownDataTypeContainer>(result);
        return siplus_error_set(SIPLUS_OK);
    } catch(std::exception& e) {
        return siplus_error_set(SIPLUS_INVOKE_ERROR, e.what());
    }
}

void siplus_value_unref(SIPlusValueRetriever *retriever) {
    if(!retriever) return;
    delete retriever;
}




int siplus_text_construct(char **text, SIPlusTextConstructor *constructor, SIPlusInvocationContext *context) {
    SIPLUS_NOT_NULL(constructor);

    try {
        auto result = constructor->constructor->construct_with(context->context);
        *text = new char[result.size() + 1];
        strncpy(*text, result.c_str(), result.size());
        (*text)[result.size()] = 0; //Null terminate that bitch
        return siplus_error_set(SIPLUS_OK);
    } catch(std::exception& e) {
        return siplus_error_set(SIPLUS_INVOKE_ERROR, e.what());
    }

}

void siplus_text_unref(SIPlusTextConstructor *parser) {
    if(!parser) return;
    delete parser;
}



int siplus_function_create(SIPlusFunction **function, void *data, SIPlusFunctionValue value, SIPlusDataDeleterCallback deleter) {
    SIPLUS_NOT_NULL(function, value);

    auto func = std::make_shared<CFunction>(data, value, deleter);
    *function = new _SIPlusFunction { .function = func };
    return SIPLUS_OK;
}

void *siplus_function_data_ptr(SIPlusFunction *function) {
    if(!function) return nullptr;

    auto ptr = dynamic_cast<CFunction*>(function->function.get());
    if(ptr != nullptr) {
        return ptr->data;
    } else {
        return nullptr;
    }
}

int siplus_function_value(SIPlusValueRetriever **retriever, SIPlusFunction *function, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **params) {
    SIPLUS_NOT_NULL(retriever, function);

    if(paramc > 0 && params == nullptr) {
        return siplus_error_set(SIPLUS_INVALID_ARG, "paramc was >0, but params was NULL");
    }

    std::shared_ptr<ValueRetriever> parentPtr = nullptr;
    std::vector<std::shared_ptr<ValueRetriever>> paramsPtr(paramc);

    if(parent) {
        parentPtr = parent->retriever;
    }

    for(int i = 0; i < paramc; i++) {
        SIPLUS_NOT_NULL(params[i])
        paramsPtr[i] = params[i]->retriever;
    }

    try {
        auto result = function->function->value(parentPtr, paramsPtr);

        *retriever = new _SIPlusValueRetriever(result);

        return SIPLUS_OK;
    } catch(std::exception e) {
        return siplus_error_set(SIPLUS_INVOKE_ERROR, e.what());
    }
}

void siplus_function_unref(SIPlusFunction *function) {
    if(!function) return;
    delete function;
}





SIPlusParseOpts *siplus_parse_opts_new() {
    return new _SIPlusParseOpts();
}

int siplus_parse_opts_add_global(SIPlusParseOpts *opts, const char *name) {
    SIPLUS_NOT_NULL(opts, name);

    opts->opts.globals.emplace_back(name);

    return siplus_error_set(SIPLUS_OK);
}

void siplus_parse_opts_delete(SIPlusParseOpts *opts) {
    if(!opts) return;
    delete opts;
}




int siplus_context_add_function(SIPlusContext *parser, const char *name, SIPlusFunction *function) {
    SIPLUS_NOT_NULL(parser, function);

    parser->context->emplace_function(name, function->function);
    return siplus_error_set(SIPLUS_OK);
}

int siplus_context_use_stl(SIPlusContext *context) {
    SIPLUS_NOT_NULL(context);

    return siplus_error_set(SIPLUS_OK, NULL);
}

int siplus_context_builder(SIPlusInvocationContextBuilder **builder, SIPlusContext *context) {
    SIPLUS_NOT_NULL(context, builder);
    *builder = new _SIPlusInvocationContextBuilder{context->context->builder()};
    return siplus_error_set(SIPLUS_OK);
}

void siplus_context_unref(SIPlusContext *context) {
    if(!context) return;
    delete context;
}




int siplus_icbuilder_with(SIPlusInvocationContextBuilder *builder, const char *name, SIPlusUnknownDataContainer *container) {
    SIPLUS_NOT_NULL(builder, name, container);

    builder->builder.with(name, *container->container);
    return siplus_error_set(SIPLUS_OK);
}

int siplus_icbuilder_default(SIPlusInvocationContextBuilder *builder, SIPlusUnknownDataContainer *container) {
    SIPLUS_NOT_NULL(builder, container);

    builder->builder.use_default(*container->container);
    return siplus_error_set(SIPLUS_OK);
}

int siplus_icbuilder_build(SIPlusInvocationContext **context, SIPlusInvocationContextBuilder *builder) {
    SIPLUS_NOT_NULL(context, builder);
    *context = new SIPlusInvocationContext(builder->builder.build());
    return siplus_error_set(SIPLUS_OK);
}

void siplus_icbuilder_delete(SIPlusInvocationContextBuilder *builder) {
    if(!builder) return;
    delete builder;
}




void siplus_invocation_unref(SIPlusInvocationContext *context) {
    if(!context) return;
    delete context;
}






SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_new_binary(const char *name) {
    return cconvert(new BinaryOperatorTypeExtension(name));
}

SIPLUS_EXPORT const SIPlusUnaryTypeExtensionDescriptor *siplus_type_extension_new_unary(const char *name) {
    return cconvert(new UnaryOperatorTypeExtension(name));
}



SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_addable() {
    return cconvert(TypeInfo::Addable);
}

SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_subtractable() {
    return cconvert<const BinaryOperatorTypeExtension>(TypeInfo::Subtractable);
}

SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_multiplicable() {
    return cconvert(TypeInfo::Multiplicable);
}

SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_divisible() {
    return cconvert(TypeInfo::Divisible);
}

SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_equatable() {
    return cconvert(TypeInfo::Equatable);
}

SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_comparable() {
    return cconvert(TypeInfo::Comparable);
}

SIPLUS_EXPORT const SIPlusUnaryTypeExtensionDescriptor *siplus_type_extension_hashable() {
    return cconvert(TypeInfo::Hashable);
}

SIPLUS_EXPORT const SIPlusUnaryTypeExtensionDescriptor *siplus_type_extension_converter(const SIPlusTypeDescriptor *to_type) {
    return cconvert(make_conversion_descriptor(cconvert(to_type)));
}


SIPLUS_EXPORT SIPlusBinaryTypeExtensionImpl *siplus_type_extension_impl_new_binary(
    const SIPlusBinaryTypeExtensionDescriptor *extension,
    void *data, 
    SIPlusBinaryTypeExtensionImplCanHandleCallback can_handle,
    SIPlusBinaryTypeExtensionImplCallback impl, 
    SIPlusDataDeleterCallback deleter
) {
    SIPLUS_NOT_NULL(can_handle, impl);

    return cconvert((BinaryOperatorTypeExtensionImpl*)new CBinaryOperatorImpl(cconvert(extension), data, can_handle, impl, deleter));
}

SIPLUS_EXPORT SIPlusUnaryTypeExtensionImpl *siplus_type_extension_impl_new_unary(
    const SIPlusUnaryTypeExtensionDescriptor *extension,
    void *data, 
    SIPlusUnaryTypeExtensionImplCallback impl, 
    SIPlusDataDeleterCallback deleter
) {
    SIPLUS_NOT_NULL(impl);

    return cconvert((UnaryOperatorTypeExtensionImpl*)new CUnaryOperatorImpl(cconvert(extension), data, impl, deleter));
}


SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_array() {
    return cconvert(types::ArrayType::descriptor);
}

SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_string() {
    return cconvert(types::StringType::descriptor);
}

SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_float() {
    return cconvert(types::FloatType::descriptor);
}

SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_integer() {
    return cconvert(types::IntegerType::descriptor);
}

SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_bool() {
    return cconvert(types::BoolType::descriptor);
}

SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_null() {
    return cconvert(types::NullType::descriptor);
}


SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_new(const char *name) {
    return cconvert(new TypeInfoDescriptor(name));
}

SIPLUS_EXPORT void siplus_type_descriptor_delete(const SIPlusTypeDescriptor *descriptor) {
    delete cconvert(descriptor);
}


SIPlusTypeInfo *siplus_type_new_s(SIPlusTypeNewParams data) {
    return siplus_type_new(data.descriptor, data.data, data.is_iterable, data.access, data.index, data.iterate, data.deleter);;
}

SIPlusTypeInfo *siplus_type_new(
    const SIPlusTypeDescriptor *descriptor,
    void *data, 
    SIPlusTypeIsIterable is_iterable, 
    SIPlusTypeAccess access, 
    SIPlusTypeIndex index, 
    SIPlusTypeIterate iterate, 
    SIPlusDataDeleterCallback deleter
) {
    return cconvert(new std::shared_ptr<TypeInfo>{new CType{
        data, 
        cconvert(descriptor), 
        is_iterable, access, index, iterate, 
        deleter
    }});
}

const SIPlusTypeDescriptor *siplus_type_descriptor(const SIPlusTypeInfo *type) {
    if(!type) return nullptr;

    return cconvert((*cconvert(type))->descriptor());
}

void *siplus_type_data_ptr(const SIPlusTypeInfo *type) {
    if(!type) return nullptr;

    auto ptr = dynamic_cast<const CType*>(cconvert(type)->get());
    if(ptr != nullptr) {
        return ptr->data;
    } else {
        return nullptr;
    }
}

const SIPlusTypeInfo *siplus_type_int() {
    return siplus_type_new_internal<types::IntegerType>();
}

const SIPlusTypeInfo *siplus_type_float() {
    return siplus_type_new_internal<types::FloatType>();
}

const SIPlusTypeInfo *siplus_type_string() {
    return siplus_type_new_internal<types::StringType>();
}

const SIPlusTypeInfo *siplus_type_bool() {
    return siplus_type_new_internal<types::BoolType>();
}

const SIPlusTypeInfo *siplus_type_array() {
    return siplus_type_new_internal<types::ArrayType>();
}

const SIPlusTypeInfo *siplus_type_null() {
    return siplus_type_new_internal<types::NullType>();
}

SIPLUS_EXPORT const SIPlusUnaryTypeExtensionImpl *siplus_type_get_extension_unary(const SIPlusTypeInfo *info, const SIPlusUnaryTypeExtensionDescriptor *extension) {
    auto impl = (*cconvert(info))->get_extension(cconvert(extension));
    return cconvert(impl);
}

SIPLUS_EXPORT const SIPlusBinaryTypeExtensionImpl *siplus_type_get_extension_binary(const SIPlusTypeInfo *info, const SIPlusBinaryTypeExtensionDescriptor *extension) {
    auto impl = (*cconvert(info))->get_extension(cconvert(extension));
    return cconvert(impl);
}

SIPLUS_EXPORT void siplus_type_add_extension_unary(SIPlusTypeInfo *type, const SIPlusUnaryTypeExtensionImpl *impl) {
    CType *ctype = dynamic_cast<CType*>(cconvert(type)->get());
    ctype->add_extension_public(cconvert(impl));
}

SIPLUS_EXPORT void siplus_type_add_extension_binary(SIPlusTypeInfo *type, const SIPlusBinaryTypeExtensionImpl *impl) {
    CType *ctype = dynamic_cast<CType*>(cconvert(type)->get());
    ctype->add_extension_public(cconvert(impl));
}

int siplus_type_access(SIPlusUnknownDataContainer **result, const SIPlusTypeInfo *type, const SIPlusUnknownDataContainer *data, char *property) 
SIPLUS_TRY({
    SIPLUS_NOT_NULL(result, type, data, property);

    *result = new SIPlusUnknownDataContainer{
        std::make_unique<UnknownDataTypeContainer>((*cconvert(type))->access(*data->container, property))
    };

    return SIPLUS_OK;
})

int siplus_type_is_iterable(int *result, const SIPlusTypeInfo *info, const SIPlusUnknownDataContainer *data) 
SIPLUS_TRY({
    SIPLUS_NOT_NULL(info, data);

    *result = (*cconvert(info))->is_iterable(*data->container) ? 1 : 0;
    return SIPLUS_OK;
})

int siplus_type_iterate(SIPlusIterator **result, const SIPlusTypeInfo *typeInfo, const SIPlusUnknownDataContainer *container) 
SIPLUS_TRY({
    SIPLUS_NOT_NULL(result, typeInfo, container);

    *result = new SIPlusIterator{ (*cconvert(typeInfo))->iterate(*container->container) };

    return SIPLUS_OK;
})

int siplus_type_is(const SIPlusTypeInfo *first, const SIPlusTypeInfo *second) {
    SIPLUS_NOT_NULL(first, second);

    if(!first) return 0;
    if(!second) return 0;

    return **cconvert(first) == **cconvert(second);
}

int siplus_type_name(char *buf, size_t size, const SIPlusTypeInfo *first) {
    auto str = (*cconvert(first))->name();
    auto min = std::min(size, str.size() + 1); // + 1 for a NUL byte

    if(buf == NULL || size == 0) return str.size();

    strncpy(buf, str.c_str(), min);

    return min;
}

void siplus_type_unref(const SIPlusTypeInfo *type) {
    if(!type) return;
    delete cconvert(type);
}




SIPlusIterator *siplus_iterator_new(
    void *data, 
    SIPlusIteratorMore more, SIPlusIteratorNext next, 
    SIPlusIteratorCurrent current, SIPlusDataDeleterCallback deleter
) {
    SIPLUS_NOT_NULL(more, next, current)

    return new SIPlusIterator{
        std::make_unique<CIterator>(data, more, next, current, deleter)
    };
}

void *siplus_iterator_data_ptr(SIPlusIterator *iterator) {
    if(!iterator) return nullptr;

    auto ptr = dynamic_cast<CIterator*>(iterator->iterator.get());
    if(ptr != nullptr) {
        return ptr->data;
    } else {
        return nullptr;
    }
}

int siplus_iterator_next(SIPlusIterator *iterator) SIPLUS_TRY({
    SIPLUS_NOT_NULL(iterator);

    iterator->iterator->next();
    return SIPLUS_OK;
})

int siplus_iterator_more(int *result, SIPlusIterator *iterator) SIPLUS_TRY({
    SIPLUS_NOT_NULL(result, iterator);

    *result = iterator->iterator->more() ? 1 : 0;
    return SIPLUS_OK;
})

int siplus_iterator_current(SIPlusUnknownDataContainer **result, SIPlusIterator *iterator) SIPLUS_TRY({
    SIPLUS_NOT_NULL(result, iterator);

    *result = new SIPlusUnknownDataContainer{
        std::make_unique<UnknownDataTypeContainer>(iterator->iterator->current())
    };
    return SIPLUS_OK;
})

void siplus_iterator_delete(SIPlusIterator *iterator) {
    if(!iterator) return;
    delete iterator;
}



SIPlusUnknownDataContainer *siplus_data_make_int(int64_t value) {
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(make_data<types::IntegerType>(value))};
}

SIPlusUnknownDataContainer *siplus_data_make_float(double value){
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(make_data<types::FloatType>(value))};
}

SIPlusUnknownDataContainer *siplus_data_make_string(const char *text){
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(make_data<types::StringType>(text))};
}

SIPlusUnknownDataContainer *siplus_data_make_bool(int value){
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(make_data<types::BoolType>(value))};
}

SIPlusUnknownDataContainer *siplus_data_make_null() {
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>()};
}

SIPlusUnknownDataContainer *siplus_data_make(const SIPlusTypeInfo *type, void *data, SIPlusDataDeleterCallback deleter) {
    return new SIPlusUnknownDataContainer{
        std::make_unique<UnknownDataTypeContainer>(*cconvert(type), data, deleter)
    };
}

int siplus_data_is(SIPlusUnknownDataContainer *container, const SIPlusTypeInfo *type) {
    if(!container || !type) return 0;
    return (*container->container->type == **cconvert(type)) ? 1 : 0;
}

int siplus_data_is_int(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::IntegerType>() ? 1 : 0;
}

int siplus_data_is_float(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::FloatType>() ? 1 : 0;
}

int siplus_data_is_string(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::StringType>() ? 1 : 0;
}

int siplus_data_is_bool(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::BoolType>() ? 1 : 0;
}

int siplus_data_is_array(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::ArrayType>() ? 1 : 0;
}

int siplus_data_is_null(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::NullType>() ? 1 : 0;
}

const SIPlusTypeInfo *siplus_data_type(SIPlusUnknownDataContainer *container) {
    SIPLUS_NOT_NULL(container);

    return cconvert(new std::shared_ptr{container->container->type});
}

void *siplus_data_ptr(SIPlusUnknownDataContainer *container) {
    SIPLUS_NOT_NULL(container);
    
    return container->container->ptr;
}

int siplus_data_as_int(int64_t *result, SIPlusUnknownDataContainer *value) {
    return siplus_data_as<types::IntegerType>(result, value);
}

int siplus_data_as_float(double *result, SIPlusUnknownDataContainer *value) {
    return siplus_data_as<types::FloatType>(result, value);
}

int siplus_data_as_bool(int *result, SIPlusUnknownDataContainer *value) {
    return siplus_data_as<types::BoolType>(result, value);
}

int siplus_data_as_string(char **result, SIPlusUnknownDataContainer *value) {
    SIPLUS_NOT_NULL(result, value);

    if(!value->container->is<types::StringType>()) {
        return siplus_error_set(SIPLUS_INVALID_ARG, "value was not an instance of string");
    }
    
    std::string& text = value->container->as<types::StringType>();
    *result = new char[text.size() + 1];
    strncpy(*result, text.c_str(), text.size());
    (*result)[text.size()] = 0;

    return SIPLUS_OK;
}

void siplus_data_delete(SIPlusUnknownDataContainer *container) {
    if(!container) return;
    delete container;
}




}
