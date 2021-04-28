# 查找 GTest 库
find_package(GTest REQUIRED)
set(CMAKE_CXX_STANDARD 11)

# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})
add_definitions(-D STD_UNIT_TEST)
add_definitions(-D RR_SMART_WASH)
#aux_source_directory(../src/ DIR_SRCS)
add_executable(test_my_class smartwashtest.cpp ../src/smartwash.cpp ../src/singleton.cpp)

# 链接测试库
target_link_libraries( test_my_class
        ${GTEST_BOTH_LIBRARIES}
        pthread )

# 添加到测试
gtest_discover_tests(test_my_class)