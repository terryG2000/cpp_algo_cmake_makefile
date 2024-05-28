//
// Created by terry on 24-3-7.
//
#include <iostream>
#include "AvlTree.h"

int main(int argc, char** argv){
    AvlTree avl;
    avl.insert(1);
    avl.insert(2);
    avl.insert(3);
    avl.insert(4);
    avl.insert(5);
    avl.insert(6);

    BinaryTree::mid_order_print(avl.root);
    std::cout << "------------------------" << std::endl;
    BinaryTree::pre_order_print(avl.root);
    std::cout << "------------------------" << std::endl;


    BinaryTree::mid_order_print(BinaryTree::search(avl.root, 2));
    std::cout << "------------------------" << std::endl;
    BinaryTree::mid_order_print(BinaryTree::search(avl.root, 100));
    std::cout << "------------------------" << std::endl;
    BinaryTree::mid_order_print(BinaryTree::search(avl.root, 5));
    std::cout << "------------------------" << std::endl;

    std::cout << "del node 2" << std::endl;
    avl.del(2);
    BinaryTree::mid_order_print(BinaryTree::search(avl.root, 1));

    std::cout << std::endl;

    BinaryTree::mid_order_print(avl.root);
    std::cout << "------------------------" << std::endl;
    BinaryTree::pre_order_print(avl.root);
    std::cout << "------------------------" << std::endl;
    return  0;
}