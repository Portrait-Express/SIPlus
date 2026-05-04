#include "siplus/csiplus.h"
#include "common.hxx"
#include "siplus/parser.hxx"
#include "siplus/text/range_iterator.hxx"
#include "siplus/types/float.hxx"
#include "siplus/types/integer.hxx"
#include "siplus/types/string.hxx"
#include "siplus/util.hxx"
#include <cstring>

using namespace SIPLUS_NAMESPACE;

template<typename T1, typename T2>
struct test_match {
    static bool match(const T1&& a, const T2&& b) {
        return a == b;
    }
};

template<>
struct test_match<char*, char*> {
    static bool match(const char* a, const char* b) {
        return !strcmp(a, b);
    }
};

template<>
struct test_match<double, double> {
    static bool match(const double& a, const double& b) {
        return nearly_equal(a, b);
    }
};

template<>
struct test_match<float, float> {
    static bool match(const float& a, const float& b) {
        return nearly_equal(a, b);
    }
};


template<typename T>
bool test_equal(SIPlusUnknownDataContainer *container, T&& val) {
    if constexpr(std::is_same_v<type_info_for_t<T>, types::BoolType>) {
        if(siplus_data_is_bool(container)) {
            int result;
            siplus_data_as_bool(&result, container);
            return static_cast<bool>(result) == val;
        } else {
            throw std::runtime_error{"Result was not a BoolType"};
        }
    } else if constexpr(std::is_same_v<type_info_for_t<T>, types::IntegerType>) {
        if(siplus_data_is_int(container)) {
            long result;
            siplus_data_as_int(&result, container);
            return result == val;
        } else {
            throw std::runtime_error{"Result was not a IntegerType"};
        }
    } else if constexpr(std::is_same_v<type_info_for_t<T>, types::FloatType>) {
        if(siplus_data_is_float(container)) {
            double result;
            siplus_data_as_float(&result, container);
            return nearly_equal(result, val);
        } else {
            throw std::runtime_error{"Result was not a FloatType"};
        }
    } else if constexpr(std::is_same_v<type_info_for_t<T>, types::StringType>) {
        if(siplus_data_is_string(container)) {
            char *result;
            siplus_data_as_string(&result, container);
            auto res = std::string{result} == val;
            siplus_string_delete(result);
            return res;
        } else {
            throw std::runtime_error{"Result was not a StringType"};
        }
    } else {
        throw std::runtime_error{"Unknown Type"};
    }
}

/**
 * struct LanguageInfo - Test Data Structure
 */
struct LanguageInfo {
    std::string name;
    struct addon_list {
        size_t count;
        std::string *vals;
    } *addons;
};
typedef struct LanguageInfo LanguageInfo;

/**
 * struct EmptyInfoType - InfoType data for types that dont need state.
 */
struct EmptyInfoType {};
typedef struct EmptyInfoType EmptyInfoType;

/**
 * struct AddonsIteratorData - Data object for iterating LanguageInfo::addons
 */
struct AddonsIteratorData {
    AddonsIteratorData(size_t size, std::string *data) : size(size), data(data) {}

    long i = 0;
    size_t size = 0;
    bool initialized = false;
    std::string *data;
};

/**
 * @brief `more` function for LanguageInfo::addons
 *
 * @param[in] data Ptr to data object
 * @return 0 if no more, 1 if more
 */
int addon_iterator_more(void *data) {
    AddonsIteratorData *info = reinterpret_cast<AddonsIteratorData*>(data);
    return info->i < info->size - 1;
}

/**
 * @brief `next` function for LanguageInfo::addons
 *
 * @param[in] data Ptr to data object
 * @return possible error code
 */
int addon_iterator_next(void *data) {
    AddonsIteratorData *info = reinterpret_cast<AddonsIteratorData*>(data);

    if(!info->initialized) {
        info->initialized = true;
    } else {
        info->i++;
    }

    return siplus_error_set(SIPLUS_OK, NULL);
}

/**
 * @brief `current` function for LanguageInfo::addons
 *
 * @param[out] result The result data object ptr
 * @param[in] data The data object for this iterator
 * @return Error code
 */
