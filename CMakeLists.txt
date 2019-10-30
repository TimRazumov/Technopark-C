cmake_minimum_required(VERSION 3.8)
project(HW2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror --pedantic")

include_directories(project/parall_substr)
include_directories(project/substr)

set(LIB_PARALL_SUBSTR
        project/parall_substr/parall_substr.c
        project/parall_substr/test_parall_substr.cpp)
add_library(_parall_substr STATIC ${LIB_PARALL_SUBSTR})

set(LIB_SUBSTR
        project/substr/substr.c
        project/substr/test_substr.cpp)
add_library(_substr SHARED ${LIB_SUBSTR})       


# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# parall_substr_lib
add_executable(test_parall_substr.out project/parall_substr/test_parall_substr.cpp)
target_link_libraries(test_parall_substr.out _parall_substr)
# links gtest
target_link_libraries(test_parall_substr.out ${GTEST_LIBRARIES})
target_link_libraries(test_parall_substr.out pthread)

# substr lib
add_executable(test_substr.out project/substr/test_substr.cpp)
target_link_libraries(test_substr.out _substr)
# links gtest
target_link_libraries(test_substr.out ${GTEST_LIBRARIES})
target_link_libraries(test_substr.out pthread)
