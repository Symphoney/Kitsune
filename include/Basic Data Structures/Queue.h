//
// Created by Rija on 4/20/2026.
//

/*
 * Queue - container adapter that stores FIFO
 * Elements inserted first should be removed first
 * Insert elements at one end - back_
 * and delete from other end - front_
 */

#pragma once
#include <iostream>

template <typename T>

class Queue {
private:
    T* arr_; // Dynamic array to store queue elements
    size_t capacity_; // Total capacity of the queue
    size_t front_; // Index of front element
    size_t back_; // Index of insertion point = index of back element + 1
    size_t size_; // Current number of elements in the queue

public:
    // Default constructor with initial capacity of 4
    // 4 is chosen as a small initial capacity to demonstrate dynamic resizing
    Queue() : capacity_(4), front_(0), back_(0), size_(0) {
        arr_ = new T[capacity_];
    }

    // Constructor with user-defined initial capacity
    Queue(const size_t sz) : capacity_(sz), front_(0), back_(0), size_(0) {
        arr_ = new T[capacity_];
    }

    // Destructor to free allocated memory
    ~Queue() {
        delete[] arr_;
    }

    // Get the current size of the queue
    size_t size() const {
        return size_;
    }

    // Check if queue is empty
    bool empty() const {
        return size_ == 0;
    }

    // Enqueue - add element to the back of the queue
    void enqueue(const T& data) {
        if (size_ == capacity_) {
            // Resize array when capacity is reached
            T* temp = new T[2 * capacity_];

            // Copy elements to new array in correct order
            for (size_t i = 0; i < size_; i++) {
                temp[i] = arr_[(front_ + i) % capacity_];
            }

            // Free old array and update pointers and capacity
            delete[] arr_;

            // Update arr_ to point to new array, reset front_ and back_, and double capacity
            arr_ = temp;
            front_ = 0;
            back_ = size_;
            capacity_ *= 2;
        }

        // Insert new element at back_ index and update back_ and size_
        arr_[back_] = data;
        // back_ is updated to the next index in a circular manner
        back_ = (back_ + 1) % capacity_;
        // Increment size after successful insertion
        size_++;
    }

    // Dequeue - remove element from the front of the queue
    void dequeue() {
        // Before trying to dequeue, check if queue is empty to avoid overflow
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }

        // Move front_ to the next index in a circular manner and decrement size
        front_ = (front_ + 1) % capacity_;
        size_--;
    }

    // Get the front element of the queue without removing it
    T front() const {
        if (empty()) {
            return T();
        }

        return arr_[front_];
    }

    // Get the back element of the queue without removing it
    T back() const {
        if (empty()) {
            return T();
        }

        return arr_[(back_ + capacity_ - 1) % capacity_];
    }
};
