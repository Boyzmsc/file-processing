#ifndef _BTREE_H
#define _BTREE_H

#include <cstdlib>
#include <cstring>
#include <stack>

struct btree_node {
  int *keys;
  int *values;
  struct btree_node **children;
  size_t nmemb;
};

struct btree_node *btree_alloc(const size_t order) {
  struct btree_node *node =
      (struct btree_node *)malloc(sizeof(struct btree_node));
  node->keys = (int *)malloc(sizeof(int) * (order - 1));
  node->values = (int *)malloc(sizeof(int) * (order - 1));
  node->children = (struct btree_node **)malloc(__SIZEOF_POINTER__ * order);
  node->nmemb = 0;
  return node;
}

void btree_free(struct btree_node *node) {
  free(node->keys);
  free(node->values);
  free(node->children);
  free(node);
}

void btree_insert(struct btree_node **tree, const size_t order, int key,
                  int value) {
  // TODO
}

void btree_erase(struct btree_node **tree, const size_t order, int key) {
  // TODO
}

void btree_inorder(struct btree_node *tree, void (*func)(int, int)) {
  // TODO
}

#endif
