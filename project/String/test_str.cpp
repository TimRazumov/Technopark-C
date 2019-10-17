#include <gtest/gtest.h>

extern "C" {
    #include "str.h"
}

TEST(String, create_str) {
    String* str = create_str_from_c_str(NULL);
    if (str) {
        GTEST_FAIL() << " String should not be created";
    }
    EXPECT_EQ(free_str(str), EXIT_FAILURE) << " Attempt to clean empty structure";
    str = create_str_from_c_str("mail.ru");
    if (!str) {
        GTEST_FAIL() << " String must be created";
    }
    EXPECT_EQ(free_str(str), EXIT_SUCCESS) << " Structure not cleaned";
    str = create_str(10);
    if (!str) {
        GTEST_FAIL() << " String must be created";
    }
    EXPECT_EQ(free_str(str), EXIT_SUCCESS) << " Structure not cleaned";
}

TEST(String, swap_str) {
    String* str1 = create_str_from_c_str("hello1");
    String* str2 = create_str_from_c_str("hello2");
    String* str3 = create_str_from_c_str("hello3");
    swap_str(&str1, &str2);  // str1 - hello2, str2 - hello1
    swap_str(&str2, &str3);  // str2 - hello3, str3 - hello1
    swap_str(&str1, &str3);  // str1 - hello1, str3 - hello2
    if (strcmp(str1->str, "hello1") || strcmp(str2->str, "hello3")
        || strcmp(str3->str, "hello2")) {
        GTEST_FAIL() << " Wrong answer";
    }
    free_str(str1);
    free_str(str2);
    free_str(str3);
}

TEST(String, split_str) {
    String* str1 = create_str_from_c_str("aaa.bbb###ccc");
    String* str2 = split_str(str1, ".");
    String* str3 = split_str(str2, "###");
    if (strcmp(str1->str, "aaa") || strcmp(str2->str, "bbb")
        || strcmp(str3->str, "ccc")) {
        GTEST_FAIL() << " Wrong answer";
    }
    free_str(str1);
    free_str(str2);
    free_str(str3);
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
