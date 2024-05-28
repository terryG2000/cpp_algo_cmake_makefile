//
// Created by terry on 24-3-5.
//

#include "cat.h"
#ifdef USE_CAT2
#include <iostream>
    #include "cat2.h"
#endif

std::string cat::barking(){
#ifdef USE_CAT2
    std::cout << cat2::barking() << std::endl;
#endif
    return "cat barking";
}