int addon_iterator_current(SIPlusUnknownDataContainer **result, void *data) {
    AddonsIteratorData *info = reinterpret_cast<AddonsIteratorData*>(data);

    *result = siplus_data_make_string(info->data[info->i].c_str());

    return siplus_error_set(SIPLUS_OK, NULL);
}

/**
 * @brief `is_iterable` function for the type info
 *
 * @param[in] data Ptr to the data type object
 * @param[in] object The Ptr to the object we are checking currently
 * @return 0 if not iterable, 1 otherwise
 */
int addon_list_is_iterable(void *data, void *object) {
    return 0;
}

/**
 * @brief `iterate` function
 *
 * @param[out] result Output ptr
 * @param[in] data The data ptr to the typeinfo
 * @param[in] object The object to iterate over
 * @return Error code
 */
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

/**
 * @brief Create a new TypeInfo for LanauageInfo::addons
 *
 * @return Type info ptr. Make sure to delete it once you are done.
 */
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

/**
 * @brief `is_iterable` function for LanguageInfo
 *
 * @param[in] data Data object for type info
 * @param[in] object Object to test
 * @return true if iterable
 */
int language_info_is_iterable(void *data, void *object) {
    return 0;
}

/**
 * @brief `access` function for LanguageInfo
 *
 * @param[out] result Output ptr
 * @param[in] info TypeInfo object
 * @param[in] data Data ptr for object
 * @param[in] property Property name
 * @return error code
 */
int language_info_access(SIPlusUnknownDataContainer **result, void *info, void *data, const char *property) {
    LanguageInfo *language = reinterpret_cast<LanguageInfo*>(data);

    if(std::string{property} == "name") {
        *result = siplus_data_make_string(language->name.c_str());
        return siplus_error_set(SIPLUS_OK, NULL);
    } else if(std::string{property} == "addons") {
        auto type = addon_list_type_new();
        *result = siplus_data_make(type, language->addons, [](void*){});
        siplus_type_unref(type);
        return siplus_error_set(SIPLUS_OK, NULL);
    }

    return siplus_error_set(SIPLUS_ERR, util::to_string("Unrecognized property name ", property).c_str());
}

/**
 * @brief Create a new TypeInfo
 *
 * @return New Type Info
 */
SIPlusTypeInfo *langauge_info_type_new() {
    SIPlusTypeInfo *info;
    EmptyInfoType *data = new EmptyInfoType();

    siplus_type_new(&info, reinterpret_cast<void*>(data), "LanguageInfo", language_info_is_iterable, language_info_access, NULL, [](void* data){
        delete reinterpret_cast<EmptyInfoType*>(data);
    });
    return info;
}

struct TestFunctionRetrieverData { 
    SIPlusValueRetriever *param;
};

int test_function_retriever_impl(SIPlusUnknownDataContainer **result, void *data, SIPlusInvocationContext *context) {
    SIPlusUnknownDataContainer *paramVal;
    TestFunctionRetrieverData *tfrd = reinterpret_cast<TestFunctionRetrieverData*>(data);

    if(auto err = siplus_value_retrieve(&paramVal, tfrd->param, context); err) {
        return err;
    }

    if(!siplus_data_is_int(paramVal)) {
        siplus_data_delete(paramVal);
        return siplus_error_set(SIPLUS_INVALID_ARG, "Expected an integer as parameter");
    }

    long val;
    if(auto err = siplus_data_as_int(&val, paramVal); err) {
        siplus_data_delete(paramVal);
        return err;
    }

    if(val == 1) {
        *result = paramVal;
        return SIPLUS_OK;
    } else {
        siplus_data_delete(paramVal);
        return siplus_error_set(SIPLUS_INVALID_ARG, "Expected parameter to be 1");
    }
}

void test_function_retriever_delete(void *data) {
    auto tfrd = reinterpret_cast<TestFunctionRetrieverData*>(data);
    siplus_value_unref(tfrd->param);
    delete tfrd;
}

struct TestFunctionData { };

