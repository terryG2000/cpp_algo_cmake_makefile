//
// Created by terry on 24-3-5.
//

#include <iostream>
#include "dog.h"
#include "cat.h"
#include "config.h"

int main(int argc, char** argv){
    cat cat;
    std::cout << cat.barking() << std::endl;
    dog dog;
    std::cout << dog.barking() << std::endl;
    std::cout << CMAKE_CXX_STANDARD << std::endl;
    return 0;
}
