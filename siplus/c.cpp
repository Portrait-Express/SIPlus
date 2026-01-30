#include "siplus/csiplus.h"
#include "siplus/siplus.hxx"
#include "siplus/util.hxx"
#include <cstring>
#include <exception>
#include <memory>

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
    auto ptr = std::make_unique<_SIPlusInvocationContext>(value.shared_from_this());
    
    auto container = impl(data, ptr.get());

    UnknownDataTypeContainer ret = *container->container;

    siplus_data_delete(container);

    return ret;
}

struct CFunction : Function {
    CFunction(
        void *data,
        SIPlusFunction impl,
        SIPlusFunctionDeleter deleter
    ) : data(data), impl(impl), deleter(deleter) {}

    std::shared_ptr<text::ValueRetriever> value(
        std::shared_ptr<text::ValueRetriever> parent,
        std::vector<std::shared_ptr<text::ValueRetriever>> parameters
    ) const override;

    ~CFunction() { if(deleter) deleter(data); }

    void *data;
    SIPlusFunction impl;
    SIPlusFunctionDeleter deleter;
};

std::shared_ptr<text::ValueRetriever> CFunction::value(
    std::shared_ptr<text::ValueRetriever> parent,
    std::vector<std::shared_ptr<text::ValueRetriever>> parameters
) const {
    auto argc = parameters.size();
    auto parentPtr = new _SIPlusValueRetriever(parent);
    auto paramsPtr = new _SIPlusValueRetriever*[argc];
    for(int i = 0; i < argc; i++) {
        paramsPtr[i] = new _SIPlusValueRetriever(parameters[i]);
    }

    auto retrieverPtr = impl(data, parentPtr, argc, paramsPtr);
    auto retriever = retrieverPtr->retriever;

    siplus_value_delete(retrieverPtr);

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

} /* namespace anonymous */


