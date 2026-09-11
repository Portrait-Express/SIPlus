#pragma once
#ifndef INCLUDE_SIPLUS_SIPLUS_H_
#define INCLUDE_SIPLUS_SIPLUS_H_

// NOTE: Function parameters can be marked (Reference) or (Owner) which denotes 
// their ownership semantics. The exact semantics depend on whether or not the 
// parameter is an `in` or an `out` parameter. The exact semanatics are as follows:
//
// `in` parameter:
// - (Reference) The caller owns this object, and must delete it themselves. Callee 
//   must not use it after the call returns.
//
// - (Owner) The callee now owns the object, and is responsible for its lifetime.
//
// `out` parameter:
// - (Reference) The object is still owned by the callee, and it's lifetime is ended
//   by some other mechanism. Instances of this will be documented separately on how 
//   the returned value is managed. Check the function's docs.
//
// - (Owner) The caller now owns the object, and is responsible for deleting it.

#include <stdint.h>
#include <stddef.h>

#include "siplus/config.h"

enum SIPlusErrors {
    SIPLUS_OK = 0,
    SIPLUS_ERR,
    SIPLUS_INVALID_ARG,
    SIPLUS_PARSE_ERROR,
    SIPLUS_INVOKE_ERROR
};

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _SIPlusTypeDescriptor                   SIPlusTypeDescriptor;

typedef struct _SIPlusTypeExtensionDescriptor          SIPlusTypeExtensionDescriptor;
typedef struct _SIPlusTypeExtensionImpl                SIPlusTypeExtensionImpl;

typedef struct _SIPlusBinaryTypeExtensionDescriptor    SIPlusBinaryTypeExtensionDescriptor;
typedef struct _SIPlusBinaryTypeExtensionImpl          SIPlusBinaryTypeExtensionImpl;

typedef struct _SIPlusUnaryTypeExtensionDescriptor     SIPlusUnaryTypeExtensionDescriptor;
typedef struct _SIPlusUnaryTypeExtensionImpl           SIPlusUnaryTypeExtensionImpl;

typedef struct _SIPlusTypeInfo                         SIPlusTypeInfo;

struct _SIPlusUnknownDataContainer;
typedef struct _SIPlusUnknownDataContainer             SIPlusUnknownDataContainer;

struct _SIPlusParser;
typedef struct _SIPlusParser                           SIPlusParser;

struct _SIPlusParseOpts;
typedef struct _SIPlusParseOpts                        SIPlusParseOpts;

struct _SIPlusFunction;
typedef struct _SIPlusFunction                         SIPlusFunction;

struct _SIPlusParserContext;
typedef struct _SIPlusParserContext                    SIPlusContext;

struct _SIPlusInvocationContext;
typedef struct _SIPlusInvocationContext                SIPlusInvocationContext;

struct _SIPlusValueRetriever;
typedef struct _SIPlusValueRetriever                   SIPlusValueRetriever;

struct _SIPlusTextConstructor;
typedef struct _SIPlusTextConstructor                  SIPlusTextConstructor;

struct _SIPlusInvocationContextBuilder;
typedef struct _SIPlusInvocationContextBuilder         SIPlusInvocationContextBuilder;

struct _SIPlusIterator;
typedef struct _SIPlusIterator                         SIPlusIterator;

typedef void (*SIPlusDataDeleterCallback)(void* data);

/**
 * @brief Get the result of this function. 
 *
 * @param[out] result (Owner) The created value retriever
 * @param[in] data (Reference) The data void* that was passed to siplus_context_add_function
 * @param[in] parent (Owner) The parent ValueRetriever
 * @param[in] paramc The size of paramv
 * @param[in] paramv (Owner) The ValueRetriever parameter list. (You do not need to delete 
 * the memory for the array iself, just siplus_value_unref)
 */
typedef int (*SIPlusFunctionValue)(SIPlusValueRetriever **result, void *data, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **paramv);



/**
 * @brief Implementation for the ValueRetriever
 *
 * @param[out] result (Owner) The result data
 * @param[in] data (Reference) The data void* passed to siplus_value_create
 * @param[in] context (Reference) The InvocationContext for this invocation of the retriever.
 * @return Error code
 */
typedef int (*SIPlusRetrieverImpl)(SIPlusUnknownDataContainer **result, void *data, SIPlusInvocationContext *context);





typedef int (*SIPlusIteratorMore)(void *data);
typedef int (*SIPlusIteratorNext)(void *data);
typedef int (*SIPlusIteratorCurrent)(SIPlusUnknownDataContainer **result, void *data);

