//
// Created by terry on 24-3-14.
//

#include <iostream>
#include <queue>
#include <functional>
#include <vector>
#include <climits> // For INT_MAX
#include <algorithm>

//并查集
#define SET_MXA_NUM 100
int set[SET_MXA_NUM];

int find_path_compress(int element){// 带路径压缩
    if(element == set[element])
        return element;
    else{
        set[element] = find_path_compress(set[element]);
        //将父节点 执行 已经 找到的祖先节点
        return set[element];
    }
}

//  将b并到a上
void union_set(int a,int b){
    int a_ancestor = find_path_compress(a);
    int b_ancestor = find_path_compress(b);
    set[b_ancestor] = a_ancestor; // 将b祖先 在父节点执行 a的祖先上
}

bool is_related(int a, int b){
    if(find_path_compress(a) == find_path_compress(b)){
        return true;
//        std::cout << a << " - "<< b << std::endl;
//        std::cout << "is related "<< std::endl;
    }
    else{
        return false;
//        std::cout << a << " - "<< b << std::endl;
//        std::cout << "NOT related "<< std::endl;
    }
}
// 并查集 结束


template <typename _tp>
struct compare_elem{
     bool operator()(_tp& a, _tp& b){
         return a[2] > b[2];
     }
};
// 定义了一个比较器  重载了operator() 见对象的（）操作作为比较操作


std::vector< std::vector<int> > connect_weight_array; //邻接表

std::vector< std::vector<int> > result;
#define NODE_NUM 8

struct sort_compare{
    bool operator()(std::vector<int> a, std::vector<int> b) {
        return a[2] < b[2]; // 升序排序
    }//
};


void sort_elements(){
    std::sort(connect_weight_array.begin(), connect_weight_array.end(), sort_compare());
    std::cout << "sort weight array" << std::endl;
    for(auto i : connect_weight_array){
        std::cout << "Edge included in MST: " << i[0] << " - " << i[1] \
            << " : Weight = " << i[2] << "   is used: " << i[3]<< std::endl;
    }
    std::cout << "-----------------------------" << std::endl;
}

int main(int argc, const char** argv){
    for(int i=0; i<SET_MXA_NUM; i++){
        set[i] = i;
    }

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
    sort_elements();

    int edge_cnt = 0;
    int array_head_index = 0, line_vertex1, line_vertex2;
    while(edge_cnt != NODE_NUM-1 ){
        // 将权重最小的线段取出
        line_vertex1 = connect_weight_array[array_head_index][0];
        line_vertex2 = connect_weight_array[array_head_index][1];
        if(is_related(line_vertex1, line_vertex2)){// 如果添加线段后出现 环路说明不是mst中
            array_head_index++;// 将最小指向下一个
            continue;// 跳到循环开始
        }
        union_set(line_vertex1, line_vertex2); // 将 端点合并到一个集合中
        edge_cnt++;
        std::cout << "Edge included in MST: " << connect_weight_array[array_head_index][0] << " - " << connect_weight_array[array_head_index][1] \
            << " : Weight = " << connect_weight_array[array_head_index][2] << "   is used: " << connect_weight_array[array_head_index][3] << std::endl;
    }


    return 0;
}
