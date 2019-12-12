cmake_minimum_required(VERSION 3.15)

add_executable(bm benchmark.cpp)

#add_library(bellman-ford-lib bellman-ford.cpp)
#
#add_library(generator-lib generator.cpp)

target_link_libraries(bm bellman-ford-lib generator-lib benchmark)