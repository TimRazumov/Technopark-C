cmake_minimum_required(VERSION 3.8)
project(HW1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror --pedantic")

include_directories(project/include)
include_directories(project/src)

set(LIB_SOURCE_FILES
        project/src/main.c
        project/src/str.c
        project/src/query_info.c)
        
add_library(url_parse_std_lib STATIC ${LIB_SOURCE_FILES})

add_executable(prog.out project/src/main.c)

target_link_libraries(prog.out url_parse_std_lib)

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests.out project/src/tests.cpp)

# links gtest
target_link_libraries(tests.out ${GTEST_LIBRARIES})
target_link_libraries(tests.out pthread)
target_link_libraries(tests.out gmock)
target_link_libraries(tests.out url_parse_std_lib)
