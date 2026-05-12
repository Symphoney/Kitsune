//
// Created by Rija on 5/7/2026.
//

#include <Windows.h>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <iostream>

// MouseTracker class tracks mouse position at regular intervals and invokes a callback when the position changes
namespace mouse_track {
    class MouseTracker {
    public:
        // Callback type that takes a POINT structure representing the mouse position
        using Callback = std::function<void(const POINT&)>;

        MouseTracker() = default;
        // Constructor that starts tracking immediately with specified interval, callback, and threshold
        explicit MouseTracker(int intervalMs, Callback cb = nullptr, int threshold = 0) {
            start(intervalMs, std::move(cb), threshold);
        }

        ~MouseTracker() {
            stop();
        }

        // Start tracking mouse position with specified interval, callback, and threshold
        void start(int intervalMs = 50, Callback cb = nullptr, int threshold = 0) {
            if (running_.exchange(true)) return;
            intervalMs_ = intervalMs;
            cb_ = std::move(cb);
            threshold_ = threshold;
            worker_ = std::thread([this]{run();});
        }

        void stop() {
            if (!running_.exchange(false)) return;
            if (worker_.joinable()) worker_.join();
        }

        bool isRunning() const { return running_.load(); }

        POINT getPosition() const {
            std::lock_guard<std::mutex> lg(mtx_);
            return lastPos_;
        }

    private:
        // Worker thread function that continuously checks the mouse position and invokes the callback if it changes beyond the threshold
        void run() {
            POINT p{0,0};
            while (running_.load()) {
                if (GetCursorPos(&p)) {
                    bool changed = false;
                    {
                        std::lock_guard<std::mutex> lg(mtx_);
                        if (std::abs(p.x - lastPos_.x) > threshold_ || std::abs(p.y - lastPos_.y) > threshold_) {
                            lastPos_ = p;
                            changed = true;
                        }
                    }
                    if (changed && cb_) cb_(p);
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs_));
            }
        }
        // Flag indicate if tracker is running
        std::atomic_bool running_{false};
        // Worker thread that checks mouse position
        std::thread worker_;
        // Mutex to protect access to lastPos_
        mutable std::mutex mtx_;
        // Last known mouse position
        POINT lastPos_{0,0};
        // Callback function to invoke when mouse position changes
        Callback cb_{};
        // Interval in milliseconds between position checks
        int intervalMs_{50};
        // Threshold in pixels to determine if position change is significant enough to invoke callback
        int threshold_{0};
    };
}


/*
int main() {
    POINT p;

    for (int i = 0; i < 30; i++) {
        if (GetCursorPos(&p)) {
            std::cout << "Mouse position: (" << p.x << ", " << p.y << ")\n";
        }

        Sleep(1000);
    }

    return 0;
}
*/

/*
*#include <Windows.h>
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