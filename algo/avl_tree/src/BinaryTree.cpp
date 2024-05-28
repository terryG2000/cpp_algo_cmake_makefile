//
// Created by terry on 24-3-7.
//

#include "BinaryTree.h"
#include <iostream>


int BinaryTree::get_hight(void) {
    if(this == nullptr) return 0;
    return this->hight;
}

void BinaryTree::mid_order_print(BinaryTree *root) {
    if(root == nullptr)
            return;
    mid_order_print(root->left_node);
    std::cout << root->key << " - ";
    mid_order_print(root->right_node);
}


void BinaryTree::pre_order_print(BinaryTree *root){
    if(root == nullptr)
        return;
    std::cout << root->key << " - ";
    mid_order_print(root->left_node);
    mid_order_print(root->right_node);
}

BinaryTree *BinaryTree::search(BinaryTree* root, int key) {
    if(root == nullptr)
        return nullptr;
    if (key < root->key){
        return search(root->left_node, key);
    }
    else if(key > root->key){
        return search(root->right_node, key);
    }
    else
        return root;
}


