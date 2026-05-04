//
// Created by Rija on 4/20/2026.
//
/*
 * Stack - LIFO order of insertion and deletion
 * Most recently inserted element is removed first
 * The first inserted element will be removed last
 * Insert and delete elements at only one end of the stack - top
 *
 */

#pragma once
#include <iostream>
template<typename T>

class Stack {
private:
    T* arr_;
    size_t next_idx_;

public:
    // Default constructor with initial capacity of 4
    Stack() {
        arr_ = new T[4];
        next_idx_ = 0;
    }

    // Constructor with user-defined initial capacity
    Stack (const size_t sz) {
        arr_ = new T[sz];
        next_idx_ = 0;
    }

    size_t size() const {
        return next_idx_;
    }

    bool empty() const {
        return next_idx_ == 0;
    }

    // Push - new elements can only be inserted at the top of the stack
    void push(const T data) {
        if (next_idx_ == 4) {
            T* temp = new T[2 * 4];

            for (int i = 0; i < 4; i++) {
                temp[i] = arr_[i];
            }

            delete[] arr_;
            arr_ = temp;
        }

        arr_[next_idx_] = data;
        next_idx_++;
    }

    // Pop - only the top element of the stack can be deleted
    void pop() {
        if (next_idx_ == 0) {
            return;
        }

        next_idx_--;
    }

    // Only the top element can be accessed in a stack
    T top() const {
        return arr_[next_idx_ - 1];
    }
};
