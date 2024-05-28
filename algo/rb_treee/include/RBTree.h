//
// Created by terry on 24-3-9.
//

#ifndef KEY_VALUE_RBTREE_H
#define KEY_VALUE_RBTREE_H
#include <cstdint>
#include <iostream>

enum class RBNodeColor {
    RED,
    BLACK
};

template <typename  key_type>
class RBNode{
public:
    RBNodeColor color;
    key_type key;

    RBNode<key_type> *left_node;
    RBNode<key_type> *right_node;
    RBNode<key_type> *father_node;

    explicit RBNode(RBNodeColor color = RBNodeColor::RED, key_type key = 0, RBNode<key_type> *father = nullptr,  \
        RBNode<key_type> *left = nullptr,  RBNode<key_type> *right = nullptr) : \
        color(color), key(key), father_node(father), left_node(left), right_node(right){};
};

template <typename  key_type>
class RBTree {
public:
    RBTree();
    RBNode<key_type> *root;
    RBNode<key_type> *nill;
    RBNode<key_type> *find(key_type key);
    void insert(key_type key);
    void pre_print();
    void mid_print();
    RBNode<key_type> *get_minimum(RBNode<key_type> *node);
    RBNode<key_type> *get_maximum(RBNode<key_type> *node);


    void del_node_by_key(key_type key);
    void del_node_by_node(RBNode<key_type> *node);
    uint8_t is_node_empty(RBNode<key_type> *node);
private:
    void insert_node(RBNode<key_type> *node, key_type key);
    void insert_fix_tree(RBNode<key_type> *node);
    void pre_order_print(RBNode<key_type> *node);
    void mid_order_print(RBNode<key_type> *node);
    RBNodeColor get_node_color(RBNode<key_type> *node);

    RBNode<key_type> *find_node(RBNode<key_type> *node, key_type key);

    RBNodeColor *get_bro_node_color(RBNode<key_type> *node);
    RBNodeColor *get_bro_node(RBNode<key_type> *node);
    void del_fix_tree(RBNode<key_type> *node);

    RBNode<key_type> *left_rotate(RBNode<key_type> *node);
    RBNode<key_type> *right_rotate(RBNode<key_type> *node);
    RBNode<key_type> **get_node_father_connect_side_pointer(RBNode<key_type> *node);

};

/**
 * 返回该节点在父节点上的连接点
 * @tparam key_type
 * @param node
 * @return  指向存储该节点指针的地址
 */
template<typename key_type>
RBNode<key_type> **RBTree<key_type>::get_node_father_connect_side_pointer(RBNode<key_type> *node) {
    if(is_node_empty(node->father_node)){
        //父节点是空节点 说明是该节点是根节点
        return &(this->root);
    }
    else if(node == node->father_node->left_node)
        return &(node->father_node->left_node);
    else if(node == node->father_node->right_node)
        return &(node->father_node->right_node);
}


template <typename  key_type>
RBTree<key_type>::RBTree(): root(nullptr){
    nill = new RBNode<key_type>(RBNodeColor::BLACK, 0);
    nill->father_node = nill;
    nill->left_node = nill;
    nill->right_node = nill;

    this->root = this->nill;
    this->root->father_node = this->nill;
}

template<typename key_type>
RBNodeColor RBTree<key_type>::get_node_color(RBNode<key_type> *node) {
    return (is_node_empty(node)) ? RBNodeColor::BLACK : \
                                ((node->color == RBNodeColor::RED) ? RBNodeColor::RED : RBNodeColor::BLACK);
}


template<typename key_type>
RBNode<key_type> *RBTree<key_type>::get_maximum(RBNode<key_type> *node) {
    while(!is_node_empty(node->right_node)){
        node = node->right_node;
    }
    return node;
}

template<typename key_type>
RBNode<key_type> *RBTree<key_type>::get_minimum(RBNode<key_type> *node) {
    while(!is_node_empty(node->left_node)){
        node = node->left_node;
    }
    return node;
}

template<typename key_type>
void RBTree<key_type>::mid_print() {
        this->mid_order_print(this->root);
}

