//
// Created by terry on 24-3-9.
//
#include <iostream>
#include <vector>

void bubble_sort(std::vector<int>& array){
    int tmp;
    for(int i=0; i<array.size(); i++){
        for(int j=i; j<array.size(); j++){
            if(array[j] < array[i]){
                tmp = array[j];
                array[j] = array[i];
                array[i] = tmp;
            }
        }
    }
}

int main(int argv,const char **argc){
    std::vector<int> array;
    array.push_back(23);
    array.push_back(112);
    array.push_back(132);
    array.push_back(12);
    array.push_back(1423);
    array.push_back(-1);
    bubble_sort(array);
    for(int i : array){
        std::cout << i << std::endl;
    }

    return 0;
}