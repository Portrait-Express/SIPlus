#pragma once
#ifndef INCLUDE_SIPLUS_SIPLUS_H_
#define INCLUDE_SIPLUS_SIPLUS_H_

#include "siplus/config.h"

#ifdef MSVC
#  ifdef SIPLUS_EXPORTING
#    define SIPLUS_EXPORTED __declspec(dllexport)
#  else
#    define SIPLUS_EXPORTED __declspec(dllimport)
#  endif
#else
#  define SIPLUS_EXPORTED
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
typedef SIPlusValueRetriever *(*SIPlusFunction)(void *data, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **paramv);



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
typedef SIPlusUnknownDataContainer *(*SIPlusRetrieverImpl)(void *data, SIPlusInvocationContext *context);



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



SIPLUS_EXPORTED int siplus_error_get(char **message);
SIPLUS_EXPORTED int siplus_error_set(int err, const char *message);
SIPLUS_EXPORTED void siplus_error_message_delete(const char *message);



SIPLUS_EXPORTED SIPlusParser *siplus_parser_new();
SIPLUS_EXPORTED int siplus_parser_context(SIPlusContext **context,  SIPlusParser *parser);
SIPLUS_EXPORTED int siplus_parser_get_interpolation(
    SIPlusTextConstructor **constructor, SIPlusParser *parser, const char *text, SIPlusParseOpts *opts);
SIPLUS_EXPORTED int siplus_parser_get_expression(
    SIPlusValueRetriever **retriever, SIPlusParser *parser, const char *expr, SIPlusParseOpts *opts);
SIPLUS_EXPORTED void siplus_parser_delete(SIPlusParser *parser);



SIPLUS_EXPORTED int siplus_value_create(SIPlusValueRetriever **retriever, void* context, SIPlusRetrieverImpl impl, SIPlusRetrieverDeleter deleter);
SIPLUS_EXPORTED int siplus_value_retrieve(SIPlusUnknownDataContainer **data, SIPlusValueRetriever *value, SIPlusInvocationContext *context);
SIPLUS_EXPORTED void siplus_value_delete(SIPlusValueRetriever *parser);



SIPLUS_EXPORTED int siplus_text_construct(char **text, SIPlusTextConstructor *value, SIPlusInvocationContext *context);
SIPLUS_EXPORTED void siplus_text_delete(SIPlusTextConstructor *parser);
SIPLUS_EXPORTED void siplus_text_result_delete(const char *text);



SIPLUS_EXPORTED SIPlusParseOpts *siplus_parse_opts_new();
SIPLUS_EXPORTED int siplus_parse_opts_add_global(SIPlusParseOpts *opts, const char *name);
SIPLUS_EXPORTED void siplus_parse_opts_delete(SIPlusParseOpts *opts);



SIPLUS_EXPORTED int siplus_context_add_function(
    SIPlusContext *context, const char *name, void *data, SIPlusFunction function, SIPlusFunctionDeleter deleter);
SIPLUS_EXPORTED int siplus_context_use_stl(SIPlusContext *context);
SIPLUS_EXPORTED int siplus_context_builder(SIPlusInvocationContextBuilder **builder, SIPlusContext *context);
SIPLUS_EXPORTED void siplus_context_delete(SIPlusContext *context);



SIPLUS_EXPORTED int siplus_icbuilder_with(SIPlusInvocationContextBuilder *builder, const char *name, SIPlusUnknownDataContainer *container);
SIPLUS_EXPORTED int siplus_icbuilder_default(SIPlusInvocationContextBuilder *builder, SIPlusUnknownDataContainer *container);
SIPLUS_EXPORTED int siplus_icbuilder_build(SIPlusInvocationContext **context, SIPlusInvocationContextBuilder *builder);



SIPLUS_EXPORTED void siplus_invocation_delete(SIPlusInvocationContext *context);



SIPLUS_EXPORTED int siplus_type_new(
    SIPlusTypeInfo **type, 
    void *data, const char *name, 
    SIPlusTypeIsIterable is_iterable, SIPlusTypeAccess access, 
    SIPlusTypeIterate iterate, SIPlusTypeDeleter deleter);
SIPLUS_EXPORTED void siplus_type_delete(SIPlusTypeInfo *type);



SIPLUS_EXPORTED int siplus_iterator_new(
    SIPlusIterator **iterator, void *data, 
    SIPlusIteratorMore more, SIPlusIteratorNext next, 
    SIPlusIteratorCurrent current, SIPlusIteratorDeleter deleter);
SIPLUS_EXPORTED void siplus_iterator_delete(SIPlusIterator *iterator);



SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_int(long value);
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_float(double value);
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_string(const char *text);
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make_bool(int value);
SIPLUS_EXPORTED SIPlusUnknownDataContainer *siplus_data_make(SIPlusTypeInfo *type, void *data, SIPlusUnknownDataContainerDeleter deleter);
SIPLUS_EXPORTED void siplus_data_delete(SIPlusUnknownDataContainer *container);



#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_SIPLUS_SIPLUS_H_