/**
 * @brief Implementation for BinaryOperatorTypeExtensionImpl::can_handle
 *
 * @param[out] result The result of the operation. 1 if this can handle the other value.
 * @param[in] (Reference) data The void* data passed to impl_new
 * @param[in] (Reference) other The other value that will be passed to invoke()
 * @return Error code
 */
typedef int (*SIPlusBinaryTypeExtensionImplCanHandleCallback)(int *result, void *data, SIPlusUnknownDataContainer *other);

/**
 * @brief Implementation for BinaryOperatorTypeExtensionImpl::invoke
 *
 * @param[out] (Owner) result The result of the operation
 * @param[in] (Reference) data The void* data passed to impl_new
 * @param[in] isLhs boolean value. Will be 1 if `thisValue` is lhs of the operation, false if rhs
 * @param[in] (Reference) thisVal The value of the type this implementation is attached to.
 * @param[in] (Reference) other The other value
 * @return Error code
 */
typedef int (*SIPlusBinaryTypeExtensionImplCallback)(SIPlusUnknownDataContainer **result, void *data, int isLhs, SIPlusUnknownDataContainer *thisVal, SIPlusUnknownDataContainer *other);


/**
 * @brief Callback for UnaryTypeExtensionImpl::invoke
 *
 * @param[in] data (Reference) The data void* passed to siplus_type_extension_unary_new
 * @param[in] container (Reference) The data object.
 * @return TRUE if the type is iterable
 */
typedef int (*SIPlusUnaryTypeExtensionImplCallback)(SIPlusUnknownDataContainer **result, void *data, SIPlusUnknownDataContainer *value);


/**
 * @brief Callback for TypeInfo::is_iterable
 *
 * @param[in] data (Reference) The data void* passed to siplus_type_new
 * @param[in] container (Reference) The data object.
 * @return TRUE if the type is iterable
 */
typedef int (*SIPlusTypeIsIterable)(void *data, void *container);

/**
 * @brief Iterate over a type
 *
 * @param[out] (Owner) A new iterator created with siplus_iterator_new
 * @param[in] (Reference) data The data void* passed to siplus_type_new
 * @param[in] (Reference) container The data object. This will be deleted after this call. 
 * @return Error code
 */
typedef int (*SIPlusTypeIterate)(SIPlusIterator **result, void *data, void *container);

/**
 * @brief Access a property on an object
 *
 * @param[out] data (Owner) The result
 * @param[in] data (Reference) The data void* passed to siplus_type_new
 * @param[in] container (Reference) The data object to access
 * @param[in] name (Reference) The property name
 * @return Error code
 */
typedef int (*SIPlusTypeAccess)(SIPlusUnknownDataContainer **result, void *data, void *container, const char *name);

/**
 * @brief Index a property on an object
 *
 * @param[out] data (Owner) The result
 * @param[in] data (Reference) The data void* passed to siplus_type_new
 * @param[in] context (Reference) Context object
 * @param[in] value (Reference) The data object to access
 * @param[in] index (Owner) The index value
 * @return Error code
 */
typedef int (*SIPlusTypeIndex)(SIPlusUnknownDataContainer **result, void *data, SIPlusContext *context,
                               void *value, SIPlusUnknownDataContainer *index);

/**
 * struct SIPlusTypeInfoData - Collection of data required for implementing SIPlusTypeInfo
 * iterate may be NULL as long as is_iterable will never be true.
 */
struct SIPlusTypeNewParams {
    void *data;
    const SIPlusTypeDescriptor *descriptor;
    SIPlusTypeAccess access;
    SIPlusTypeIndex index;
    SIPlusTypeIterate iterate;
    SIPlusTypeIsIterable is_iterable;
    SIPlusDataDeleterCallback deleter;
};
typedef struct SIPlusTypeNewParams SIPlusTypeNewParams;


/**
 * @brief Free a string result. Any function that uses char** to return text 
 * must have this called afterwards unless otherwise specified.
 *
 * @param[in] ptr (Owner) The text pointer returned from another siplus_* function
 */
SIPLUS_EXPORT void siplus_string_delete(const char *ptr);

/**
 * @brief Get the error message. Free the pointer with `siplus_string_delete`.
 *
 * @param[out] message (Owner) The message
 * @return The error code stored with the message.
 */
SIPLUS_EXPORT int siplus_error_get(char **message);

/**
 * @brief Set an error. If any of your function implementations fail, call this.
 *
 * @param[in] err The error code
 * @param[in] message (Reference) The error message. This is copied and stored, so you may free your message.
 * @return The value passed into `err`
 */
