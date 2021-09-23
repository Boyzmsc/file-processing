#include <bits/stdc++.h>

template <typename T> struct Node{
    T key;
    T value;
    Node<T> *left;
    Node<T> *right;
};

template <typename T> class Bstree{
    private:
        Node<T> *root;

        Node<T> *insert(Node<T> *tree, T key, T value){
            if(tree == nullptr){
                tree = new Node<T>;
                tree->key = key;
                tree->value = value;
                tree->left = nullptr;
                tree->right = nullptr;
            }

            if(tree->key == key){
                return tree;
            }else if(tree->key > key){
                tree->left = insert(tree->left, key, value);
            }else {
                tree->right = insert(tree->right, key, value);
            }

            return tree;
        }

        Node<T> *find_max(Node<T> *tree){
            while(tree->right != nullptr){
                tree = tree->right;
            }
            return tree;
        }

        Node<T> *remove(Node<T> *tree, T key){
            if (tree != nullptr){
                if (tree->key > key){
                    tree->left = remove(tree->left, key);
                }else if(tree->key < key){
                    tree->right = remove(tree->right, key);
                }else{
                    if (tree->left != nullptr && tree->right != nullptr){
                        // While both children exist
                        Node<T> *tmp = find_max(tree->left);
                        tree->key = tmp->key;
                        tree->value = tmp->value;
                        tree->left = remove(tree->left, tmp->key);
                    }else if(tree->left == nullptr && tree->right == nullptr){
                        // While both children not exist
                        delete tree;
                        tree = nullptr;
                    }
                    else{
                        // While only one child exists
                        if (tree->left == nullptr){
                            tree = tree->right;
                        }else if(tree->right == nullptr){
                            tree = tree->left;
                        }
                    }
                } 
            }else{
                printf("Not Found %d!\n", key);
                return tree;
            }
            return tree;
        }
        
        void bst_inorder(Node<T> *tree){
            if (tree != nullptr){
                bst_inorder(tree->left);
                printf("%d ", tree->key);
                bst_inorder(tree->right);
            }
        };

    public:
        Bstree(){
            root = nullptr;
        };

        void bst_insert(T key, T value){
            root = insert(root, key, value);
        };
        void bst_remove(T key){
            root = remove(root, key);
        };
        void bst_show(){
            bst_inorder(root);
        };
};