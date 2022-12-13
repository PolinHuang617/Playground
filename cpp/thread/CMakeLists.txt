cmake_minimum_required(VERSION 3.12)

project(IPC)

# SET(CMAKE_BUILD_TYPE "Releases")  # 定义编译类型
SET(CMAKE_BUILD_TYPE "Debug")  # 定义编译类型
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb") # 定义Debug编译参数
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") # 定义Release编译参数

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
endif()

add_subdirectory(mutex)
add_subdirectory(condition_variable)
add_subdirectory(future)
add_subdirectory(thread_pool)

