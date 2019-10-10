#include <gtest/gtest.h>


extern "C" {
    #include "query_info.h"
}

#define OK 0
#define BAD_ALLOC -1
#define WRONG_ANSWER -2


TEST(QueryInfo, create_query_info) {
    QueryInfo* query_info = create_query_info(NULL);
    if (query_info) {
        GTEST_FAIL() << " Information structure should not be created";
    }
    EXPECT_EQ(free_query_info(query_info), BAD_ALLOC) << " Attempt to clean empty structure";
    query_info = create_query_info("mail.ru");
    if (!query_info) {
        GTEST_FAIL() << " Information structure must be created";
    }
    EXPECT_EQ(free_query_info(query_info), OK) << " Structure not cleaned";
}

static int RunProtocol(const char* url, const char* protocol) {
    int res = OK;
    QueryInfo* query_info = create_query_info(url);
    if (strcmp(query_info->protocol->str, protocol)) {
        res = WRONG_ANSWER;
    }
    free_query_info(query_info);
    return res;
}

TEST(QueryInfo, Protocol) {
    int* res = new int[3];
    res[0] = RunProtocol("https://mail.ru", "https");
    res[1] = RunProtocol("http://mail.ru/path/doc.css?a=1&b=2&c=3&d=4#part170", "http");
    res[2] = RunProtocol("P2P://mail.ru.A.b.", "P2P");
    for (size_t i = 0; i < 3; i++) {
        if (res[i] == BAD_ALLOC) {
            GTEST_FAIL() << " Information structure must be created";
        }
        if (res[i] == WRONG_ANSWER) {
             GTEST_FAIL() << " Lines should be equal";
        }
    }
    delete[] res;
}

// TEST(QueryInfo, DNS) {
// }
// TEST(QueryInfo, port) {
// }
// TEST(QueryInfo, QueryStr) {
// }
// TEST(QueryInfo, part) {
// }

TEST(String, create_str) {
    String* str = create_str_from_c_str(NULL);
    if (str) {
        GTEST_FAIL() << " String should not be created";
    }
    EXPECT_EQ(free_str(str), BAD_ALLOC) << " Attempt to clean empty structure";
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
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
