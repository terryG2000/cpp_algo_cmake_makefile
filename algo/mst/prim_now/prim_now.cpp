//
// Created by terry on 24-3-14.
//

#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <climits> // For INT_MAX

template <typename _tp>
struct compare_elem{
     bool operator()(_tp& a, _tp& b){
         return a[2] > b[2];
     }
};
// 定义了一个比较器  重载了operator() 见对象的（）操作作为比较操作

std::vector< std::vector<int> > connect_weight_array; //邻接表
std::vector< std::vector<int> > result;
std::vector<int > weight_array;
std::vector<int > visited;
std::vector< std::vector<int> > tmp_res;
#define NODE_NUM 8
// Function to find the index of the row with the minimum second element
int findMinSecondElementRow(const std::vector<std::vector<int>>& matrix) {
    int minIndex = -1;
    int minValue = INT_MAX;

    for (int i = 0; i < matrix.size(); ++i) {
        if (matrix[i].size() > 1 && matrix[i][2] < minValue) {
            minValue = matrix[i][2];
            minIndex = i;
        }
    }

    return minIndex;
}

int main(int argc, const char** argv){
    // 定义优先队列
    std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, compare_elem<std::vector<int>>> pq;

    weight_array.assign(NODE_NUM, INT_MAX); //  初始化为最大值
    visited.assign(NODE_NUM, false);
    tmp_res.assign(NODE_NUM, {INT_MAX, INT_MAX, INT_MAX, INT_MAX}); //  初始化为最大值
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
    int node_id = 5, other_node_id = 0, edge_cnt = 0;
    weight_array[node_id] = INT_MIN;
    visited[node_id] = true;
    //添加第一个顶点到树中
    do{
        for(int k=connect_weight_array.size() - 1; k >= 0; k-- ){
            if(connect_weight_array[k][0] == node_id ||  connect_weight_array[k][1] == node_id ){
                // 是顶点的邻接边
                other_node_id = (connect_weight_array[k][0] != node_id) ? connect_weight_array[k][0] : connect_weight_array[k][1];
                if(weight_array[other_node_id] > connect_weight_array[k][2]){
                    // 更新权重数组 和 PQ
                    weight_array[other_node_id] = connect_weight_array[k][2];
                    connect_weight_array[k][3] = other_node_id; // 新节点的id
                    tmp_res[other_node_id] = connect_weight_array[k];
//                    pq.push(connect_weight_array[k]);
                }
            }
        }
        node_id = tmp_res[findMinSecondElementRow(tmp_res)][3];
        weight_array[node_id] = INT_MIN;
//        result.push_back(pq.top()); // 使用优先队列时无法 根性元素的权重  所以改用数组
        result.push_back(tmp_res[findMinSecondElementRow(tmp_res)]);
        edge_cnt++;

//        std::cout << "Edge included in MST: " << pq.top()[0] << " - " << pq.top()[1] \
//            << " : Weight = " << pq.top()[2] << "   is used: " << pq.top()[3]<< std::endl;
        std::cout << "Edge included in MST: " << tmp_res[findMinSecondElementRow(tmp_res)][0] << " - " << tmp_res[findMinSecondElementRow(tmp_res)][1] \
            << " : Weight = " << tmp_res[findMinSecondElementRow(tmp_res)][2] << "   is used: " << tmp_res[findMinSecondElementRow(tmp_res)][3]<< std::endl;
//        pq.pop();
        tmp_res[findMinSecondElementRow(tmp_res)] = std::vector<int>({INT_MAX, INT_MAX, INT_MAX, INT_MAX});
    } while(/*!pq.empty() &&*/ edge_cnt!=NODE_NUM-1);

    return 0;
}
