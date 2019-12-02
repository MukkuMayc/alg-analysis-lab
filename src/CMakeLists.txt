cmake_minimum_required(VERSION 3.15)
project(bellman-ford)

add_executable(bellman-ford main.cpp)

add_library(bellman-ford-lib bellman-ford.cpp)