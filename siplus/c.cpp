#include "siplus/csiplus.h"
#include "siplus/siplus.hxx"
#include "siplus/types/array.hxx"
#include "siplus/types/bool.hxx"
#include "siplus/types/float.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"
#include "siplus/util.hxx"
#include <cstring>
#include <exception>
#include <iostream>
#include <memory>

#define __STR(x) #x
#define STR(x) __STR(x)

#define __COUNT(a1,a2,a3,a4,a5,a6,a7,a8,a9,a,...) a
#define COUNT(...) __COUNT(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)


#define __CONCAT_EX(a, b) a##b
#define CONCAT_EX(a, b) __CONCAT_EX(a, b)

#define __SIPLUS_NOT_NULL(var) \
    if(!var) return siplus_error_set(SIPLUS_INVALID_ARG, STR(var) " cannot be NULL");

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

struct _SIPlusTypeInfo {
    std::shared_ptr<TypeInfo> info;
};

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
    std::shared_ptr<text::ValueRetriever> retriever;
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
    std::unique_ptr<text::Iterator> iterator;
};

struct _SIPlusFunction {
    std::shared_ptr<Function> function;
};

namespace {

struct CValueRetriever : text::ValueRetriever {
    CValueRetriever(
        void *data, 
        SIPlusRetrieverImpl impl,
        SIPlusRetrieverDeleter deleter
    ) : data(data), impl(impl), deleter(deleter) {}

    UnknownDataTypeContainer retrieve(InvocationContext& value) const override;

    ~CValueRetriever() { if(deleter) deleter(data); }

    void *data;
    SIPlusRetrieverImpl impl;
    SIPlusRetrieverDeleter deleter;
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
        SIPlusFunctionDeleter deleter
    ) : data(data), impl(impl), deleter(deleter) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

    ~CFunction() { if(deleter) deleter(data); }

    void *data;
    SIPlusFunctionValue impl;
    SIPlusFunctionDeleter deleter;
};

std::shared_ptr<text::ValueRetriever> CFunction::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
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
        std::string name,
        SIPlusTypeIsIterable is_iterable,
        SIPlusTypeAccess access,
        SIPlusTypeIterate iterate,
        SIPlusTypeDeleter deleter
    ) : data_(data), name_(name), is_iterable_(is_iterable), iterate_(iterate), access_(access), deleter_(deleter) { }

    std::string name() const override;
    bool is_iterable(const UnknownDataTypeContainer &data) const override;

    UnknownDataTypeContainer access(const UnknownDataTypeContainer &data, const std::string &name) const override;
    std::unique_ptr<text::Iterator> iterate(const UnknownDataTypeContainer &data) const override;

    ~CType() { if(deleter_) deleter_(data_); }

    void *data_;
    std::string name_;
    SIPlusTypeIsIterable is_iterable_;
    SIPlusTypeIterate iterate_;
    SIPlusTypeAccess access_;
    SIPlusTypeDeleter deleter_;
};

std::string CType::name() const {
    return name_;
}

bool CType::is_iterable(const UnknownDataTypeContainer &data) const {
    return is_iterable_(data_, data.ptr);
}

