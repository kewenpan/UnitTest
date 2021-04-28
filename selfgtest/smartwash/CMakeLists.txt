cmake_minimum_required(VERSION 3.00)
project(SmartWash)

#set(CMAKE_CXX_STANDARD 11)
#SET(CMAKE_C_COMPILER g++)
#add_compile_options(-std=c++11)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

add_definitions(-D RR_SMART_WASH)

include_directories(include)

add_definitions(-D STD_UNIT_TEST)
aux_source_directory(src DIR_SRCS)
aux_source_directory(main DIR_MAIN)
# 指定生成目标
add_executable (SmartWash ${DIR_SRCS} ${DIR_MAIN})

# 添加测试目录
add_subdirectory(test)