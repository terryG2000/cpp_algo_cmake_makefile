cmake_minimum_required(VERSION 3.20)
project(AVL_TREE LANGUAGES CXX VERSION 0.1)

set(CMAKE_CXX_STANDARD  11)
set(CMAKE_CXX_STANDARD_REQUIRED  True)

add_subdirectory(./src)

add_executable(avltree main.cpp)
target_link_libraries(avltree PUBLIC src_obj)
