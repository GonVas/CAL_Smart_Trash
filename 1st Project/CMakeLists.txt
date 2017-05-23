cmake_minimum_required(VERSION 3.6)
project(untitled2)

set(CMAKE_CXX_STANDARD 11)

#SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_COMPILER             "/usr/bin/g++")
SET (CMAKE_CXX_FLAGS                " -o3 -pthread ")
set(SOURCE_FILES main.cpp src/Graph/PriQueue.hpp src/Graph/Test.cpp src/Graph/DisjointSet.hpp)
add_executable(untitled2 ${SOURCE_FILES})