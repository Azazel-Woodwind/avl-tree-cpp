#include <iostream>
using std::cout;

#include "tree.h"
#include "treemap.h"

int main() {
    TreeMap<int, int> treeMap;
    treeMap.insert(1, 2);
    treeMap.insert(2, 3);
    treeMap.insert(3, 4);
    treeMap.insert(4, 5);

    cout << "TreeMap: ";
    treeMap.write(cout);
    cout << "\n";

    cout << "TreeMap[1]: " << treeMap.find(1)->v << "\n";
    cout << "TreeMap[2]: " << treeMap.find(2)->v << "\n";
    cout << "TreeMap[3]: " << treeMap.find(3)->v << "\n";
    cout << "TreeMap[4]: " << treeMap.find(4)->v << "\n";

    BinarySearchTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);

    cout << "Tree: ";
    tree.write(cout);
    cout << "\n";

    cout << "Tree[1]: " << tree.find(1)->data << "\n";
    cout << "Tree[2]: " << tree.find(2)->data << "\n";
    cout << "Tree[3]: " << tree.find(3)->data << "\n";
    cout << "Tree[4]: " << tree.find(4)->data << "\n";

    return 0;
}