template<typename key_type>
void RBTree<key_type>::pre_print() {
    this->pre_order_print(this->root);
}

template<typename key_type>
void RBTree<key_type>::insert(key_type key) {
    insert_node(this->root, key);
}

template<typename key_type>
RBNodeColor *RBTree<key_type>::get_bro_node(RBNode<key_type> *node) {
    return (node->father_node->left_node == node) ? (node->father_node->right_node) : \
                                                        (node->father_node->left_node);
}

template<typename key_type>
RBNodeColor *RBTree<key_type>::get_bro_node_color(RBNode<key_type> *node) {
    return (node->father_node->left_node == node) ? (node->father_node->right_node->color) : \
                                                        (node->father_node->left_node->color);
}

template<typename key_type>
RBNode<key_type> *RBTree<key_type>::find(key_type key) {
    return find_node(this->root, key);
}

template<typename key_type>
RBNode<key_type> *RBTree<key_type>::right_rotate(RBNode<key_type> *root) {
    //    1、新的根节点 = 根节点左节点
//    2、新根节点的右子节点 = 根节点
//    3、根节点的左节点 = 新根节点的右节点

    RBNode<key_type> *newroot = root->left_node;
    RBNode<key_type> *tmp = newroot->right_node;

    newroot->right_node = root;
    root->left_node = tmp;

    //修改各节点父节点指向
    newroot->father_node = root->father_node; //新根节点父节点变为旧根节点的父节点
    root->father_node = newroot; //  旧根的父节点变成新根节点
    if(!is_node_empty(tmp)) tmp->father_node = root; // 原新根节点的右节点的父节点 变为旧根

    return newroot;
}

template<typename key_type>
uint8_t RBTree<key_type>::is_node_empty(RBNode<key_type> *node){
    return ((node == this->nill) || (node == nullptr)) ? 1u:0u;
}

template<typename key_type>
RBNode<key_type> *RBTree<key_type>::left_rotate(RBNode<key_type> *root) {
    //    1、新的根节点 = 根节点右节点
    //    2、新根节点的左子节点 = 根节点
    //    3、根节点的右节点 = 新根节点的左节点

    RBNode<key_type> *newroot = root->right_node;
    RBNode<key_type> *tmp = newroot->left_node;

    newroot->left_node = root;
    root->right_node = tmp;

    //修改各节点父节点指向
    newroot->father_node = root->father_node; //新根节点父节点变为旧根节点的父节点
    root->father_node = newroot; //  旧根的父节点变成新根节点
    if(!is_node_empty(tmp)) tmp->father_node = root; // 原新根节点的左节点的父节点 变为旧根

    return newroot;
}

template<typename key_type>
void RBTree<key_type>::del_node_by_key(key_type key) {
    del_node_by_node(find_node(this->root, key));
}

