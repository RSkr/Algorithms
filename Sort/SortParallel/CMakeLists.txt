cmake_minimum_required(VERSION 3.15)
project(SortParallel)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

add_executable(SortParallel main.cpp)