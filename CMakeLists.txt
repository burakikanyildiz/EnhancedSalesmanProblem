cmake_minimum_required(VERSION 2.8.12.2)
project(project3_burak_yildiz_2015400069)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCE_FILES main.cpp WeightedGraph.cpp WeightedGraph.h Road.cpp Road.h)
add_executable(project3 ${SOURCE_FILES})