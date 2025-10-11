#pragma once
#include "IUart.h"
#include <vector>
#include <queue>
#include <mutex>

class VirtualUART : public IUart {
public:
    VirtualUART() = default;

    // Override IUart methods correctly
    void send(const char* data, int length) override {
        std::lock_guard<std::mutex> lock(mutex_);
        for (int i = 0; i < length; ++i) {
            buffer_.push(data[i]);
        }
    }

    int receive(char* buffer, int length) override {
        std::lock_guard<std::mutex> lock(mutex_);
        int i = 0;
        while (!buffer_.empty() && i < length) {
            buffer[i++] = buffer_.front();
            buffer_.pop();
        }
        return i;
    }

private:
    std::queue<char> buffer_;
    std::mutex mutex_;
};