SIPLUS_EXPORT int siplus_error_set(int err, const char *message);



/**
 * @brief Create a new parser instance.
 *
 * @return (Owner) The new parser.
 */
SIPLUS_EXPORT SIPlusParser *siplus_parser_new();

/**
 * @brief Get the parser's context
 *
 * @param[out] context (Owner) The context
 * @param[in] parser (Reference) The parser
 * @return Error code
 */
SIPLUS_EXPORT int siplus_parser_context(SIPlusContext **context,  SIPlusParser *parser);

/**
 * @brief Get an interpolation from the parser
 *
 * @param[out] constructor (Owner) The constructor result. You will need to `unref` this when you are finished.
 * @param[in] parser (Reference) The parser
 * @param[in] text (Reference) The interpolation's text
 * @param[in] opts (Reference) Parser options. Pass NULL to use default as a shortcut.
 * @return Error code
 */
SIPLUS_EXPORT int siplus_parser_get_interpolation(SIPlusTextConstructor **constructor, SIPlusParser *parser, const char *text, SIPlusParseOpts *opts);
/**
 * @brief Get an expression ValueRetriever
 *
 * @param[out] retriever (Owner) The retriever result. You will need to `unref` this when you are finished.
 * @param[in] parser (Reference) The parser
 * @param[in] expr (Reference) The expression
 * @param[in] opts (Reference) Parser options. Pass NULL to use default as a shortcut.
 * @return Error code
 */
SIPLUS_EXPORT int siplus_parser_get_expression(SIPlusValueRetriever **retriever, SIPlusParser *parser, const char *expr, SIPlusParseOpts *opts);

/**
 * @brief Delete a parser. 
 *
 * @param[in] parser (Owner) The parser to delete
 */
SIPLUS_EXPORT void siplus_parser_delete(SIPlusParser *parser);



/**
 * @brief Create a new function
 *
 * @param[out] function (Owner) The function. You will need to `unref` this when you are finished.
 * @param[in] data (Owner) Any data you wish to store with this function.
 * @param[in] value `value` implementation
 * @param[in] deleter Deleter for `data` when this function is deleted
 * @return Error code
 */
SIPLUS_EXPORT int siplus_function_create(SIPlusFunction **function, void *data, SIPlusFunctionValue value, SIPlusDataDeleterCallback deleter);

/**
 * @brief Get the void *data passed into siplus_function_create.
 *
 * @param[in] function (Reference) Pointer to the object
 * @return The void *passed to siplus_function_create, or NULL if function is 
 * not valid, or not a function created with siplus_function_create
 */
SIPLUS_EXPORT void *siplus_function_data_ptr(SIPlusFunction *function);

/**
 * @brief Get the value from a function
 *
 * @param[out] retriever (Owner) The result of `value`. You will need to `unref` this when you are finished.
 * @param[in] function (Reference) The function
 * @param[in] parent (TODO) Parent value. Use NULL if none.
 * @param[in] paramc Parameter count
 * @param[in] params (TODO) Parameter list
 * @return Error code
 */
SIPLUS_EXPORT int siplus_function_value(SIPlusValueRetriever **retriever, SIPlusFunction *function, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **params);

/**
 * @brief Dereference a function. These are reference counted, so this will not 
 * always result in a deletion of your function.
 *
 * @param[in] function (Owner) The function
 */
SIPLUS_EXPORT void siplus_function_unref(SIPlusFunction *function);



/**
 * @brief Get the result from a TextConstructor.
 *
 * @param[out] text (Owner) The result. Delete this with `siplus_string_delete`
 * @param[in] value (Reference) The text constructor
 * @param[in] context (Reference) The invocation context
 * @return Error code
 */
SIPLUS_EXPORT int siplus_text_construct(char **text, SIPlusTextConstructor *value, SIPlusInvocationContext *context);

/**
 * @brief Dereference a TextConstructor.
 *
 * @param[in] constructor (Owner) The constructor
 */
SIPLUS_EXPORT void siplus_text_unref(SIPlusTextConstructor *constructor);



/**
 * @brief Create a new ValueRetriever
 *
 * @param[out] retriever (Owner) The ValueRetriever
 * @param[in] data (Owner) Data to store with your retriever
 * @param[in] impl The implementation to retrieve the value
 * @param[in] deleter Deleter for `data`
 * @return Error Code
 */
SIPLUS_EXPORT int siplus_value_create(SIPlusValueRetriever **retriever, void* data, SIPlusRetrieverImpl impl, SIPlusDataDeleterCallback deleter);

