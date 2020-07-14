cmake_minimum_required(VERSION 3.15)
project(w1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")

add_executable(w1 main.cpp)