cmake_minimum_required(VERSION 3.19)
project(cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp main.cc SparseGraph.h DenseGraph.h GraphReader.h PathSearcher.h)