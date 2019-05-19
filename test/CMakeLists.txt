add_executable(matrix_test test.cpp)
target_link_libraries(matrix_test matrix Catch2::Catch2)

include(Catch)
catch_discover_tests(matrix_test)
