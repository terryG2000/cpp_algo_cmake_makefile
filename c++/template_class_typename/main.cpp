//
// Created by terry on 24-3-8.
//
#include <iostream>
template <typename T>
class MyClass {
public:
    using NestedType = int; // 嵌套类型，依赖于模板参数T

    void function() {
        NestedType vec; // 使用嵌套类型
    }
};

template <typename T>
void myFunction() {
    typename MyClass<T>::NestedType myVar; // 明确指出NestedType是一个类型
}

int main(int argc,const char** argv){


    return 0;
}