int test_function_value(SIPlusValueRetriever **result, void *data, SIPlusValueRetriever *parent, int paramc, SIPlusValueRetriever **paramv) {
    TestFunctionData *tfd = reinterpret_cast<TestFunctionData*>(data);
    TestFunctionRetrieverData *tfrd = new TestFunctionRetrieverData{};

    SIPlusValueRetriever *param;
    if(parent) {
        param = parent;
        for(int i = 0; i < paramc; i++) { siplus_value_unref(paramv[i]); }
        if(paramc > 0) {
            return siplus_error_set(SIPLUS_INVALID_ARG, "Expected no parameters when parent is specified");
        }
    } else {
        for(int i = 0; i < paramc; i++) { 
            if(i > 0) {
                siplus_value_unref(paramv[i]); 
            } else {
                param = paramv[i];
            }
        }
        if(paramc != 1) {
            return siplus_error_set(SIPLUS_INVALID_ARG, "Expected only 1 parameter when parent is not specified");
        }
    }

    tfrd->param = param;
    int err = siplus_value_create(result, reinterpret_cast<void*>(tfrd), test_function_retriever_impl, test_function_retriever_delete);
    if(err) { return err; }

    return SIPLUS_OK;
}

void test_function_delete(void *data) {
    delete reinterpret_cast<TestFunctionData*>(data);
}

SIPlusUnknownDataContainer *get_testdata() {
    SIPlusTypeInfo *typeInfo = langauge_info_type_new();
    auto info = new LanguageInfo{};
    info->name = "C";
    info->addons = new LanguageInfo::addon_list();
    info->addons->count = 2;
    info->addons->vals = new std::string[] {"Num1", "Num2"};

    auto ret = siplus_data_make(typeInfo, info, [](void* info){ 
        delete[] reinterpret_cast<LanguageInfo*>(info)->addons->vals; 
        delete reinterpret_cast<LanguageInfo*>(info)->addons; 
        delete reinterpret_cast<LanguageInfo*>(info); 
    });

    siplus_type_unref(typeInfo);

    return ret;
}

int get_testcontext(SIPlusInvocationContext **ic, SIPlusParser *parser) {
    SIPlusContext *context = nullptr;
    SIPlusInvocationContextBuilder *icb = nullptr;
    SIPlusUnknownDataContainer *data = get_testdata();

    auto finish = [&](int code) {
        siplus_data_delete(data);
        siplus_context_unref(context);
        siplus_icbuilder_delete(icb);
        return code;
    };

    if(auto result = siplus_parser_context(&context, parser); result) {
        return result;
    }

    if(auto result = siplus_context_builder(&icb, context); result) {
        return finish(result);
    }


    if(auto result = siplus_icbuilder_default(icb, data); result) {
        return finish(result);
    }

    if(auto result = siplus_icbuilder_build(ic, icb); result)  {
        return finish(result);
    }

    return finish(SIPLUS_OK);
}

/**
 * @brief Create a Parser instance for testing
 *
 * @param[out] parser A pointer to a pointer where the parser will be set
 * @return SIPLUS_OK if no errors.
 */
int get_parser(SIPlusParser **parser) {
    SIPlusContext *context = nullptr;
    SIPlusFunction *function = nullptr;
    TestFunctionData *tfd = new TestFunctionData{};
    char *errorMsg = nullptr;

    
    auto finish = [&](int result) {
        if (result) {
            siplus_parser_delete(*parser);
            *parser = nullptr;
        }
        siplus_context_unref(context);
        siplus_function_unref(function);
        return result;
    };

    *parser = siplus_parser_new();

    if(auto result = siplus_parser_context(&context, *parser); result) {
        return finish(result);
    }

    siplus_context_use_stl(context);

    if(auto result = siplus_function_create(&function, reinterpret_cast<void*>(tfd), test_function_value, test_function_delete); result) {
        return finish(result);
    }

    //Add custom `test` function
    if(auto result = siplus_context_add_function(context, "test", function); result) {
        return finish(result);
    }

    return finish(SIPLUS_OK);
}

