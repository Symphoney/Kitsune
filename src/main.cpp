//
// Created by Rija on 4/14/2026.
//

#include <iostream>
#include <array>
#include "Queue.h"

int main() {
        Queue<int> q; // Initialize queue of ints

        // Enqueue some elements
        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        q.enqueue(4);

        // Print size of the queue
        std::cout << "Size: " << q.size() << '\n';

        // Dequeue two elements
        q.dequeue();
        q.dequeue();

        // Print size of the queue after dequeuing
        std::cout << "Size: " << q.size() << '\n';

    return 0;
}