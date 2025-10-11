#pragma once
#include <mutex>
#include <condition_variable>

namespace RTOS {
    class Semaphore {
    private:
        std::mutex mtx;
        std::condition_variable cv;
        bool available;

    public:
        Semaphore(bool initial = true) : available(initial) {}

        void take() {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return available; });
            available = false;
        }

        void give() {
            {
                std::lock_guard<std::mutex> lock(mtx);
                available = true;
            }
            cv.notify_one();
        }
    };
}