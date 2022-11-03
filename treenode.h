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

#include <algorithm>
using std::max;

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
            leftChild.release();
            leftChild.reset(child);
            child -> parent = this;
        }

        void setRightChild(TreeNode<T>* child) {
            rightChild.release();
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
                rightDepth = rightChild -> maxDepth();
            }
            return 1 + max(leftDepth, rightDepth);
        }

        int balanceFactor() {
            int leftDepth = leftChild ? leftChild -> maxDepth() : 0;
            int rightDepth = rightChild ? rightChild -> maxDepth() : 0;
            return leftDepth - rightDepth;
        }

        void rotateLeft() {
            if (parent) {
                if (parent -> data < data) {
                    parent -> setRightChild(rightChild.get());
                }
                else {
                    parent -> setLeftChild(rightChild.get());
                }
            }
            rightChild -> setLeftChild(this);
            rightChild.release();
        }

        void rotateRight() {
            leftChild -> parent = parent;

            if (parent) {
                if (parent -> data < data) {
                    parent -> setRightChild(leftChild.get());
                }
                else {
                    parent -> setLeftChild(leftChild.get());
                }
            }

            leftChild -> setRightChild(this);
            leftChild.release();
        }
};

template<typename T>
class TreeNodeIterator {
    TreeNode<T>* current;
    public:
        TreeNodeIterator(TreeNode<T>* currentIn) : current(currentIn) {}

        T& operator*() {
            return current -> data;
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
                while (parent && parent -> rightChild.get() == current) {
                    current = parent;
                    parent = current -> parent;
                }
                current = parent;
            }
            else {
                current = current -> rightChild.get();
                while (current -> leftChild) {
                    current = current -> leftChild.get();
                }
            }
        }
};

// do not edit below this line

#endif
