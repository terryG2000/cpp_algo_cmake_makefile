//
// Created by terry on 24-3-7.
//
#ifndef AVL_TREE_AVLTREE_H
#define AVL_TREE_AVLTREE_H

#include <BinaryTree.h>

class AvlTree {
public:
    BinaryTree* root;
    BinaryTree* left_rotate(BinaryTree *root);
    BinaryTree* right_rotate(BinaryTree *root);

    BinaryTree* insert_node(BinaryTree *node, int key);
    BinaryTree* del_node(BinaryTree *node, int key);

    void insert(int key);
    void del(int key);

    int get_balance(BinaryTree *node);
    int max(int a, int b);
    AvlTree() : root(nullptr) {};
};

#endif //AVL_TREE_AVLTREE_H
