#include <bits/stdc++.h>
using namespace std;

struct avl_node {
  int key;
  int value;
  struct avl_node *left;
  struct avl_node *right;
  int height;
};

avl_node *avl_alloc() {
  avl_node *node = (avl_node *)malloc(sizeof(avl_node));
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

int max(const int a, const int b) { return (a > b) ? a : b; }

int height(const avl_node *tree) { return tree == NULL ? 0 : tree->height; }

void avl_rotate_left(avl_node **tree, avl_node *curr, avl_node *parent) {
  avl_node *tmp = curr->right;
  curr->right = tmp->left;
  tmp->left = curr;

  if (parent == NULL) {
    *tree = tmp;
  } else if (parent->left == curr) {
    parent->left = tmp;
  } else {
    parent->right = tmp;
  }
}

void avl_rotate_right(avl_node **tree, avl_node *curr, avl_node *parent) {
  avl_node *tmp = curr->left;
  curr->left = tmp->right;
  tmp->right = curr;

  if (parent == NULL) {
    *tree = tmp;
  } else if (parent->left == curr) {
    parent->left = tmp;
  } else {
    parent->right = tmp;
  }
}

void avl_insert(avl_node **tree, int key, int value) {
  avl_node *parent = NULL;
  avl_node *curr = *tree;
  avl_node *check = NULL;
  stack<avl_node *> s;

  while (curr != NULL) {
    if (key == curr->key) {
      return;
    }

    parent = curr;
    s.push(curr);

    if (key > curr->key) {
      curr = curr->right;
    } else {
      curr = curr->left;
    }
  }

  curr = avl_alloc();
  curr->key = key;
  curr->value = value;

  if (parent == NULL) {
    *tree = curr;
  } else if (key < parent->key) {
    parent->left = curr;
  } else {
    parent->right = curr;
  }

  while (!s.empty()) {
    curr = s.top();
    s.pop();

    curr->height = max(height(curr->left), height(curr->right)) + 1;

    // Check Balance Factor(curr->right) << endl;
    if ((height(curr->left) + 1 < height(curr->right)) ||
        (height(curr->right) + 1 < height(curr->left))) {
      check = curr;

      if (s.empty()) {
        parent = NULL;
      } else {
        parent = s.top();
      }

      break;
    }
  }

  if (check == NULL) {
    return;
  }

  // Left Case
  if (height(check->left) > height(check->right) + 1) {
    // Left-Left Case
    if (height(check->left->left) > height(check->left->right)) {
      s.push(check->left->left);
      s.push(check->left);
      s.push(check);
      avl_rotate_right(tree, check, parent);
    }
    // Left-Right Case
    else {
      s.push(check->left->right);
      s.push(check->left);
      s.push(check);
      avl_rotate_left(tree, check->left, check);
      avl_rotate_right(tree, check, parent);
    }
  }
  // Right Case
  else {
    // Right-Right Case
    if (height(check->right->left) < height(check->right->right)) {
      s.push(check->right->right);
      s.push(check->right);
      s.push(check);
      avl_rotate_left(tree, check, parent);
    }
    // Right-Left Case
    else {
      s.push(check->right->left);
      s.push(check->right);
      s.push(check);
      avl_rotate_right(tree, check->right, check);
      avl_rotate_left(tree, check, parent);
    }
  }

  while (!s.empty()) {
    curr = s.top();
    s.pop();
    curr->height = max(height(curr->left), height(curr->right)) + 1;
  }
}

void avl_erase(avl_node **tree, int key) {
  avl_node *parent = NULL;
  avl_node *curr = *tree;
  avl_node *check = NULL;
  stack<avl_node *> s;

  while (curr != NULL && curr->key != key) {
    parent = curr;
    s.push(curr);

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
    avl_node *tmp = parent;
    s.push(curr);

    if (height(curr->left) <= height(curr->right)) {
      curr = curr->right;
      if (curr->left != NULL) {
        s.push(curr);
      }

      while (curr->left != NULL) {
        tmp = curr;
        curr = curr->left;
        if (curr->left != NULL) {
          s.push(curr);
        }
      }
    } else {
      curr = curr->left;
      s.push(curr);

      while (curr->right != NULL) {
        tmp = curr;
        curr = curr->right;
        if (curr->right != NULL) {
          s.push(curr);
        }
      }
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

  while (!s.empty()) {
    curr = s.top();
    s.pop();

    curr->height = max(height(curr->left), height(curr->right)) + 1;

    // Check Balance Factor(curr->right) << endl;
    if ((height(curr->left) + 1 < height(curr->right)) ||
        (height(curr->right) + 1 < height(curr->left))) {
      check = curr;

      if (s.empty()) {
        parent = NULL;
      } else {
        parent = s.top();
      }

      break;
    }
  }

  if (check == NULL) {
    return;
  }

  // Left Case
  if (height(check->left) > height(check->right) + 1) {
    // Left-Left Case
    if (height(check->left->left) > height(check->left->right)) {
      s.push(check->left->left);
      s.push(check->left);
      s.push(check);
      avl_rotate_right(tree, check, parent);
    }
    // Left-Right Case
    else {
      s.push(check->left->right);
      s.push(check->left);
      s.push(check);
      avl_rotate_left(tree, check->left, check);
      avl_rotate_right(tree, check, parent);
    }
  }
  // Right Case
  else {
    // Right-Right Case
    if (height(check->right->left) < height(check->right->right)) {
      s.push(check->right->right);
      s.push(check->right);
      s.push(check);
      avl_rotate_left(tree, check, parent);
    }
    // Right-Left Case
    else {
      s.push(check->right->left);
      s.push(check->right);
      s.push(check);
      avl_rotate_right(tree, check->right, check);
      avl_rotate_left(tree, check, parent);
    }
  }

  while (!s.empty()) {
    curr = s.top();
    s.pop();
    curr->height = max(height(curr->left), height(curr->right)) + 1;
  }
}

int avl_search(avl_node *tree, int key) {
  if (tree != NULL) {
    if (tree->key == key) {
      return tree->value;
    } else if (key < tree->key) {
      return avl_search(tree->left, key);
    } else {
      return avl_search(tree->right, key);
    }
  } else {
    // Not Found
    return -1;
  }
}

void avl_inorder(avl_node *tree) {
  if (tree != NULL) {
    avl_inorder(tree->left);
    printf("%d ", tree->key);
    avl_inorder(tree->right);
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

void avl_print(avl_node *tree, Path *prev, bool isRight) {
  if (tree == NULL) {
    return;
  }

  string prev_str = "    ";
  Path *p = new Path(prev, prev_str);

  avl_print(tree->right, p, true);

  if (!prev) {
    p->str = "---";
  } else if (isRight) {
    p->str = ".---";
    prev->str = "   ";
    prev_str = "   |";
  } else {
    p->str = "\'---";
    prev->str = "   ";
  }

  showPath(p);
  cout << tree->key << endl;

  if (prev) {
    prev->str = prev_str;
  }
  p->str = "   |";

  avl_print(tree->left, p, false);
}