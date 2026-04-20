//
// Created by Rija on 4/20/2026.
//
/*
 * Tree Data Structure - Collection of elements aka nodes
 * connected to each other via edges. There exists ONE path between 2 nodes
 */

#include <vector>
#include <iostream>

template <typename T>
class TreeNode {
private:
    T data_;

public:
    // Vector to store child nodes of the current node
    std::vector<TreeNode*> children;

    // Constructor to initialize data and create an empty vector for child nodes
    explicit TreeNode(T data) : data_(data) {}

    // Destructor to free memory allocated for child nodes
    ~TreeNode() {
        for (int i = 0; i < children.size(); ++i) {
            delete children[i];
        }
    }

    // Insert new child node
    void insert(const T data) {
        if (children.empty()) {
            children.push_back(new TreeNode<T>(data));
            return;
        }

        size_t min_idx = 0;
        size_t min_size = children[0]->children.size();
        for (size_t i = 1; i < children.size(); ++i) {
            if (children[i]->children.size() < min_size) {
                min_size = children[i]->children.size();
                min_idx = i;
            }
        }
        children[min_idx]->children.push_back(new TreeNode<T>(data));
    }

    // Get data of the current node
    T data() const {
        return data_;
    }

    // Get number of child nodes of the current node
    size_t size() const {
        return children.size();
    }

    // Overload [] operator to access child nodes by index
    TreeNode<T>* operator[](const int idx) {
        return children[idx];
    }

    // Count total number of nodes in the tree rooted at the current node
    size_t count_nodes() const {
        size_t count = 1;
        for (size_t i = 0; i < children.size(); ++i) {
            count += children[i]->count_nodes();
        }
        return count;
    }

    // Get height of the tree rooted at the current node
    size_t height() const {
        size_t max_height = 0;
        for (size_t i = 0; i < children.size(); ++i) {
            size_t child_height = children[i]->height();
            if (child_height > max_height) max_height = child_height;
        }
        return max_height + 1;
    }

    // Print nodes at a given depth and return the count of nodes printed
    size_t print_at_depth(const int depth) const {
        if (depth == 0) {
            std::cout << data_ << " ";
            return 1;
        }
        size_t count = 0;
        for (size_t i = 0; i < children.size(); ++i) {
            count += children[i]->print_at_depth(depth - 1);
        }
        return count;
    }
};

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