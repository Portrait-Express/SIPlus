#include "siplus/csiplus.h"
#include "common.hxx"
#include "siplus/util.hxx"

using namespace SIPLUS_NAMESPACE;

struct LanguageInfo {
    std::string name;
};
typedef struct LanguageInfo LanguageInfo;

struct LanguageInfoType {};
typedef struct LanguageInfoType LanguageInfoType;

int language_info_is_iterable(void *data, void *object) {
    return 0;
}

int language_info_access(SIPlusUnknownDataContainer **result, void *data, void *info, const char *property) {
    LanguageInfo *language = reinterpret_cast<LanguageInfo*>(info);

    if(std::string{property} == "name") {
        *result = siplus_data_make_string(language->name.c_str());
        return siplus_error_set(SIPLUS_OK, NULL);
    }

    return siplus_error_set(SIPLUS_ERR, util::to_string("Unrecognized property name ", property).c_str());
}

SIPlusTypeInfo *langauge_info_type_new() {
    SIPlusTypeInfo *info;
    LanguageInfoType *data = new LanguageInfoType();

    siplus_type_new(&info, reinterpret_cast<void*>(data), "LanguageInfo", language_info_is_iterable, language_info_access, NULL, [](void* data){
        delete reinterpret_cast<LanguageInfoType*>(data);
    });
    return info;
}


int test_c(int argc, char **argv) {
    return group("C API", []() {
        return tests(
            test("basic", []() {
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
                    return finish(result);
                }

                if((result = siplus_parser_get_interpolation(&constructor, parser, "Hello, from { .name }", parseOpts))) {
                    return finish(result);
                }

                if((result = siplus_context_builder(&icb, context))) {
                    return finish(result);
                }


                info = new LanguageInfo{};
                container = siplus_data_make(typeInfo, info, [](void* info){ 
                    delete reinterpret_cast<LanguageInfo*>(info); 
                });
                if((result = siplus_icbuilder_default(icb, container))) {
                    return finish(result);
                } else {
                    siplus_data_delete(container);
                    container = 0;
                }

                if((result = siplus_icbuilder_build(&ic, icb)))  {
                    return finish(result);
                }

                if((result = siplus_text_construct(&textResult, constructor, ic))) {
                    return finish(result);
                }

                return finish(0);
            })
        );
    });
}
