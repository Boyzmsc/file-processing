#include <bits/stdc++.h>
using namespace std;

struct btree_node {
  int *keys;
  btree_node **children;
  int cnt;
};

btree_node *btree_alloc(int order) {
  btree_node *node = (btree_node *)malloc(sizeof(btree_node));
  node->keys = (int *)malloc(sizeof(int) * (order - 1));
  node->children = (btree_node **)malloc(__SIZEOF_POINTER__ * order);
  node->cnt = 0;
  return node;
}

void btree_free(btree_node *node) {
  free(node->keys);
  free(node->children);
  free(node);
}

int binarySearch(const int key, const int *keys, int cnt) {
  int idx;
  int low = 0;
  int high = cnt;

  while (low < high) {
    idx = (low + high) / 2;
    if (key < keys[idx]) {
      high = idx;
    } else if (key > keys[idx]) {
      low = idx + 1;
    } else {
      return idx;
    }
  }

  return low;
}

void insertBT(btree_node **tree, int order, int key) {
  int idx;
  btree_node *tmp;
  btree_node *curr = *tree;
  btree_node *sibling = NULL;
  stack<btree_node *> nStack;
  stack<int> iStack;

  while (curr != NULL) {
    idx = binarySearch(key, curr->keys, curr->cnt);
    // Key Already Exists
    if (idx < curr->cnt && key == curr->keys[idx]) {
      while (!nStack.empty()) {
        nStack.pop();
      }
      while (!iStack.empty()) {
        iStack.pop();
      }
      return;
    }
    nStack.push(curr);
    iStack.push(idx);
    curr = curr->children[idx];
  }

  while (!nStack.empty()) {
    curr = nStack.top();
    nStack.pop();
    idx = iStack.top();
    iStack.pop();

    if (curr->cnt < order - 1) {
      memcpy(&curr->keys[idx + 1], &curr->keys[idx],
             sizeof(int) * (curr->cnt - idx));
      memcpy(&curr->children[idx + 2], &curr->children[idx + 1],
             __SIZEOF_POINTER__ * (curr->cnt - idx));
      curr->cnt++;

      curr->keys[idx] = key;
      curr->children[idx + 1] = sibling;
      while (!nStack.empty()) {
        nStack.pop();
      }
      while (!iStack.empty()) {
        iStack.pop();
      }
      return;
    }

    // Overflow
    tmp = btree_alloc(order + 1);
    memcpy(&tmp->keys[0], &curr->keys[0], sizeof(int) * idx);
    memcpy(&tmp->keys[idx + 1], &curr->keys[idx],
           sizeof(int) * (curr->cnt - idx));
    memcpy(&tmp->children[0], &curr->children[0],
           __SIZEOF_POINTER__ * (idx + 1));
    memcpy(&tmp->children[idx + 2], &curr->children[idx + 1],
           __SIZEOF_POINTER__ * (curr->cnt - idx));

    tmp->keys[idx] = key;
    tmp->children[idx + 1] = sibling;

    sibling = btree_alloc(order);
    sibling->cnt = (order - 1) / 2;
    curr->cnt = order / 2;

    memcpy(&curr->keys[0], &tmp->keys[0], sizeof(int) * curr->cnt);
    memcpy(&sibling->keys[0], &tmp->keys[curr->cnt + 1],
           sizeof(int) * sibling->cnt);
    memcpy(&curr->children[0], &tmp->children[0],
           __SIZEOF_POINTER__ * (curr->cnt + 1));
    memcpy(&sibling->children[0], &tmp->children[curr->cnt + 1],
           __SIZEOF_POINTER__ * (sibling->cnt + 1));

    key = tmp->keys[curr->cnt];
    btree_free(tmp);
  }

  // Root Splited => Level Increases
  *tree = btree_alloc(order);
  (*tree)->cnt = 1;
  (*tree)->keys[0] = key;
  (*tree)->children[0] = curr;
  (*tree)->children[1] = sibling;
}

