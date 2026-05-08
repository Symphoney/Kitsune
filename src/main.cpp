#include <Windows.h>
#include <iostream>
#include "mouse_track.h"

int main() {
    mouse_track::MouseTracker tracker(100, [](const POINT& p) {
        std::cout << "Mouse moved to: (" << p.x << ", " << p.y << ")\n";
    }, 10);

    std::cout << "Tracking mouse. Hit Enter to make it stop.\n";
    std::cin.get(); // waits for user input

    return 0;
}