int test_interpolation(SIPlusParser *parser, std::string text, std::string expected, bool expect_fail = false) {
    SIPlusParseOpts *opts = siplus_parse_opts_new();
    SIPlusInvocationContext *context = nullptr;
    SIPlusTextConstructor *constructor = nullptr;
    char *textResult = nullptr;

    auto finish = [&](int code) {
        siplus_parse_opts_delete(opts);
        siplus_invocation_unref(context);
        siplus_text_unref(constructor);
        return code;
    };

    if(auto result = siplus_parser_get_interpolation(&constructor, parser, text.c_str(), opts); result) {
        siplus_error_get(&textResult);
        if(textResult != NULL) printf("%s\n", textResult);
        siplus_string_delete(textResult);
        return finish(result);
    }

    if(auto result = get_testcontext(&context, parser); result) {
        siplus_error_get(&textResult);
        if(textResult != NULL) printf("%s\n", textResult);
        siplus_string_delete(textResult);
        return finish(result);
    }

    auto result = siplus_text_construct(&textResult, constructor, context);
    if((expect_fail && !result) || (!expect_fail && result)) {
        siplus_error_get(&textResult);
        if(textResult != NULL) printf("%s\n", textResult);
        siplus_string_delete(textResult);
        return finish(result);
    }

    std::string constructed{textResult};
    siplus_string_delete(textResult);

    if(constructed == expected) {
        return finish(0);
    } else {
        std::cout 
            << "Interpolation " << text << " failed. Expected \"" << expected 
            << "\". Got \"" << constructed << "\"." << std::endl;

        return finish(1);
    }
}

template<typename T>
bool test_expression(SIPlusParser *parser, std::string text, T&& expected, bool expect_fail = false) {
    SIPlusParseOpts *opts = siplus_parse_opts_new();
    SIPlusInvocationContext *context = nullptr;
    SIPlusValueRetriever *retriever = nullptr;
    SIPlusUnknownDataContainer *container = nullptr;
    char *textResult = nullptr;

    auto finish = [&](int code) {
        siplus_parse_opts_delete(opts);
        siplus_invocation_unref(context);
        siplus_data_delete(container);
        siplus_value_unref(retriever);
        return code;
    };

    if(auto result = siplus_parser_get_expression(&retriever, parser, text.c_str(), opts); result) {
        siplus_error_get(&textResult);
        if(textResult != NULL) printf("Expression: %s - %s\n", text.c_str(), textResult);
        siplus_string_delete(textResult);
        return finish(result);
    }

    if(auto result = get_testcontext(&context, parser); result) {
        siplus_error_get(&textResult);
        if(textResult != NULL) printf("Expression: %s - %s\n", text.c_str(), textResult);
        siplus_string_delete(textResult);
        return finish(result);
    }

    auto result = siplus_value_retrieve(&container, retriever, context);
    if(result) {
        if(!expect_fail) {
            siplus_error_get(&textResult);
            if(textResult != NULL) printf("Expression: %s - %s\n", text.c_str(), textResult);
            siplus_string_delete(textResult);
            return finish(result);
        } else {
            return finish(SIPLUS_OK);
        }
    }

    bool is_equal = test_equal(container, std::forward<T>(expected));
    if((expect_fail && is_equal) || (!expect_fail && !is_equal)) {
        SIPlusTypeInfo *info;
        char *typeName;
        siplus_data_type(&info, container);
        siplus_type_name(&typeName, info);

        std::cout << "Value was not equal to expected value " << expected 
            << ". Got value of type " << std::string{typeName} << std::endl;

        siplus_string_delete(typeName);
        siplus_type_unref(info);
        return finish(SIPLUS_ERR);
    }
    
    return finish(SIPLUS_OK);
}

int test_c(int argc, char** const argv) {
    return test("C API", []() {
        int result = 0;
        SIPlusParser *parser = nullptr;
        char *textResult = nullptr;

        auto finish = [&](int err) {
            siplus_string_delete(textResult);
            siplus_parser_delete(parser);

            return err;
        };

        if(auto result = get_parser(&parser); result) {
            siplus_error_get(&textResult);
            if(textResult != NULL) printf("%s\n", textResult);
            return finish(result);
        }

        result = test_interpolation(parser,  
            "Hello, from { .name }. Plugins are { .addons | join \" \" }", 
            "Hello, from C. Plugins are Num1 Num2");
        if(result) { return finish(1); }

        result = test_expression(parser, "test 1", 1);
        if(result) { return finish(1); }

        result = test_expression(parser, "test 2", 2, true);
        if(result) { return finish(1); }


        return finish(0);
    });
}
