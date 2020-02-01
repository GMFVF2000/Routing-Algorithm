cmake_minimum_required(VERSION 3.13)
project(RoutingAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(RoutingAlgorithm main.cpp Matrix.cpp Matrix.h Algorithm.cpp Algorithm.h DFSGraph.cpp DFSGraph.h)