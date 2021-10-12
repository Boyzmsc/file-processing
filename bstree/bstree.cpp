#include <bits/stdc++.h>
using namespace std;

struct bst_node {
  int key;
  int value;
  struct bst_node *left;
  struct bst_node *right;
};

bst_node *bst_alloc(void) {
  bst_node *node = (bst_node *)malloc(sizeof(bst_node));
  node->left = NULL;
  node->right = NULL;
  return node;
}

void bst_insert(bst_node **tree, int key, int value) {
  bst_node *parent = NULL;
  bst_node *curr = *tree;

  while (curr != NULL) {
    if (key == curr->key) {
      return;
    }

    parent = curr;

    if (key > curr->key) {
      curr = curr->right;
    } else {
      curr = curr->left;
    }
  }

  curr = bst_alloc();
  curr->key = key;
  curr->value = value;

  if (parent == NULL) {
    *tree = curr;
  } else if (key < parent->key) {
    parent->left = curr;
  } else {
    parent->right = curr;
  }
}

void bst_erase(bst_node **tree, int key) {
  bst_node *parent = NULL;
  bst_node *curr = *tree;

  while (curr != NULL && curr->key != key) {
    parent = curr;

    if (key < curr->key) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  if (curr == NULL) {
    return;
  }

  // Both Children Nodes Exist
  if (curr->left != NULL && curr->right != NULL) {
    parent = curr;
    bst_node *tmp = parent;

    curr = curr->left;
    while (curr->right != NULL) {
      tmp = curr;
      curr = curr->right;
    }

    parent->key = curr->key;
    parent->value = curr->value;
    parent = tmp;
  }

  // Both Children Nodes Don't Exist or Not
  if (curr->left == NULL && curr->right == NULL) {
    if (parent == NULL) {
      *tree = NULL;
    } else if (parent->left == curr) {
      parent->left = NULL;
    } else {
      parent->right = NULL;
    }
  } else if (curr->left != NULL) {
    if (parent == NULL) {
      *tree = curr->left;
    } else if (parent->left == curr) {
      parent->left = curr->left;
    } else {
      parent->right = curr->left;
    }
  } else {
    if (parent == NULL) {
      *tree = curr->right;
    } else if (parent->left == curr) {
      parent->left = curr->right;
    } else {
      parent->right = curr->right;
    }
  }

  free(curr);
}

int bst_search(bst_node *tree, int key) {
  if (tree != NULL) {
    if (tree->key == key) {
      return tree->value;
    } else if (key < tree->key) {
      return bst_search(tree->left, key);
    } else {
      return bst_search(tree->right, key);
    }
  } else {
    // Not Found
    return -1;
  }
}

void bst_inorder(bst_node *tree) {
  if (tree != NULL) {
    bst_inorder(tree->left);
    printf("%d ", tree->key);
    bst_inorder(tree->right);
  }
}

struct Path {
  Path *prev;
  string str;

  Path(Path *prev, string str) {
    this->prev = prev;
    this->str = str;
  }
};

void showPath(Path *p) {
  if (p == NULL) {
    return;
  }
  showPath(p->prev);
  cout << p->str;
}

void bst_print(bst_node *tree, Path *prev, bool isRight) {
  if (tree == NULL) {
    return;
  }

  string prev_str = "    ";
  Path *p = new Path(prev, prev_str);

  bst_print(tree->right, p, true);

  if (!prev) {
    p->str = "───";
  } else if (isRight) {
    p->str = "┎───";
    prev->str = "   ";
    prev_str = "   │";
  } else {
    p->str = "┖───";
    prev->str = "   ";
  }

  showPath(p);
  cout << tree->key << endl;

  if (prev) {
    prev->str = prev_str;
  }
  p->str = "   │";

  bst_print(tree->left, p, false);
}