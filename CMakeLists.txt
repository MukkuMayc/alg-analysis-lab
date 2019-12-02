cmake_minimum_required(VERSION 3.15)
project(algorithm-analysis)

add_subdirectory(src)
include_directories(src)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    include(GoogleTest)
    add_subdirectory(tests)
endif()
