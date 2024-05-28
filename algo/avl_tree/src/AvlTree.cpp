//
// Created by terry on 24-3-7.
//

#include "../include/AvlTree.h"
#include <iostream>


BinaryTree* AvlTree::left_rotate(BinaryTree *root){
//    1、新的根节点 = 根节点右节点
//    2、新根节点的左子节点 = 根节点
//    3、根节点的右节点 = 新根节点的左节点

    BinaryTree *newroot = root->right_node;
    BinaryTree *tmp = newroot->left_node;

    newroot->left_node = root;
    root->right_node = tmp;

    root->hight = max(root->left_node->get_hight(), root->right_node->get_hight()) + 1;
    newroot->hight = max(newroot->left_node->get_hight(), newroot->right_node->get_hight()) + 1;

    return newroot;
}

BinaryTree* AvlTree::right_rotate(BinaryTree *root){
//    1、新的根节点 = 根节点左节点
//    2、新根节点的右子节点 = 根节点
//    3、根节点的左节点 = 新根节点的右节点

    BinaryTree *newroot = root->left_node;
    BinaryTree *tmp = newroot->right_node;

    newroot->right_node = root;
    root->left_node = tmp;

    root->hight = max(root->left_node->get_hight(), root->right_node->get_hight()) + 1;
    newroot->hight = max(newroot->left_node->get_hight(), newroot->right_node->get_hight()) + 1;

    return newroot;
}

int AvlTree::max(int a, int b) {
    return a>b ? a:b;
}
/**
 *
 * @param root 被插入树的根节点
 * @param val  插入的值
 * @return 插入完成的 根节点
 */
BinaryTree *AvlTree::insert_node(BinaryTree *node, int key) {
    if(node == nullptr)
        return new BinaryTree(key);
        //找到了插入位置

    if(key < node->key){
        node->left_node = insert_node(node->left_node, key);
    }
    else if(key > node->key){
        node->right_node = insert_node(node->right_node, key);
    }
    else
        return node;//已存在相同元素 不需要操作直接返回

    //更新树高
    node->hight = 1 + max(node->left_node->get_hight(), node->right_node->get_hight());
    // 获取平衡因子
    int balance = get_balance(node);

    //根据平衡因子判断 失衡情况来均衡节点
    //LL
    if (balance > 1 && get_balance(node->left_node) > 0){
        return right_rotate(node);
    }
    //LR
    if (balance > 1 && get_balance(node->left_node) < 0){
        node->left_node = left_rotate(node->left_node);
        return right_rotate(node);
    }

    //RR
    if (balance < -1 && get_balance(node->right_node) < 0){
        return left_rotate(node);
    }
    //RL
    if (balance <- 1 && get_balance(node->right_node) > 0){
        node->right_node = right_rotate(node->right_node);
        return left_rotate(node);
    }

    return node;// 没有失衡 直接返回
}

int AvlTree::get_balance(BinaryTree *node) {
    return node->left_node->get_hight() - node->right_node->get_hight();
}

void AvlTree::insert(int key) {
    this->root = insert_node(this->root, key);
}

BinaryTree *AvlTree::del_node(BinaryTree *node, int key) {
    if(node == nullptr)
        return nullptr;

    if(key < node->key){
        node->left_node = del_node(node->left_node, key);
    }
    else if(key > node->key){
        node->right_node = del_node(node->right_node, key);
    }
    else{// 找到了节点 开始删除操作
        if( (node->left_node == nullptr) || (node->right_node == nullptr) )
        {
            BinaryTree *tmp = (node->left_node != nullptr) ? node->left_node : node->right_node;

            delete node;//删除节点
            if(tmp != nullptr){ //存在一个子节点时
                node = tmp;
            }
            else{ // 没有子节点 将node 设为空
                node = nullptr;
            }
        }
        else{
            // 使用前驱值 来替换当前节点值
            node->key = node->left_node->key;
            //删除前驱节点
            node->left_node = del_node(node->left_node, node->key);
        }
    }

    if(node == nullptr)
        return nullptr; // 节点删除完成直接返回
    //更新树高
    node->hight = 1 + max(node->left_node->get_hight(), node->right_node->get_hight());
    // 获取平衡因子
    int balance = get_balance(node);

    //LL
    if (balance > 1 && get_balance(node->left_node) > 0){
        return right_rotate(node);
    }
    //LR
    if (balance > 1 && get_balance(node->left_node) < 0){
        node->left_node = left_rotate(node->left_node);
        return right_rotate(node);
    }

    //RR
    if (balance < -1 && get_balance(node->right_node) < 0){
        return left_rotate(node);
    }
    //RL
    if (balance <- 1 && get_balance(node->right_node) > 0){
        node->right_node = right_rotate(node->right_node);
        return left_rotate(node);
    }

    return node;// 没有失衡 直接返回
}

void AvlTree::del(int key) {
    this->root = del_node(this->root, key);
}

