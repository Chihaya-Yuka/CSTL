#include "rb_tree.h"
#include <stdlib.h>

static void rb_tree_init_node(RBTree_node *node, int key) {
    node->key = key;
    node->color = RED;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
}

static RBTree_node *rb_tree_find_(RBTree_node *node, int key) {
    if (node == NULL) {
        return NULL;
    }
    if (node->key == key) {
        return node;
    }
    if (key < node->key) {
        return rb_tree_find_(node->left, key);
    } else {
        return rb_tree_find_(node->right, key);
    }
}

static void rb_tree_rotate_left(RBTree *tree, RBTree_node *node) {
    RBTree_node *right = node->right;
    node->right = right->left;
    if (right->left != NULL) {
        right->left->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == NULL) {
        tree->root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

static void rb_tree_rotate_right(RBTree *tree, RBTree_node *node) {
    RBTree_node *left = node->left;
    node->left = left->right;
    if (left->right != NULL) {
        left->right->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == NULL) {
        tree->root = left;
    } else if (node == node->parent->right) {
        node->parent->right = left;
    } else {
        node->parent->left = left;
    }
    left->right = node;
    node->parent = left;
}

static void rb_tree_insert_fixup(RBTree *tree, RBTree_node *node) {
    while (node != tree->root && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            RBTree_node *uncle = node->parent->parent->right;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rb_tree_rotate_left(tree, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rb_tree_rotate_right(tree, node->parent->parent);
            }
        } else {
            RBTree_node *uncle = node->parent->parent->left;
            if (uncle != NULL && uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rb_tree_rotate_right(tree, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rb_tree_rotate_left(tree, node->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

static void rb_tree_transplant(RBTree *tree, RBTree_node *u, RBTree_node *v) {
    if (u->parent == NULL) {
        tree->root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

static RBTree_node *rb_tree_minimum(RBTree_node *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

static void rb_tree_delete_fixup(RBTree *tree, RBTree_node *node, RBTree_node *parent) {
    while (node != tree->root && (node == NULL || node->color == BLACK)) {
        if (node == parent->left) {
            RBTree_node *sibling = parent->right;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rb_tree_rotate_left(tree, parent);
                sibling = parent->right;
            }
            if ((sibling->left == NULL || sibling->left->color == BLACK) &&
                (sibling->right == NULL || sibling->right->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->right == NULL || sibling->right->color == BLACK) {
                    sibling->left->color = BLACK;
                    sibling->color = RED;
                    rb_tree_rotate_right(tree, sibling);
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->right != NULL) {
                    sibling->right->color = BLACK;
                }
                rb_tree_rotate_left(tree, parent);
                node = tree->root;
            }
        } else {
            RBTree_node *sibling = parent->left;
            if (sibling->color == RED) {
                sibling->color = BLACK;
                parent->color = RED;
                rb_tree_rotate_right(tree, parent);
                sibling = parent->left;
            }
            if ((sibling->right == NULL || sibling->right->color == BLACK) &&
                (sibling->left == NULL || sibling->left->color == BLACK)) {
                sibling->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (sibling->left == NULL || sibling->left->color == BLACK) {
                    sibling->right->color = BLACK;
                    sibling->color = RED;
                    rb_tree_rotate_left(tree, sibling);
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = BLACK;
                if (sibling->left != NULL) {
                    sibling->left->color = BLACK;
                }
                rb_tree_rotate_right(tree, parent);
                node = tree->root;
            }
        }
    }
    if (node != NULL) {
        node->color = BLACK;
    }
}

void rb_tree_init(RBTree *tree) {
    tree->root = NULL;
}

RBTree_node *rb_tree_insert(RBTree *tree, int key) {
    RBTree_node *node = malloc(sizeof(RBTree_node));
    if (node == NULL) {
        return NULL;
    }
    rb_tree_init_node(node, key);

    RBTree_node *y = NULL;
    RBTree_node *x = tree->root;

    while (x != NULL) {
        y = x;
        if (key < x->key) {
            x = x->left;
        } else if (key > x->key) {
            x = x->right;
        } else {
            free(node);
            return x;  // Key already exists
        }
    }

    node->parent = y;
    if (y == NULL) {
        tree->root = node;
    } else if (key < y->key) {
        y->left = node;
    } else {
        y->right = node;
    }

    rb_tree_insert_fixup(tree, node);
    return node;
}

void rb_tree_remove(RBTree *tree, int key) {
    RBTree_node *node = rb_tree_find(tree, key);
    if (node == NULL) {
        return;
    }

    RBTree_node *y = node;
    RBTree_node *x;
    rb_color y_original_color = y->color;

    if (node->left == NULL) {
        x = node->right;
        rb_tree_transplant(tree, node, node->right);
    } else if (node->right == NULL) {
        x = node->left;
        rb_tree_transplant(tree, node, node->left);
    } else {
        y = rb_tree_minimum(node->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == node) {
            if (x != NULL) {
                x->parent = y;
            }
        } else {
            rb_tree_transplant(tree, y, y->right);
            y->right = node->right;
            y->right->parent = y;
        }
        rb_tree_transplant(tree, node, y);
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
    }

    free(node);

    if (y_original_color == BLACK) {
        rb_tree_delete_fixup(tree, x, (x == NULL) ? y->parent : x->parent);
    }
}

RBTree_node *rb_tree_find(RBTree *tree, int key) {
    return rb_tree_find_(tree->root, key);
}

static void rb_tree_destroy_recursive(RBTree_node *node) {
    if (node != NULL) {
        rb_tree_destroy_recursive(node->left);
        rb_tree_destroy_recursive(node->right);
        free(node);
    }
}

void rb_tree_destroy(RBTree *tree) {
    rb_tree_destroy_recursive(tree->root);
    tree->root = NULL;
}
