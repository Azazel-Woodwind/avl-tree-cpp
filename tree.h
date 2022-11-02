#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:

template<typename T>
class BinarySearchTree {
    unique_ptr<TreeNode<T>> root;

    public:
        BinarySearchTree() {}

        BinarySearchTree(const BinarySearchTree<T>& other) {
            root.reset(new TreeNode<T>(other.root -> data));
            copy(root.get(), other.root.get());
        }

        void copy(TreeNode<T>* currentNode, TreeNode<T>* otherNode) {
            if (otherNode -> leftChild) {
                currentNode -> setLeftChild(new TreeNode<T>(otherNode -> leftChild -> data));
                copy(currentNode -> leftChild, otherNode -> leftChild);
            }
            if (otherNode -> rightChild) {
                currentNode -> setRightChild(new TreeNode<T>(otherNode -> rightChild -> data));
                copy(currentNode -> rightChild, otherNode -> rightChild);
            }
        }

        BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other) {
            deleteTree(root);
            root.reset(new TreeNode<T>(other.root -> data));
            copy(root.get(), other.root.get());
            return *this;
        }

        void deleteTree(unique_ptr<TreeNode<T>> currentNode) {
            if (!currentNode) {
                return;
            }

            deleteTree(currentNode -> leftChild);
            deleteTree(currentNode -> rightChild);
            currentNode.reset();
        }

        void write(ostream& os) const {
            root -> write(os);
        }

        TreeNode<T>* insert(T data) {
            return insertHelper(data, root.get());
        }

        TreeNode<T>* insertHelper(T data, TreeNode<T>* currentNode) {
            if (!currentNode) {
                TreeNode<T>* newRoot = new TreeNode<T>(data);
                root.reset(newRoot);
                return newRoot;
            }

            if (data < currentNode -> data) {
                if (!currentNode -> leftChild) {
                    TreeNode<T>* child = new TreeNode<T>(data);
                    currentNode -> setLeftChild(child);
                    return child;
                }
                insertHelper(data, (currentNode -> leftChild).get());
            }
            else if (currentNode -> data < data) {
                if (!currentNode -> rightChild) {
                    TreeNode<T>* child = new TreeNode<T>(data);
                    currentNode -> setRightChild(child);
                    return child;
                }
                insertHelper(data, (currentNode -> rightChild).get());
            }
            else {
                return currentNode;
            }

            return nullptr;
        }

        TreeNode<T>* find(T data) {
            return findHelper(data, root.get());
        }

        TreeNode<T>* findHelper(T data, TreeNode<T>* currentNode) {
            if (!currentNode) {
                return nullptr;
            }

            if (data < currentNode -> data) {
                return findHelper(data, (currentNode -> leftChild).get());
            }
            else if (currentNode -> data < data) {
                return findHelper(data, (currentNode -> rightChild).get());
            }
            else {
                return currentNode;
            }
        }
};


// do not edit below this line

#endif
