//
// Created by terry on 24-3-9.
//
#include <iostream>
#include <vector>
#include <cstdlib> // for rand()

void swap(int& a, int& b){
    int tmp; // 用于交换
    tmp = a;
    a = b;
    b = tmp;
}

void quick_sort(int* array, int left, int right){
    int pivot = left; // 枢纽 位置不动，除非和另一个位置交换
    int scaner = right;

    if((right - left) + 1 <= 1) return; // 如果数组大小小于等于1 直接返回不用排序
    // pivot 左边小于pivot位置处值  pivot 右边大于pivot位置处值
    while(pivot != scaner){
        if( (array[scaner] > array[pivot] &&  scaner<pivot ) || \
            (array[scaner] < array[pivot] &&  scaner>pivot )){
            /*如果scaner 在 pivot 左侧 且 scaner处的值大于pivot处的值 或
            如果scaner 在 pivot 右侧 且 scaner处的值小于pivot处的值*/
            swap(array[scaner], array[pivot]); // 交换数组值
            swap(scaner, pivot); // 交换scaner 和 pivot 值
        }
        if(scaner > pivot) scaner--;
        else  scaner++;
        // scnaer 始终要往pivot 靠
    }
    quick_sort(array, left, pivot - 1);//对 pivot 左侧进行排序
   quick_sort(array, pivot + 1, right);//对 pivot 右侧进行排序

}

#define  ARRAY_SIZE 10
int main(int argv,const char **argc){
    int* array =new int[ARRAY_SIZE];
    for(int i=0; i<ARRAY_SIZE; i++){
        array[i] = std::rand();
    }
    quick_sort(array, 0, ARRAY_SIZE - 1);
    for(int i=0; i<ARRAY_SIZE; i++){
        std::cout << array[i] << std::endl;
    }

    return 0;
}



