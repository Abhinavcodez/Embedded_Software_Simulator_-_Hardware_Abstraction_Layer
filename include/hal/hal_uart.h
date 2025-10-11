#pragma once
#include <cstdint>
#include <cstddef>
#include <functional>

using uart_callback_t = std::function<void(uint8_t)>;

class IUart {
public:
    virtual ~IUart() = default;
    virtual bool init() = 0;
    virtual void write(const uint8_t* data, size_t len) = 0;
    // non-blocking read: returns true if a byte was available
    virtual bool read(uint8_t &out) = 0;
    virtual void set_callback(uart_callback_t cb) = 0;
};