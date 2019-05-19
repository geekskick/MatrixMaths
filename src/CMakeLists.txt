add_library(matrix INTERFACE) 

target_compile_features(matrix INTERFACE cxx_range_for cxx_auto_type)
target_include_directories(matrix INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