template<typename key_type>
void RBTree<key_type>::del_node_by_node(RBNode<key_type> *node) {
    RBNode<key_type> *deleted_node;
    RBNode<key_type> *successor_node;
    if(is_node_empty(node)) return;
    if( (is_node_empty(node->left_node)) && (is_node_empty(node->right_node)) ){
        // 没有子节点
        deleted_node = node;
        //被删节点就是 传入的节点
    }
    else if( !(is_node_empty(node->left_node)) && (is_node_empty(node->right_node)) ){
        //如果被删节点只有一个非空子节点 那被删的的节点就是传入的节点
        deleted_node = node->left_node;
        node->key = deleted_node->key;
        // 用真正要被删除的节点值 替换传入的节点的节点值
    }
    else if( (is_node_empty(node->left_node)) && !(is_node_empty(node->right_node)) ){
        //如果被删节点只有一个非空子节点 那被删的的节点就是传入的节点
        deleted_node = node->right_node;
        node->key = deleted_node->key;
        // 用真正要被删除的节点值 替换传入的节点的节点值
    }
    else{
        //被删节点有两个子节点 找到左子树 最有侧节点 作为真正被删节点
        deleted_node = get_maximum(node->left_node);

        node->key = deleted_node->key;
        // 用真正要被删除的节点值 替换传入的节点的节点值
        if(!is_node_empty(deleted_node->left_node)){
            deleted_node->key = deleted_node->left_node->key;
            deleted_node = deleted_node->left_node;
        }
        else if(!is_node_empty(deleted_node->right_node)){
            deleted_node->key = deleted_node->right_node->key;
            deleted_node = deleted_node->right_node;
        }
    }
    //到这一步 deleted_node 一定是没有子树的节点

    // 找到 deleted_node 的后继 节点
    successor_node = this->nill;

    // 修改后继节点的连接
    if(is_node_empty(deleted_node->father_node)){
        // 被删节点是根节点
        this->root = this->nill;
    }
    else if(deleted_node == deleted_node->father_node->left_node){
        deleted_node->father_node->left_node = successor_node;
        successor_node->father_node = deleted_node->father_node; // 连接上
    }
    else if(deleted_node == deleted_node->father_node->right_node){
        deleted_node->father_node->right_node = successor_node;
        successor_node->father_node = deleted_node->father_node; // 连接上
    }

    //如果被删节点是黑色的 就需要调整  根节点不需要调整
    if(deleted_node->color == RBNodeColor::BLACK && deleted_node !=this->root){
        del_fix_tree(successor_node);
    }

    if(!is_node_empty(deleted_node->father_node) && deleted_node == deleted_node->father_node->left_node){
        deleted_node->father_node->left_node = this->nill;// 子节点恢复为空
    }
    else if(!is_node_empty(deleted_node->father_node) && deleted_node == deleted_node->father_node->right_node){
        deleted_node->father_node->right_node = this->nill;// 子节点恢复为空
    }
    successor_node->father_node = this->nill;

    delete deleted_node;
}


/**
 *
 * @tparam key_type
 * @param node  删除后节点的后继节点 也就是少一个黑节点的 子节点点
 */