UnknownDataTypeContainer CType::access(const UnknownDataTypeContainer &data, const std::string &name) const {
    if(!access_) TypeInfo::access(data, name);

    SIPlusUnknownDataContainer *container;
    if(access_(&container, data_, data.ptr, name.c_str())) {
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

std::unique_ptr<text::Iterator> CType::iterate(const UnknownDataTypeContainer &data) const {
    if(!iterate_) TypeInfo::iterate(data);

    SIPlusIterator *iterator;
    if(iterate_(&iterator, data_, data.ptr)) {
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

struct CIterator : text::Iterator {
    CIterator(
        void *data,
        SIPlusIteratorMore more,
        SIPlusIteratorNext next,
        SIPlusIteratorCurrent current,
        SIPlusIteratorDeleter deleter
    ) : data_(data), more_(more), next_(next), current_(current), deleter_(deleter) {}

    bool more() override;
    void next() override;
    UnknownDataTypeContainer current() override;

    ~CIterator() { if(deleter_) deleter_(data_); }

    void *data_;
    SIPlusIteratorMore more_;
    SIPlusIteratorNext next_;
    SIPlusIteratorCurrent current_;
    SIPlusIteratorDeleter deleter_;
};


bool CIterator::more() {
    return more_(data_);
}

void CIterator::next() {
    if(auto err = next_(data_); err) {
        throw std::runtime_error{
            last_message.value_or(
                util::to_string(
                    "next() on iterator failed with ", error_name(err)
                ))};
    }
}

UnknownDataTypeContainer CIterator::current() {
    SIPlusUnknownDataContainer *container;
    if(auto err = current_(&container, data_); err) {
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
        auto msg = util::to_string("value was not an instance of ", T{}.name());
        return siplus_error_set(SIPLUS_INVALID_ARG, msg);
    }

    *result = value->container->as<T>();
    return SIPLUS_OK;
} 


} /* namespace anonymous */


extern "C" {



SIPLUS_EXPORTED void siplus_string_delete(const char *ptr) {
    if(!ptr) { return; }
    delete[] ptr;
}



SIPLUS_EXPORTED int siplus_error_get(char **message) {
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

SIPLUS_EXPORTED int siplus_error_set(int err, const char *message) {
    last_error = err;
    if(message) {
        last_message = message;
    } else {
        last_message = std::nullopt;
    }
    return err;
}



SIPLUS_EXPORTED SIPlusParser *siplus_parser_new() {
    return new _SIPlusParser();
}

SIPLUS_EXPORTED int siplus_parser_context(SIPlusContext **context, SIPlusParser *parser) {
    SIPLUS_NOT_NULL(parser, context);

    *context =  new _SIPlusParserContext(parser->parser.context().shared_from_this());
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_parser_get_interpolation(
    SIPlusTextConstructor **constructor, SIPlusParser *parser, const char *text, SIPlusParseOpts *opts) {
    SIPLUS_NOT_NULL(constructor, parser, text);

    *constructor = new _SIPlusTextConstructor();

    try {
        auto result = parser->parser.get_interpolation(text, opts ? opts->opts : ParseOpts{});
        (*constructor)->constructor = std::make_shared<text::TextConstructor>(result);
        return siplus_error_set(SIPLUS_OK);
    } catch(std::exception& e) {
        return siplus_error_set(SIPLUS_PARSE_ERROR, e.what());
    }
}

SIPLUS_EXPORTED int siplus_parser_get_expression(
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

SIPLUS_EXPORTED void siplus_parser_delete(SIPlusParser *parser) {
    if(!parser) return;
    delete parser;
}





SIPLUS_EXPORTED int siplus_value_create(SIPlusValueRetriever **retriever, void* context, SIPlusRetrieverImpl impl, SIPlusRetrieverDeleter deleter) {
    SIPLUS_NOT_NULL(impl);

    *retriever = new _SIPlusValueRetriever();
    (*retriever)->retriever = std::make_shared<CValueRetriever>(context, impl, deleter);

    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_value_retrieve(SIPlusUnknownDataContainer **data, SIPlusValueRetriever *value, SIPlusInvocationContext *context) {
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

SIPLUS_EXPORTED void siplus_value_unref(SIPlusValueRetriever *retriever) {
    if(!retriever) return;
    delete retriever;
}




SIPLUS_EXPORTED int siplus_text_construct(char **text, SIPlusTextConstructor *constructor, SIPlusInvocationContext *context) {
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

SIPLUS_EXPORTED void siplus_text_unref(SIPlusTextConstructor *parser) {
    if(!parser) return;
    delete parser;
}



SIPLUS_EXPORTED int siplus_function_create(SIPlusFunction **function, void *data, SIPlusFunctionValue value, SIPlusFunctionDeleter deleter) {
    SIPLUS_NOT_NULL(function, value, deleter);

    auto func = std::make_shared<CFunction>(data, value, deleter);
    *function = new _SIPlusFunction { .function = func };
    return SIPLUS_OK;
}

SIPLUS_EXPORTED int siplus_function_value(SIPlusValueRetriever **retriever, SIPlusFunction *function, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **params) {
    SIPLUS_NOT_NULL(retriever, function);

    if(paramc > 0 && params == nullptr) {
        return siplus_error_set(SIPLUS_INVALID_ARG, "paramc was >0, but params was NULL");
    }

    std::shared_ptr<text::ValueRetriever> parentPtr = nullptr;
    std::vector<std::shared_ptr<text::ValueRetriever>> paramsPtr(paramc);

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

SIPLUS_EXPORTED void siplus_function_unref(SIPlusFunction *function) {
    if(!function) return;
    delete function;
}



SIPLUS_EXPORTED SIPlusParseOpts *siplus_parse_opts_new() {
    return new _SIPlusParseOpts();
}

SIPLUS_EXPORTED int siplus_parse_opts_add_global(SIPlusParseOpts *opts, const char *name) {
    SIPLUS_NOT_NULL(opts, name);

    opts->opts.globals.emplace_back(name);

    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED void siplus_parse_opts_delete(SIPlusParseOpts *opts) {
    if(!opts) return;
    delete opts;
}




SIPLUS_EXPORTED int siplus_context_add_function(SIPlusContext *parser, const char *name, SIPlusFunction *function) {
    SIPLUS_NOT_NULL(parser, function);

    parser->context->emplace_function(name, function->function);
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_context_use_stl(SIPlusContext *context) {
    SIPLUS_NOT_NULL(context);

    context->context->use_stl();

    return siplus_error_set(SIPLUS_OK, NULL);
}

SIPLUS_EXPORTED int siplus_context_builder(SIPlusInvocationContextBuilder **builder, SIPlusContext *context) {
    SIPLUS_NOT_NULL(context, builder);
    *builder = new _SIPlusInvocationContextBuilder{context->context->builder()};
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED void siplus_context_unref(SIPlusContext *context) {
    if(!context) return;
    delete context;
}




SIPLUS_EXPORTED int siplus_icbuilder_with(SIPlusInvocationContextBuilder *builder, const char *name, SIPlusUnknownDataContainer *container) {
    SIPLUS_NOT_NULL(builder, name, container);

    builder->builder.with(name, *container->container);
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_icbuilder_default(SIPlusInvocationContextBuilder *builder, SIPlusUnknownDataContainer *container) {
    SIPLUS_NOT_NULL(builder, container);

    builder->builder.use_default(*container->container);
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_icbuilder_build(SIPlusInvocationContext **context, SIPlusInvocationContextBuilder *builder) {
    SIPLUS_NOT_NULL(context, builder);
    *context = new SIPlusInvocationContext(builder->builder.build());
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED void siplus_icbuilder_delete(SIPlusInvocationContextBuilder *builder) {
    if(!builder) return;
    delete builder;
}




SIPLUS_EXPORTED void siplus_invocation_unref(SIPlusInvocationContext *context) {
    if(!context) return;
    delete context;
}




SIPLUS_EXPORTED int siplus_type_new(
    SIPlusTypeInfo **type,
    void *data, const char *name, 
    SIPlusTypeIsIterable is_iterable, SIPlusTypeAccess access, 
    SIPlusTypeIterate iterate, SIPlusTypeDeleter deleter
) {
    SIPLUS_NOT_NULL(type, name, is_iterable);

    *type = new SIPlusTypeInfo{
        std::make_shared<CType>(
            data, name, is_iterable, access, iterate, deleter
        )
    };

    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_int() {
    return new SIPlusTypeInfo{ std::make_shared<types::IntegerType>() };
}

SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_float() {
    return new SIPlusTypeInfo{ std::make_shared<types::FloatType>() };
}

SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_string() {
    return new SIPlusTypeInfo{ std::make_shared<types::StringType>() };
}

SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_bool() {
    return new SIPlusTypeInfo{ std::make_shared<types::BoolType>() };
}

SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_array() {
    return new SIPlusTypeInfo{ std::make_shared<types::ArrayType>() };
}

SIPLUS_EXPORTED int siplus_type_access(SIPlusUnknownDataContainer **result, SIPlusTypeInfo *type, SIPlusUnknownDataContainer *data, char *property) 
SIPLUS_TRY({
    SIPLUS_NOT_NULL(result, type, data, property);

    *result = new SIPlusUnknownDataContainer{
        std::make_unique<UnknownDataTypeContainer>(type->info->access(*data->container, property))
    };

    return SIPLUS_OK;
})

SIPLUS_EXPORTED int siplus_type_is_iterable(int *result, SIPlusTypeInfo *info, SIPlusUnknownDataContainer *data) 
SIPLUS_TRY({
    SIPLUS_NOT_NULL(info, data);

    *result = info->info->is_iterable(*data->container) ? 1 : 0;
    return SIPLUS_OK;
})

SIPLUS_EXPORTED int siplus_type_iterate(SIPlusIterator **result, SIPlusTypeInfo *typeInfo, SIPlusUnknownDataContainer *container) 
SIPLUS_TRY({
    SIPLUS_NOT_NULL(result, typeInfo, container);

    *result = new SIPlusIterator{ typeInfo->info->iterate(*container->container) };

    return SIPLUS_OK;
})

SIPLUS_EXPORTED int siplus_type_is(SIPlusTypeInfo *first, SIPlusTypeInfo *second) {
    if(!first) return 0;
    if(!second) return 0;

    return *first->info == *second->info;
}

SIPLUS_EXPORTED int siplus_type_name(char **name, SIPlusTypeInfo *first) {
    SIPLUS_NOT_NULL(name, first);

    auto str = first->info->name();
    *name = new char[str.size() + 1];
    strncpy(*name, str.c_str(), str.size());
    (*name)[str.size()] = 0;

    return SIPLUS_OK;
}

SIPLUS_EXPORTED void siplus_type_unref(SIPlusTypeInfo *type) {
    if(!type) return;
    delete type;
}




SIPLUS_EXPORTED int siplus_iterator_new(
    SIPlusIterator **iterator, void *data, 
    SIPlusIteratorMore more, SIPlusIteratorNext next, 
    SIPlusIteratorCurrent current, SIPlusIteratorDeleter deleter
) {
    SIPLUS_NOT_NULL(iterator, more, next, current)

    *iterator = new SIPlusIterator{
        std::make_unique<CIterator>(data, more, next, current, deleter)
    };

    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_iterator_next(SIPlusIterator *iterator) SIPLUS_TRY({
    SIPLUS_NOT_NULL(iterator);

    iterator->iterator->next();
    return SIPLUS_OK;
})

SIPLUS_EXPORTED int siplus_iterator_more(int *result, SIPlusIterator *iterator) SIPLUS_TRY({
    SIPLUS_NOT_NULL(result, iterator);

    *result = iterator->iterator->more() ? 1 : 0;
    return SIPLUS_OK;
})

SIPLUS_EXPORTED int siplus_iterator_current(SIPlusUnknownDataContainer **result, SIPlusIterator *iterator) SIPLUS_TRY({
    SIPLUS_NOT_NULL(result, iterator);

    *result = new SIPlusUnknownDataContainer{
        std::make_unique<UnknownDataTypeContainer>(iterator->iterator->current())
    };
    return SIPLUS_OK;
})

SIPLUS_EXPORTED void siplus_iterator_delete(SIPlusIterator *iterator) {
    if(!iterator) return;
    delete iterator;
}



SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_int(long value) {
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(make_data(value))};
}

SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_float(double value){
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(make_data(value))};
}

SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_string(const char *text){
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(make_data(text))};
}

SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_bool(int value){
    return new SIPlusUnknownDataContainer{std::make_unique<UnknownDataTypeContainer>(make_data(value))};
}

SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make(SIPlusTypeInfo *type, void *data, SIPlusUnknownDataContainerDeleter deleter) {
    return new SIPlusUnknownDataContainer{
        std::make_unique<UnknownDataTypeContainer>(type->info, data, deleter)
    };
}

SIPLUS_EXPORTED int siplus_data_is(SIPlusUnknownDataContainer *container, SIPlusTypeInfo *type) {
    if(!container || !type) return 0;
    return (*container->container->type == *type->info) ? 1 : 0;
}

SIPLUS_EXPORTED int siplus_data_is_int(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::IntegerType>() ? 1 : 0;
}

SIPLUS_EXPORTED int siplus_data_is_float(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::FloatType>() ? 1 : 0;
}

SIPLUS_EXPORTED int siplus_data_is_string(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::StringType>() ? 1 : 0;
}

SIPLUS_EXPORTED int siplus_data_is_bool(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::BoolType>() ? 1 : 0;
}

SIPLUS_EXPORTED int siplus_data_is_array(SIPlusUnknownDataContainer *container) {
    if(!container) return 0;
    return container->container->type->is<types::ArrayType>() ? 1 : 0;
}

SIPLUS_EXPORTED int siplus_data_type(SIPlusTypeInfo **type, SIPlusUnknownDataContainer *container) {
    SIPLUS_NOT_NULL(container, type);

    *type = new _SIPlusTypeInfo{};
    (*type)->info = container->container->type;

    return SIPLUS_OK;
}

SIPLUS_EXPORTED int siplus_data_ptr(void **data, SIPlusUnknownDataContainer *container) {
    SIPLUS_NOT_NULL(data, container);
    
    *data = container->container->ptr;
    return SIPLUS_OK;
}

SIPLUS_EXPORTED int siplus_data_as_int(long *result, SIPlusUnknownDataContainer *value) {
    return siplus_data_as<types::IntegerType>(result, value);
}

SIPLUS_EXPORTED int siplus_data_as_float(double *result, SIPlusUnknownDataContainer *value) {
    return siplus_data_as<types::FloatType>(result, value);
}

SIPLUS_EXPORTED int siplus_data_as_bool(int *result, SIPlusUnknownDataContainer *value) {
    return siplus_data_as<types::BoolType>(result, value);
}

SIPLUS_EXPORTED int siplus_data_as_string(char **result, SIPlusUnknownDataContainer *value) {
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

SIPLUS_EXPORTED void siplus_data_delete(SIPlusUnknownDataContainer *container) {
    if(!container) return;
    delete container;
}




}
