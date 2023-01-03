cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Node.cpp Node.h LDFS.h LDFS.cpp RBFS.cpp RBFS.h LDFS.test.cpp RBFS.test.cpp)
