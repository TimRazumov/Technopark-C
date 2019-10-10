//#include <gmock/gmock.h>
#include <gtest/gtest.h>


extern "C" {
    #include "query_info.h"
}


TEST(QueryInfo, CreateDelete) {
    QueryInfo* query_info = create_query_info(NULL);
    if (query_info) {
        GTEST_FAIL() << " Information structure should not be created";
    }
    query_info = create_query_info("mail.ru");
    if (!query_info) {
        GTEST_FAIL() << " Information structure must be created";
    }
    free_query_info(query_info);
    /*try {
        print_query_info(query_info);
    } catch (...) {
        
    }*/
    // EXPECT_EQ(64, 64);
    //char* url = "a.b.c.d.e.d";
    //QueryInfo* query_info = create_query_info(url);
    //GTEST_FAIL() << " DArray should throw an exception";
    
}

TEST(QueryInfo, Protocol) {
    QueryInfo* query_info = create_query_info("https://mail.ru");
    if (!query_info) {
        GTEST_FAIL() << " Information structure must be created";
    }
    if (strcmp(query_info->protocol->str, "https")) {
        GTEST_FAIL() << " Lines should be equal";
    }
    // EXPECT_EQ;
    free_query_info(query_info);
    //char* url = "a.b.c.d.e.d";
    //QueryInfo* query_info = create_query_info(url);
    //GTEST_FAIL() << " DArray should throw an exception";
    
}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
