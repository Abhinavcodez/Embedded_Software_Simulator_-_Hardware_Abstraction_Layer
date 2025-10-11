#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

namespace RTOS {
    template <typename T>
    class Queue {
    private:
        std::queue<T> q;
        std::mutex mtx;
        std::condition_variable cv;
        size_t max_size;

    public:
        explicit Queue(size_t size = 10) : max_size(size) {}

        bool send(const T &item) {
            std::unique_lock<std::mutex> lock(mtx);
            if (q.size() >= max_size)
                return false;
            q.push(item);
            cv.notify_one();
            return true;
        }

        bool receive(T &item, int timeout_ms = -1) {
            std::unique_lock<std::mutex> lock(mtx);
            if (timeout_ms < 0) {
                cv.wait(lock, [this] { return !q.empty(); });
            } else {
                if (!cv.wait_for(lock, std::chrono::milliseconds(timeout_ms),
                                 [this] { return !q.empty(); }))
                    return false; // timeout
            }
            item = q.front();
            q.pop();
            return true;
        }

        size_t size() {
            std::lock_guard<std::mutex> lock(mtx);
            return q.size();
        }
    };
}