template<typename key_type>
void RBTree<key_type>::del_fix_tree(RBNode<key_type> *node) {
    /*get_node_color(node) == RBNodeColor::BLACK*/
    while(1){
        if(node == this->root) break;
        if(node == node->father_node->left_node){ // 节点在左侧
            RBNode<key_type> *bro_node = node->father_node->right_node;
            if(get_node_color(bro_node) == RBNodeColor::RED){
                bro_node->father_node->color = RBNodeColor::RED;
                bro_node->color = RBNodeColor::BLACK;
                *get_node_father_connect_side_pointer(bro_node->father_node) = left_rotate(bro_node->father_node);
                // 转换为兄黑
                bro_node = node->father_node->right_node; // 旋转后兄弟节点变了
            }
            if(get_node_color(bro_node->left_node) == RBNodeColor::BLACK && \
                        get_node_color(bro_node->right_node) == RBNodeColor::BLACK ){
                // 兄黑 双侄子黑
                bro_node->color = RBNodeColor::RED;
                if(node->father_node->color == RBNodeColor::RED) {
                    node->father_node->color = RBNodeColor::BLACK;
                    break; // 结束循环 调整结束
                }
                // 否则node 父节点这条支路上 就少一个黑节点 违反了规则 需要继续对父节点调整
                node = node->father_node;
            }
            else{ // 有一个侄子节点为红色
                if(get_node_color(bro_node->left_node) == RBNodeColor::RED &&  \
                        get_node_color(bro_node->right_node) == RBNodeColor::BLACK ){
                    // 兄黑 顺侄红
                    bro_node->color = RBNodeColor::RED;
                    bro_node->left_node->color = RBNodeColor::BLACK;
                    *get_node_father_connect_side_pointer(bro_node) = right_rotate(bro_node);
                    // 旋转节点 变成 对侄红
                    bro_node = node->father_node->right_node; // 旋转后兄弟节点变了
                }
                // 因为兄黑 情况 父节点红黑都有可能 所以这里旋转换色 用节点之间的颜色交换
                bro_node->color = node->father_node->color;
                node->father_node->color = RBNodeColor::BLACK;
                bro_node->right_node->color = RBNodeColor::BLACK;
                *get_node_father_connect_side_pointer(node->father_node) = left_rotate(node->father_node);

                break;
                //调整结束
            }
        }
        else{ // 节点在父节点右侧
            RBNode<key_type> *bro_node = node->father_node->left_node;
            if(get_node_color(bro_node) == RBNodeColor::RED){
                bro_node->father_node->color = RBNodeColor::RED;
                bro_node->color = RBNodeColor::BLACK;
                *get_node_father_connect_side_pointer(bro_node->father_node) = right_rotate(bro_node->father_node);
                // 转换为兄黑
                bro_node = node->father_node->left_node; // 旋转后兄弟节点变了
            }
            if(get_node_color(bro_node->right_node) == RBNodeColor::BLACK && \
                        get_node_color(bro_node->left_node) == RBNodeColor::BLACK ){
                // 兄黑 双侄子黑
                bro_node->color = RBNodeColor::RED;
                if(node->father_node->color == RBNodeColor::RED) {
                    node->father_node->color = RBNodeColor::BLACK;
                    break; // 结束循环 调整结束
                }
                // 否则node 父节点这条支路上 就少一个黑节点 违反了规则 需要继续对父节点调整
                node = node->father_node;
            }
            else{ // 有一个侄子节点为红色
                if(get_node_color(bro_node->right_node) == RBNodeColor::RED &&  \
                        get_node_color(bro_node->left_node) == RBNodeColor::BLACK ){
                    // 兄黑 顺侄红
                    bro_node->color = RBNodeColor::RED;
                    bro_node->right_node->color = RBNodeColor::BLACK;
                    *get_node_father_connect_side_pointer(bro_node) = left_rotate(bro_node);
                    // 旋转节点 变成 对侄红
                    bro_node = node->father_node->left_node; // 旋转后兄弟节点变了
                }
                // 因为兄黑 情况 父节点红黑都有可能 所以这里旋转换色 用节点之间的颜色交换
                bro_node->color = node->father_node->color;
                node->father_node->color = RBNodeColor::BLACK;
                bro_node->left_node->color = RBNodeColor::BLACK;
                *get_node_father_connect_side_pointer(node->father_node) = right_rotate(node->father_node);

                break;
                //调整结束
            }
        }
    }
}


template<typename key_type>
void RBTree<key_type>::insert_node(RBNode<key_type> *node, key_type key) {
    RBNode<key_type> *pre = this->nill;
    RBNode<key_type> *cur = this->root;

    while(!is_node_empty(cur) ){
        pre = cur;
        if(key < cur->key){
            cur = cur->left_node;
        }
        else if (key > cur->key){
            cur = cur->right_node;
        }
        else
            return;
    }
    //如果插入节点是根节点
    if (is_node_empty(pre)){ // 还没进循环就 所以pre 是空指针
        this->root = new RBNode<int>(RBNodeColor::BLACK, key, this->nill, this->nill, this->nill);
        cur = this->root;
    }
    else{
        if(key < pre->key){
            pre->left_node = new RBNode<int>(RBNodeColor::RED, key, pre, this->nill, this->nill);
            cur = pre->left_node;
        }
        else if(key > pre->key){
            pre->right_node = new RBNode<int>(RBNodeColor::RED, key, pre, this->nill, this->nill);
            cur = pre->right_node;
        }
    }
    //到这里插入完成
    insert_fix_tree(cur); // 这是被插入节点的s

    this->root->color = RBNodeColor::BLACK;
}




