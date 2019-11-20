#include <dlfcn.h>
#include <gtest/gtest.h>

extern "C" {
    #include "parall_substr.h"
}

#define SUBSTR_LIB "./lib_substr.so"
#define TEST1 "lib_substr/test/test_case/test1.txt"
#define TEST2 "lib_substr/test/test_case/test2.txt"
#define TEST3 "lib_substr/test/test_case/test3.txt"

TEST(substr_lib, get_substr_info) {
    void *dl_handle = dlopen(SUBSTR_LIB, RTLD_LAZY);
    if (!dl_handle) {
        GTEST_FAIL();
        return;
    }
    chunk_info* (*foo)(const char* const) = NULL;
    *(void **) (&foo) = dlsym(dl_handle, "get_substr_info");
    if (!foo) {
        GTEST_FAIL();
        dlclose(dl_handle);
        return;
    }
    if ((*foo)(NULL)) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        return;
    }
    FILE* f = fopen(TEST1, "r");
    if (!f) {
        GTEST_FAIL();
        dlclose(dl_handle);
        return;
    }
    fseek(f, 0, SEEK_END);
    size_t file_size = ftell(f);
    rewind(f);
    char* str = (char*)calloc(file_size + 1, sizeof(char));
    if (!str) {
        fclose(f);
        dlclose(dl_handle);
        return;
    }
    fgets(str, file_size + 1, f);
    chunk_info* info = (*foo)(str);
    free(str);
    fclose(f);
    if (!info || info->size != 691 || info->pos != 671 || info->max != 5) {
        GTEST_FAIL() << " Wrong answer";
        free(info);
        dlclose(dl_handle);
        return;
    }
    free(info);

    f = fopen(TEST2, "r");
    if (!f) {
        GTEST_FAIL();
        dlclose(dl_handle);
        return;
    }
    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    rewind(f);
    str = (char*)calloc(file_size + 1, sizeof(char));
    if (!str) {
        fclose(f);
        dlclose(dl_handle);
        return;
    }
    fgets(str, file_size + 1, f);
    info = (*foo)(str);
    free(str);
    fclose(f);
    if (!info || info->size != 1048576 || info->pos != 47913 || info->max != 20) {
        GTEST_FAIL() << " Wrong answer";
        free(info);
        dlclose(dl_handle);
        return;
    }
    free(info);

    f = fopen(TEST3, "r");
    if (!f) {
        GTEST_FAIL();
        dlclose(dl_handle);
        return;
    }
    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    rewind(f);
    str = (char*)calloc(file_size + 1, sizeof(char));
    if (!str) {
        fclose(f);
        dlclose(dl_handle);
        return;
    }
    fgets(str, file_size + 1, f);
    info = (*foo)(str);
    free(str);
    fclose(f);
    if (!info || info->size != 104857600 || info->pos != 51843502 || info->max != 24) {
        GTEST_FAIL() << " Wrong answer";
        free(info);
        dlclose(dl_handle);
        return;
    }
    free(info);
    return;
}

