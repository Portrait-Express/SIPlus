#pragma once
#ifndef INCLUDE_SIPLUS_SIPLUS_H_
#define INCLUDE_SIPLUS_SIPLUS_H_

#include "siplus/config.h"

#ifdef SIPLUS_BUILD
#  if defined(SIPLUS_EXPORTING) && defined(_MSC_VER)
#    define SIPLUS_EXPORTED __declspec(dllexport)
#  else
#    define SIPLUS_EXPORTED
#  endif
#else
#  ifdef _MSC_VER
#    define SIPLUS_EXPORTED __declspec(dllimport)
#  else
#    define SIPLUS_EXPORTED
#  endif
#endif

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

struct _SIPlusTypeInfo;
typedef struct _SIPlusTypeInfo                     SIPlusTypeInfo;

struct _SIPlusUnknownDataContainer;
typedef struct _SIPlusUnknownDataContainer         SIPlusUnknownDataContainer;

struct _SIPlusParser;
typedef struct _SIPlusParser                       SIPlusParser;

struct _SIPlusParseOpts;
typedef struct _SIPlusParseOpts                    SIPlusParseOpts;

struct _SIPlusFunction;
typedef struct _SIPlusFunction                     SIPlusFunction;

struct _SIPlusParserContext;
typedef struct _SIPlusParserContext                SIPlusContext;

struct _SIPlusInvocationContext;
typedef struct _SIPlusInvocationContext            SIPlusInvocationContext;

struct _SIPlusValueRetriever;
typedef struct _SIPlusValueRetriever               SIPlusValueRetriever;

struct _SIPlusTextConstructor;
typedef struct _SIPlusTextConstructor              SIPlusTextConstructor;

struct _SIPlusInvocationContextBuilder;
typedef struct _SIPlusInvocationContextBuilder     SIPlusInvocationContextBuilder;

struct _SIPlusIterator;
typedef struct _SIPlusIterator                     SIPlusIterator;

/**
 * @brief Deleter callback for when the SIPlusFunction is deleted. This 
 * typically happens during siplus_parser_delete.
 *
 * @param[in] data The void* passed to siplus_context_add_function
 */
typedef void (*SIPlusFunctionDeleter)(void *data);

/**
 * @brief Get the result of this function. 
 * - SIPlus will delete the returned SIPlusValueRetriever.
 * - YOU are responsble for deleting ALL passed parameters (used or not).
 *
 * @param[in] data The data void* that was passed to siplus_context_add_function
 * @param[in] parent The parent ValueRetriever
 * @param[in] paramc The size of paramv
 * @param[in] paramv The ValueRetriever parameter list
 */
typedef int (*SIPlusFunctionValue)(SIPlusValueRetriever **result, void *data, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **paramv);



/**
 * @brief Deleter callback for when the SIPlusValueRetriever is deleted.
 *
 * @param[in] data The void* passed to siplus_value_create
 */
typedef void (*SIPlusRetrieverDeleter)(void *data);

/**
 * @brief Implementation for the ValueRetriever
 *
 * @param[in] data The data void* passed to siplus_value_create
 * @param[in] context The InvocationContext for this invocation of the retriever.
 */
typedef int (*SIPlusRetrieverImpl)(SIPlusUnknownDataContainer **result, void *data, SIPlusInvocationContext *context);



/**
 * @brief Deleter for UnknownDataContainer. This is called when all instances 
 * of the stored object are deleted. This is not necessarily when you call 
 * siplus_data_delete(), as UnknownDataContainer uses an internal reference 
 * counting mechanism similar to shared_ptr.
 *
 * @param[in] data The void* data passed to siplus_data_make
 */
typedef void (*SIPlusUnknownDataContainerDeleter)(void *data);



typedef int (*SIPlusIteratorMore)(void *data);
typedef int (*SIPlusIteratorNext)(void *data);
typedef int (*SIPlusIteratorCurrent)(SIPlusUnknownDataContainer **result, void *data);
typedef void (*SIPlusIteratorDeleter)(void *data);


/**
 * @brief Callback for TypeInfo::is_iterable
 *
 * @param[in] data The data void* passed to siplus_type_new
 * @param[in] container The data object. This will be deleted after this call. 
 * You do not need to, and should not, delete it
 * @return TRUE if the type is iterable
 */
