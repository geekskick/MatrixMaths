enable_testing()

add_executable(matrix_test test.cpp)
target_link_libraries(matrix_test LINK_PUBLIC matrix)
add_test(NAME matrix_test COMMAND foobar)
