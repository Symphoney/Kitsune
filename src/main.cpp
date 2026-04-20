//
// Created by Rija on 4/14/2026.
//

#include <iostream>
#include <array>
#include "Queue.h"

int main() {
        Queue<int> q;

        q.enqueue(1);
        q.enqueue(2);
        q.enqueue(3);
        q.enqueue(4);

        std::cout << "Size: " << q.size() << '\n';

        q.dequeue();
        q.dequeue();

        std::cout << "Size: " << q.size() << '\n';

    return 0;
}