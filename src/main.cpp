//
// Created by Rija on 4/14/2026.
//

#include <iostream>
#include <array>
#include "Stack.h"

int main() {

        Stack<int> s;

        s.push(1);
        s.push(2);
        s.push(3);
        s.push(4);

        std::cout << "Top element: " << s.top() << '\n';
        std::cout << "Stack size: " << s.size() << '\n';

        s.pop();
        std::cout << "Top element after pop: " << s.top() << '\n';
        std::cout << "Stack size after pop: " << s.size() << '\n';

    return 0;
}