/**
 * @brief Get the void *data passed into siplus_value_create
 *
 * @param[in] value (Reference) Pointer to the object
 * @return The void *passed to siplus_value_create, or NULL if value is 
 * not valid, or not a value created with siplus_value_create
 */
SIPLUS_EXPORT void *siplus_value_data_ptr(SIPlusValueRetriever *value);

/**
 * @brief retrieve the value from a ValueRetriever
 *
 * @param[out] data (Owner) The result of the operation
 * @param[in] value (Reference) The ValueRetriever
 * @param[in] context (Reference) The invocation context
 * @return Error Code
 */
SIPLUS_EXPORT int siplus_value_retrieve(SIPlusUnknownDataContainer **data, SIPlusValueRetriever *value, SIPlusInvocationContext *context);

/**
 * @brief Dereference a ValueRetriever. These are reference counted, so this will not 
 * always result in a deletion of your ValueRetriever.
 *
 * @param[in] function (Owner) The ValueRetriever
 */
SIPLUS_EXPORT void siplus_value_unref(SIPlusValueRetriever *parser);



/**
 * @brief Create new Parser Opts
 *
 * @return (Owner) New parser options
 */
SIPLUS_EXPORT SIPlusParseOpts *siplus_parse_opts_new();
/**
 * @brief Add a global to be available in a template.
 *
 * @param[in] opts (Reference) The options
 * @param[in] name (Reference) The name of the global variable
 * @return Error code
 */
SIPLUS_EXPORT int siplus_parse_opts_add_global(SIPlusParseOpts *opts, const char *name);

/**
 * @brief Delete parser options
 *
 * @param[in] opts (Owner) The options to free
 */
SIPLUS_EXPORT void siplus_parse_opts_delete(SIPlusParseOpts *opts);



/**
 * @brief Add a function to a ParserContext, to make it available during template creation.
 *
 * @param[in] context (Reference) The context
 * @param[in] name (Reference) The name of the function
 * @param[in] function (Reference) The function 
 * @return Error Code
 */
SIPLUS_EXPORT int siplus_context_add_function(SIPlusContext *context, const char *name, SIPlusFunction *function);

/**
 * @brief Attach the STL library of functions and converters.
 *
 * @param[in] context (Reference) Context
 * @return Error Code
 */
SIPLUS_EXPORT int siplus_context_use_stl(SIPlusContext *context);

/**
 * @brief Get a builder for an InvocationContext.
 *
 * @param[out] builder (Owner) The created ContextBuilder
 * @param[in] context (Reference) The Parser context
 * @return Error Code
 */
SIPLUS_EXPORT int siplus_context_builder(SIPlusInvocationContextBuilder **builder, SIPlusContext *context);

/**
 * @brief Dereference a ParserContext. Call this for any context received from siplus_parser_context().
 *
 * @param[in] function (Owner) The context
 */
SIPLUS_EXPORT void siplus_context_unref(SIPlusContext *context);



/**
 * @brief Define a value for a variable for this Invocation.
 *
 * @param[in] builder (Reference) The InvocationContextBuilder
 * @param[in] name (Reference) The name of the variable
 * @param[in] container (Reference) The data
 * @return Error Code
 */
SIPLUS_EXPORT int siplus_icbuilder_with(SIPlusInvocationContextBuilder *builder, const char *name, SIPlusUnknownDataContainer *container);

/**
 * @brief Set the default data to use
 *
 * @param[in] builder (Reference) The InvocationContextBuilder
 * @param[in] container (Reference) The data
 * @return Error code
 */
SIPLUS_EXPORT int siplus_icbuilder_default(SIPlusInvocationContextBuilder *builder, SIPlusUnknownDataContainer *container);

/**
 * @brief Get an InvocationContext from the Builder
 *
 * @param[out] context (Owner) The InvocationContext
 * @param[in] builder (Reference) The builder
 * @return Error code
 */
SIPLUS_EXPORT int siplus_icbuilder_build(SIPlusInvocationContext **context, SIPlusInvocationContextBuilder *builder);

/**
 * @brief Free an InvocationContextBuilder
 *
 * @param[in] builder (Owner) The builder
 */
SIPLUS_EXPORT void siplus_icbuilder_delete(SIPlusInvocationContextBuilder *builder);



/**
 * @brief Free an InvocationContext
 *
 * @param[in] context (Owner) The InvocationContext
 */
SIPLUS_EXPORT void siplus_invocation_unref(SIPlusInvocationContext *context);



SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_new_binary(const char *name);
SIPLUS_EXPORT const SIPlusUnaryTypeExtensionDescriptor *siplus_type_extension_new_unary(const char *name);


SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_addable();
SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_subtractable();
SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_multiplicable();
SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_divisible();
SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_equatable();
SIPLUS_EXPORT const SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_comparable();
SIPLUS_EXPORT const SIPlusUnaryTypeExtensionDescriptor *siplus_type_extension_hashable();
SIPLUS_EXPORT const SIPlusUnaryTypeExtensionDescriptor *siplus_type_extension_converter(const SIPlusTypeDescriptor *to_type);


SIPLUS_EXPORT SIPlusBinaryTypeExtensionImpl *siplus_type_extension_impl_new_binary(
    const SIPlusBinaryTypeExtensionDescriptor *extension,
    void *data, 
    SIPlusBinaryTypeExtensionImplCanHandleCallback can_handle,
    SIPlusBinaryTypeExtensionImplCallback impl, 
    SIPlusDataDeleterCallback deleter
);

SIPLUS_EXPORT SIPlusUnaryTypeExtensionImpl *siplus_type_extension_impl_new_unary(
    const SIPlusUnaryTypeExtensionDescriptor *extension,
    void *data, 
    SIPlusUnaryTypeExtensionImplCallback impl, 
    SIPlusDataDeleterCallback deleter
);

SIPLUS_EXPORT SIPlusUnaryTypeExtensionDescriptor *siplus_type_extension_impl_descriptor_unary(const SIPlusUnaryTypeExtensionImpl *impl);
SIPLUS_EXPORT SIPlusBinaryTypeExtensionDescriptor *siplus_type_extension_impl_descriptor_binary(const SIPlusBinaryTypeExtensionImpl *impl);

SIPLUS_EXPORT int siplus_type_extension_impl_invoke_unary(
    SIPlusUnknownDataContainer **out,
    const SIPlusUnaryTypeExtensionImpl *impl,
    SIPlusUnknownDataContainer *data
);
SIPLUS_EXPORT int siplus_type_extension_impl_invoke_binary(
    SIPlusUnknownDataContainer **out,
    const SIPlusBinaryTypeExtensionImpl *impl,
    int isLhs,
    SIPlusUnknownDataContainer *thisValue,
    SIPlusUnknownDataContainer *other
);



/**
 * @brief Create a new TypeInfoDescriptor. The returned pointer will be used to 
 * uniquely identify a new type. Generally this should only be called once for
 * each type over the program's lifespan. These are considered static storage 
 * objects that will survive for long times.
 *
 * Using `siplus_type_descriptor_delete` is generally discouraged as well. 
 * Usually type descriptors will be left for the kernel to remove when unmapping
 * process memory. 
 *
 * @param[in] name The name of the type this descriptor will represent.
 * @return A pointer to a new type descriptor.
 */
SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_new(const char *name);

/**
 * @brief Get a descriptor for the array type.
 *
 * @return The type descriptor. Do not free this.
 */
SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_array();

/**
 * @brief Get a descriptor for the string type.
 *
 * @return The type descriptor. Do not free this.
 */
SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_string();

/**
 * @brief Get a descriptor for the float type.
 *
 * @return The type descriptor. Do not free this.
 */
SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_float();

/**
 * @brief Get a descriptor for the integer type.
 *
 * @return The type descriptor. Do not free this.
 */
SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_integer();

/**
 * @brief Get a descriptor for the bool type.
 *
 * @return The type descriptor. Do not free this.
 */
SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_bool();

/**
 * @brief Get a descriptor for the null type.
 *
 * @return The type descriptor. Do not free this.
 */
SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor_null();

/**
 * @brief Delete a type descriptor. Only do this when you are SURE that the 
 * type will never be used again, and only call this on desciptors you created. 
 * Ideally, never call this and just let the pointer leak to get cleaned up at 
 * process end.
 */
SIPLUS_EXPORT void siplus_type_descriptor_delete(const SIPlusTypeDescriptor *descriptor);



/**
 * @brief Create a new TypeInfo. This method takes a struct containing the arguments 
 * to siplus_type_new, in order to reduce the parameter count. Each member of 
 * `data` follows the same rules as the corresponding parameter in `siplus_type_new`
 *
 * @param[out] type (Owner) The created type info
 * @param[in] data Parameter collection to pass to `siplus_type_new`
 * @return [TODO:description]
 */
SIPLUS_EXPORT SIPlusTypeInfo *siplus_type_new_s(SIPlusTypeNewParams data);

