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

void bst_inorder(bst_node *tree) {
  if (tree != NULL) {
    bst_inorder(tree->left);
    printf("%d ", tree->key);
    bst_inorder(tree->right);
  }
}

struct Trunk {
  Trunk *prev;
  string str;

  Trunk(Trunk *prev, string str) {
    this->prev = prev;
    this->str = str;
  }
};

void showTrunks(Trunk *p) {
  if (p == nullptr) {
    return;
  }
  showTrunks(p->prev);
  cout << p->str;
}

void bst_print(bst_node *tree, Trunk *prev, bool isLeft) {
  if (tree == nullptr) {
    return;
  }

  string prev_str = "    ";
  Trunk *trunk = new Trunk(prev, prev_str);

  bst_print(tree->right, trunk, true);

  if (!prev) {
    trunk->str = "———";
  } else if (isLeft) {
    trunk->str = "┏———";
    prev->str = "   ";
    prev_str = "   |";
  } else {
    trunk->str = "┗———";
    prev->str = "   ";
  }

  showTrunks(trunk);
  cout << tree->key << endl;

  if (prev) {
    prev->str = prev_str;
  }
  trunk->str = "   |";

  bst_print(tree->left, trunk, false);
}