template<typename key_type>
void RBTree<key_type>::insert_fix_tree(RBNode<key_type> *node){

    //情况1 父节点 黑色时直接跳过
    //剩下的情况都是父节点 红色的
    while(node != this->root && node->father_node->color == RBNodeColor::RED){
        // 父节点在左侧
        if (node->father_node == node->father_node ->father_node->left_node){
            RBNode<key_type> *uncle = node->father_node->father_node->right_node;
            if(uncle->color == RBNodeColor::RED){ //叔叔节点也是红色
                // 祖父节点 染色为红，父叔节点染色为黑
                node->father_node->color = RBNodeColor::BLACK;
                uncle->color = RBNodeColor::BLACK;
                node->father_node->father_node->color = RBNodeColor::RED;

                node = node->father_node->father_node;// 本循环结束
                // 此时祖父节点为红色, 循条件环值判断是是否有两个连续红色
            }
            else{
                /*叔节点为黑色
                 *      1、插入节点和父节点同侧
                 *      2、插入节点和父节点不同侧
                 * */
                if(node->father_node->right_node == node){
                    //不同侧 旋转父节点 变成同侧
                    // 变换后 父节点为红色, 循条件环值判断是是否有两个连续红色
                    *get_node_father_connect_side_pointer(node->father_node) = left_rotate(node->father_node);
                    node = node->left_node;
                }
                // 同侧
                node->father_node->father_node->color = RBNodeColor::RED;
                node->father_node->color = RBNodeColor::BLACK;
                node->color = RBNodeColor::RED;
                RBNode<key_type> **connect_side = get_node_father_connect_side_pointer(node->father_node->father_node);
                *connect_side = right_rotate(node->father_node->father_node);
//                node = node->father_node;
                break;
            }
        }
        else{ //父节点在右侧
            RBNode<key_type> *uncle = node->father_node->father_node->left_node;
            if(uncle->color == RBNodeColor::RED){ //叔叔节点也是红色
                // 祖父节点 染色为红，父叔节点染色为黑
                node->father_node->color = RBNodeColor::BLACK;
                uncle->color = RBNodeColor::BLACK;
                node->father_node->father_node->color = RBNodeColor::RED;

                node = node->father_node->father_node; // 本循环结束
                // 此时祖父节点为红色, 循条件环值判断是是否有两个连续红色
            }
            else{
                /*叔节点为黑色
                 *      1、插入节点和父节点同侧
                 *      2、插入节点和父节点不同侧
                 * */
                if(node->father_node->left_node == node){
                    //不同侧 旋转父节点 变成同侧
                    // 变换后 父节点为红色, 循条件环值判断是是否有两个连续红色
                    *get_node_father_connect_side_pointer(node->father_node) = right_rotate( node->father_node);
                    node = node->right_node;
                }
                // 同侧
                node->father_node->father_node->color = RBNodeColor::RED;
                node->father_node->color = RBNodeColor::BLACK;
                node->color = RBNodeColor::RED;
                RBNode<key_type> **connect_side = get_node_father_connect_side_pointer(node->father_node->father_node);
                *connect_side = left_rotate(node->father_node->father_node);
//                node = node->father_node;
                break;
            }
        }
        this->root->color = RBNodeColor::BLACK;
    }

    this->root->color = RBNodeColor::BLACK;
}
template<typename key_type>
void RBTree<key_type>::mid_order_print(RBNode<key_type> *node) {
    if(is_node_empty( node ))
        return;
    mid_order_print(node->left_node);
    std::cout << node->key << "-";
    if(node->color == RBNodeColor::RED)
        std::cout << "RED" << std::endl;
    else
        std::cout << "BLACK" << std::endl;
    mid_order_print(node->right_node);
}

template<typename key_type>
void RBTree<key_type>::pre_order_print(RBNode<key_type> *node) {
    if(is_node_empty( node ))
        return;
    std::cout << node->key << "-";
    if(node->color == RBNodeColor::RED)
        std::cout << "RED" << std::endl;
    else
        std::cout << "BLACK" << std::endl;
    mid_order_print(node->left_node);
    mid_order_print(node->right_node);
}

template<typename key_type>
RBNode<key_type> *RBTree<key_type>::find_node(RBNode<key_type> *node, key_type key) {
    if(is_node_empty( node ))
        return this->nill;

    if (key < node->key) {
        return find_node(node->left_node, key);
    }
    else if(key > node->key){
        return find_node(node->right_node, key);
    }

    return node;
}

#endif //KEY_VALUE_RBTREE_H