extern "C" {



SIPLUS_EXPORTED int siplus_error_get(char **message) {
    if(message) {
        if(last_message) {
            size_t size = last_message->size();

            *message = new char[size + 1];
            strncpy(*message, last_message->c_str(), size);
            (*message)[size + 1] = 0;
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

SIPLUS_EXPORTED void siplus_error_message_delete(const char *message) {
    if(!message) return;
    delete message;
}



SIPLUS_EXPORTED SIPlusParser *siplus_parser_new() {
    return new _SIPlusParser();
}

SIPLUS_EXPORTED int siplus_parser_context(SIPlusContext **context, SIPlusParser *parser) {
    if(!parser) return siplus_error_set(SIPLUS_INVALID_ARG, "parser cannot be NULL");
    if(!context) return siplus_error_set(SIPLUS_INVALID_ARG, "context cannot be NULL");

    *context =  new _SIPlusParserContext(parser->parser.context().shared_from_this());
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_parser_get_interpolation(
    SIPlusTextConstructor **constructor, SIPlusParser *parser, const char *text, SIPlusParseOpts *opts) {
    if(!constructor) return siplus_error_set(SIPLUS_INVALID_ARG, "constructor cannot be NULL");
    if(!parser) return siplus_error_set(SIPLUS_INVALID_ARG, "parser cannot be NULL");
    if(!text) return siplus_error_set(SIPLUS_INVALID_ARG, "text cannot be NULL");

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
    if(!retriever) return siplus_error_set(SIPLUS_INVALID_ARG, "retriever cannot be NULL");
    if(!parser) return siplus_error_set(SIPLUS_INVALID_ARG, "parser cannot be NULL");
    if(!expr) return siplus_error_set(SIPLUS_INVALID_ARG, "expr cannot be NULL");

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
    if(!impl) return siplus_error_set(SIPLUS_INVALID_ARG, "impl cannot be NULL");

    *retriever = new _SIPlusValueRetriever();
    (*retriever)->retriever = std::make_shared<CValueRetriever>(context, impl, deleter);

    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_value_retrieve(SIPlusUnknownDataContainer **data, SIPlusValueRetriever *value, SIPlusInvocationContext *context) {
    if(!value) return siplus_error_set(SIPLUS_INVALID_ARG, "value cannot be NULL");

    try {
        auto result = value->retriever->retrieve(*context->context);
        *data = new _SIPlusUnknownDataContainer();
        (*data)->container = std::make_unique<UnknownDataTypeContainer>(result);
        return siplus_error_set(SIPLUS_OK);
    } catch(std::exception& e) {
        return siplus_error_set(SIPLUS_INVOKE_ERROR, e.what());
    }
}

SIPLUS_EXPORTED void siplus_value_delete(SIPlusValueRetriever *retriever) {
    if(!retriever) return;
    delete retriever;
}




SIPLUS_EXPORTED int siplus_text_construct(char **text, SIPlusTextConstructor *constructor, SIPlusInvocationContext *context) {
    if(!constructor) return siplus_error_set(SIPLUS_INVALID_ARG, "value cannot be NULL");

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

SIPLUS_EXPORTED void siplus_text_delete(SIPlusTextConstructor *parser) {
    if(!parser) return;
    delete parser;
}

SIPLUS_EXPORTED void siplus_text_result_delete(const char *text) {
    if(!text) return;
    delete[] text;
}





SIPLUS_EXPORTED SIPlusParseOpts *siplus_parse_opts_new() {
    return new _SIPlusParseOpts();
}

SIPLUS_EXPORTED int siplus_parse_opts_add_global(SIPlusParseOpts *opts, const char *name) {
    if(!opts) return siplus_error_set(SIPLUS_INVALID_ARG, "opts cannot be NULL");
    if(!name) return siplus_error_set(SIPLUS_INVALID_ARG, "name cannot be NULL");

    opts->opts.globals.emplace_back(name);

    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED void siplus_parse_opts_delete(SIPlusParseOpts *opts) {
    if(!opts) return;
    delete opts;
}




SIPLUS_EXPORTED int siplus_context_add_function(
    SIPlusContext *parser, const char *name, void *data, SIPlusFunction function, SIPlusFunctionDeleter deleter) {
    if(!parser) return siplus_error_set(SIPLUS_INVALID_ARG, "parser cannot be NULL");
    if(!function) return siplus_error_set(SIPLUS_INVALID_ARG, "function cannot be NULL");

    parser->context->emplace_function<CFunction>(name, data, function, deleter);
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_context_use_stl(SIPlusContext *context) {
    if(!context) return siplus_error_set(SIPLUS_INVALID_ARG, "context cannot be NULL");

    context->context->use_stl();

    return siplus_error_set(SIPLUS_OK, NULL);
}

SIPLUS_EXPORTED int siplus_context_builder(SIPlusInvocationContextBuilder **builder, SIPlusContext *context) {
    if(!context) return siplus_error_set(SIPLUS_INVALID_ARG, "context cannot be NULL");
    if(!builder) return siplus_error_set(SIPLUS_INVALID_ARG, "builder cannot be NULL");
    *builder = new _SIPlusInvocationContextBuilder{context->context->builder()};
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED void siplus_context_delete(SIPlusContext *context) {
    if(!context) return;
    delete context;
}




SIPLUS_EXPORTED int siplus_icbuilder_with(SIPlusInvocationContextBuilder *builder, const char *name, SIPlusUnknownDataContainer *container) {
    if(!builder) return siplus_error_set(SIPLUS_INVALID_ARG, "builder cannot be NULL");
    if(!name) return siplus_error_set(SIPLUS_INVALID_ARG, "name cannot be NULL");
    if(!container) return siplus_error_set(SIPLUS_INVALID_ARG, "container cannot be NULL");

    builder->builder.with(name, *container->container);
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_icbuilder_default(SIPlusInvocationContextBuilder *builder, SIPlusUnknownDataContainer *container) {
    if(!builder) return siplus_error_set(SIPLUS_INVALID_ARG, "builder cannot be NULL");
    if(!container) return siplus_error_set(SIPLUS_INVALID_ARG, "container cannot be NULL");

    builder->builder.use_default(*container->container);
    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED int siplus_icbuilder_build(SIPlusInvocationContext **context, SIPlusInvocationContextBuilder *builder) {
    if(!context) return siplus_error_set(SIPLUS_INVALID_ARG, "context cannot be NULL");
    if(!builder) return siplus_error_set(SIPLUS_INVALID_ARG, "builder cannot be NULL");

    *context = new SIPlusInvocationContext(builder->builder.build());
    delete builder;
    return siplus_error_set(SIPLUS_OK);
}




SIPLUS_EXPORTED void siplus_invocation_delete(SIPlusInvocationContext *context) {
    if(!context) return;
    delete context;
}




SIPLUS_EXPORTED int siplus_type_new(
    SIPlusTypeInfo **type,
    void *data, const char *name, 
    SIPlusTypeIsIterable is_iterable, SIPlusTypeAccess access, 
    SIPlusTypeIterate iterate, SIPlusTypeDeleter deleter
) {
    if(!type) return siplus_error_set(SIPLUS_INVALID_ARG, "type cannot be NULL");
    if(!name) return siplus_error_set(SIPLUS_INVALID_ARG, "name cannot be NULL");
    if(!is_iterable) return siplus_error_set(SIPLUS_INVALID_ARG, "is_iterable cannot be NULL");

    *type = new SIPlusTypeInfo{
        std::make_shared<CType>(
            data, name, is_iterable, access, iterate, deleter
        )
    };

    return siplus_error_set(SIPLUS_OK);
}

SIPLUS_EXPORTED void siplus_type_delete(SIPlusTypeInfo *type) {
    delete type;
}




SIPLUS_EXPORTED int siplus_iterator_new(
    SIPlusIterator **iterator, void *data, 
    SIPlusIteratorMore more, SIPlusIteratorNext next, 
    SIPlusIteratorCurrent current, SIPlusIteratorDeleter deleter
) {
    if(!iterator) return siplus_error_set(SIPLUS_INVALID_ARG, "iterator cannot be NULL");
    if(!more) return siplus_error_set(SIPLUS_INVALID_ARG, "more cannot be NULL");
    if(!next) return siplus_error_set(SIPLUS_INVALID_ARG, "next cannot be NULL");
    if(!current) return siplus_error_set(SIPLUS_INVALID_ARG, "current cannot be NULL");

    *iterator = new SIPlusIterator{
        std::make_unique<CIterator>(data, more, next, current, deleter)
    };

    return siplus_error_set(SIPLUS_OK);
}

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

using a = std::remove_cv_t<const char *>;
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

SIPLUS_EXPORTED void siplus_data_delete(SIPlusUnknownDataContainer *container) {
    if(!container) return;
    delete container;
}




}
