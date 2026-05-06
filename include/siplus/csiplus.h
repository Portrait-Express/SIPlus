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

SIPLUS_EXPORTED void siplus_string_delete(const char *ptr);

SIPLUS_EXPORTED int siplus_error_get(char **message);
SIPLUS_EXPORTED int siplus_error_set(int err, const char *message);

SIPLUS_EXPORTED SIPlusParser *siplus_parser_new();
SIPLUS_EXPORTED int siplus_parser_context(SIPlusContext **context,  SIPlusParser *parser);
SIPLUS_EXPORTED int siplus_parser_get_interpolation(SIPlusTextConstructor **constructor, SIPlusParser *parser, const char *text, SIPlusParseOpts *opts);
SIPLUS_EXPORTED int siplus_parser_get_expression(SIPlusValueRetriever **retriever, SIPlusParser *parser, const char *expr, SIPlusParseOpts *opts);
SIPLUS_EXPORTED void siplus_parser_delete(SIPlusParser *parser);

SIPLUS_EXPORTED int siplus_function_create(SIPlusFunction **function, void *data, SIPlusFunctionValue value, SIPlusFunctionDeleter deleter);
SIPLUS_EXPORTED int siplus_function_value(SIPlusValueRetriever **retriever, SIPlusFunction *function, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **params);
SIPLUS_EXPORTED void siplus_function_unref(SIPlusFunction *function);

SIPLUS_EXPORTED int siplus_text_construct(char **text, SIPlusTextConstructor *value, SIPlusInvocationContext *context);
SIPLUS_EXPORTED void siplus_text_unref(SIPlusTextConstructor *parser);

SIPLUS_EXPORTED int siplus_value_create(SIPlusValueRetriever **retriever, void* context, SIPlusRetrieverImpl impl, SIPlusRetrieverDeleter deleter);
SIPLUS_EXPORTED int siplus_value_retrieve(SIPlusUnknownDataContainer **data, SIPlusValueRetriever *value, SIPlusInvocationContext *context);
SIPLUS_EXPORTED void siplus_value_unref(SIPlusValueRetriever *parser);

SIPLUS_EXPORTED SIPlusParseOpts *siplus_parse_opts_new();
SIPLUS_EXPORTED int siplus_parse_opts_add_global(SIPlusParseOpts *opts, const char *name);
SIPLUS_EXPORTED void siplus_parse_opts_delete(SIPlusParseOpts *opts);

SIPLUS_EXPORTED int siplus_context_add_function(SIPlusContext *context, const char *name, SIPlusFunction *function);
SIPLUS_EXPORTED int siplus_context_use_stl(SIPlusContext *context);
SIPLUS_EXPORTED int siplus_context_builder(SIPlusInvocationContextBuilder **builder, SIPlusContext *context);
SIPLUS_EXPORTED void siplus_context_unref(SIPlusContext *context);

SIPLUS_EXPORTED int siplus_icbuilder_with(SIPlusInvocationContextBuilder *builder, const char *name, SIPlusUnknownDataContainer *container);
SIPLUS_EXPORTED int siplus_icbuilder_default(SIPlusInvocationContextBuilder *builder, SIPlusUnknownDataContainer *container);
SIPLUS_EXPORTED int siplus_icbuilder_build(SIPlusInvocationContext **context, SIPlusInvocationContextBuilder *builder);
SIPLUS_EXPORTED void siplus_icbuilder_delete(SIPlusInvocationContextBuilder *builder);

SIPLUS_EXPORTED void siplus_invocation_unref(SIPlusInvocationContext *context);

SIPLUS_EXPORTED int siplus_type_new(SIPlusTypeInfo **type, void *data, const char *name, SIPlusTypeIsIterable is_iterable, SIPlusTypeAccess access, SIPlusTypeIterate iterate, SIPlusTypeDeleter deleter);
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_int();
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_float();
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_string();
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_bool();
SIPLUS_EXPORTED SIPlusTypeInfo *siplus_type_array();
SIPLUS_EXPORTED int siplus_type_access(SIPlusUnknownDataContainer **result, SIPlusTypeInfo *type, SIPlusUnknownDataContainer *data, char *property);
SIPLUS_EXPORTED int siplus_type_is_iterable(int *result, SIPlusTypeInfo *info, SIPlusUnknownDataContainer *data);
SIPLUS_EXPORTED int siplus_type_iterate(SIPlusIterator **result, SIPlusTypeInfo *typeInfo, SIPlusUnknownDataContainer *container);
SIPLUS_EXPORTED int siplus_type_name(char **name, SIPlusTypeInfo *first);
SIPLUS_EXPORTED void siplus_type_unref(SIPlusTypeInfo *type);



SIPLUS_EXPORTED int siplus_iterator_new(SIPlusIterator **iterator, void *data, SIPlusIteratorMore more, SIPlusIteratorNext next, SIPlusIteratorCurrent current, SIPlusIteratorDeleter deleter);
SIPLUS_EXPORTED int siplus_iterator_next(SIPlusIterator *iterator);
SIPLUS_EXPORTED int siplus_iterator_more(int *result, SIPlusIterator *iterator);
SIPLUS_EXPORTED int siplus_iterator_current(SIPlusUnknownDataContainer **result, SIPlusIterator *iterator);
SIPLUS_EXPORTED void siplus_iterator_delete(SIPlusIterator *iterator);



SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_int(long value);
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_float(double value);
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_string(const char *text);
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_bool(int value);

SIPLUS_EXPORTED int siplus_data_is_int(SIPlusUnknownDataContainer *container);
SIPLUS_EXPORTED int siplus_data_is_float(SIPlusUnknownDataContainer *container);
SIPLUS_EXPORTED int siplus_data_is_string(SIPlusUnknownDataContainer *container);
SIPLUS_EXPORTED int siplus_data_is_bool(SIPlusUnknownDataContainer *container);
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
