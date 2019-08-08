cmake_minimum_required(VERSION 3.14)
project(double_dispatch)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGET_NAME double_dispatch)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g -DDEBUG")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -DRELEASE")
endif()

set(PROJECT_CMAKE_IN ${double_dispatch_SOURCE_DIR}/cmake/in)
set(PROJECT_DEPS_DIR ${double_dispatch_SOURCE_DIR}/deps)
set(PROJECT_SRC_DIR ${double_dispatch_SOURCE_DIR}/src)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

set(THREADS_PREFER_PTHREAD_FLAG ON)
include(FindThreads)

#
# Testing
#
set(BUILD_TESTING OFF)
set(GOOGLETEST_DEPS_DIR ${PROJECT_DEPS_DIR}/googletest)

configure_file(${PROJECT_CMAKE_IN}/deps.in ${PROJECT_DEPS_DIR}/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${PROJECT_DEPS_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${PROJECT_DEPS_DIR})

# gtest, gtest_main, gmock and gmock_main targets are available from now on
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${GOOGLETEST_DEPS_DIR})

set(BUILD_TESTING ON)
enable_testing()

add_subdirectory(test)
