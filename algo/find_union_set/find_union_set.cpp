//
// Created by terry on 24-3-13.
//

#include <iostream>

#define SET_MXA_NUM 100
int set[SET_MXA_NUM];

int find(int element){// 不带路径压缩
    if(element == set[element])
        return element;
    else
        return find(set[element]);
}

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

void is_related(int a, int b){
    if(find(a) == find(b)){
        std::cout << a << " - "<< b << std::endl;
        std::cout << "is related "<< std::endl;
    }
    else{
        std::cout << a << " - "<< b << std::endl;
        std::cout << "NOT related "<< std::endl;
    }
}
int main(int argc, const char** argv){
    for (int i = 0; i < SET_MXA_NUM; i++){
        set[i] = i;
    }
    union_set(2, 4);
    union_set(5, 7);
    union_set(1, 3);
    union_set(8, 9);
    union_set(1, 2);
    union_set(5, 6);
    union_set(2, 3);
    is_related(3 , 4);
    is_related(7 , 10);
    is_related(8 , 9);

    return 0;
}