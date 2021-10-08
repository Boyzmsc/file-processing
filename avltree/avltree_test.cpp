#include "avltree.cpp"
#include <bits/stdc++.h>

int main() {
  const int testcases[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80,
                           66, 10, 22, 30, 44, 55, 50, 60, 25, 49};

  struct avl_node *tree = NULL;

  for (const int *it = testcases;
       it < testcases + sizeof(testcases) / sizeof(int); ++it) {
    avl_insert(&tree, *it, 0);
    avl_inorder(tree);
    printf("\n");
    if (it == testcases + (sizeof(testcases) / sizeof(int)) - 1) {
      cout << "------------------------------------------------------" << endl;
      avl_print(tree, nullptr, false);
      cout << "------------------------------------------------------" << endl;
    }
  }
  for (const int *it = testcases;
       it < testcases + sizeof(testcases) / sizeof(int); ++it) {
    avl_erase(&tree, *it);
    avl_inorder(tree);
    printf("\n");
  }
  for (const int *it = testcases;
       it < testcases + sizeof(testcases) / sizeof(int); ++it) {
    avl_insert(&tree, *it, 0);
    avl_inorder(tree);
    printf("\n");
    if (it == testcases + (sizeof(testcases) / sizeof(int)) - 1) {
      cout << "------------------------------------------------------" << endl;
      avl_print(tree, nullptr, false);
      cout << "------------------------------------------------------" << endl;
    }
  }
  for (const int *it = testcases + sizeof(testcases) / sizeof(int) - 1;
       testcases <= it; --it) {
    avl_erase(&tree, *it);
    avl_inorder(tree);
    printf("\n");
  }
}
