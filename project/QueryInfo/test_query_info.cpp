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

TEST(QueryInfo, num_domains) {
    String* str_url = create_str_from_c_str("a.bry.ccccccc.tytytyt.sdfsd.");
    EXPECT_EQ(num_domains(str_url), 5) << " Wrong answer";
    free_str(str_url);
    str_url = create_str_from_c_str("");
    EXPECT_EQ(num_domains(str_url), 1) << " Wrong answer";
    free_str(str_url);
    str_url = create_str_from_c_str("a.b.c");
    EXPECT_EQ(num_domains(str_url), 3) << " Wrong answer";
    free_str(str_url);
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
