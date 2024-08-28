#ifndef RB_TREE_H
#define RB_TREE_H

enum rb_color {
    RED,
    BLACK
};

typedef struct RBTree_node_t {
    int key;
    enum rb_color color;
    struct RBTree_node_t *left;
    struct RBTree_node_t *right;
    struct RBTree_node_t *parent;
} RBTree_node;

void rb_tree_init(RBTree_node *root, int key);
RBTree_node *rb_tree_insert(RBTree_node *root, int key);
void rb_tree_remove(RBTree_node *root, int key);
RBTree_node *rb_tree_find(RBTree_node *node, int key);
RBTree_node *rb_tree_find_(RBTree_node *node, int key, int return_insert_place);
void rb_tree_rotate_left(RBTree_node *node);
void rb_tree_rotate_right(RBTree_node *node);
RBTree_node *rb_tree_adjust(RBTree_node *node);
void rb_tree_solve_double_red(RBTree_node *node);
void rb_tree_solve_double_black(RBTree_node *node);
void rb_tree_add_as_left(RBTree_node *root, RBTree_node *node);
void rb_tree_add_as_right(RBTree_node *root, RBTree_node *node);
RBTree_node *rb_tree_get_root(RBTree_node *node);

#define rb_tree_is_root(node) ((node)->parent == NULL)
#define rb_tree_is_not_root(node) ((node)->parent != NULL)
#define rb_tree_is_leaf(node) (rb_tree_has_none(node))
#define rb_tree_is_left(node) (!(rb_tree_is_not_root(node)) && (node)->parent->left == (node))
#define rb_tree_is_right(node) (!(rb_tree_is_not_root(node)) && (node)->parent->right == (node))
#define rb_tree_is_red(node) ((node)->color == RED)
#define rb_tree_is_black(node) ((node)->color == BLACK)
#define rb_tree_has_left(node) ((node)->left != NULL)
#define rb_tree_has_right(node) ((node)->right != NULL)
#define rb_tree_has_both(node) (rb_tree_has_left(node) && rb_tree_has_right(node))
#define rb_tree_has_any(node) (rb_tree_has_left(node) || rb_tree_has_right(node))
#define rb_tree_has_none(node) (!(rb_tree_has_any(node)))

#endif // RB_TREE_H