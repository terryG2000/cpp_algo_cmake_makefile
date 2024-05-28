option(USE_CAT2 "Use cat2" OFF)
# 创建一个条件编译变量 第二个参数是说明 第三个是 默认值 ON/OFF
if(USE_CAT2)# 如果为ON
    set(src cat.cpp dog.cpp cat2.cpp)
else()
    set(src cat.cpp dog.cpp)
endif ()

add_library(AnimalLib OBJECT  ${src})
target_include_directories(AnimalLib PUBLIC .)
# 将当前文件夹加入AnimalLib 的头文件路径中

if(USE_CAT2)
    target_compile_definitions(AnimalLib PRIVATE "USE_CAT2")
    #它相当于在编译AnimalLib时，为其源代码添加了#define USE_CAT2。
endif ()

