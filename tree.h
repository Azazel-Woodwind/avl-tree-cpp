#ifndef TREE_H
#define TREE_H

#include "treenode.h"

// TODO your code goes here:

template<typename T>
class BinarySearchTree {
    private:
        unique_ptr<TreeNode<T>> root;

        void copy(TreeNode<T>* currentNode, TreeNode<T>* otherNode) {
            if (otherNode -> leftChild) {
                currentNode -> setLeftChild(new TreeNode<T>(otherNode -> leftChild -> data));
                copy(currentNode -> leftChild.get(), otherNode -> leftChild.get());
            }
            if (otherNode -> rightChild) {
                currentNode -> setRightChild(new TreeNode<T>(otherNode -> rightChild -> data));
                copy(currentNode -> rightChild.get(), otherNode -> rightChild.get());
            }
        }

        void deleteTree(unique_ptr<TreeNode<T>>& currentNode) {
            if (!currentNode) {
                return;
            }

            deleteTree(currentNode -> leftChild);
            deleteTree(currentNode -> rightChild);
            currentNode.reset();
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
                return insertHelper(data, (currentNode -> leftChild).get());
            }
            else if (currentNode -> data < data) {
                if (!currentNode -> rightChild) {
                    TreeNode<T>* child = new TreeNode<T>(data);
                    currentNode -> setRightChild(child);
                    return child;
                }
                return insertHelper(data, (currentNode -> rightChild).get());
            }
            else {
                return currentNode;
            }

            return nullptr;
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

    public:
        BinarySearchTree() {}

        BinarySearchTree(const BinarySearchTree<T>& other) {
            root.reset(new TreeNode<T>(other.root -> data));
            copy(root.get(), other.root.get());
        }

        BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other) {
            deleteTree(root);
            root.reset(new TreeNode<T>(other.root -> data));
            copy(root.get(), other.root.get());
            return *this;
        }

        int maxDepth() {
            return root -> maxDepth();
        }
    

        TreeNodeIterator<T> begin() {
            TreeNode<T>* leftMost = root.get();
            while (leftMost && leftMost -> leftChild) {
                leftMost = leftMost -> leftChild.get();
            }
            return TreeNodeIterator<T>(leftMost);
        }

        TreeNodeIterator<T> end() {
            return TreeNodeIterator<T>(nullptr);;
        }

        void write(ostream& os) const {
            root -> write(os);
        }

        TreeNode<T>* insert(T data) {
            TreeNode<T>* res = insertHelper(data, root.get());
            if (!res || !res -> parent || !((res -> parent) -> parent)) {
                return res;
            }
            int balanceFactor = res -> parent -> parent -> balanceFactor();
            if (!(balanceFactor == 2 || balanceFactor == -2)) {
                return res;
            }
            if (res -> parent -> data < res -> data && res -> parent -> parent -> data < res -> parent -> data) {
                if (res -> parent -> parent == root.get()) {
                    root.release();
                    root.reset(res -> parent);
                }
                res -> parent -> parent -> rotateLeft();
            }
            else if (res -> data < res -> parent -> data && res -> parent -> data < res -> parent -> parent -> data) {
                if (res -> parent -> parent == root.get()) {
                    root.release();
                    root.reset(res -> parent);
                }
                res -> parent -> parent -> rotateRight();
            }
            else if (res -> parent -> data < res -> data && res -> parent -> data < res -> parent -> parent -> data) {
                if (res -> parent -> parent == root.get()) {
                    root.release();
                    root.reset(res);
                }
                res -> parent -> rotateLeft();
                res -> parent -> rotateRight();
            }
            else {
                if (res -> parent -> parent == root.get()) {
                    root.release();
                    root.reset(res);
                }
                res -> parent -> rotateRight();
                res -> parent -> rotateLeft();
            }
            return res;
        }

        TreeNode<T>* find(T data) {
            return findHelper(data, root.get());
        }

};


// do not edit below this line

#endif
