#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::ostream;

#include <memory>
using std::unique_ptr;

#include <utility>
using std::pair;

// TODO your code for the TreeNode class goes here:

template<typename T>
class TreeNode {
    public:
        T data;
        unique_ptr<TreeNode<T>> leftChild;
        unique_ptr<TreeNode<T>> rightChild;
        TreeNode<T>* parent;

        TreeNode(T dataIn) : data(dataIn), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {}

        void setLeftChild(TreeNode<T>* child) {
            leftChild.reset(child);
            child -> parent = this;
        }

        void setRightChild(TreeNode<T>* child) {
            rightChild.reset(child);
            child -> parent = this;
        }

        void write(ostream& os) const {
            if (leftChild) {
                leftChild -> write(os);
            }
            os << " " << data << " ";
            if (rightChild) {
                rightChild -> write(os);
            }
        }

        int maxDepth() {
            int leftDepth = 0, rightDepth = 0;
            if (leftChild) {
                leftDepth = leftChild -> maxDepth();
            }
            if (rightChild) {
                rightDepth = rightChild -> maxDepth()
            }
            return 1 + max(leftDepth, rightDepth);
        }
};

template<typename T>
class TreeNodeIterator {
    TreeNode<T>* current;
    public:
        TreeNodeIterator(TreeNode<T>* currentIn) : current(currentIn) {}

        TreeNode<T>& operator*() {
            return *current;
        }

        bool operator==(const TreeNodeIterator<T>& other) {
            return current == other.current;
        }

        bool operator!=(const TreeNodeIterator<T>& other) {
            return !(*this == other);
        }

        void operator++() {
            if ((!current -> leftChild) && !(current -> rightChild)) {
                TreeNode<T>* parent = current -> parent;
                while (parent && parent -> rightChild == current) {
                    current = parent;
                    parent = current -> parent;
                }
                current = parent;
            }
            else {
                current = current -> rightChuld;
                while (current -> leftChild) {
                    current = current -> leftChild;
                }
            }
        }
};

// do not edit below this line

#endif
