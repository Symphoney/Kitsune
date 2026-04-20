//
// Created by Rija on 4/14/2026.
//

#include "Tree.h"
#include <iostream>

int main() {

    TreeNode<int>* root = new TreeNode<int>(1);
    TreeNode<int>* node1 = new TreeNode<int>(2);
    TreeNode<int>* node2 = new TreeNode<int>(3);
    TreeNode<int>* node3 = new TreeNode<int>(4);

    root->children.push_back(node1); // Add node1 as a child of root
    root->children.push_back(node2); // Add node2 as a child of root
    node1->children.push_back(node3); // Add node3 as a child of node1

    root->insert(5);

    std::cout << "Height of tree: " << root->height() << '\n';

    std::cout << "Nodes at depth 1: ";
    root->print_at_depth(1);
    std::cout << '\n';
    std::cout << "Nodes at depth 2: ";
    root->print_at_depth(2);
    std::cout << '\n'; // Should print 4 and 5
    std::cout << "Root: " << root->data() << '\n';
    std::cout << "Number of children of root: " << root->size() << '\n';

    delete root;

    return 0;
}