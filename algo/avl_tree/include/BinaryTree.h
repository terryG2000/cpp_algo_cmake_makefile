//
// Created by terry on 24-3-7.
//

#ifndef AVL_TREE_BINARYTREE_H
#define AVL_TREE_BINARYTREE_H


class BinaryTree {
public:
    int key;
    BinaryTree *left_node;
    BinaryTree *right_node;
    int hight;

    int get_hight(void);
    static void mid_order_print(BinaryTree *root);
    static void pre_order_print(BinaryTree *root);
    static BinaryTree* search(BinaryTree* root, int key);

    BinaryTree() : hight(1), key(0), left_node(nullptr), right_node(nullptr) {};
    explicit BinaryTree(int key) : hight(1), key(key), left_node(nullptr), right_node(nullptr) {};

};


#endif //AVL_TREE_BINARYTREE_H
