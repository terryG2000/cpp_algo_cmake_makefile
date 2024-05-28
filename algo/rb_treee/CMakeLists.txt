cmake_minimum_required(VERSION 3.20)
project(rb_tree CXX)

set(CMAKE_CXX_STANDARD_REQUIRED  True)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(./src)

add_executable(rb_tree main.cpp)
target_link_libraries(rb_tree PUBLIC RBTree_lib)
