cmake_minimum_required(VERSION 3.0)
project(MatrixMaths)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(test)

add_executable(MatrixMaths main.cpp)
target_link_libraries(MatrixMaths LINK_PUBLIC matrix)