/**
 * @brief Create a new TypeInfo
 *
 * @param[out] type (Owner) The TypeInfo
 * @param[in] data (Owner) Data to store with the type.
 * @param[in] name (Reference) The name of your type
 * @param[in] is_iterable `is_iterable()` implementation. REQUIRED
 * @param[in] access `access()` implementation. You may pass NULL of there are no accessible properties.
 * @param[in] index `index()` implementation. You may pass NULL to use the default indexer behavior.
 * @param[in] iterate iterate() implementation. You may pass NULL if your type is not iterable.
 * @param[in] deleter Deleter for `data`. You may pass NULL.
 * @return Error Code
 */
SIPLUS_EXPORT SIPlusTypeInfo *siplus_type_new(const SIPlusTypeDescriptor *descriptor, void *data, SIPlusTypeIsIterable is_iterable, SIPlusTypeAccess access, SIPlusTypeIndex index, SIPlusTypeIterate iterate, SIPlusDataDeleterCallback deleter);


/**
 * @brief Get an implementation for a type extension.
 *
 * @param[in] type The type to find an implementation on
 * @param[in] impl The impl to add
 * @return Error code
 */
SIPLUS_EXPORT const SIPlusUnaryTypeExtensionImpl *siplus_type_get_extension_unary(const SIPlusTypeInfo *info, const SIPlusUnaryTypeExtensionDescriptor *extension);

/**
 * @brief Get an implementation for a type extension.
 *
 * @param[in] type The type to find an implementation on
 * @param[in] impl The impl to add
 * @return Error code
 */
SIPLUS_EXPORT const SIPlusBinaryTypeExtensionImpl *siplus_type_get_extension_binary(const SIPlusTypeInfo *info, const SIPlusBinaryTypeExtensionDescriptor *extension);

/**
 * @brief Add an implementation for a type extension. Only call this on types 
 * that you created with siplus_type_new.
 *
 * @param[in] type The type to add an implementation to
 * @param[in] impl The impl to add
 * @return Error code
 */
SIPLUS_EXPORT void siplus_type_add_extension_unary(SIPlusTypeInfo *type, const SIPlusUnaryTypeExtensionImpl *impl);

/**
 * @brief Add an implementation for a type extension. Only call this on types 
 * that you created with siplus_type_new.
 *
 * @param[in] type The type to add an implementation to
 * @param[in] impl The impl to add
 * @return Error code
 */
SIPLUS_EXPORT void siplus_type_add_extension_binary(SIPlusTypeInfo *type, const SIPlusBinaryTypeExtensionImpl *impl);

/**
 * @brief Get the void *data passed into siplus_type_new.
 *
 * @param[in] type (Reference) Pointer to the object
 * @return The void *passed to siplus_type_new, or NULL if type is 
 * not valid, or not a type created with siplus_type_new
 */
SIPLUS_EXPORT void *siplus_type_data_ptr(const SIPlusTypeInfo *type);

/**
 * @brief Get the descriptor for this type info.
 *
 * @return The descriptor of the type.
 */
SIPLUS_EXPORT const SIPlusTypeDescriptor *siplus_type_descriptor(const SIPlusTypeInfo *type);

/**
 * @brief Get the base IntegerType TypeInfo
 *
 * @return (Owner) The TypeInfo
 */
SIPLUS_EXPORT const SIPlusTypeInfo *siplus_type_int();

/**
 * @brief Get the base FloatType TypeInfo
 *
 * @return (Owner) The TypeInfo
 */
SIPLUS_EXPORT const SIPlusTypeInfo *siplus_type_float();

/**
 * @brief Get the base StringType TypeInfo
 *
 * @return (Owner) The TypeInfo
 */
SIPLUS_EXPORT const SIPlusTypeInfo *siplus_type_string();

/**
 * @brief Get the base BoolType TypeInfo
 *
 * @return (Owner) The TypeInfo
 */
SIPLUS_EXPORT const SIPlusTypeInfo *siplus_type_bool();

/**
 * @brief Get the base ArrayType TypeInfo
 *
 * @return (Owner) The TypeInfo
 */
SIPLUS_EXPORT const SIPlusTypeInfo *siplus_type_array();

/**
 * @brief Get the base NullType TypeInfo
 *
 * @return (Owner) The TypeInfo
 */
SIPLUS_EXPORT const SIPlusTypeInfo *siplus_type_null();

/**
 * @brief Call `access` for a type
 *
 * @param[out] result (Owner) The result
 * @param[in] type (Reference) The TypeInfo
 * @param[in] data (Reference) The data object
 * @param[in] property (Reference) The property to access
 * @return Error code
 */
SIPLUS_EXPORT int siplus_type_access(SIPlusUnknownDataContainer **result, const SIPlusTypeInfo *type, const SIPlusUnknownDataContainer *data, char *property);

