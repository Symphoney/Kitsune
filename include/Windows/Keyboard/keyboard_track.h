#pragma once

#include <Windows.h>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <vector>
#include <array>
#include <chrono>

namespace keyboard_track {

class KeyboardTracker {
public:
    using Callback = std::function<void(int vk, bool down)>;

    KeyboardTracker() = default;

    explicit KeyboardTracker(int intervalMs, Callback cb = nullptr, const std::vector<int>& keys = {}) {
        start(intervalMs, std::move(cb), keys);
    }

    ~KeyboardTracker() {
        stop();
    }

    // Start polling. If `keys` is empty, monitor all VK codes (0-255).
    void start(int intervalMs = 50, Callback cb = nullptr, const std::vector<int>& keys = {}) {
        if (running_.exchange(true)) return;
        {
            std::lock_guard<std::mutex> lg(mtx_);
            cb_ = std::move(cb);
            keys_ = keys; // empty => monitor all
        }
        prev_.fill(0);
        intervalMs_ = intervalMs;
        worker_ = std::thread([this]{ run(); });
    }

    void stop() {
        if (!running_.exchange(false)) return;
        if (worker_.joinable()) worker_.join();
    }

    bool isRunning() const { return running_.load(); }

private:
    void run() {
        while (running_.load()) {
            Callback cbCopy;
            std::vector<int> keysCopy;
            {
                std::lock_guard<std::mutex> lg(mtx_);
                cbCopy = cb_;
                keysCopy = keys_;
            }

            if (cbCopy) {
                if (keysCopy.empty()) {
                    for (int vk = 0; vk < 256; ++vk) checkKey(vk, cbCopy);
                } else {
                    for (int vk : keysCopy) {
                        if (vk >= 0 && vk < 256) checkKey(vk, cbCopy);
                    }
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs_));
        }
    }

    void checkKey(int vk, const Callback& cb) {
        SHORT state = GetAsyncKeyState(vk);
        bool down = (state & 0x8000) != 0;
        bool wasDown = prev_[vk] != 0;
        if (down != wasDown) {
            prev_[vk] = down ? 1 : 0;
            cb(vk, down);
        } else {
            prev_[vk] = down ? 1 : 0;
        }
    }

    std::atomic_bool running_{false};
    std::thread worker_;
    mutable std::mutex mtx_;
    std::vector<int> keys_;            // empty => monitor all
    std::array<char, 256> prev_;       // previous down state per VK
    Callback cb_{};
    int intervalMs_{50};
};

}

/*
*#include <Windows.h>
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
*/
