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
         return a[2] > b[2];
     }
};
// 定义了一个比较器  重载了operator() 见对象的（）操作作为比较操作

std::vector< std::vector<int> > connect_weight_array; //邻接表
std::vector< std::vector<int> > result;
std::vector<bool> visited;
#define NODE_NUM 8

int main(int argc, const char** argv){
    // 定义优先队列
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, compare_elem<std::vector<int>>> pq;

    visited.assign(NODE_NUM, false);

    connect_weight_array.push_back(std::vector<int>({0, 7, 16, 0}));
    connect_weight_array.push_back(std::vector<int>({2, 3, 17, 0}));
    connect_weight_array.push_back(std::vector<int>({1, 7, 19, 0}));
    connect_weight_array.push_back(std::vector<int>({0, 2, 26, 0}));
    connect_weight_array.push_back(std::vector<int>({5, 7, 28, 0}));
    connect_weight_array.push_back(std::vector<int>({1, 3, 29, 0}));
    connect_weight_array.push_back(std::vector<int>({1, 5, 32, 0}));
    connect_weight_array.push_back(std::vector<int>({2, 7, 34, 0}));
    connect_weight_array.push_back(std::vector<int>({4, 5, 35, 0}));
    connect_weight_array.push_back(std::vector<int>({1, 2, 36, 0}));
    connect_weight_array.push_back(std::vector<int>({4, 7, 37, 0}));
    connect_weight_array.push_back(std::vector<int>({0, 4, 38, 0}));
    connect_weight_array.push_back(std::vector<int>({6, 2, 40, 0}));
    connect_weight_array.push_back(std::vector<int>({3, 6, 52, 0}));
    connect_weight_array.push_back(std::vector<int>({6, 0, 58, 0}));
    connect_weight_array.push_back(std::vector<int>({6, 4, 93, 0}));

    // 添加元素

    int edge_cnt = 0, i = 0;
    visited[i] = true;
    while (edge_cnt != NODE_NUM-1){
        for(int k=connect_weight_array.size() - 1; k >= 0; k-- ){
            if((connect_weight_array[k][0] == i ||  connect_weight_array[k][1] == i )\
                && connect_weight_array[k][3] == 0){ // 边的任意一个顶点属于新顶点
                connect_weight_array[k][3] = 1; // 标记为已加入队列
                pq.push(connect_weight_array[k]);
            }
        }


        while(1){
            if(visited[pq.top()[0]] == true && visited[pq.top()[1]] == true ){
                //树内部的边 失效的 需要删除
                pq.pop();
            }
            else
                break;
        }
        i = (  visited[pq.top()[0]] == false ) ? pq.top()[0] : pq.top()[1];// 取出新加入的顶点
        result.push_back(pq.top());
        visited[pq.top()[0]] = true;
        visited[pq.top()[1]] = true;
        edge_cnt++;
        std::cout << "Edge included in MST: " << pq.top()[0] << " - " << pq.top()[1] \
            << " : Weight = " << pq.top()[2] << "   is used: " << pq.top()[3]<< std::endl;
        pq.pop();
    }
    return 0;
}
