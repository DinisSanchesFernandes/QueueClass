project(QueueClass)
cmake_minimum_required(VERSION 3.10)

SET(TARGET_H
    Queue.h
)

SET(TARGET_SRC
    main.cpp
)

set(CMAKE_CXX_STANDARD 11)

add_executable(QueueClass ${TARGET_SRC})