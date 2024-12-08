#ifndef RB_TREE_H
#define RB_TREE_H

enum RB_COLOR{
    RED, BLACK
};

typedef struct RBTree_node_t{
    enum RB_COLOR color;
    int data;
    struct RBTree_node_t *left;
    struct RBTree_node_t *right;
    struct RBTree_node_t *parent;
} RBTree_node;

typedef struct RBTree_t{
    RBTree_node *root;
} RBTree;

void RBTree_init(RBTree *tree);
void RBTree_free(RBTree *tree);
void RBTree_rotate_left(RBTree *tree, RBTree_node *node);
void RBTree_rotate_right(RBTree *tree, RBTree_node *node);
void RBTree_insert_node(RBTree *tree, RBTree_node *node);
void RBTree_insert_fixup(RBTree *tree, RBTree_node *node);
void RBTree_delete_node(RBTree *tree, RBTree_node *node);
void RBTree_delete_fixup(RBTree *tree, RBTree_node *node, RBTree_node *parent);
void RBTree_insert(RBTree *tree, int data);
void RBTree_delete(RBTree *tree, int data);
RBTree_node *RBTree_search(RBTree *tree, int data);
int RBTree_contains(RBTree *tree, int data);

#define RBTree_is_red(node) ((node) && (node)->color == RED)
#define RBTree_is_black(node) ((node) && (node)->color == BLACK)
#define RBTree_set_red(node) ((node)->color = RED)
#define RBTree_set_black(node) ((node)->color = BLACK)
#define RBTree_has_left(node) ((node)->left != NULL)
#define RBTree_has_right(node) ((node)->right != NULL)
#define RBTree_has_both(node) (RBTree_has_left(node) && RBTree_has_right(node))
#define RBTree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)
#define RBTree_is_root(node) ((node)->parent == NULL)

#endif