TEST(substr_lib, comp_direct_parallel_approach) {
    void *dl_handle = dlopen(SUBSTR_LIB, RTLD_LAZY);
    if (!dl_handle) {
        GTEST_FAIL();
        return;
    }
    char* (*direct_foo)(const char* const) = NULL;
    char* (*parall_foo)(const char* const) = NULL;
    *(void **) (&direct_foo) = dlsym(dl_handle, "get_max_substr_without_repeat_from_file");
    *(void **) (&parall_foo) = dlsym(dl_handle, "get_max_substr_without_repeat_from_file_parall");
    if (!direct_foo || !parall_foo) {
        GTEST_FAIL();
        dlclose(dl_handle);
        return;
    }
    if ((*direct_foo)(NULL) || (*parall_foo)(NULL)) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        return;
    }

    char* direct_str = (*direct_foo)(TEST1);  // 700 b
    char* parall_str = (*parall_foo)(TEST1);
    if (!direct_str || !parall_str) {
        GTEST_FAIL() << " Error";
        free(direct_str);
        free(parall_str);
        dlclose(dl_handle);
        return;
    }
    if (strcmp(direct_str, parall_str)) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(direct_str);
        free(parall_str);
        return;
    }
    free(direct_str);
    free(parall_str);

    direct_str = (*direct_foo)(TEST2);  // 1 mb
    parall_str = (*parall_foo)(TEST2);
    if (!direct_str || !parall_str) {
        GTEST_FAIL() << " Error";
        free(direct_str);
        free(parall_str);
        dlclose(dl_handle);
        return;
    }
    if (strcmp(direct_str, parall_str)) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(direct_str);
        free(parall_str);
        return;
    }
    free(direct_str);
    free(parall_str);

    direct_str = (*direct_foo)(TEST3);  // 100 mb
    parall_str = (*parall_foo)(TEST3);
    if (!direct_str || !parall_str) {
        GTEST_FAIL() << " Error";
        free(direct_str);
        free(parall_str);
        dlclose(dl_handle);
        return;
    }
    if (strcmp(direct_str, parall_str)) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(direct_str);
        free(parall_str);
        return;
    }
    free(direct_str);
    free(parall_str);
    dlclose(dl_handle);
}

TEST(substr_lib, get_max_substr_without_repeat_from_file) {
    void *dl_handle = dlopen(SUBSTR_LIB, RTLD_LAZY);
    if (!dl_handle) {
        GTEST_FAIL();
        return;
    }
    char* (*foo)(const char* const) = NULL;
    *(void **) (&foo) = dlsym(dl_handle, "get_max_substr_without_repeat_from_file");
    if (!foo) {
        GTEST_FAIL();
        dlclose(dl_handle);
        return;
    }
    if ((*foo)(NULL)) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        return;
    }
    char* str = (*foo)(TEST1);  // 700 b
    if (!str) {
        GTEST_FAIL() << " Error";
        dlclose(dl_handle);
        return;
    }
    if (strcmp(str, "kwjhl")) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(str);
        return;
    }
    free(str);

    str = (*foo)(TEST2);  // 1 mb
    if (!str) {
        GTEST_FAIL() << " Error";
        dlclose(dl_handle);
        return;
    }
    if (strcmp(str, "vyrkhudsoqintcgafjeb")) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(str);
        return;
    }
    free(str);

    str = (*foo)(TEST3);  // 100 mb
    if (!str) {
        GTEST_FAIL() << " Error";
        dlclose(dl_handle);
        return;
    }
    if (strcmp(str, "wtklaehqozdcrvxnpibfjymu")) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(str);
        return;
    }
    free(str);
    dlclose(dl_handle);
    return;
}

TEST(substr_lib, get_max_substr_without_repeat_from_file_parall) {
    void *dl_handle = dlopen(SUBSTR_LIB, RTLD_LAZY);
    if (!dl_handle) {
        GTEST_FAIL();
        return;
    }
    char* (*foo)(const char* const) = NULL;
    *(void **) (&foo) = dlsym(dl_handle, "get_max_substr_without_repeat_from_file_parall");
    if (!foo) {
        GTEST_FAIL();
        dlclose(dl_handle);
        return;
    }
    if ((*foo)(NULL)) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        return;
    }
    char* str = (*foo)(TEST1);  // 700 b
    if (!str) {
        GTEST_FAIL() << " Error";
        dlclose(dl_handle);
        return;
    }
    if (strcmp(str, "kwjhl")) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(str);
        return;
    }
    free(str);

    str = (*foo)(TEST2);  // 1 mb
    if (!str) {
        GTEST_FAIL() << " Error";
        dlclose(dl_handle);
        return;
    }
    if (strcmp(str, "vyrkhudsoqintcgafjeb")) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(str);
        return;
    }
    free(str);

    str = (*foo)(TEST3);  // 100 mb
    if (!str) {
        GTEST_FAIL() << " Error";
        dlclose(dl_handle);
        return;
    }
    if (strcmp(str, "wtklaehqozdcrvxnpibfjymu")) {
        GTEST_FAIL() << " Wrong answer";
        dlclose(dl_handle);
        free(str);
        return;
    }
    free(str);
    dlclose(dl_handle);
    return;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
