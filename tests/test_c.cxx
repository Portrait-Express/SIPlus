#include "siplus/csiplus.h"
#include "common.hxx"
#include "siplus/util.hxx"

using namespace SIPLUS_NAMESPACE;

struct LanguageInfo {
    std::string name;
    struct addon_list {
        size_t count;
        std::string *vals;
    } *addons;
};
typedef struct LanguageInfo LanguageInfo;

struct EmptyInfoType {};
typedef struct EmptyInfoType EmptyInfoType;

struct AddonsIteratorData {
    AddonsIteratorData(size_t size, std::string *data) : size(size), data(data) {}

    long i = 0;
    size_t size = 0;
    bool initialized = false;
    std::string *data;
};

int addon_iterator_more(void *data) {
    AddonsIteratorData *info = reinterpret_cast<AddonsIteratorData*>(data);
    return info->i < info->size - 1;
}

int addon_iterator_next(void *data) {
    AddonsIteratorData *info = reinterpret_cast<AddonsIteratorData*>(data);

    if(!info->initialized) {
        info->initialized = true;
    } else {
        info->i++;
    }

    return siplus_error_set(SIPLUS_OK, NULL);
}

int addon_iterator_current(SIPlusUnknownDataContainer **result, void *data) {
    AddonsIteratorData *info = reinterpret_cast<AddonsIteratorData*>(data);

    *result = siplus_data_make_string(info->data[info->i].c_str());

    return siplus_error_set(SIPLUS_OK, NULL);
}

int addon_list_is_iterable(void *data, void *object) {
    return 0;
}

int addon_list_iterate(SIPlusIterator **result, void *data, void *object) {
    LanguageInfo::addon_list *list = reinterpret_cast<LanguageInfo::addon_list*>(object);
    AddonsIteratorData *iteratorData = new AddonsIteratorData(list->count, list->vals);

    return siplus_iterator_new(
        result, reinterpret_cast<void*>(iteratorData), 
        addon_iterator_more, addon_iterator_next, addon_iterator_current, 
        [](void *data) {
            delete reinterpret_cast<AddonsIteratorData*>(data);
        });
}

SIPlusTypeInfo *addon_list_type_new() {
    SIPlusTypeInfo *info;
    EmptyInfoType *data = new EmptyInfoType();

    siplus_type_new(
        &info, reinterpret_cast<void*>(data), "LanguageInfo.addons(std:string[])", 
        addon_list_is_iterable, NULL, addon_list_iterate, [](void* data){
            delete reinterpret_cast<EmptyInfoType*>(data);
        });
    return info;
}

int language_info_is_iterable(void *data, void *object) {
    return 0;
}

int language_info_access(SIPlusUnknownDataContainer **result, void *data, void *info, const char *property) {
    LanguageInfo *language = reinterpret_cast<LanguageInfo*>(info);

    if(std::string{property} == "name") {
        *result = siplus_data_make_string(language->name.c_str());
        return siplus_error_set(SIPLUS_OK, NULL);
    } else if(std::string{property} == "addons") {
        auto type = addon_list_type_new();
        *result = siplus_data_make(type, language->addons, [](void*){});
        siplus_type_delete(type);
        return siplus_error_set(SIPLUS_OK, NULL);
    }

    return siplus_error_set(SIPLUS_ERR, util::to_string("Unrecognized property name ", property).c_str());
}

SIPlusTypeInfo *langauge_info_type_new() {
    SIPlusTypeInfo *info;
    EmptyInfoType *data = new EmptyInfoType();

    siplus_type_new(&info, reinterpret_cast<void*>(data), "LanguageInfo", language_info_is_iterable, language_info_access, NULL, [](void* data){
        delete reinterpret_cast<EmptyInfoType*>(data);
    });
    return info;
}

int test_c(int argc, char **argv) {
    return test("C API", []() {
        int result;
        SIPlusParser *parser = siplus_parser_new();
        SIPlusParseOpts *parseOpts = siplus_parse_opts_new();
        SIPlusContext *context = 0;
        SIPlusUnknownDataContainer *container = 0;
        SIPlusTypeInfo *typeInfo = langauge_info_type_new();
        SIPlusInvocationContextBuilder *icb = 0;
        SIPlusInvocationContext *ic = 0;
        SIPlusTextConstructor *constructor = 0;
        LanguageInfo *info;
        char *textResult = 0;

        auto finish = [&](int err) {
            siplus_text_result_delete(textResult);
            siplus_invocation_delete(ic);
            siplus_text_delete(constructor);
            siplus_type_delete(typeInfo);
            siplus_context_delete(context);
            siplus_parse_opts_delete(parseOpts);
            siplus_parser_delete(parser);

            return err;
        };

        if((result = siplus_parser_context(&context, parser))) {
            siplus_error_get(&textResult);
            if(textResult != NULL) printf("%s\n", textResult);
            return finish(result);
        }

        siplus_context_use_stl(context);

        if((result = siplus_parser_get_interpolation(&constructor, parser, "Hello, from { .name }. Plugins are { .addons | join \" \" }", parseOpts))) {
            siplus_error_get(&textResult);
            if(textResult != NULL) printf("%s\n", textResult);
            return finish(result);
        }

        if((result = siplus_context_builder(&icb, context))) {
            siplus_error_get(&textResult);
            if(textResult != NULL) printf("%s\n", textResult);
            return finish(result);
        }


        info = new LanguageInfo{};
        info->addons = new LanguageInfo::addon_list();
        info->addons->count = 2;
        info->addons->vals = new std::string[] {"Num1", "Num2"};
        container = siplus_data_make(typeInfo, info, [](void* info){ 
            delete[] reinterpret_cast<LanguageInfo*>(info)->addons->vals; 
            delete reinterpret_cast<LanguageInfo*>(info)->addons; 
            delete reinterpret_cast<LanguageInfo*>(info); 
        });
        if((result = siplus_icbuilder_default(icb, container))) {
            siplus_error_get(&textResult);
            if(textResult != NULL) printf("%s\n", textResult);
            return finish(result);
        } else {
            siplus_data_delete(container);
            container = 0;
        }

        if((result = siplus_icbuilder_build(&ic, icb)))  {
            siplus_error_get(&textResult);
            if(textResult != NULL) printf("%s\n", textResult);
            return finish(result);
        }

        if((result = siplus_text_construct(&textResult, constructor, ic))) {
            siplus_error_get(&textResult);
            if(textResult != NULL) printf("%s\n", textResult);
            return finish(result);
        }

        return finish(0);
    });
}
