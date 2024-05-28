
//调整
void rbtree_delete_fixup(RedBlackTree *T, rbtree_node *x) {

    while ((x != T->root) && (x->color == BLACK)) {
        if (x == x->parent->left) {

            rbtree_node *w = x->parent->right; // 兄弟节点
            if (w->color == RED) { // 如果兄弟节点是红色的
                //旋转父节点 转换成兄弟节点是黑色的
                w->color = BLACK;
                x->parent->color = RED;

                rbtree_left_rotate(T, x->parent);
                w = x->parent->right;
            }
            // 后面按照兄弟节点是黑色 来处理

            // 如果两个侄子节点都是黑色的
            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbtree_right_rotate(T, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rbtree_left_rotate(T, x->parent);

                x = T->root;
            }

        }
        else {

            rbtree_node *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rbtree_right_rotate(T, x->parent);
                w = x->parent->left;
            }

            if ((w->left->color == BLACK) && (w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            }
            else {

                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbtree_left_rotate(T, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rbtree_right_rotate(T, x->parent);

                x = T->root;
            }

        }
    }

    x->color = BLACK;
}


rbtree_node *rbtree_delete(RedBlackTree *T, rbtree_node *z)
{
    rbtree_node *y = T->nil;
    rbtree_node *x = T->nil;

    if ((z->left == T->nil) || (z->right == T->nil))
    {
        // 如果被删除节点的两个子节点 有一个为空
        // 被删除的节点就时传入的节点z
        y = z;
    }
    else
    {
        // 都不为空时 找到后继节点 左子树的最右侧节点
        y=rbtree_successor(T, z);
    }

    // 找到被删除节点 不为空的一侧节点
    // 最终被删除的节点 至多只有一个非空子节点
    // 如果有一个非空节点
    if (y->left != T->nil)
        x = y->left;
    else if (y->right != T->nil)
        x = y->right;


    x->parent = y->parent;
    if (y->parent == T->nil)
        T->root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    // 将x 连接到被删节点父结点上  替代被删节点

    //如果z 是带两个子节点的 用后继节点值替代z的值
    if (y != z)
    {
        z->key = y->key;
        z->value = y->value;
    }

    // 前面主要功能是找打要被删除的节点

    // 调整
    if (y->color == BLACK) {
        rbtree_delete_fixup(T, x);//删除节点后 原节点的后继节点
        // x是 替代节点  替代被删节点在去调整
    }

    return y;
}