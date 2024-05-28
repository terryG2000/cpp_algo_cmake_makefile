//
// Created by terry on 24-3-9.
//


#include <iostream>
#include "RBTree.h"
#include <string>


int main(int argc, char** argv){
    RBTree<int> root;
    RBNode<int> *res_node;

    root.insert(9);
    root.insert(10);
    root.insert(11);
    root.insert(20);
    root.insert(30);
    root.insert(40);
    root.insert(123);
    root.insert(1234);
    std::cout << "main " << std::endl;
    res_node = root.find(123);
    if(res_node != nullptr)
        std::cout << "find 1 " << std::endl;

    std::cout << "find maximum " << root.get_maximum(root.root)->key << std::endl;
    std::cout << "find minimum " << root.get_minimum(root.root)->key << std::endl;
    root.mid_print();

    std::cout << "del 20 ----------------" << std::endl;
    root.del_node_by_key(20);
    root.mid_print();
    std::cout << "----------------------------" << std::endl;

    std::cout << "del 30 ----------------" << std::endl;
    root.del_node_by_key(30);
    root.mid_print();
    std::cout << "----------------------------" << std::endl;

    std::cout << "del 10 ----------------" << std::endl;
    root.del_node_by_key(10);
    root.mid_print();
    std::cout << "----------------------------" << std::endl;

    std::cout << "del 123 ----------------" << std::endl;
    root.del_node_by_key(123);
    root.mid_print();
    std::cout << "----------------------------" << std::endl;

    std::cout << "del 11 ----------------" << std::endl;
    root.del_node_by_key(11);
    root.mid_print();
    std::cout << "----------------------------" << std::endl;

    std::cout << "del 40 ----------------" << std::endl;
    root.del_node_by_key(40);
    root.mid_print();
    std::cout << "----------------------------" << std::endl;

    std::cout << "del 9 ----------------" << std::endl;
    root.del_node_by_key(9);
    root.mid_print();
    std::cout << "----------------------------" << std::endl;


    std::cout << "del 1234 ----------------" << std::endl;
    root.del_node_by_key(1234);
    root.mid_print();
    std::cout << "----------------------------" << std::endl;
    return 0;
}