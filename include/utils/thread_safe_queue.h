#pragma once
#include <mutex>
#include <condition_variable>
#include <deque>
#include <chrono>
#include <optional>

template<typename T>
class ThreadSafeQueue {
    std::deque<T> q;
    std::mutex m;
    std::condition_variable cv;
public:
    void push(const T& v) {
        {
            std::lock_guard<std::mutex> lk(m);
            q.push_back(v);
        }
        cv.notify_one();
    }
    // blocking pop
    T pop() {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk, [this]{ return !q.empty(); });
        T v = std::move(q.front()); q.pop_front();
        return v;
    }
    // try pop with timeout
    bool pop_for(T& out, std::chrono::milliseconds ms) {
        std::unique_lock<std::mutex> lk(m);
        if (!cv.wait_for(lk, ms, [this]{ return !q.empty(); })) return false;
        out = std::move(q.front()); q.pop_front(); return true;
    }
    bool try_pop(T& out) {
        std::lock_guard<std::mutex> lk(m);
        if (q.empty()) return false;
        out = std::move(q.front()); q.pop_front(); return true;
    }
    bool empty() {
        std::lock_guard<std::mutex> lk(m);
        return q.empty();
    }
};