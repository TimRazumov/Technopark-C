#include <dlfcn.h>
#include <gtest/gtest.h>

extern "C" {
    #include "parall_substr.h"
}

#define SUBSTR_LIB "./lib_substr.so"
#define TEST1 "test_lib_substr/test_case/test1.txt"
#define TEST2 "test_lib_substr/test_case/test2.txt"
#define TEST3 "test_lib_substr/test_case/test3.txt"

TEST(substr, get_substr_info) {
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

TEST(substr, get_max_substr_without_repeat_from_file) {
    char* str = get_max_substr_without_repeat_from_file("tests/test1.txt");  // 700 b
    if (!str) {
        GTEST_FAIL() << " Error";
        return;
    }
    if (strcmp(str, "kwjhl")) {
        GTEST_FAIL() << " Wrong answer";
        return;
    }
    free(str);

    str = get_max_substr_without_repeat_from_file("tests/test2.txt");  // 1 mb
    if (!str) {
        GTEST_FAIL() << " Error";
        return;
    }
    if (strcmp(str, "vyrkhudsoqintcgafjeb")) {
        GTEST_FAIL() << " Wrong answer";
        return;
    }
    free(str);

    str = get_max_substr_without_repeat_from_file("tests/test3.txt");  // 100 mb
    if (!str) {
        GTEST_FAIL() << " Error";
        return;
    }
    if (strcmp(str, "wtklaehqozdcrvxnpibfjymu")) {
        GTEST_FAIL() << " Wrong answer";
        return;
    }
    free(str);
    return;
}

/*TEST(parall_substr, get_max_substr_without_repeat_from_file_parall) {
    char* str = get_max_substr_without_repeat_from_file_parall("tests/test1.txt");  // 700 b
    if (!str) {
        GTEST_FAIL() << " Error";
        return;
    }
    if (strcmp(str, "kwjhl")) {
        GTEST_FAIL() << " Wrong answer";
        return;
    }
    free(str);

    str = get_max_substr_without_repeat_from_file_parall("tests/test2.txt");  // 1 mb
    if (!str) {
        GTEST_FAIL() << " Error";
        return;
    }
    if (strcmp(str, "vyrkhudsoqintcgafjeb")) {
        GTEST_FAIL() << " Wrong answer";
        return;
    }
    free(str);

    str = get_max_substr_without_repeat_from_file_parall("tests/test3.txt");  // 100 mb
    if (!str) {
        GTEST_FAIL() << " Error";
        return;
    }
    if (strcmp(str, "wtklaehqozdcrvxnpibfjymu")) {
        GTEST_FAIL() << " Wrong answer";
        return;
    }
    free(str);
    return;
}*/

// direct and parallel comparison

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