typedef int (*SIPlusTypeIsIterable)(void *data, void *container);

/**
 * @brief Iterate over a type
 *
 * @param[in] data The data void* passed to siplus_type_new
 * @param[in] container The data object. This will be deleted after this call. 
 * @return A new iterator created with siplus_iterator_new
 */
typedef int (*SIPlusTypeIterate)(SIPlusIterator **result, void *data, void *container);

/**
 * @brief Access a property on an object
 *
 * @param[in] data The data void* passed to siplus_type_new
 * @param[in] container The data object to access
 * @param[in] name The property name
 */
typedef int (*SIPlusTypeAccess)(SIPlusUnknownDataContainer **result, void *data, void *container, const char *name);

/**
 * @brief Deleter for SIPlusTypeInfo
 *
 * @param[in] data The data void* passed to siplus_type_new
 */
typedef void (*SIPlusTypeDeleter)(void *data);

/**
 * @brief Free a string result. Any function that uses char** to return text 
 * must have this called afterwards unless otherwise specified.
 *
 * @param[in] ptr The text pointer returned from another siplus_* function
 */
SIPLUS_EXPORTED void siplus_string_delete(const char *ptr);

/**
 * @brief Get the error message. Free the pointer with `siplus_string_delete`.
 *
 * @param[out] message The message
 * @return The error code stored with the message.
 */
SIPLUS_EXPORTED int siplus_error_get(char **message);

/**
 * @brief Set an error. If any of your function implementations fail, call this.
 *
 * @param[in] err The error code
 * @param[in] message The error message. This is copied and stored, so you may free your message.
 * @return The value passed into `err`
 */
SIPLUS_EXPORTED int siplus_error_set(int err, const char *message);



/**
 * @brief Create a new parser instance.
 *
 * @return The new parser.
 */
SIPLUS_EXPORTED SIPlusParser *siplus_parser_new();

/**
 * @brief Get the parser's context
 *
 * @param[out] context The context
 * @param[in] parser The parser
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_parser_context(SIPlusContext **context,  SIPlusParser *parser);

/**
 * @brief Get an interpolation from the parser
 *
 * @param[out] constructor The constructor result. You will need to `unref` this when you are finished.
 * @param[in] parser The parser
 * @param[in] text The interpolation's text
 * @param[in] opts Parser options. Pass NULL to use default as a shortcut.
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_parser_get_interpolation(SIPlusTextConstructor **constructor, SIPlusParser *parser, const char *text, SIPlusParseOpts *opts);
/**
 * @brief Get an expression ValueRetriever
 *
 * @param[out] retriever The retriever result. You will need to `unref` this when you are finished.
 * @param[in] parser The parser
 * @param[in] expr The expression
 * @param[in] opts Parser options. Pass NULL to use default as a shortcut.
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_parser_get_expression(SIPlusValueRetriever **retriever, SIPlusParser *parser, const char *expr, SIPlusParseOpts *opts);

/**
 * @brief Delete a parser. 
 *
 * @param[in] parser The parser to delete
 */
SIPLUS_EXPORTED void siplus_parser_delete(SIPlusParser *parser);



/**
 * @brief Create a new function
 *
 * @param[out] function The function. You will need to `unref` this when you are finished.
 * @param[in] data Any data you wish to store with this function.
 * @param[in] value `value` implementation
 * @param[in] deleter Deleter for `data` when this function is deleted
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_function_create(SIPlusFunction **function, void *data, SIPlusFunctionValue value, SIPlusFunctionDeleter deleter);

/**
 * @brief Get the value from a function
 *
 * @param[out] retriever The result of `value`. You will need to `unref` this when you are finished.
 * @param[in] function The function
 * @param[in] parent Parent value. Use NULL if none.
 * @param[in] paramc Parameter count
 * @param[in] params Parameter list
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_function_value(SIPlusValueRetriever **retriever, SIPlusFunction *function, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **params);

/**
 * @brief Dereference a function. These are reference counted, so this will not 
 * always result in a deletion of your function.
 *
 * @param[in] function The function
 */
SIPLUS_EXPORTED void siplus_function_unref(SIPlusFunction *function);



/**
 * @brief Get the result from a TextConstructor.
 *
 * @param[out] text The result. Delete this with `siplus_string_delete`
 * @param[in] value The text constructor
 * @param[in] context The invocation context
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_text_construct(char **text, SIPlusTextConstructor *value, SIPlusInvocationContext *context);

/**
 * @brief Dereference a TextConstructor.
 *
 * @param[in] constructor The constructor
 */
