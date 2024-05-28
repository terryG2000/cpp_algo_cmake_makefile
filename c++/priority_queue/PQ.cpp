//
// Created by terry on 24-3-14.
//

#include <iostream>
#include <queue>
#include <functional>
#include <vector>

template <typename _tp>
struct compare_elem{
     bool operator()(_tp& a, _tp& b){
         return a[1] > b[1];
     }
};
// 定义了一个比较器  重载了operator() 见对象的（）操作作为比较操作

int main(int argc, const char** argv){
    // 定义优先队列
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, compare_elem<std::vector<int>>> pq;

    // 添加元素
    pq.push(std::vector<int>({1, 20}));
    pq.push({2, 15});
    pq.push({3, 30});

    // 打印并删除顶部元素
    while (!pq.empty()) {
        std::vector<int> top = pq.top(); // 获取顶部元素
        pq.pop(); // 删除顶部元素
        std::cout << "Popped element: [" << top[0] << ", " << top[1] << "]" << std::endl;
    }

    return 0;
}