/**
 * @brief Check if a type is iterable
 *
 * @param[out] result The result. 1 if the type is iterable.
 * @param[in] info (Reference) The type info
 * @param[in] data (Reference) The data object
 * @return Error code
 */
SIPLUS_EXPORT int siplus_type_is_iterable(int *result, const SIPlusTypeInfo *info, const SIPlusUnknownDataContainer *data);

/**
 * @brief Iterate on a type
 *
 * @param[out] result (Owner) The iterator
 * @param[in] typeInfo (Reference) The TypeInfo
 * @param[in] container (Reference) The data
 * @return Error code
 */
SIPLUS_EXPORT int siplus_type_iterate(SIPlusIterator **result, const SIPlusTypeInfo *typeInfo, const SIPlusUnknownDataContainer *container);

/**
 * @brief Get the name of the type. Delete the result with `siplus_string_delete`.
 *
 * @param[in] buf (Reference) The location to copy the name to
 * @param[in] size The size of `buf`
 * @param[in] first (Reference) The type
 * @return The number of bytes copied. If either `buf` is NULL, or `size` is 0,
 * this returns the size of the string to be copied.
 */
SIPLUS_EXPORT int siplus_type_name(char *buf, size_t size, const SIPlusTypeInfo *first);

/**
 * @brief Checks if types are equal (if they both have the same descriptor).
 *
 * @param[in] first (Reference) The type
 * @param[in] second (Reference) The other type
 * @return Error Code
 */
SIPLUS_EXPORT int siplus_type_is(const SIPlusTypeInfo *first, const SIPlusTypeInfo *second);

/**
 * @brief Dereference a TypeInfo. These are reference counted, so this will not 
 * always result in an immediate deletion of your TypeInfo.
 *
 * @param[in] type (Owner) The TypeInfo
 */
SIPLUS_EXPORT void siplus_type_unref(const SIPlusTypeInfo *type);



/**
 * @brief Create a new Iterator
 *
 * @param[out] iterator (Owner) The created iterator
 * @param[in] data (Owner) Data to store with your iterator
 * @param[in] more Check if there is more elements
 * @param[in] next Move to the next value.
 * @param[in] current Implementation to get the current value.
 * @param[in] deleter Deleter for `data`
 * @return Error code
 */
SIPLUS_EXPORT SIPlusIterator *siplus_iterator_new(void *data, SIPlusIteratorMore more, SIPlusIteratorNext next, SIPlusIteratorCurrent current, SIPlusDataDeleterCallback deleter);

/**
 * @brief Get the void *data passed into siplus_iterator_new.
 *
 * @param[in] iterator (Reference) Pointer to the object
 * @return The void *passed to siplus_iterator_new, or NULL if iterator is 
 * not valid, or not an iterator created with siplus_iterator_new
 */
SIPLUS_EXPORT void *siplus_iterator_data_ptr(SIPlusIterator *iterator);

/**
 * @brief Move to the next Iterator item.
 *
 * @param[in] iterator (Reference) The iterator
 * @return Error code
 */
SIPLUS_EXPORT int siplus_iterator_next(SIPlusIterator *iterator);

/**
 * @brief Check if there are more items remaining
 *
 * @param[out] result 1 if there are more items, and next() can be called.
 * @param[in] iterator (Reference) The iterator
 * @return Error code
 */
SIPLUS_EXPORT int siplus_iterator_more(int *result, SIPlusIterator *iterator);

/**
 * @brief Get the current item
 *
 * @param[out] result (Owner) The result
 * @param[in] iterator (Reference) The iterator
 * @return Error code
 */
SIPLUS_EXPORT int siplus_iterator_current(SIPlusUnknownDataContainer **result, SIPlusIterator *iterator);

/**
 * @brief Delete an iterator. Iterators are uniquely referenced, and this WILL lead 
 * to deletion of the iterator, unlike most other instances.
 *
 * @param[in] iterator (Owner) The iterator
 */
SIPLUS_EXPORT void siplus_iterator_delete(SIPlusIterator *iterator);



/**
 * @brief Make a data container for a long.
 *
 * @param[in] value 
 * @return Data container
 */
SIPLUS_EXPORT SIPlusUnknownDataContainer *siplus_data_make_int(int64_t value);

/**
 * @brief Make a data container for a double.
 *
 * @param[in] value 
 * @return (Owner) Data container
 */
SIPLUS_EXPORT SIPlusUnknownDataContainer *siplus_data_make_float(double value);

/**
 * @brief Make a data container for a string.
 *
 * @param[in] value 
 * @return (Owner) Data container
 */
