#ifndef _AVLTREE_H
#define _AVLTREE_H

#include <cstdlib>
#include <stack>

struct avl_node
{
    int key;
    int value;
    struct avl_node *left;
    struct avl_node *right;
    size_t height;
};

static inline struct avl_node *avl_alloc()
{
    struct avl_node *node = (struct avl_node *)malloc(sizeof(struct avl_node));
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

static inline size_t max(const size_t a, const size_t b);

static inline size_t height(const struct avl_node *tree);

static inline void avl_rotate_left(struct avl_node **root, struct avl_node *x, struct avl_node *parent);

static inline void avl_rotate_right(struct avl_node **root, struct avl_node *x, struct avl_node *parent);

extern inline void avl_insert(struct avl_node **tree, int key, int value);

extern inline void avl_erase(struct avl_node **tree, int key);

extern inline void avl_inorder(const struct avl_node *tree, void (*func)(const int, int));

#endif
