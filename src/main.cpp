#include <Windows.h>
#include <iostream>
#include "Windows/Keyboard/keyboard_track.h"

int main() {
    keyboard_track::KeyboardTracker tracker(50, [](int vk, bool down) {
        std::cout << "VK " << vk << (down ? " pressed\n" : " released\n");
    });

    std::cout << "Tracking keyboard. Press Enter to stop.\n";
    std::cin.get();

    return 0;
}