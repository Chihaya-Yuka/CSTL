#include <stdlib.h>
#include "rb_tree.h"

void RBTree_init(RBTree *tree){
    tree->root = NULL;
}

void RBTree_free(RBTree *tree){
    RBTree_node *node = tree->root;
    while(node != NULL){
        if(RBTree_has_left(node)){
            node = node->left;
        }else if(RBTree_has_right(node)){
            node = node->right;
        }else{
            RBTree_node *parent = node->parent;
            if(RBTree_is_root(node)){
                tree->root = NULL;
            }else if(node == parent->left){
                parent->left = NULL;
            }else{
                parent->right = NULL;
            }
            free(node);
            node = parent;
        }
    }
}

void RBTree_rotate_left(RBTree *tree, RBTree_node *node){
    RBTree_node *right = node->right;
    node->right = right->left;
    if(RBTree_has_left(right)){
        right->left->parent = node;
    }
    right->parent = node->parent;
    if(RBTree_is_root(node)){
        tree->root = right;
    }else if(node == node->parent->left){
        node->parent->left = right;
    }else{
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

void RBTree_rotate_right(RBTree *tree, RBTree_node *node){
    RBTree_node *left = node->left;
    node->left = left->right;
    if(RBTree_has_right(left)){
        left->right->parent = node;
    }
    left->parent = node->parent;
    if(RBTree_is_root(node)){
        tree->root = left;
    }else if(node == node->parent->right){
        node->parent->right = left;
    }else{
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
}

void RBTree_insert_node(RBTree *tree, RBTree_node *node){

    RBTree_node *y = NULL;
    RBTree_node *x = tree->root;
    while(x != NULL){
        y = x;
        if(node->data < x->data){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    node->parent = y;
    if(y == NULL){
        tree->root = node;
    }else if(node->data < y->data){
        y->left = node;
    }else{
        y->right = node;
    }
    node->left = NULL;
    node->right = NULL;
    RBTree_set_red(node);
    RBTree_insert_fixup(tree, node);
}

void RBTree_insert_fixup(RBTree *tree, RBTree_node *node){
    if(node == NULL){
        return;
    }
    RBTree_node *y;
    while((!RBTree_is_root(node)) && RBTree_is_red(node->parent)){
        if(node->parent == node->parent->parent->left){
            y = node->parent->parent->right;
            if(y != NULL && RBTree_is_red(y)){
                RBTree_set_black(node->parent);
                RBTree_set_black(y);
                RBTree_set_red(node->parent->parent);
                node = node->parent->parent;
            }else{
                if(node == node->parent->right){
                    node = node->parent;
                    RBTree_rotate_left(tree, node);
                }
                RBTree_set_black(node->parent);
                RBTree_set_red(node->parent->parent);
                RBTree_rotate_right(tree, node->parent->parent);
            }
        }else{
            y = node->parent->parent->left;
            if(y != NULL && RBTree_is_red(y)){
                RBTree_set_black(node->parent);
                RBTree_set_black(y);
                RBTree_set_red(node->parent->parent);
                node = node->parent->parent;
            }else{
                if(node == node->parent->left){
                    node = node->parent;
                    RBTree_rotate_right(tree, node);
                }
                RBTree_set_black(node->parent);
                RBTree_set_red(node->parent->parent);
                RBTree_rotate_left(tree, node->parent->parent);
            }
        }
    }
    RBTree_set_black(tree->root);
}

void RBTree_delete_node(RBTree *tree, RBTree_node *node){
    RBTree_node *child, *parent;
    enum RB_COLOR color;

    if(RBTree_has_both(node)){
        RBTree_node *replace = node;

        replace = replace->right;
        while(RBTree_has_left(replace)){
            replace = replace->left;
        }

        if(!RBTree_is_root(node)){
            if(node->parent->left == node){
                node->parent->left = replace;
            }else{
                node->parent->right = replace;
            }
        }else{
            tree->root = replace;
        }

        child = replace->right;
        parent = replace->parent;
        color = replace->color;
        if(parent == node){
            parent = replace;
        }else{
            if(child != NULL){
                child->parent = parent;
            }
            parent->left = child;
            replace->right = node->right;
            node->right->parent = replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if(color == BLACK){
            RBTree_delete_fixup(tree, child, parent);
        }
        free(node);

        return;
    }

    if(!RBTree_has_left(node)){
        child = node->right;
    }else{
        child = node->left;
    }

    parent = node->parent;
    color = node->color;

    if(child != NULL){
        child->parent = parent;
    }

    if(parent != NULL){
        if(parent->left == node){
            parent->left = child;
        }else{
            parent->right = child;
        }
    }else{
        tree->root = child;
    }

    if(color == BLACK){
        RBTree_delete_fixup(tree, child, parent);
    }
    free(node);
}

void RBTree_delete_fixup(RBTree *tree, RBTree_node *node, RBTree_node *parent){
    RBTree_node *other;
    if(node == NULL || parent == NULL){
        return;
    }

    while((!RBTree_is_root(node)) && RBTree_is_black(node)){
        if(parent->left == node){
            other = parent->right;
            if(RBTree_is_red(other)){
                RBTree_set_black(other);
                RBTree_set_red(parent);
                RBTree_rotate_left(tree, parent);
                other = parent->right;
            }
            if((!RBTree_has_left(other)) || (!RBTree_has_right(other))){
                break;
            }
            if((RBTree_is_black(other->left)) && (RBTree_is_black(other->right))){
                RBTree_set_red(other);
                node = parent;
                parent = node->parent;
            }else{
                if(RBTree_is_black(other->right)){
                    RBTree_set_black(other->left);
                    RBTree_set_red(other);
                    RBTree_rotate_right(tree, other);
                    other = parent->right;
                }
                other->color = parent->color;
                RBTree_set_black(parent);
                RBTree_set_black(other->right);
                RBTree_rotate_left(tree, parent);
                node = tree->root;
                break;
            }
        }else{
            other = parent->left;
            if(RBTree_is_red(other)){
                RBTree_set_black(other);
                RBTree_set_red(parent);
                RBTree_rotate_right(tree, parent);
                other = parent->left;
            }
            if((!RBTree_has_left(other)) || (!RBTree_has_right(other))){
                break;
            }
            if((RBTree_is_black(other->left)) && (RBTree_is_black(other->right))){
                RBTree_set_red(other);
                node = parent;
                parent = node->parent;
            }else{
                if(RBTree_is_black(other->left)){
                    RBTree_set_black(other->right);
                    RBTree_set_red(other);
                    RBTree_rotate_left(tree, other);
                    other = parent->left;
                }
                other->color = parent->color;
                RBTree_set_black(parent);
                RBTree_set_black(other->left);
                RBTree_rotate_right(tree, parent);
                node = tree->root;
                break;
            }
        }
    }
    if(node != NULL){
        RBTree_set_black(node);
    }
}

void RBTree_insert(RBTree *tree, int data){
    RBTree_node *node = (RBTree_node *)malloc(sizeof(RBTree_node));
    node->data = data;
    RBTree_insert_node(tree, node);
}

void RBTree_delete(RBTree *tree, int data){
    RBTree_node *node = RBTree_search(tree, data);
    if(node != NULL){
        RBTree_delete_node(tree, node);
    }
}

RBTree_node *RBTree_search(RBTree *tree, int data){
    RBTree_node *node = tree->root;
    while(node != NULL){
        if(data == node->data){
            return node;
        }else if(data < node->data){
            node = node->left;
        }else{
            node = node->right;
        }
    }
    return NULL;
}

int RBTree_contains(RBTree *tree, int data){
    return RBTree_search(tree, data) != NULL;
}
