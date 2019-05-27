cmake_minimum_required(VERSION 2.6)
 

set (CMAKE_CXX_STANDARD 11)
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(task task.cpp Rover.hpp Rover.cpp)
target_link_libraries(task ${GTEST_LIBRARIES} pthread)