SIPLUS_EXPORT SIPlusUnknownDataContainer *siplus_data_make_string(const char *text);

/**
 * @brief Make a data container for a boolean.
 *
 * @param[in] value 
 * @return (Owner) Data container
 */
SIPLUS_EXPORT SIPlusUnknownDataContainer *siplus_data_make_bool(int value);

/**
 * @brief Make a data container for null.
 *
 * @param[in] value 
 * @return (Owner) Data container
 */
SIPLUS_EXPORT SIPlusUnknownDataContainer *siplus_data_make_null();

/**
 * @brief Check if a data container holds an IntegerType
 *
 * @param[in] container (Reference) Data container
 * @return 1 if container is an IntegerType
 */
SIPLUS_EXPORT int siplus_data_is_int(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds an FloatType
 *
 * @param[in] container (Reference) Data container
 * @return 1 if container is a FloatType
 */
SIPLUS_EXPORT int siplus_data_is_float(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds an StringType
 *
 * @param[in] container (Reference) Data container
 * @return 1 if container is a StringType
 */
SIPLUS_EXPORT int siplus_data_is_string(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds an BoolType
 *
 * @param[in] container (Reference) Data container
 * @return 1 if container is a BoolType
 */
SIPLUS_EXPORT int siplus_data_is_bool(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds a NullType
 *
 * @param[in] container (Reference) Data container
 * @return 1 if container is a NullType
 */
SIPLUS_EXPORT int siplus_data_is_null(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds an ArrayType
 *
 * @param[in] container (Reference) Data container
 * @return 1 if container is an ArrayType
 */
SIPLUS_EXPORT int siplus_data_is_array(SIPlusUnknownDataContainer *container);

/**
 * @brief Get this data container as a int.
 *
 * @param[out] result The location to store the result
 * @param[in] value (Reference) The container to read
 * @return Error code
 */
SIPLUS_EXPORT int siplus_data_as_int(int64_t *result, SIPlusUnknownDataContainer *value);

/**
 * @brief Get this data container as a float.
 *
 * @param[out] result The location to store the result
 * @param[in] value (Reference) The container to read
 * @return Error code
 */
SIPLUS_EXPORT int siplus_data_as_float(double *result, SIPlusUnknownDataContainer *value);

/**
 * @brief Get this data container as a bool.
 *
 * @param[out] result The location to store the result
 * @param[in] value (Reference) The container to read
 * @return Error code
 */
SIPLUS_EXPORT int siplus_data_as_bool(int *result, SIPlusUnknownDataContainer *value);

/**
 * @brief Get this data container as a string. The value in `result` after this call,
 * must eventually be freed with `siplus_string_delete`
 *
 * @param[out] result (Owner) The location to store the result
 * @param[in] value (Reference) The container to read
 * @return Error code
 */
SIPLUS_EXPORT int siplus_data_as_string(char **result, SIPlusUnknownDataContainer *value);

/**
 * @brief Create a new data container. This call will not fail (outside of low memory scenarios).
 *
 * @param[in] type (Reference) The type of the data
 * @param[in] data (Owner) The void* to pass to the TypeInfo implementation functions
 * @param[in] deleter Logic to delete the void*.
 * @return (Owner) The newly created container.
 */
SIPLUS_EXPORT SIPlusUnknownDataContainer *siplus_data_make(const SIPlusTypeInfo *type, void *data, SIPlusDataDeleterCallback deleter);

/**
 * @brief Check if a container is of a certain type.
 *
 * @param[in] container (Reference) The data container
 * @param[in] type (Reference) The type to check
 * @return Error code.
 */
SIPLUS_EXPORT int siplus_data_is(SIPlusUnknownDataContainer *container, const SIPlusTypeInfo *type);

/**
 * @brief Get the type of the container.
 *
 * @param[out] type (Owner) The type of the container. This must be deleted.
 * @param[in] container (Reference) The container to check
 * @return Error code
 */
SIPLUS_EXPORT const SIPlusTypeInfo *siplus_data_type(SIPlusUnknownDataContainer *container);

/**
 * @brief Get the void* to the data
 *
 * @param[out] data (Reference) The void*
 * @param[in] container (Reference) The container
 * @return Error code
 */
SIPLUS_EXPORT void *siplus_data_ptr(SIPlusUnknownDataContainer *container);

/**
 * @brief Delete a reference to a data container.
 *
 * @param[in] container (Owner) The container to delete
 */
SIPLUS_EXPORT void siplus_data_delete(SIPlusUnknownDataContainer *container);

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_SIPLUS_SIPLUS_H_
