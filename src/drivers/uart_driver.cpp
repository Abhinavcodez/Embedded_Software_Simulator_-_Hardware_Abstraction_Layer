#include "drivers/uart_driver.h"
#include <fstream>
#include <iostream>

static uart_callback_t uart_rx_cb = nullptr;
static std::fstream uart_stream;

static void uart_init(const std::string &dev_name) {
    uart_stream.open(dev_name, std::ios::in | std::ios::out | std::ios::app);
    if (!uart_stream.is_open())
        std::cerr << "[UART] Failed to open virtual UART file: " << dev_name << "\n";
    else
        std::cout << "[UART] Initialized on " << dev_name << "\n";
}

static void uart_write(uint8_t data) {
    if (uart_stream.is_open()) {
        uart_stream.put(static_cast<char>(data));
        uart_stream.flush();
    }
}

static uint8_t uart_read() {
    if (!uart_stream.is_open() || uart_stream.eof()) return 0;
    return static_cast<uint8_t>(uart_stream.get());
}

static void uart_set_callback(uart_callback_t cb) { uart_rx_cb = cb; }

static uart_driver_t virtual_uart = {
    .init = uart_init,
    .write = uart_write,
    .read = uart_read,
    .set_callback = uart_set_callback,
};

uart_driver_t *get_virtual_uart() { return &virtual_uart; }