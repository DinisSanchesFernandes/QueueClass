cmake_minimum_required(VERSION 3.10)
project(runTests)

find_package(GTest REQUIRED)

include_directories(${GTES_INCLUDE_DIRS})

add_executable(runTests main.cpp ../Queue.h)
target_link_libraries(runTests ${GTEST_LIBRARIES})