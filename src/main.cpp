//
// Created by Rija on 4/14/2026.
//

#include "Tree.h"
#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<TreeNode<int>> root  = std::make_unique<TreeNode<int>>(1);

    root->children.push_back(std::make_unique<TreeNode<int>>(2));
    root->children.push_back(std::make_unique<TreeNode<int>>(3));
    root->children[0]->children.push_back(std::make_unique<TreeNode<int>>(4));

    root->insert(5);

    std::cout << "Height of tree: " << root->height() << '\n';

    std::cout << "Nodes at depth 0: ";
    root->print_at_depth(0);
    std::cout << "\nNodes at depth 1: ";
    root->print_at_depth(1);
    std::cout << "\nNodes at depth 2: ";
    root->print_at_depth(2);

    std::cout << "\n\nRoot value: " << root->data() << '\n';
    std::cout << "Number of children of root: " << root->size() << '\n';


    return 0;
}