SIPLUS_EXPORTED void siplus_text_unref(SIPlusTextConstructor *constructor);



/**
 * @brief Create a new ValueRetriever
 *
 * @param[out] retriever The ValueRetriever
 * @param[in] data Data to store with your retriever
 * @param[in] impl The implementation to retrieve the value
 * @param[in] deleter Deleter for `data`
 * @return Error Code
 */
SIPLUS_EXPORTED int siplus_value_create(SIPlusValueRetriever **retriever, void* data, SIPlusRetrieverImpl impl, SIPlusRetrieverDeleter deleter);

/**
 * @brief retrieve the value from a ValueRetriever
 *
 * @param[out] data The result of the operation
 * @param[in] value The ValueRetriever
 * @param[in] context The invocation context
 * @return Error Code
 */
SIPLUS_EXPORTED int siplus_value_retrieve(SIPlusUnknownDataContainer **data, SIPlusValueRetriever *value, SIPlusInvocationContext *context);

/**
 * @brief Dereference a ValueRetriever. These are reference counted, so this will not 
 * always result in a deletion of your ValueRetriever.
 *
 * @param[in] function The ValueRetriever
 */
SIPLUS_EXPORTED void siplus_value_unref(SIPlusValueRetriever *parser);



/**
 * @brief Create new Parser Opts
 *
 * @return New parser options
 */
SIPLUS_EXPORTED SIPlusParseOpts *siplus_parse_opts_new();
/**
 * @brief Add a global to be available in a template.
 *
 * @param[in] opts The options
 * @param[in] name The name of the global variable
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_parse_opts_add_global(SIPlusParseOpts *opts, const char *name);

/**
 * @brief Delete parser options
 *
 * @param[in] opts The options to free
 */
SIPLUS_EXPORTED void siplus_parse_opts_delete(SIPlusParseOpts *opts);



/**
 * @brief Add a function to a ParserContext, to make it available during template creation.
 *
 * @param[in] context The context
 * @param[in] name The name of the function
 * @param[in] function The function
 * @return Error Code
 */
SIPLUS_EXPORTED int siplus_context_add_function(SIPlusContext *context, const char *name, SIPlusFunction *function);

/**
 * @brief Attach the STL library of functions and converters.
 *
 * @param[in] context Context
 * @return Error Code
 */
SIPLUS_EXPORTED int siplus_context_use_stl(SIPlusContext *context);

/**
 * @brief Get a builder for an InvocationContext.
 *
 * @param[out] builder The created ContextBuilder
 * @param[in] context The Parser context
 * @return Error Code
 */
SIPLUS_EXPORTED int siplus_context_builder(SIPlusInvocationContextBuilder **builder, SIPlusContext *context);

/**
 * @brief Dereference a ParserContext. Call this for any context received from siplus_parser_context().
 *
 * @param[in] function The function
 */
SIPLUS_EXPORTED void siplus_context_unref(SIPlusContext *context);



/**
 * @brief Define a value for a variable for this Invocation.
 *
 * @param[in] builder The InvocationContextBuilder
 * @param[in] name The name of the variable
 * @param[in] container The data
 * @return Error Code
 */
SIPLUS_EXPORTED int siplus_icbuilder_with(SIPlusInvocationContextBuilder *builder, const char *name, SIPlusUnknownDataContainer *container);

/**
 * @brief Set the default data to use
 *
 * @param[in] builder The InvocationContextBuilder
 * @param[in] container The data
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_icbuilder_default(SIPlusInvocationContextBuilder *builder, SIPlusUnknownDataContainer *container);

/**
 * @brief Get an InvocationContext from the Builder
 *
 * @param[out] context The InvocationContext
 * @param[in] builder The builder
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_icbuilder_build(SIPlusInvocationContext **context, SIPlusInvocationContextBuilder *builder);

/**
 * @brief Free an InvocationContextBuilder
 *
 * @param[in] builder The builder
 */
SIPLUS_EXPORTED void siplus_icbuilder_delete(SIPlusInvocationContextBuilder *builder);



/**
 * @brief Free an InvocationContext
 *
 * @param[in] context The InvocationContext
 */
