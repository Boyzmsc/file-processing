#include "bstree.cpp"

int main()
{
    const int testcases[] = {40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 25, 49};

    Bstree<int> bst;

    for (const int *it = testcases; it < testcases + sizeof(testcases) / sizeof(int); ++it)
    {
        bst.bst_insert(*it, 0);
        bst.bst_show();
        printf("\n");
    }
    for (const int *it = testcases; it < testcases + sizeof(testcases) / sizeof(int); ++it)
    {
        bst.bst_remove(*it);
        bst.bst_show();
        printf("\n");
    }
    for (const int *it = testcases; it < testcases + sizeof(testcases) / sizeof(int); ++it)
    {
        bst.bst_insert(*it, 0);
        bst.bst_show();
        printf("\n");
    }
    for (const int *it = testcases + sizeof(testcases) / sizeof(int) - 1; testcases <= it; --it)
    {
        bst.bst_remove(*it);
        bst.bst_show();
        printf("\n");
    }
}