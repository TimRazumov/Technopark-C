//#include <gmock/gmock.h>
#include <gtest/gtest.h>


extern "C" {
    #include "query_info.h"
}


TEST(QueryInfo, Create) {
    QueryInfo* query_info = create_query_info(NULL);
    if (query_info) {
        GTEST_FAIL() << " Information structure should not be created";
    }
    query_info = create_query_info("mail.ru");
    if (!query_info) {
        GTEST_FAIL() << " Information structure must be created";
    }
    free_query_info(query_info);
    EXPECT_EQ(64, 64);
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
