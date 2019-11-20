cmake_minimum_required(VERSION 3.8)
project(HW2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror -Wpedantic")

include_directories(lib_substr/parall_substr lib_substr/substr)

set(LIB_SUBSTR
        lib_substr/substr/substr.c
        lib_substr/parall_substr/parall_substr.c)
#add_library(_substr STATIC ${LIB_SUBSTR}) 
add_library(_substr MODULE ${LIB_SUBSTR})       

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# test
add_executable(test.out test_lib_substr/test.cpp)

# links gtest
target_link_libraries(test.out ${GTEST_LIBRARIES})
target_link_libraries(test.out pthread)
target_link_libraries(test.out ${CMAKE_DL_LIBS})