SIPLUS_EXPORTED void siplus_invocation_unref(SIPlusInvocationContext *context);



/**
 * @brief Create a new TypeInfo
 *
 * @param[out] type The TypeInfo
 * @param[in] data Data to store with the type.
 * @param[in] name The name of your type
 * @param[in] is_iterable `is_iterable()` implementation. REQUIRED
 * @param[in] access `access()` implementation. You may pass NULL of there are no accessible properties.
 * @param[in] iterate iterate() implementation. You may pass NULL if your type is not iterable.
 * @param[in] deleter Deleter for `data`. You may pass NULL.
 * @return Error Code
 */
SIPLUS_EXPORTED int siplus_type_new(SIPlusTypeInfo **type, void *data, const char *name, SIPlusTypeIsIterable is_iterable, SIPlusTypeAccess access, SIPlusTypeIterate iterate, SIPlusTypeDeleter deleter);

/**
 * @brief Get the base IntegerType TypeInfo
 *
 * @return The TypeInfo
 */
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_int();

/**
 * @brief Get the base FloatType TypeInfo
 *
 * @return The TypeInfo
 */
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_float();

/**
 * @brief Get the base StringType TypeInfo
 *
 * @return The TypeInfo
 */
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_string();

/**
 * @brief Get the base BoolType TypeInfo
 *
 * @return The TypeInfo
 */
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_bool();

/**
 * @brief Get the base ArrayType TypeInfo
 *
 * @return The TypeInfo
 */
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_array();

/**
 * @brief Get the base NullType TypeInfo
 *
 * @return The TypeInfo
 */
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_null();

/**
 * @brief Call `access` for a type
 *
 * @param[out] result The result
 * @param[in] type The TypeInfo
 * @param[in] data The data object
 * @param[in] property The property to access
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_type_access(SIPlusUnknownDataContainer **result, SIPlusTypeInfo *type, SIPlusUnknownDataContainer *data, char *property);

/**
 * @brief Check if a type is iterable
 *
 * @param[out] result The result. 1 if the type is iterable.
 * @param[in] info The type info
 * @param[in] data The data object
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_type_is_iterable(int *result, SIPlusTypeInfo *info, SIPlusUnknownDataContainer *data);

/**
 * @brief Iterate on a type
 *
 * @param[out] result The iterator
 * @param[in] typeInfo The TypeInfo
 * @param[in] container The data
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_type_iterate(SIPlusIterator **result, SIPlusTypeInfo *typeInfo, SIPlusUnknownDataContainer *container);

/**
 * @brief Get the name of the type. Delete the result with `siplus_string_delete`.
 *
 * @param[out] name The name of the type
 * @param[in] first The type
 * @return Error Code
 */
SIPLUS_EXPORTED int siplus_type_name(char **name, SIPlusTypeInfo *first);

/**
 * @brief Dereference a TypeInfo. These are reference counted, so this will not 
 * always result in a deletion of your TypeInfo.
 *
 * @param[in] type The TypeInfo
 */
SIPLUS_EXPORTED void siplus_type_unref(SIPlusTypeInfo *type);



/**
 * @brief Create a new Iterator
 *
 * @param[out] iterator The created iterator
 * @param[in] data Data to store with your iterator
 * @param[in] more Check if there is more elements
 * @param[in] next Move to the next value.
 * @param[in] current Implementation to get the current value.
 * @param[in] deleter Deleter for `data`
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_iterator_new(SIPlusIterator **iterator, void *data, SIPlusIteratorMore more, SIPlusIteratorNext next, SIPlusIteratorCurrent current, SIPlusIteratorDeleter deleter);

/**
 * @brief Move to the next Iterator item.
 *
 * @param[in] iterator The iterator
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_iterator_next(SIPlusIterator *iterator);

/**
 * @brief Check if there are more items remaining
 *
 * @param[out] result 1 if there are more items, and next() can be called.
 * @param[in] iterator The iterator
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_iterator_more(int *result, SIPlusIterator *iterator);

/**
 * @brief Get the current item
 *
 * @param[out] result The result
 * @param[in] iterator The iterator
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_iterator_current(SIPlusUnknownDataContainer **result, SIPlusIterator *iterator);

/**
 * @brief Delete an iterator. Iterators are uniquely referenced, and this WILL lead 
 * to deletion of the iterator, unlike most other instances.
 *
 * @param[in] iterator The iterator
 */
