//
// Created by Rija on 4/20/2026.
//
/*
 * Tree Data Structure - Collection of elements aka nodes
 * connected to each other via edges. There exists ONE path between 2 nodes
 */

#include <vector>
#include <iostream>
#include <memory>

/*
 * Memory leak - new and delete. If treenode doesn't recursively destroy owned children,
 * the other new nodes leak. smart pointers automate ownership and deletion.
 *
 * std::unique_ptr<T>: single owner; automatically deletes when owner is destroyed.
 * - use for parent-owning-children trees
 *
 * std::shared_ptr<T>: reference-counted shared ownership
 * - use when multiple owners must share ownership of an object
 *
 * std::weak_ptr<T>: non-owning observer to break cycles with shared_ptr
 * - use to prevent memory leaks in cyclic references
 *
 * make children store std::unique_ptr<TreeNode<T>> so the tree frees all nodes automatically when root
 * is destroyed
 * - TreeNode stores children in std::vector<std::unique_ptr<TreeNode<T>>> children;
 * - insert adds a new child to the node
 * - height and print_at_depth are recursive implementation
 */


template <typename T>

struct TreeNode {
    T value;
    std::vector<std::unique_ptr<TreeNode<T>>> children;

    explicit TreeNode(T v) : value(v) {}

    T data() const { return value; }

    std::size_t size() const { return children.size(); }

    int height() const {
        int h = 0;
        for (const auto &c : children) {
            int ch = c ? c->height() : 0;
            if (ch > h) h = ch;
        }

        return 1 + h;
    }

    void print_at_depth(int d) const {
        if (d < 0) return;
        if (d == 0) {
            std::cout << value << ' ';
            return;
        }
        for (const auto &c : children) {
            if (c) c->print_at_depth(d - 1);
        }
    }

    void insert(const T &v) {
        children.push_back(std::make_unique<TreeNode<T>>(v));
    }
};

/*

// Helper functions to demonstrate tree traversal methods
void print(TreeNode<int>* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->data() << '\n';

    for (int i = 0; i < root->size(); i++) {
        print(root->children[i]);
    }
}

// Preorder traversal: Visit root, then recursively visit each child
void preorder(TreeNode<int>* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->data() << '\n';

    for (int i = 0; i < root->size(); i++) {
        preorder(root->children[i]);
    }
}

// Postorder traversal: Recursively visit each child, then visit root
void postorder(TreeNode<int>* root) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < root->size(); i++) {
        postorder(root->children[i]);
    }

    std::cout << root->data() << ' ';
}
*/