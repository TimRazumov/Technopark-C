#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "query_info.h"




TEST(QueryInfo, xur) {
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
