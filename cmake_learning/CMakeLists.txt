cmake_minimum_required(VERSION  3.20.0)
project(cmake_test)

set(CMAKE_CXX_STANDARD  11)
set(CMAKE_CXX_STANDARD_REQUIRED  True)
configure_file(config.h.in config.h)
# 第一个参数模板文件 第二个是在构建二进制目录中生成的文件名
#include_directories(${PROJECT_BINARY_DIR})
## 将构建没目录添加到头文件路径中 在这之后的所有目标都会包含


add_subdirectory(animal)
# 添加子文件 并查找执行 cmaklists
add_executable(cmake_learn_app main.cpp)
target_include_directories(cmake_learn_app PUBLIC ${PROJECT_BINARY_DIR})
target_link_libraries(cmake_learn_app PUBLIC AnimalLib)
# 将库连接到可执行文件