void deleteBT(btree_node **tree, int order, int key) {
  int idx;
  btree_node *curr = *tree;
  btree_node *parent = NULL;
  btree_node *sibling = NULL;
  stack<btree_node *> nStack;
  stack<int> iStack;

  while (curr != NULL) {
    idx = binarySearch(key, curr->keys, curr->cnt);
    if (idx < curr->cnt && key == curr->keys[idx]) {
      break;
    }
    nStack.push(curr);
    iStack.push(idx);
    curr = curr->children[idx];
  }

  // Key Not Found
  if (curr == NULL) {
    while (!nStack.empty()) {
      nStack.pop();
    }
    while (!iStack.empty()) {
      iStack.pop();
    }
    return;
  }

  // Key In Internal Node
  if (curr->children[idx + 1] != NULL) {
    parent = curr;
    nStack.push(curr);
    iStack.push(idx + 1);

    for (curr = curr->children[idx + 1]; curr->children[0] != NULL;
         curr = curr->children[0]) {
      nStack.push(curr);
      iStack.push(0);
    }

    parent->keys[idx] = curr->keys[0];
    idx = 0;
  }

  // Exchange Key With Successor
  curr->cnt--;
  memcpy(&curr->keys[idx], &curr->keys[idx + 1],
         sizeof(int) * (curr->cnt - idx));

  while (!nStack.empty()) {
    // Not Underflow
    if (((order - 1) / 2) <= curr->cnt) {
      while (!nStack.empty()) {
        nStack.pop();
      }
      while (!iStack.empty()) {
        iStack.pop();
      }
      return;
    }

    // Underflow
    idx = iStack.top();
    iStack.pop();
    parent = nStack.top();
    nStack.pop();

    // Match Best Sibling
    if (idx == 0) {
      sibling = parent->children[1];
    } else if (idx == parent->cnt) {
      sibling = parent->children[idx - 1];
    } else if (parent->children[idx - 1]->cnt <
               parent->children[idx + 1]->cnt) {
      sibling = parent->children[idx + 1];
    } else {
      sibling = parent->children[idx - 1];
    }

    // Distribution Case
    if (((order - 1) / 2) < sibling->cnt) {
      if (sibling == parent->children[idx - 1]) {
        memcpy(&curr->keys[1], &curr->keys[0], sizeof(int) * curr->cnt);
        curr->cnt++;
        memcpy(&curr->children[1], &curr->children[0],
               __SIZEOF_POINTER__ * curr->cnt);

        curr->keys[0] = parent->keys[idx - 1];
        curr->children[0] = sibling->children[sibling->cnt];
        sibling->cnt--;
        parent->keys[idx - 1] = sibling->keys[sibling->cnt];
      } else {
        curr->keys[curr->cnt] = parent->keys[idx];
        curr->cnt++;
        curr->children[curr->cnt] = sibling->children[0];
        parent->keys[idx] = sibling->keys[0];

        memcpy(&sibling->children[0], &sibling->children[1],
               __SIZEOF_POINTER__ * sibling->cnt);
        sibling->cnt--;
        memcpy(&sibling->keys[0], &sibling->keys[1],
               sizeof(int) * sibling->cnt);
      }

      while (!nStack.empty()) {
        nStack.pop();
      }
      while (!iStack.empty()) {
        iStack.pop();
      }
      return;
    }

    // Merge Case
    if (sibling == parent->children[idx - 1]) {
      sibling->keys[sibling->cnt] = parent->keys[idx - 1];
      sibling->cnt++;
      memcpy(&sibling->keys[sibling->cnt], &curr->keys[0],
             sizeof(int) * curr->cnt);
      memcpy(&sibling->children[sibling->cnt], &curr->children[0],
             __SIZEOF_POINTER__ * (curr->cnt + 1));
      memcpy(&parent->keys[idx - 1], &parent->keys[idx],
             sizeof(int) * (parent->cnt - idx));
      memcpy(&parent->children[idx], &parent->children[idx + 1],
             __SIZEOF_POINTER__ * (parent->cnt - idx));
      parent->cnt--;

      sibling->cnt += curr->cnt;
      btree_free(curr);
    } else {
      curr->keys[curr->cnt] = parent->keys[idx];
      curr->cnt++;
      memcpy(&curr->keys[curr->cnt], &sibling->keys[0],
             sizeof(int) * sibling->cnt);
      memcpy(&curr->children[curr->cnt], &sibling->children[0],
             __SIZEOF_POINTER__ * (sibling->cnt + 1));
      parent->cnt--;
      memcpy(&parent->keys[idx], &parent->keys[idx + 1],
             sizeof(int) * (parent->cnt - idx));
      memcpy(&parent->children[idx + 1], &parent->children[idx + 2],
             __SIZEOF_POINTER__ * (parent->cnt - idx));

      curr->cnt += sibling->cnt;
      btree_free(sibling);
    }
    curr = parent;
  }

  // Root Merged Case => Level Decreases
  if (curr->cnt == 0) {
    *tree = curr->children[0];
    btree_free(curr);
  }
}

void inorderBT(btree_node *tree) {
  if (tree != NULL) {
    for (int i = 0; i < tree->cnt; i++) {
      inorderBT(tree->children[i]);
      printf("%d ", tree->keys[i]);
    }
    inorderBT(tree->children[tree->cnt]);
  }
}