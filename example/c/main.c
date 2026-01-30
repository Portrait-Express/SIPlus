#include <stdio.h>
#include <stdlib.h>
#include <siplus/csiplus.h>
#include <string.h>

struct LanguageInfo {
    char *name;
};
typedef struct LanguageInfo LanguageInfo;

LanguageInfo *langauge_info_new(const char *name) {
    LanguageInfo *info = malloc(sizeof(LanguageInfo));
    size_t size = strlen(name) + 1;

    info->name = malloc(size + 1);
    strncpy(info->name, name, size);
    info->name[size+1] = 0;

    return info;
}

void langauge_info_free(LanguageInfo *info) {
    free(info->name);
    free(info);
}

struct LanguageInfoType {};
typedef struct LanguageInfoType LanguageInfoType;

int language_info_is_iterable(void *data, void *object) {
    return 0;
}

int language_info_access(SIPlusUnknownDataContainer **result, void *data, void *info, const char *property) {
    if(!strncmp(property, "name", 4)) {
        *result = siplus_data_make_string(((LanguageInfo*)info)->name);
        return siplus_error_set(SIPLUS_OK, NULL);
    }

    char buf[128];
    snprintf(buf, sizeof(buf), "Unrecognized property name %s", property);
    return siplus_error_set(SIPLUS_ERR, buf);
}

SIPlusTypeInfo *langauge_info_type_new() {
    SIPlusTypeInfo *info;
    LanguageInfoType *data = malloc(sizeof(LanguageInfoType));

    siplus_type_new(&info, data, "LanguageInfo", language_info_is_iterable, language_info_access, NULL, free);
    return info;
}

int main(int argc, char **argv) {
    int result;
    SIPlusParser *parser = siplus_parser_new();
    SIPlusParseOpts *parseOpts = siplus_parse_opts_new();
    SIPlusContext *context = 0;
    SIPlusUnknownDataContainer *container = 0;
    SIPlusTypeInfo *typeInfo = langauge_info_type_new();
    SIPlusInvocationContextBuilder *icb = 0;
    SIPlusInvocationContext *ic = 0;
    SIPlusTextConstructor *constructor = 0;
    LanguageInfo *info = langauge_info_new("C");
    char *textResult = 0;

    if((result = siplus_parser_context(&context, parser))) {
        siplus_error_get(&textResult);
        if(textResult) printf("Error getting context: %s\n", textResult);
        goto cleanup;
    }

    if((result = siplus_parser_get_interpolation(&constructor, parser, "Hello, from { .name }", parseOpts))) {
        siplus_error_get(&textResult);
        if(textResult) printf("Error parsing: %s\n", textResult);
        goto cleanup;
    }

    if((result = siplus_context_builder(&icb, context))) {
        siplus_error_get(&textResult);
        if(textResult) printf("Error preparing: %s\n", textResult);
        goto cleanup;
    }


    container = siplus_data_make(typeInfo, info, free);
    if((result = siplus_icbuilder_default(icb, container))) {
        siplus_error_get(&textResult);
        if(textResult) printf("Error preparing: %s\n", textResult);
        goto cleanup;
    } else {
        siplus_data_delete(container);
        container = 0;
    }

    if((result = siplus_icbuilder_build(&ic, icb)))  {
        siplus_error_get(&textResult);
        if(textResult) printf("Error preparing: %s\n", textResult);
        goto cleanup;
    }

    if((result = siplus_text_construct(&textResult, constructor, ic))) {
        siplus_error_get(&textResult);
        if(textResult) printf("Error during invocation: %s\n", textResult);
        goto cleanup;
    }

    printf("Result: %s", textResult);
        
cleanup:
    siplus_text_result_delete(textResult);
    siplus_invocation_delete(ic);
    siplus_text_delete(constructor);
    siplus_type_delete(typeInfo);
    siplus_context_delete(context);
    siplus_parse_opts_delete(parseOpts);
    siplus_parser_delete(parser);
    return result;
}
