#pragma once
#include "IGpio.h"
#include <unordered_map>
#include <mutex>

class VirtualGPIO : public IGpio {
public:
    VirtualGPIO() = default;

    // Override IGpio methods correctly
    void write(int pin, bool value) override {
        std::lock_guard<std::mutex> lock(mutex_);
        pins_[pin] = value;
    }

    bool read(int pin) override {
        std::lock_guard<std::mutex> lock(mutex_);
        if (pins_.find(pin) != pins_.end())
            return pins_[pin];
        return false;
    }

private:
    std::unordered_map<int, bool> pins_;
    std::mutex mutex_;
};