cmake_minimum_required(VERSION 3.1)

project(struct_test)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")
set( CMAKE_VERBOSE_MAKEFILE on )
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# set(DEPENDENT_LIBRARIES  Dependent libraries)

set(CMAKE_CXX_FLAGS "-fPIC -gdwarf-2 -pthread -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

string(TOUPPER CMAKE_BUILD_TYPE BUILD_TYPE)
message(STATUS "CXX_FLAGS = " CMAKE_CXX_FLAGS " " ${CMAKE_CXX_FLAGS_BUILD_TYPE})

# include_directories(CMAKE_SOURCE_DIR/include)

# link_directories(CMAKE_SOURCE_DIR/lib/)

add_executable(${PROJECT_NAME} entry.cpp)
# add_executable(PROJECT_NAMEBUILD_TYPE_POSTFIX SRCS UTILS)
# target_link_libraries(PROJECT_NAMEBUILD_TYPE_POSTFIX DEPENDENT_LIBRARIES)