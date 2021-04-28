#cmake_minimum_required(VERSION 3.0)
#
#project(foo)
#add_subdirectory(tests)
cmake_minimum_required(VERSION 3.00)
project(MyProject)

find_package(RapidJSON)
set(CMAKE_CXX_STANDARD 11)
include_directories(include /usr/local/include/rapidjson/)
include_directories(src)

# 开启测试
enable_testing()

set(MY_PROJECT_SRC
        src/myclass.cpp)

add_executable(MyProject
        ${MY_PROJECT_SRC}
        src/main.cpp)

# 添加测试目录
add_subdirectory(tests)