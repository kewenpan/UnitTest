cmake_minimum_required(VERSION 3.0)
#
#enable_testing()
#
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIR})
#include_directories(../src/)
#add_executable(Footest fooTest.cpp)
#target_link_libraries(Footest ${GTEST_BOTH_LIBRARIES})
#
#add_test(
#        NAME Footest
#        COMMAND Footest
#)

# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(include /usr/local/include/rapidjson/)

add_executable(test_my_class jsonchecktest.cpp)

# 链接测试库
target_link_libraries( test_my_class
        ${GTEST_BOTH_LIBRARIES}
        pthread )

# 添加到测试
gtest_discover_tests(test_my_class)