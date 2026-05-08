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

namespace mouse_track {
    class MouseTracker {
    public:
        using Callback = std::function<void(const POINT&)>;

        MouseTracker() = default;
        explicit MouseTracker(int intervalMs, Callback cb = nullptr, int threshold = 0) {
            start(intervalMs, std::move(cb), threshold);
        }

        ~MouseTracker() {
            stop();
        }

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

        std::atomic_bool running_{false};
        std::thread worker_;
        mutable std::mutex mtx_;
        POINT lastPos_{0,0};
        Callback cb_{};
        int intervalMs_{50};
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