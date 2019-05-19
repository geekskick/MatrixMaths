cmake_minimum_required(VERSION 3.14)
project(MatrixMaths)

add_subdirectory(src)

find_package(Catch2 REQUIRED)
include(CTest)
add_subdirectory(test)

add_executable(MatrixMaths main.cpp)
target_link_libraries(MatrixMaths matrix)