SIPLUS_EXPORTED void siplus_iterator_delete(SIPlusIterator *iterator);



/**
 * @brief Make a data container for a long.
 *
 * @param[in] value 
 * @return Data container
 */
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_int(long value);

/**
 * @brief Make a data container for a double.
 *
 * @param[in] value 
 * @return Data container
 */
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_float(double value);

/**
 * @brief Make a data container for a string.
 *
 * @param[in] value 
 * @return Data container
 */
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_string(const char *text);

/**
 * @brief Make a data container for a boolean.
 *
 * @param[in] value 
 * @return Data container
 */
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_bool(int value);

/**
 * @brief Make a data container for null.
 *
 * @param[in] value 
 * @return Data container
 */
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_null();

/**
 * @brief Check if a data container holds an IntegerType
 *
 * @param[in] container Data container
 * @return 1 if container is an IntegerType
 */
SIPLUS_EXPORTED int siplus_data_is_int(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds an FloatType
 *
 * @param[in] container Data container
 * @return 1 if container is a FloatType
 */
SIPLUS_EXPORTED int siplus_data_is_float(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds an StringType
 *
 * @param[in] container Data container
 * @return 1 if container is a StringType
 */
SIPLUS_EXPORTED int siplus_data_is_string(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds an BoolType
 *
 * @param[in] container Data container
 * @return 1 if container is a BoolType
 */
SIPLUS_EXPORTED int siplus_data_is_bool(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds a NullType
 *
 * @param[in] container Data container
 * @return 1 if container is a NullType
 */
SIPLUS_EXPORTED int siplus_data_is_null(SIPlusUnknownDataContainer *container);

/**
 * @brief Check if a data container holds an ArrayType
 *
 * @param[in] container Data container
 * @return 1 if container is an ArrayType
 */
SIPLUS_EXPORTED int siplus_data_is_array(SIPlusUnknownDataContainer *container);

/**
 * @brief Get this data container as a int.
 *
 * @param[out] result The location to store the result
 * @param[in] value The container to read
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_data_as_int(long *result, SIPlusUnknownDataContainer *value);

/**
 * @brief Get this data container as a float.
 *
 * @param[out] result The location to store the result
 * @param[in] value The container to read
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_data_as_float(double *result, SIPlusUnknownDataContainer *value);

/**
 * @brief Get this data container as a bool.
 *
 * @param[out] result The location to store the result
 * @param[in] value The container to read
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_data_as_bool(int *result, SIPlusUnknownDataContainer *value);

/**
 * @brief Get this data container as a string. The value in `result` after this call,
 * must eventually be freed with `siplus_string_delete`
 *
 * @param[out] result The location to store the result
 * @param[in] value The container to read
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_data_as_string(char **result, SIPlusUnknownDataContainer *value);

/**
 * @brief Create a new data container. This call will not fail (outside of low memory scenarios).
 *
 * @param[in] type The type of the data
 * @param[in] data The void* to pass to the TypeInfo implementation functions
 * @param[in] deleter Logic to delete the void*.
 * @return The newly created container.
 */
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make(SIPlusTypeInfo *type, void *data, SIPlusUnknownDataContainerDeleter deleter);

/**
 * @brief Check if a container is of a certain type.
 *
 * @param[out] result The result of the check.
 * @param[in] container The data container
 * @param[in] type The type to check
 * @return Error code.
 */
SIPLUS_EXPORTED int siplus_data_is(SIPlusUnknownDataContainer *container, SIPlusTypeInfo *type);

/**
 * @brief Get the type of the container.
 *
 * @param[out] type The type of the container. This must be deleted.
 * @param[in] container The container to check
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_data_type(SIPlusTypeInfo **type, SIPlusUnknownDataContainer *container);

/**
 * @brief Get the void* to the data
 *
 * @param[out] data The void*
 * @param[in] container The container
 * @return Error code
 */
SIPLUS_EXPORTED int siplus_data_ptr(void **data, SIPlusUnknownDataContainer *container);

/**
 * @brief Delete a reference to a data container.
 *
 * @param[in] container The container to delete
 */
SIPLUS_EXPORTED void siplus_data_delete(SIPlusUnknownDataContainer *container);

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_SIPLUS_SIPLUS_H_
