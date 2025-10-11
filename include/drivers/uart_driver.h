#pragma once
#include <cstdint>
#include <functional>
#include <string>

using uart_callback_t = std::function<void(uint8_t)>;

struct uart_driver_t {
    void (*init)(const std::string &dev_name);
    void (*write)(uint8_t data);
    uint8_t (*read)();
    void (*set_callback)(uart_callback_t cb);
};

// Factory method
uart_driver_t *get_virtual_uart();