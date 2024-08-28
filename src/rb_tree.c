#include <rb_tree.h>
#include <stdlib.h>

void rb_tree_init(RBTree_node *root, int key) {
    root->key = key;
    root->color = BLACK;
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;
}

RBTree_node *rb_tree_insert(RBTree_node *root, int key) {
    RBTree_node *exist = rb_tree_find(root, key);
    if (exist != NULL) {
        return exist;
    }
    RBTree_node *new_node = (RBTree_node *)malloc(sizeof(RBTree_node));
    RBTree_node *insert_node = rb_tree_find_(root, key, 1);
    rb_tree_init(new_node, key);
    new_node->color = RED;
    if (key < insert_node->key) {
        rb_tree_add_as_left(insert_node, new_node);
    } else {
        rb_tree_add_as_right(insert_node, new_node);
    }
    rb_tree_solve_double_red(new_node);
    return new_node;
}

void rb_tree_remove(RBTree_node *root, int key) {
    RBTree_node *node = rb_tree_find(root, key);
    if (node == NULL) {
        return;
    }
    RBTree_node *node_delete = node;
    RBTree_node *successor = NULL;
    if (rb_tree_has_both(node)) {
        node_delete = node->right;
        while (rb_tree_has_left(node_delete)) {
            node_delete = node_delete->left;
        }

        int tmp = node_delete->key;
        node_delete->key = node->key;
        node->key = tmp;

        RBTree_node *parent = node_delete->parent;
        if (parent == node) {
            parent->right = node_delete->right;
        } else {
            parent->left = node_delete->right;
        }
        successor = node_delete->right;
    } else {
        if (!rb_tree_has_left(node)) {
            successor = node->right;
        } else {
            successor = node->left;
        }

        if (rb_tree_is_not_root(node_delete)) {
            if (rb_tree_is_left(node_delete)) {
                node_delete->parent->left = successor;
            } else {
                node_delete->parent->right = successor;
            }
        }
    }
    RBTree_node *delete_parent = node_delete->parent;
    if (successor) {
        successor->parent = delete_parent;
    }
    if (delete_parent == NULL) {
        root = successor;
    }
    int node_delete_is_red = rb_tree_is_red(node_delete);
    free(node_delete);
    if (delete_parent == NULL) {
        if (root != NULL) {
            root->color = BLACK;
        }
        return;
    }
    if (node_delete_is_red) {
        return;
    }
    if (successor != NULL && rb_tree_is_red(successor)) {
        successor->color = BLACK;
        return;
    }
    rb_tree_solve_double_black(successor);
}

RBTree_node *rb_tree_find(RBTree_node *node, int key) {
    rb_tree_find_(node, key, 0);
}

RBTree_node *rb_tree_find_(RBTree_node *node, int key, int return_insert_place) {
    if (node->key == key) {
        return node;
    }
    if (node->key > key) {
        return node->left == NULL ? (return_insert_place ? node : NULL)
            : rb_tree_find(node->left, key);
    } else {
        return node->right == NULL ? (return_insert_place ? node : NULL)
            : rb_tree_find(node->right, key);
    }
}

void rb_tree_rotate_left(RBTree_node *node) {
    RBTree_node *right_child = node->right;
    RBTree_node *right_left_child = right_child->left;

    node->right = right_left_child;
    if (rb_tree_has_left(right_child)) {
        right_left_child->parent = node;
    }

    RBTree_node *parent = node->parent;
    right_child->left = node;
    node->parent = right_child;

    if (rb_tree_is_root(node)) {
        right_child->parent = NULL;
        return;
    }

    if (node == parent->left) {
        parent->left = right_child;
    } else {
        parent->right = right_child;
    }
    right_child->parent = parent;
}

void rb_tree_rotate_right(RBTree_node *node) {
    RBTree_node *left_child = node->left;
    RBTree_node *left_right_child = left_child->right;

    node->left = left_right_child;
    if (rb_tree_has_right(left_child)) {
        left_right_child->parent = node;
    }

    RBTree_node *parent = node->parent;
    left_child->right = node;
    node->parent = left_child;

    if (rb_tree_is_root(node)) {
        left_child->parent = NULL;
        return;
    }

    if (node == parent->left) {
        parent->left = left_child;
    } else {
        parent->right = left_child;
    }
    left_child->parent = parent;
}

