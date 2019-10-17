cmake_minimum_required(VERSION 3.8)
project(HW1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror --pedantic")

include_directories(project/QueryInfo)
include_directories(project/String)

set(LIB_SOURCE_FILES
        project/String/str.c
        project/String/test_str.cpp
        project/QueryInfo/query_info.c
        project/QueryInfo/test_query_info.cpp)
        
add_library(url_parse_std_lib STATIC ${LIB_SOURCE_FILES})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# query_info
add_executable(test_query_info.out project/QueryInfo/test_query_info.cpp)
target_link_libraries(test_query_info.out url_parse_std_lib)
# links gtest
target_link_libraries(test_query_info.out ${GTEST_LIBRARIES})
target_link_libraries(test_query_info.out pthread)

# string
add_executable(test_str.out project/String/test_str.cpp)
target_link_libraries(test_str.out url_parse_std_lib)
# links gtest
target_link_libraries(test_str.out ${GTEST_LIBRARIES})
target_link_libraries(test_str.out pthread)
