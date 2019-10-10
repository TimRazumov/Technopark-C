#include <gtest/gtest.h>


extern "C" {
    #include "query_info.h"
}

#define OK 0
#define NULL_PTR -1
#define WRONG_ANSWER -2

TEST(QueryInfo, create_query_info) {
    QueryInfo* query_info = create_query_info(NULL);
    if (query_info) {
        GTEST_FAIL() << " Information structure should not be created";
        return;
    }
    EXPECT_EQ(free_query_info(query_info), NULL_PTR) << " Attempt to clean empty structure";
    query_info = create_query_info("http://www.corp.mail.ru:8080");
    if (!query_info) {
        goto exit;
    }
    if (query_info->port != 8080 || query_info->num_domains != 4 || strcmp(query_info->domains[0]->str, "www")
        || strcmp(query_info->domains[1]->str, "corp") || strcmp(query_info->domains[2]->str, "mail")
        || strcmp(query_info->domains[3]->str, "ru") || strcmp(query_info->protocol->str, "http")) {
        GTEST_FAIL() << " Wrong url";
    }
    EXPECT_EQ(free_query_info(query_info), OK) << " Structure not cleaned";
    query_info = create_query_info("https://aaa.bbb.ccc./path1/path2/doc.html?a=1&b=2#part100");
    if (!query_info) {
        goto exit;
    }
    if (strcmp(query_info->protocol->str, "https") || query_info->num_domains != 3
        || strcmp(query_info->domains[0]->str, "aaa") || strcmp(query_info->domains[1]->str, "bbb")
        || strcmp(query_info->domains[2]->str, "ccc.")
        || strcmp(query_info->doc_path->str, "path1/path2/doc.html")
        || strcmp(query_info->query_string->str, "a=1&b=2") || strcmp(query_info->part->str, "part100")) {
        GTEST_FAIL() << " Wrong url";
    }
    EXPECT_EQ(free_query_info(query_info), OK) << " Structure not cleaned";
    return;
    exit:
    GTEST_FAIL() << " Information structure must be created";
    return;
}

TEST(String, create_str) {
    String* str = create_str_from_c_str(NULL);
    if (str) {
        GTEST_FAIL() << " String should not be created";
    }
    EXPECT_EQ(free_str(str), NULL_PTR) << " Attempt to clean empty structure";
    str = create_str_from_c_str("mail.ru");
    if (!str) {
        GTEST_FAIL() << " String must be created";
    }
    EXPECT_EQ(free_str(str), OK) << " Structure not cleaned";
    str = create_str(10);
    if (!str) {
        GTEST_FAIL() << " String must be created";
    }
    EXPECT_EQ(free_str(str), OK) << " Structure not cleaned";
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
        GTEST_FAIL() << " String should not be created";
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
        GTEST_FAIL() << " String should not be created";
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