RBTree_node *rb_tree_adjust(RBTree_node *node) {
    RBTree_node *parent = node->parent;
    if (parent == NULL) {
        return NULL;
    }
    RBTree_node *grandparent = parent->parent;
    if (grandparent == NULL) {
        return NULL;
    }
    RBTree_node *local_root = NULL;

    if (rb_tree_is_left(parent) && rb_tree_is_left(node)) {
        rb_tree_add_as_left(grandparent, parent->right);
        rb_tree_add_as_right(parent, grandparent);
        local_root = parent;
    } else if (rb_tree_is_right(parent) && rb_tree_is_right(node)) {
        rb_tree_add_as_right(grandparent, parent->left);
        rb_tree_add_as_left(parent, grandparent);
        local_root = parent;
    } else if (rb_tree_is_left(parent) && rb_tree_is_right(node)) {
        rb_tree_add_as_right(parent, node->left);
        rb_tree_add_as_left(grandparent, node->right);
        rb_tree_add_as_left(node, parent);
        rb_tree_add_as_right(node, grandparent);
        local_root = node;
    } else if (rb_tree_is_right(parent) && rb_tree_is_left(node)) {
        rb_tree_add_as_left(parent, node->right);
        rb_tree_add_as_right(grandparent, node->left);
        rb_tree_add_as_right(node, parent);
        rb_tree_add_as_left(node, grandparent);
        local_root = node;
    }
    return node;
}

void rb_tree_solve_double_red(RBTree_node *node) {
    if (rb_tree_is_root(node)) {
        node->color = BLACK;
        return;
    }

    RBTree_node *parent = node->parent;
    if (rb_tree_is_black(parent)) {
        return;
    }

    RBTree_node *grandparent = parent->parent;
    if (grandparent == NULL) {
        return;
    }

    RBTree_node *uncle =
        rb_tree_is_left(parent) ? grandparent->right : grandparent->left;
    if (rb_tree_is_black(uncle)) {
        if (rb_tree_is_left(parent) && rb_tree_is_left(node)) {
            parent->color = BLACK;
        } else {
            node->color = BLACK;
        }
        grandparent->color = RED;
        RBTree_node *grandgrandparent = grandparent->parent;
        RBTree_node *sub_root = rb_tree_adjust(node);
        if (grandgrandparent == NULL) {
            sub_root->color = BLACK;
            sub_root->parent = NULL;
        } else {
            if (sub_root->key < grandgrandparent->key) {
                rb_tree_add_as_left(grandgrandparent, sub_root);
            } else {
                rb_tree_add_as_right(grandgrandparent, sub_root);
            }
        }
    } else {
        parent->color = BLACK;
        uncle->color = BLACK;
        if (rb_tree_is_not_root(grandparent)) {
            grandparent->color = RED;
        }
        rb_tree_solve_double_red(grandparent);
    }
}

void rb_tree_solve_double_black(RBTree_node *node) {
    RBTree_node *parent = node->parent;
    if (parent == NULL) {
        return;
    }
    RBTree_node *root = rb_tree_get_root(node);
    RBTree_node *sibling = rb_tree_is_left(node) ? node->right : node->left;
    if (rb_tree_is_red(sibling)) {
        sibling->color = BLACK;
        parent->color = RED;
        RBTree_node *grandparent = parent->parent;
        RBTree_node *local_root = rb_tree_is_left(sibling)
            ? rb_tree_adjust(sibling->left)
            : rb_tree_adjust(sibling->right);
        if (grandparent == NULL) {
            local_root->color = BLACK;
            local_root->parent = NULL;
            root = local_root;
        } else {
            if (local_root->key < grandparent->key) {
                rb_tree_add_as_left(grandparent, local_root);
            } else {
                rb_tree_add_as_right(grandparent, local_root);
            }
        }
        rb_tree_solve_double_black(node);
    } else {
        RBTree_node *red = rb_tree_has_left(node) && rb_tree_is_red(node->left)
            ? node->left
            : (rb_tree_has_right(node) && rb_tree_is_red(node->right)
                ? node->right
                : NULL);
        if(red != NULL){
            enum rb_color parent_color = parent->color;
            RBTree_node *grandparent = parent;
            RBTree_node *local_root = rb_tree_adjust(red);
            if(grandparent == NULL){
                local_root->color = BLACK;
                local_root->parent = NULL;
                root = local_root;
            } else {
                if(local_root->key < grandparent->key){
                    rb_tree_add_as_left(grandparent, local_root);
                } else {
                    rb_tree_add_as_right(grandparent, local_root);
                }
            }
            local_root->color = parent_color;  // TODO: bugs?
            local_root->left->color = BLACK;
            local_root->right->color = BLACK;
        } else {
            if(rb_tree_is_black(parent)){
                parent->color = BLACK;
                node->color = RED;
            } else {
                node->color = RED;
            }
            rb_tree_solve_double_black(parent);
        }
    }
}

void rb_tree_add_as_left(RBTree_node *root, RBTree_node *node) {
    root->left = node;
    if (node != NULL) {
        node->parent = root;
    }
}

void rb_tree_add_as_right(RBTree_node *root, RBTree_node *node) {
    root->right = node;
    if (node != NULL) {
        node->parent = root;
    }
}

RBTree_node *rb_tree_get_root(RBTree_node *node) {
    while (node->parent != NULL) {
        node = node->parent;
    }
    return node;
}