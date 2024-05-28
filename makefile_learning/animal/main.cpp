//
// Created by terry on 24-3-5.
//

#include <iostream>
#include "dog.h"
#include "cat.h"

int main(int argc, char** argv){
    cat cat;
    std::cout << cat.barking() << std::endl;
    dog dog;
    std::cout << dog.barking() << std::endl;
    return 0;
}
